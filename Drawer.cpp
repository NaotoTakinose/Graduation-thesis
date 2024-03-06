#include "Drawer.h"
#include "Conf.h"
#include "SimHandler.h"
#include "Vector2D.h"
#include "Virus.h"
#include "Wall.h"
#include <autogl.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

SimHandler* Drawer::_sim = NULL;

//======================================================================
void Drawer::drawWall()
{
    Wall* walls = _sim->walls();
    for (int i=0; i<NUM_WALL; i++)
    {
        Wall* w = &(walls[i]);
        AutoGL_SetColor(0, 0, 0);
        AutoGL_DrawLine(w->begin().x(), w->begin().y(), 0.0,
                        w->end().x(),   w->end().y(),   0.0); 
    }
}

//======================================================================
void Drawer::drawExits()
{
    AutoGL_SetColor(0.2, 0.2, 0.2);

    Vector2D* exits = _sim->exits();
    for (int i=0; i<NUM_EXIT; i++)
    {
        double x = exits[i].x();
        double y = exits[i].y();
        
        // 左の出入り口
        if (i<=3)
        {
            AutoGL_DrawQuadrangle( x,   y+2, 0.0,
                                   x,   y-2, 0.0,
                                   x+5, y-2, 0.0,
                                   x+5, y+2, 0.0);
        }
        // 右の出入り口
        else if (i<=7)
        {
            AutoGL_DrawQuadrangle( x-5, y+2, 0.0,
                                   x-5, y-2, 0.0,
                                   x,   y-2, 0.0,
                                   x,   y+2, 0.0);
        }
        // 上の出入口
        else if (i<=9)
        {
            AutoGL_DrawQuadrangle( x-2.5, y-5, 0.0,
                                   x-2.5, y,   0.0,
                                   x+2.5, y,   0.0,
                                   x+2.5, y-5, 0.0);
        }
        // 下の出入り口
        else
        {
            AutoGL_DrawQuadrangle( x-2.5, y,   0.0,
                                   x-2.5, y+5, 0.0,
                                   x+2.5, y+5, 0.0,
                                   x+2.5, y,   0.0);
        }
    }
    

#ifdef NODEF    
    //右の入り口
    AutoGL_DrawQuadrangle( ROOM_XSIZE, EXIT_YSIZE/2,    0.0,
                           ROOM_XSIZE, -EXIT_YSIZE/2,   0.0,
                           ROOM_XSIZE+5, -EXIT_YSIZE/2, 0.0,
                           ROOM_XSIZE+5, EXIT_YSIZE/2,  0.0);
    //左の入り口
    AutoGL_DrawQuadrangle( -ROOM_XSIZE, EXIT_YSIZE/2,    0.0,
                           -ROOM_XSIZE, -EXIT_YSIZE/2,   0.0,
                           -ROOM_XSIZE-5, -EXIT_YSIZE/2, 0.0,
                           -ROOM_XSIZE-5, EXIT_YSIZE/2,  0.0);

    //出口3
    AutoGL_DrawQuadrangle( -ROOM_XSIZE/2-2, ROOM_YSIZE, 0.0,
                           -ROOM_XSIZE/2-2, ROOM_YSIZE+4, 0.0,
                           -ROOM_XSIZE/2+2, ROOM_YSIZE+4, 0.0,
                           -ROOM_XSIZE/2+2, ROOM_YSIZE, 0.0);

    //出口4
    AutoGL_DrawQuadrangle( ROOM_XSIZE/2-2, ROOM_YSIZE, 0.0,
                           ROOM_XSIZE/2-2, ROOM_YSIZE+4, 0.0,
                           ROOM_XSIZE/2+2, ROOM_YSIZE+4, 0.0,
                           ROOM_XSIZE/2+2, ROOM_YSIZE, 0.0);

    //出口5
    AutoGL_DrawQuadrangle( ROOM_XSIZE/2-2, -ROOM_YSIZE, 0.0,
                           ROOM_XSIZE/2-2, -ROOM_YSIZE-4, 0.0,
                           ROOM_XSIZE/2+2, -ROOM_YSIZE-4, 0.0,
                           ROOM_XSIZE/2+2, -ROOM_YSIZE, 0.0);
    
    //出口6
    AutoGL_DrawQuadrangle( -ROOM_XSIZE/2-2, -ROOM_YSIZE, 0.0,
                           -ROOM_XSIZE/2-2, -ROOM_YSIZE-4, 0.0,
                           -ROOM_XSIZE/2+2, -ROOM_YSIZE-4, 0.0,
                           -ROOM_XSIZE/2+2, -ROOM_YSIZE, 0.0);
#endif
}

//======================================================================
void Drawer::drawPedestrians(bool isIdShown)
{
    vector<Pedestrian*>* pedestrians = _sim->pedestrians();
    for (unsigned int i=0; i<pedestrians->size(); i++)
    {
        float r = 0.0;
        float g = 0.0;
        float b = 0.0;
        
        Pedestrian* pedestrian = (*pedestrians)[i];
        Vector2D p = pedestrian->position();
        switch (pedestrian->startId())
        {
        case 0:
            r = 1.0;
            break;
        case 1:
            b = 1.0;
            break;
        default:
            r = 1.0;
            b = 1.0;
            break;
        }
        if (pedestrian->isInfected())
        {
            r *= 0.75;
            b *= 0.75;
        }
        AutoGL_SetColor(r, g, b);
        AutoGL_DrawCircle3D(p.x(), p.y(), 1.5,
                            0, 0, 1, AGENT_SIZE, 3);
        if (isIdShown)
        {
            AutoGL_SetColor(0, 0, 0);
            stringstream ss;
            ss << (*pedestrians)[i]->id();
            AutoGL_DrawString(p.x()+0.2, p.y()+0.2, 3.0,
                              ss.str().c_str());
        }
    }
}

//======================================================================
void Drawer::drawViruses()
{
    vector<Virus*>* viruses = _sim->viruses();
    for (unsigned int i=0; i<viruses->size(); i++)
    {
        Virus* virus = (*viruses)[i];
        Vector2D p = virus->position();
        AutoGL_SetColor(1, 1, 0);
        AutoGL_DrawCircle3D(p.x(), p.y(), 0.5,
                            0, 0, 1, 2, 3);
    }
}
