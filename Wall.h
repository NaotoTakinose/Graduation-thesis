#ifndef __WALL_H__
#define __WALL_H__

#include "Vector2D.h"

// 壁クラス
class Wall
{
private:
    int      _id;       //< 識別番号
    Vector2D _begin;
    Vector2D _end;

public:
    /// 識別番号を返す
    int id() const
    {
        return _id;
    }

    /// 始点を返す
    Vector2D begin() const
    {
        return _begin;
    }

    /// 終点を返す
    Vector2D end() const
    {
        return _end;
    }
    
    /// 初期化
    void initialize(int id,
                    double begin_x, double begin_y,
                    double end_x, double end_y);
};

#endif //__WALL_H__
