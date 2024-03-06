#ifndef __VECTOR_2D_H__
#define __VECTOR_2D_H__

#include <cmath>

/* 2次元ベクトルクラス */
class Vector2D
{
private:
    float _x; //< x成分
    float _y; //< y成分

public:
    /* コンストラクタ */
    Vector2D()
    {
        _x = 0;
        _y = 0;
    };

    /* コンストラクタ */
    Vector2D(float x, float y)
    {
        _x = x;
        _y = y;
    };

    /* デフォルトのデストラクタ         */
    /* デフォルトのコピーコンストラクタ */
    /* デフォルトの代入演算子           */

    /* アクセッサ ------- */
    /* アクセッサ */
    /* x成分を返す */
    float x() const
    {
        return _x;
    };

    /* y成分を返す */
    float y() const
    {
        return _y;
    };

    /* 成分を設定する */
    void setXY(float x, float y)
    {
        _x = x;
        _y = y;
    };

    /* 大きさを返す */
    float size() const
    {
        return sqrt(_x*_x+_y*_y);
    }

    /* 演算子 ----------- */
    Vector2D& operator+=(const Vector2D& rhs)
    {
        _x += rhs._x;
        _y += rhs._y;
        return *this;
    };

    Vector2D& operator-=(const Vector2D& rhs)
    {
        _x -= rhs._x;
        _y -= rhs._y;
        return *this;
    };

    Vector2D& operator*=(float k)
    {
        _x *= k;
        _y *= k;
        return *this;
    };

    Vector2D& operator/=(float d)
    {
        _x /= d;
        _y /= d;
        return *this;
    };

    const Vector2D operator-() const
    {
        return Vector2D(-_x, -_y);
    };
};

/* ベクトル演算 */
Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);
Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);
Vector2D operator*(const Vector2D& lhs, float k);
Vector2D operator*(float k, const Vector2D& rhs);
Vector2D operator/(const Vector2D& lhs, float d);
float    operator*(const Vector2D& lhs, const Vector2D& rhs);

double distance_vertex(Vector2D p1, Vector2D p2);
double cross_vector(Vector2D vl, Vector2D vr);
double dot_product(Vector2D vl, Vector2D vr);

Vector2D create_unit_vector( Vector2D v );

bool isCross(float ax, float ay, float bx, float by,
             float cx, float cy, float dx, float dy);

#endif //__VECTOR_2D_H__
