#ifndef __PEDESTRIAN_H__
#define __PEDESTRIAN_H__

#include <vector>

#include "Vector2D.h"

class SimHandler;

/// 歩行者クラス
class Pedestrian
{
public:
    Pedestrian(){};
    Pedestrian(int id, double px, double py,
               double vx, double vy, int startId, int goalId);
    ~Pedestrian(){};

    /// 加速度決定
    void determineAccel();    

private:
    /// 目的地からの引力を計算
    void _calcForceFromGoal();

    /// 他の歩行者からの斥力を計算
    void _calcForceFromPedestrian();
    
    /// 壁からの斥力を計算
    void _calcForceFromWall();

public:
    /// 速度決定と歩行
    void walk();

    /// 咳をする
    void cough();

    /// 暴露を判定する
    void checkExposure();
    
private:
    /// 識別番号
    int _id;

    /// 感染しているか否か
    bool _isInfected;

    /// 暴露したか否か
    bool _isExposed;

    /// 暴露カウンタ[step]
    /**
     * これが閾値を超えると暴露と判定される
     */
    int _exposureCounter;

    /*
     * 以前の暴露スコア
     * double _exposureScore;
     */
    
    /// 位置ベクトル
    Vector2D _position;

    /// 速度ベクトル
    Vector2D _velocity;

    /// 加速度ベクトル
    Vector2D _accel;
    
    /// 出発地ID
    int _startId;

    /// 出発地の位置
    Vector2D _start;
    
    /// 最終目的地ID
    int _goalId;

    /// 目的地の位置
    Vector2D _goal;

    /// 最高速度[m/sec]
    static constexpr double VMAX = 1.34;

    /// ゴールについたか否か
    bool _hasArrivedGoal;

    /// シミュレーション管理オブジェクト
    SimHandler* _sim;

    /// 加速度のもとになる外力
    std::vector<Vector2D> _accelFactors;
    
public:
    int id() const
    {
        return _id;
    }
    
    Vector2D position() const
    {
        return _position;
    }

    Vector2D velocity() const
    {
        return _velocity;
    }

    int startId() const
    {
        return _startId;
    }

    int goalId() const
    {
        return _goalId;
    }
    
    bool hasArrivedGoal() const
    {
        return _hasArrivedGoal;
    }

    bool isInfected() const
    {
        return _isInfected;
    }

    bool isExposed() const
    {
        return _isExposed;
    }
    
    void setSimHandler(SimHandler* sim)
    {
        _sim = sim;
    }
    
private:
    // SFMのパラメータ
    /*
     * モデルは以下を参照．
     * Helbing, D., Farkas, I. & Vicsek, T.,
     * Simulating dynamical features of escape panic.
     * Nature vol. 407, pp. 487--490, 2000.
     * https://doi.org/10.1038/35035023
     */
    static constexpr double SFM_MASS  = 80;
    static constexpr double SFM_TAU   = 0.5;
    static constexpr double SFM_A     = 2.0e+3;
    static constexpr double SFM_B     = 0.08;
    static constexpr double SFM_K     = 1.2e+5;
    static constexpr double SFM_KAPPA = 2.5e+5;
 
public:
    /// 情報を表示する
    void print() const;
};

#endif //__PEDESTRIAN_H__
