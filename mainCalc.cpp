#include "SimHandler.h"
#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;

/// シミュレーション管理オブジェクト
unique_ptr<SimHandler> sim;

/// main関数
int main(int argc, char* argv[])
{
    // シミュレーション管理オブジェクトの生成
    sim.reset(new SimHandler);
    sim->parseArguments(argc, argv);
    sim->generateWalkSpace();

    sim->continuousRun();
    
    sim.reset();
    return 0;
}
