#ifndef __DRAWER_H__
#define __DRAWER_H__

class SimHandler;

class Drawer
{
private:
    Drawer(){};
    ~Drawer(){};

public:
    /// シミュレーション管理オブジェクトをセットする
    static void setSimHandler(SimHandler* sim)
    {
        _sim = sim;
    }
    
    /// 壁を描画する
    static void drawWall();

    /// 出入り口を描画する
    static void drawExits();

    /// 歩行者を描画する
    static void drawPedestrians(bool isIdShown);

    /// ウイルスを描画する
    static void drawViruses();
    
private:
    /// シミュレーション管理オブジェクト
    static SimHandler* _sim;
};

#endif //__DRAWER_H__
