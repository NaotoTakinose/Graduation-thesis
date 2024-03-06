#include "Vector2D.h"

/* 二項演算子 */
Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
{
    return (Vector2D(lhs) += rhs);
}

Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs)
{
    return (Vector2D(lhs) -= rhs);
}

Vector2D operator*(const Vector2D& lhs, float k)
{
    return (Vector2D(lhs) *= k);
}

Vector2D operator*(float k, const Vector2D& rhs)
{
    return (Vector2D(rhs) *= k);
}

Vector2D operator/(const Vector2D& lhs, float d)
{
    return (Vector2D(lhs) /= d);
}

float operator*(const Vector2D& lhs, const Vector2D& rhs)
{
    return (lhs.x()*rhs.x()+lhs.y()+rhs.y());
}

/// 点間距離
double distance_vertex(Vector2D p1, Vector2D p2)
{
    return sqrt( ( p2.x() - p1.x() ) * ( p2.x() - p1.x() )
                + ( p2.y() - p1.y() ) * ( p2.y() - p1.y() ));
}

// ベクトル外積
double cross_vector(Vector2D vl, Vector2D vr)
{
    return vl.x() * vr.y() - vl.y() * vr.x();
}

// 単位ベクトル生成
Vector2D create_unit_vector( Vector2D v )
{
    double len = sqrt( ( v.x() * v.x() )
                       + ( v.y() * v.y()) );
    Vector2D ret;
    ret = Vector2D(v.x() / len, v.y() / len);
    return ret;
}

// ベクトル内積
double dot_product(Vector2D vl, Vector2D vr)
{
    return vl.x() * vr.x() + vl.y() * vr.y();
}

//交差判定
bool isCross(float ax, float ay, float bx, float by,
             float cx, float cy, float dx, float dy)
{
    float ta = (cx - dx) * (ay - cy) + (cy - dy) * (cx - ax);
    float tb = (cx - dx) * (by - cy) + (cy - dy) * (cx - bx);
    float tc = (ax - bx) * (cy - ay) + (ay - by) * (ax - cx);
    float td = (ax - bx) * (dy - ay) + (ay - by) * (ax - dx);
    return tc * td <= 0 && ta * tb <= 0;
}
