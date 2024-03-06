#include "Visualizer.h"
#include "Drawer.h"
#include "Pedestrian.h"
#include "SimHandler.h"
#include <autogl.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#define VIEW_SIZE 125

using namespace std;

//======================================================================
// 静的変数の初期値
bool Visualizer::_isIdleEventOn = false;
int Visualizer::_isCapturingOn  = 0;
int Visualizer::_isIdShown      = 0;
SimHandler* Visualizer::_sim    = NULL;
int Visualizer::_targetId       = 0;

//======================================================================
void Visualizer::setViewingParameters()
{
    // サイズや視線方向の設定
    AutoGL_SetViewSize(VIEW_SIZE);
    AutoGL_SetViewCenter(0,0,0);
    AutoGL_SetViewDirection(0,0,1);
    AutoGL_SetViewUpVector(0,1,0);

    // パネルの設定
    AutoGL_SetViewRedrawCallback(redrawView);
    AutoGL_SetMode2D(AUTOGL_MODE_2D_TRANSLATE);
    AutoGL_SetDefaultCallbackInMode2D(NULL);
    AutoGL_EnableDragInMode2D();
    AutoGL_SetPanelInMode2D();
    AutoGL_EnableIdleEvent();

    // IDを表示するか
    AutoGL_AddBoolean(&_isIdShown, "_isIdShown");
    AutoGL_SetLabel("Show Pedestrian ID");
 
    // パネルにShow Detailボタンを追加
    AutoGL_AddInteger(&_targetId, "_targetId");
    AutoGL_SetLabel("Pedestrian ID:");
    AutoGL_AddCallback(showDetailButtonCallback,
                       "ShowDetailButtonCallback");
    AutoGL_SetLabel("Show Pedestrian Detail");
    
    // パネルにDrawボタンを追加
    AutoGL_AddCallback(drawButtonCallback, "drawButtonCallback");
    AutoGL_SetLabel("Draw");

    // パネルにPrintボタンを追加
    AutoGL_AddCallback(printButtonCallback, "printButtonCallback");
    AutoGL_SetLabel("Print");

    // パネルにAnimateボタンを追加
    AutoGL_AddCallback(animateButtonCallback, "animateButtonCallback");
    AutoGL_SetLabel("Animate");

    // パネルにIncrementボタンを追加
    AutoGL_AddCallback(incrementButtonCallback,
                       "incrementButtonCallback");
    AutoGL_SetLabel("Increment");

    // パネルにResetボタンを追加
    AutoGL_AddCallback(resetButtonCallback, "resetButtonCallback");
    AutoGL_SetLabel("Reset");

    // パネルにQuitボタンを追加
    AutoGL_AddCallback(quitButtonCallback, "quitButtonCallback");
    AutoGL_SetLabel("Quit");
    
    // パネルに画像保存ボタンを追加
    AutoGL_AddBoolean(&_isCapturingOn, "_isCapturingOn");
    AutoGL_SetLabel("With Capturing");
    AutoGL_SetPanelForSave();

    // 背景色の設定
    AutoGL_SetBackgroundColor(0.9,0.9,0.9);
}

//======================================================================
void Visualizer::showDetailButtonCallback()
{
    Pedestrian* p = NULL;
    vector<Pedestrian*>* pedestrians = _sim->pedestrians();
    for (unsigned int i=0; i<pedestrians->size(); i++)
    {
        if ((*pedestrians)[i]->id()==_targetId)
        {
            p = (*pedestrians)[i];
            break;
        }
    }
    if (!p)
    {
        cout << "Pedestrian ID: " << _targetId
             << " not found." << endl;
    }
    else
    {
        p->print();
    }
}

//======================================================================
void Visualizer::drawButtonCallback()
{
    AutoGL_DrawView();
}

//======================================================================
void Visualizer::printButtonCallback()
{
    _sim->print();
}

//======================================================================
void Visualizer::animateButtonCallback()
{
    if (_isIdleEventOn)
    {
        AutoGL_SetIdleEventCallback(NULL);
        _isIdleEventOn = false;
    }
    else
    {
        AutoGL_SetIdleEventCallback(idleEvent);
        _isIdleEventOn = true;
    }
}

//======================================================================
void Visualizer::incrementButtonCallback()
{
    _sim->timeIncrement();
    AutoGL_DrawView();
}

//======================================================================
void Visualizer::resetButtonCallback()
{
    cout << "not implemented..." << endl;
}

//======================================================================
void Visualizer::quitButtonCallback()
{
    exit(EXIT_SUCCESS);
}

//======================================================================
void Visualizer::redrawView()
{
    // ステップ数の描画
    stringstream ss;
    ss << "Step: " << _sim->step()
       << ", Agent: " << _sim->pedestrians()->size();
    AutoGL_SetColor(0, 0, 0);
    AutoGL_DrawStringAtScaledPosition(0.02, 0.97, ss.str().c_str());
    
    // 壁の描画
    Drawer::drawWall();

    // 出入り口の描画
    Drawer::drawExits();

    // 歩行者の描画
    Drawer::drawPedestrians(_isIdShown);

    // ウイルスの描画
    Drawer::drawViruses();
}

//======================================================================
void Visualizer::idleEvent()
{
    _sim->run();
    AutoGL_DrawView();
}

//======================================================================
void Visualizer::setSimHandler(SimHandler* sim)
{
    _sim = sim;
}
