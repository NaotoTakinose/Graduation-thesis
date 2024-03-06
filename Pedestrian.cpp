#include "Pedestrian.h"
#include "Conf.h"
#include "GlobalValue.h"
#include "SimHandler.h"
#include "Virus.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

//======================================================================
Pedestrian::Pedestrian(int id, double px, double py,
                       double vx, double vy, int startId, int goalId)
    : _id(id)
{
    _position.setXY(px, py);
    _start.setXY(px, py);
    _velocity.setXY(vx, vy);
    _startId  = startId;
    _goalId   = goalId;

    double rate = GV::infectionRate();
    if (rand()%100<rate)
    {
        _isInfected = true;
    }
    else
    {
        _isInfected = false;
    }
    _isExposed = false;
    _exposureCounter = 0;

    _hasArrivedGoal = false;
    _sim = NULL;
    
    // ゴールの決定
    int r;
    switch (goalId)
    {
    case 0:
#ifdef MODEL3
        r = rand()%2;
#else
        r = rand()%4;
#endif
        switch (r)
        {
        case 2:
            _goal = Vector2D(-ROOM_XSIZE,  ROOM_YSIZE/2);
            break;
        case 3:
            _goal = Vector2D(-ROOM_XSIZE,  ROOM_YSIZE/4);
            break;
        case 0:
            _goal = Vector2D(-ROOM_XSIZE, -ROOM_YSIZE/4);
            break;
        case 1:
            _goal = Vector2D(-ROOM_XSIZE, -ROOM_YSIZE/2);
            break;
        }
        break;
    case 1:
#ifdef MODEL3
        r = rand()%2;
#else
        r = rand()%4;
#endif
        switch (r)
        {
        case 0:
            _goal = Vector2D(ROOM_XSIZE,  ROOM_YSIZE/2);
            break;
        case 1:
            _goal = Vector2D(ROOM_XSIZE,  ROOM_YSIZE/4);
            break;
        case 2:
            _goal = Vector2D(ROOM_XSIZE, -ROOM_YSIZE/4);
            break;
        case 3:
            _goal = Vector2D(ROOM_XSIZE, -ROOM_YSIZE/2);
            break;
        }
        break;
    case 2:
        _goal = Vector2D(-ROOM_XSIZE/2,  ROOM_YSIZE);
        break;
    case 3:
        _goal = Vector2D( ROOM_XSIZE/2,  ROOM_YSIZE);
        break;
    case 4:
        _goal = Vector2D(-ROOM_XSIZE/2, -ROOM_YSIZE);
        break;
    case 5:
        _goal = Vector2D( ROOM_XSIZE/2, -ROOM_YSIZE);
        break;
    default:
        cout << "GoalId: " << goalId << endl; 
    }
}

//======================================================================
void Pedestrian::determineAccel()
{
    _accelFactors.clear();
    
    _calcForceFromGoal();
    _calcForceFromPedestrian();
    _calcForceFromWall();

    _accel.setXY(0, 0);
    for (unsigned int i=0; i<_accelFactors.size(); i++)
    {
        _accel += _accelFactors[i];
    }
    if (isnan(_accel.x()) || isnan(_accel.y()))
    {
#pragma omp critical(Pedestrian_print)
        {
            print();
        }
    }
}

//======================================================================
void Pedestrian::_calcForceFromGoal()
{
    // 希望進行方向の単位ベクトル
    Vector2D dir = create_unit_vector(_goal - _position);
    _accelFactors.emplace_back
        ((VMAX * dir - _velocity) / SFM_TAU);
}

//======================================================================
void Pedestrian::_calcForceFromPedestrian()
{
    vector<Pedestrian*>* pedestrians = _sim->pedestrians();
    for (unsigned int i=0; i<pedestrians->size(); i++)
    {
        /*
         * 出入り口付近の過密を避けるため，
         * 出入り口から2m以内は歩行者間の相互作用を無視
         */
        if (distance_vertex(_start, _position) < 5
            || distance_vertex(_goal, _position) < 5)
        {
            continue;
        }

        Vector2D sf(0, 0);
        Pedestrian* p = (*pedestrians)[i];

        // 自分自身は無視
        if (p==this)
        {
            continue;
        }
        // 2m以上離れたら無視
        /*
         * 合わせて，距離がゼロの場合も無視する
         * 歩行中にこのような状況になることはないはずだが，
         * 発生した瞬間に歩行者が重なることがまれにあり得る
         */
        double d = distance_vertex(p->position(), _position);
        if (d>2 || d<1e-9)
        {
            continue;
        }
        // _numNeighbors++;
        
        // 2人の体のサイズ
        double r = 2 * AGENT_BODY_SIZE;
        double diff = r - d;
        
        // 他者から自分への単位方向ベクトル
        Vector2D n = create_unit_vector(_position - p->position());
        sf += SFM_A * exp(diff/SFM_B) * n;

        if (diff>=0)
        {
            // "body force"
            sf += n * SFM_K * diff;

            // tangential direction
            Vector2D t(-n.y(), n.x());

            // tangential velocity difference
            double tvd = dot_product((p->velocity()-_velocity), t);

            // "sliding friction force"
            sf += t * (SFM_KAPPA * diff * tvd);
        }
        
        _accelFactors.emplace_back(sf/SFM_MASS);

        /*
          Vector2D rel_v = p->velocity() - _velocity;
          double theta = dot_product(rel_v, n)/rel_v.size();

          _exposureScore += (theta+1)/(2 * max(d*d,0.2) );
        */
    }
}

//======================================================================
void Pedestrian::_calcForceFromWall()
{
    Wall* walls = _sim->walls();
    for (int i=0; i<NUM_WALL; i++)
    {
        Vector2D sf(0, 0);
        Wall* w = &(walls[i]);
        /*
         * 点Pと線分ABの距離dを d=|(PA×AB)/|AB||で求める
         */
        Vector2D PA(w->begin().x() - _position.x(),
                    w->begin().y() - _position.y());
        Vector2D AB(w->end().x()   - w->begin().x(),
                    w->end().y()   - w->begin().y());
        double length = AB.size();
        double d = fabs(cross_vector(PA, AB)/length);
        
        // 2m以上離れたら無視
        if (d>2)
        {
            continue;
        }
        
        // 法線ベクトル
        Vector2D n;
        switch (i)
        {
        case 0:
            n.setXY(0, -1);
            break;
        case 1:
            n.setXY(-1, 0);
            break;
        case 2:
            n.setXY(0, 1);
            break;
        case 3:
            n.setXY(1, 0);
            break;
        }

        double diff = AGENT_BODY_SIZE-d;

        // "repulsive interaction force"
        sf += SFM_A * exp(diff/SFM_B) * n;
        
        if (diff>=0)
        {
            // "body force"
            sf += n * SFM_K * diff;

            // tangential direction
            Vector2D t(-n.y(), n.x());

            // tangential velocity difference
            double tvd = cross_vector(_velocity, t);

            // "sliding friction force"
            sf += t * (SFM_KAPPA * diff * tvd);
        }
        
        _accelFactors.emplace_back(sf/SFM_MASS);
    }
}

//======================================================================
void Pedestrian::walk()
{
    _velocity += _accel    * 0.1; //[m/sec]
    if (_velocity.size() > VMAX)
    {
        _velocity = create_unit_vector(_velocity) * VMAX;
    }

    _position += _velocity * 0.1; //[m]

    // ゴール判定
    if (distance_vertex(_goal, _position) < 1.5)
    {
        _hasArrivedGoal = true;
    }
}

//======================================================================
void Pedestrian::cough()
{
    // 感染者でないエージェントやゴールしたエージェントは咳をしない
    if (!_isInfected || _hasArrivedGoal)
    {
        return;
    }

    double prob = GV::coughProb() / 36000.0; // [/hour]->[/step]
    double r = (double)rand()/RAND_MAX;      // [0,1]

    // 確率が要件を満たしたらウイルスを配置
    if (r<prob)
    {
        _sim->placeVirus(_position.x(), _position.y());
    }
}

//======================================================================
void Pedestrian::checkExposure()
{
    // 到着者，感染者および暴露済みの者はチェックの必要なし
    if (_hasArrivedGoal || _isInfected || _isExposed)
    {
        return;
    }

    double dth = GV::exposureSize();
    int    cth = GV::judgeExposureTime() * 10; //[sec]->[step]  
    vector<Virus*>* viruses = _sim->viruses();
    for (unsigned int i=0; i<viruses->size(); i++)
    {
        Vector2D p = (*viruses)[i]->position();
        double distance = distance_vertex(_position, p);
        if (distance < dth)
        {
            _exposureCounter++;
            if (_exposureCounter>cth)
            {
                _isExposed = true;
                _sim->incrementNumExposed();
                /*
                cout << "ID[" << _id << "] has exposed at ("
                     << _position.x() << ", " << _position.y()
                     << ")" << endl;
                */
                break;
            }
        }
    }
}

//======================================================================
void Pedestrian::print() const
{
    cout << "********** Pedestrian (ID:" << _id
         << ") **********" << endl;
    cout << "Position: (" << _position.x() << ", "
         << _position.y() << ")" << endl;
    cout << "vmax: " << VMAX
         << ", velocity: (" << _velocity.x()
         << ", " << _velocity.y() << ")/"
         << _velocity.size() << endl;
    // cout << "NumNeighborAgents: " << _numNeighbors << endl;
    /*
    cout << "Near agents: " << endl;
    for (Agent* agent : _nearAgents) {
        cout << "\t" << agent->id() << "/L("
             << agent->position().x() << ", "
             << agent->position().y() << "), G("
             << agent->globalPosition().x() <<  ", "
             << agent->globalPosition().y() << ")"
             << endl;
    }
    */
    
    cout << "Accel Factors: " << endl;
    for (unsigned int i=0; i<_accelFactors.size(); i++) {
        cout << "\t (" << _accelFactors[i].x() << ", "
             << _accelFactors[i].y() << ")" << endl;
    }
}
