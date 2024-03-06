#include "SimHandler.h"
#include "Conf.h"
#include "GlobalValue.h"
#include "Pedestrian.h"
#include "Virus.h"
#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

//======================================================================
SimHandler::SimHandler()
    : _step(0),
      _numPedestrians(0), _numInfected(0), _numExposed(0),
      _numViruses(0)
{
    _pedestrians.clear();
    _viruses.clear();
}

//======================================================================
SimHandler::~SimHandler()
{
    // _pedestriansの削除
    for (unsigned int i=0; i<_pedestrians.size(); i++)
    {
        delete _pedestrians[i];
    }
    _pedestrians.clear();

    // _virusesの削除
    for (unsigned int i=0; i<_viruses.size(); i++)
    {
        delete _viruses[i];
    }
    _viruses.clear();
}

//======================================================================
void SimHandler::parseArguments(int argc, char** argv)
{
    if (argc!=7 && argc!=8) {
        cout << "Usage: ./station exposureSize[m] virusStayTime[sec]"
             << " infectionRate[%] judgeExposureTime[sec] coughProb[/h]"
             << " agentGenerationRate[%/step] randomSeed" << endl;
        exit(1);
    }
    
    GV::setExposureSize(atof(argv[1]));
    GV::setVirusStayTime(atoi(argv[2]));
    GV::setInfectionRate(atoi(argv[3]));
    GV::setJudgeExposureTime(atoi(argv[4]));
    GV::setCoughProb(atof(argv[5]));
    GV::setAgentGenerationRate(atoi(argv[6]));
    if (argc == 8)
    {
        GV::setRandomSeed(atoi(argv[7]));
    }
    else
    {
        GV::setRandomSeed(0);
    }

    // 乱数の種
#ifdef DEBUG
    srand(GV::randomSeed);
#else
    srand(time(NULL));
#endif
}

//======================================================================
void SimHandler::generateWalkSpace()
{
    // 外壁
    _walls[0].initialize(0,
                         -ROOM_XSIZE-2,  ROOM_YSIZE+2,
                          ROOM_XSIZE+2,  ROOM_YSIZE+2);
    _walls[1].initialize(1,
                          ROOM_XSIZE+2,  ROOM_YSIZE+2,
                          ROOM_XSIZE+2, -ROOM_YSIZE-2);
    _walls[2].initialize(2,
                         -ROOM_XSIZE-2, -ROOM_YSIZE-2,
                          ROOM_XSIZE+2, -ROOM_YSIZE-2);
    _walls[3].initialize(3,
                         -ROOM_XSIZE-2,  ROOM_YSIZE+2,
                         -ROOM_XSIZE-2, -ROOM_YSIZE-2);

    // 出入り口
    _exits[0] = Vector2D(-ROOM_XSIZE,  ROOM_YSIZE/2);  //出入り口0_0
    _exits[1] = Vector2D(-ROOM_XSIZE,  ROOM_YSIZE/4);  //出入り口0_1
    _exits[2] = Vector2D(-ROOM_XSIZE, -ROOM_YSIZE/4);  //出入り口0_2
    _exits[3] = Vector2D(-ROOM_XSIZE, -ROOM_YSIZE/2);  //出入り口0_3

    _exits[4] = Vector2D(ROOM_XSIZE,  ROOM_YSIZE/2);   //出入り口1_0
    _exits[5] = Vector2D(ROOM_XSIZE,  ROOM_YSIZE/4);   //出入り口1_1
    _exits[6] = Vector2D(ROOM_XSIZE, -ROOM_YSIZE/4);   //出入り口1_2
    _exits[7] = Vector2D(ROOM_XSIZE, -ROOM_YSIZE/2);   //出入り口1_3
    
    _exits[8]  = Vector2D(-ROOM_XSIZE/2,  ROOM_YSIZE); //出入り口2
    _exits[9]  = Vector2D( ROOM_XSIZE/2,  ROOM_YSIZE); //出入り口3
    _exits[10] = Vector2D(-ROOM_XSIZE/2, -ROOM_YSIZE); //出入り口4
    _exits[11] = Vector2D( ROOM_XSIZE/2, -ROOM_YSIZE); //出入り口5
}

//======================================================================
void SimHandler::run()
{
    if (_step<MAX_STEP)
    {
        timeIncrement();
    }
    if (_step>=MAX_STEP)
    {
        print();
    }
}

//======================================================================
void SimHandler::continuousRun()
{
    while (_step<MAX_STEP)
    {
        timeIncrement();

        if (_step%10==0)
        {
            cout << _step/10 << "[sec]" << endl;
        }
    }
    
    print();
}

//======================================================================
void SimHandler::timeIncrement()
{
    // ステップ数の更新
    _step++;

    // 歩行者生成
    _createAgent();

    // 歩行者の総数
    int pedestrianSize = _pedestrians.size();

    // 歩行者の加速度更新
    for (int i=0; i<pedestrianSize; i++)
    {
        _pedestrians[i]->determineAccel();
    }

    // 歩行者の速度・位置更新
    for (int i=0; i<pedestrianSize; i++)
    {
        _pedestrians[i]->walk();
    }

    // 歩行者の咳
    for (int i=0; i<pedestrianSize; i++)
    {
        _pedestrians[i]->cough();
    }

    // ウイルスの減少
    for (unsigned int i=0; i<_viruses.size(); i++)
    {
        _viruses[i]->fade();
    }

    // 歩行者の暴露チェック
    for (int i=0; i<pedestrianSize; i++)
    {
        _pedestrians[i]->checkExposure();
    }
    _virussim();
    // 歩行者の削除
    _deleteArriedPedestrians();

    // ウイルスの削除
    _deleteDeadViruses();
}
//======================================================================
void SimHandler::_virussim()
{

}
//======================================================================
void SimHandler::_createAgent()
{
    double generationRate = GV::agentGenerationRate()/100.0;

    for (int i=0; i<6; i++)
    {
#ifdef MODEL2
        // 歩行者は出入り口0からしか入場しない
        if (i>=1)
        {
            continue;
        }
        int rGoal;
#else
#ifdef MODEL3
        // 歩行者は出入り口0, 1からしか入場しない
        if (i>=2)
        {
            continue;
        }
#endif //MODEL3
#endif //MODEL2
        
        // 生成確率の判定
        double r = (rand()%1000) / 1000.0;
        if (r > generationRate)
        {
            continue;
        }

        // 生成位置とゴール
        double px, py;
        int goalId;
        double r1 = (rand()%2000- 900)/1000.0;
        double r2 = (rand()%2000-1400)/1000.0;
        int rSub;
        switch (i)
        {
        case 0: // 左の入り口(出入り口0)
#ifdef MODEL3
            rSub = rand()%2;
            px = -ROOM_XSIZE;
            py = _exits[rSub].y() + r1; //添字は0-1
            rGoal = rand()%3;
            switch (rGoal)
            {
            case 0:
                goalId = 1;
                break;
            case 1:
                goalId = 2;
                break;
            case 2:
                goalId = 3;
                break;
            }
#else
            rSub = rand()%4;
            px = -ROOM_XSIZE;
            py = _exits[rSub].y() + r1; //添字は0-3
            // 自分以外の目的地
            goalId = rand()%6;
            while (goalId==i)
            {
                goalId = rand()%6;
            }
#endif
            break;
        case 1: // 右の出入り口(出入り口1)
#ifdef MODEL3
            rSub = rand()%2;
            px = ROOM_XSIZE;
            py = _exits[6+rSub].y() + r1; //添字は6-7
            rGoal = rand()%3;
            switch (rGoal)
            {
            case 0:
                goalId = 0;
                break;
            case 1:
                goalId = 4;
                break;
            case 2:
                goalId = 5;
                break;
            }
#else
            rSub = rand()%4;
            px =  ROOM_XSIZE;
            py = _exits[4+rSub].y() + r1; //添字は4-7
            // 自分以外の目的地
            goalId = rand()%6;
            while (goalId==i)
            {
                goalId = rand()%6;
            }
#endif
            break;
        case 2: // 左上出入り口(出入り口2)
            px = -ROOM_XSIZE/2 + r2;
            py = ROOM_YSIZE;
            // 左か右の目的地
            goalId = rand()%2;
            break;
        case 3: // 右上出入り口(出入り口3)
            px = ROOM_XSIZE/2 + r2;
            py = ROOM_YSIZE;
            // 左か右の目的地
            goalId = rand()%2;
            break;
        case 4: // 左下出入り口(出入り口4)
            px = -ROOM_XSIZE/2 + r2;
            py = -ROOM_YSIZE;
            // 左か右の目的地
            goalId = rand()%2;
            break;
        case 5: // 右下出入り口(出入り口4)
            px = ROOM_XSIZE/2 + r2;
            py = -ROOM_YSIZE;
            // 左か右の目的地
            goalId = rand()%2;
            break;
        default:
            cout << "i=" << i << endl;
        }
        Pedestrian* p
            = new Pedestrian(_numPedestrians, px, py,
                             0, 0, i, goalId);
        p->setSimHandler(this);
        _pedestrians.push_back(p);
        _numPedestrians++;
        if (p->isInfected())
        {
            _numInfected++;
        }
    }
}

//======================================================================
void SimHandler::_deleteArriedPedestrians()
{
    vector<Pedestrian*>::iterator itp = _pedestrians.begin();
    while (itp != _pedestrians.end())
    {
        if ((*itp)->hasArrivedGoal())
        {
            delete (*itp);
            itp = _pedestrians.erase(itp);
        }
        else
        {
            itp++;
        }
    }
    
}

//======================================================================
void SimHandler::placeVirus(double x, double y)
{
#pragma omp critical(SimHandler_placeVirus)
    {
        int counter =  GV::virusStayTime();
        Virus* v = new Virus(_numViruses, x, y, counter);
        _viruses.emplace_back(v);
        _numViruses++;
    }
}

//======================================================================
void SimHandler::_deleteDeadViruses()
{
    vector<Virus*>::iterator itv = _viruses.begin();
    while (itv != _viruses.end())
    {
        if ((*itv)->isDead())
        {
            delete (*itv);
            itv = _viruses.erase(itv);
        }
        else
        {
            itv++;
        }
    }
}

//======================================================================
void SimHandler::print()
{
    cout << "---------設定条件---------" << endl;
    cout << "暴露範囲："
         << GV::exposureSize() << "m"<< endl;
    cout << "ウイルス滞留時間："
         << GV::virusStayTime() << "秒" << endl;
    cout << "暴露判定時間："
         << GV::judgeExposureTime() << "秒" << endl;
    cout << "初期感染率："
         << GV::infectionRate() << "%" << endl;
    cout << "エージェント発生率率："
         << GV::agentGenerationRate() << "%" << endl;
    cout << "くしゃみをする確率："
         << GV::coughProb() << "回/時間" << endl;

    cout << "---------実行値---------"<<  endl;
    cout << "歩行者の総数："
         << _numPedestrians << "人" <<endl;
    // cout << "咳のチャレンジ回数："<< NUM_Ch << "回"<< endl;
    cout << "感染者数："
         << _numInfected << "人"<< endl;
    cout << "暴露人数："
         << _numExposed << "人"<< endl;
     cout << "ウイルスの数："
         << _numViruses << "個" << endl;
    
    cout << "---------結果---------"<<  endl;
    cout << "(感染率, 発生率, 感染者数, 暴露者数, 歩行者総数)" << endl;
    cout << GV::infectionRate() << ","
         << GV::agentGenerationRate() << ","
         << _numInfected << ","
         << _numExposed << ","
         << _numPedestrians <<endl;
}
