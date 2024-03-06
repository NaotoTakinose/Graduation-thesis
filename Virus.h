#ifndef __VIRUS_H__
#define __VIRUS_H__

#include "Vector2D.h"

/// ウイルスクラス
class Virus
{
public:
    Virus(){};
    Virus(int id, double x, double y, int lifeCounter);

    /// ウイルスの残存カウンタを減らす
    void fade()
    {
        _lifeCounter--;
    }

    /// ウイルスの滞留が終わったか否か
    bool isDead()
    {
        return (_lifeCounter <= 0);
    }

private:
    /// 識別番号
    int _id;

    /// 位置ベクトル
    Vector2D _position;

    /// 残存カウンタ
    int _lifeCounter;
    
public:
    int id() const
    {
        return _id;
    }
    
    Vector2D position() const
    {
        return _position;
    }
};

#endif //__VIRUS_H__
