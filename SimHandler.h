#ifndef __SIM_HANDLER_H__
#define __SIM_HANDLER_H__

#include "Conf.h"
#include "Pedestrian.h"
#include "Wall.h"
#include <omp.h>
#include <vector>

class Pedestrian;
class Virus;

/// シミュレーション全体を管理するクラス
class SimHandler
{
public:
    SimHandler();
    ~SimHandler();

    /// 引数の処理
    void parseArguments(int argc, char** argv);

    void _virussim();

    /// 歩行空間を定義する
    void generateWalkSpace();

    /// シミュレーションを開始する
    void run();

    /// 指定時刻までシミュレーションを実行する
    void continuousRun();

    /// 各時刻ステップの処理
    void timeIncrement();

private:
    /// エージェントを生成する
    void _createAgent();

    /// 目的地に到達した歩行者を削除する
    void _deleteArriedPedestrians();

public:
    /// ウイルスを生成し配置する
    void placeVirus(double x, double y);

private:
    /// 死滅したウイルスを削除する
    void _deleteDeadViruses();

private:
    /// ステップ数
    int _step;

    /// 歩行者の集合
    std::vector<Pedestrian*> _pedestrians;

    /// ウイルスの集合
    std::vector<Virus*> _viruses;

    /// 歩行者数
    int _numPedestrians;

    /// 感染者数
    int _numInfected;

    /// 暴露者数
    int _numExposed;
    
    /// ウイルス数
    int _numViruses;
    
    /// 壁
    Wall _walls[NUM_WALL];

    /// 出入り口の位置
    Vector2D _exits[NUM_EXIT];

public:
    int step() const
    {
        return _step;
    }

    std::vector<Pedestrian*>* pedestrians()
    {
        return &_pedestrians;
    }

    std::vector<Virus*>* viruses()
    {
        return &_viruses;
    }
    
    Wall* walls()
    {
        return _walls;
    }

    Vector2D* exits()
    {
        return _exits;
    }

    void incrementNumExposed()
    {
#pragma omp atomic
        _numExposed++;
    }
    
public:
    /// 結果の表示
    void print();
};

#endif //__SIM_HANDLER_H__
