#ifndef __VISUALIZER_H__
#define __VISUALIZER_H__

class SimHandler;

/// GUI機能をまとめるクラス
class Visualizer
{
public:
    Visualizer(){}
    ~Visualizer(){}

    /// 可視化パラメータの設定
    void setViewingParameters();

    /// シミュレーション管理オブジェクトの設定
    void setSimHandler(SimHandler* sim);
    
    /// 描画関数
    static void redrawView();

    /// アニメーション関数
    static void idleEvent();
    /// ShowDetailボタン
    static void showDetailButtonCallback();
    /// Drawボタン
    static void drawButtonCallback();
    /// Printボタン
    static void printButtonCallback();
    /// Animateボタン
    static void animateButtonCallback();
    /// Incrementボタン
    static void incrementButtonCallback();
    /// Resetボタン
    static void resetButtonCallback();
    /// Quitボタン
    static void quitButtonCallback();

private:
    /// IdleEventフラグ
    static bool _isIdleEventOn;

    /// ID表示フラグ
    static int _isIdShown;
    
    /// 画面保存フラグ
    static int _isCapturingOn;

    /// シミュレーション管理オブジェクト
    static SimHandler* _sim;

    /// 出力対象の歩行者のID
    static int _targetId;
};

#endif //__VISUALIZER_H__
