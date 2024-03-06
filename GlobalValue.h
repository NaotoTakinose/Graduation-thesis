#ifndef __GLOBAL_VALUE_H__
#define __GLOBAL_VALUE_H__

/// グローバル変数をまとめたクラス
class GlobalValue
{
private:
    GlobalValue(){};
    ~GlobalValue(){};

private:
    /// 暴露範囲 (マスク着用の有無) [m]
    /**
     * @note exposureRange?
     */
    static double _exposureSize;
public:
    static void setExposureSize(double range)
    {
        _exposureSize = range;
    }
    static double exposureSize()
    {
        return _exposureSize;
    }

private:
    /// ウイルスの滞留時間 (換気の度合い) [sec]
    /**
     * @note virusStaySteps?
     */
    static int _virusStayTime;
public:
    static void setVirusStayTime(int step)
    {
        _virusStayTime = step;
    }
    static int virusStayTime()
    {
        return _virusStayTime;
    }

private:
    /// 初期感染率 [%]
    static int _infectionRate;
public:
    static void setInfectionRate(int rate)
    {
        _infectionRate = rate;
    }
    static int infectionRate()
    {
        return _infectionRate;
    }

private:
    /// エージェント発生率 [%]
    static int _agentGenerationRate;
public:
    static void setAgentGenerationRate(int rate)
    {
        _agentGenerationRate = rate;
    }
    static int agentGenerationRate()
    {
        return _agentGenerationRate;
    }
    
private:
    /// 咳・くしゃみの確率 [回/h]
    static double _coughProb;
public:
    static void setCoughProb(double prob)
    {
        _coughProb = prob;
    }
    static double coughProb()
    {
        return _coughProb;
    }

private:
    /// 暴露とみなす時間 [秒]
    static int _judgeExposureTime;
public:
    static void setJudgeExposureTime(int time)
    {
        _judgeExposureTime = time;
    }
    static int judgeExposureTime()
    {
        return _judgeExposureTime;
    }

private:
    // 乱数の種
    static int _randomSeed;
public:
    static void setRandomSeed(int seed)
    {
        _randomSeed = seed;
    }
    static int randomSeed()
    {
        return _randomSeed;
    }
};

// GlobalValueを"GV"で呼び出せるようにする
using GV = GlobalValue; 
    
#endif //__GLOBAL_VALUE_H__
