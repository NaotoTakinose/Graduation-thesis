#include "Wall.h"

//======================================================================
void Wall::initialize(int id,
                      double begin_x, double begin_y,
                      double end_x, double end_y)
{
    _id = id;
    _begin = Vector2D(begin_x, begin_y);
    _end = Vector2D(end_x, end_y);
}
