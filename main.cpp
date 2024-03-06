#include "Drawer.h"
#include "SimHandler.h"
#include "Visualizer.h"
#include <autogl.h>
#include <iostream>
#include <memory>

using namespace std;

/// シミュレーション管理オブジェクト
unique_ptr<SimHandler> sim;

/// 可視化オブジェクト
unique_ptr<Visualizer> vis;

/* main関数 */
void AutoGL_SetUp(int argc, char* argv[])
{
    // シミュレーション管理オブジェクトの生成
    sim.reset(new SimHandler);
    sim->parseArguments(argc, argv);
    sim->generateWalkSpace();
        
    // 可視化オブジェクトの生成
    /*
     * 可視化パラメータの設定などをまとめる
     */
    vis.reset(new Visualizer);
    vis->setSimHandler(sim.get());
    vis->setViewingParameters();
    Drawer::setSimHandler(sim.get());
}
