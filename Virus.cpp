#include "Virus.h"

using namespace std;

//======================================================================
Virus::Virus(int id, double x, double y, int lifeCounter)
    : _id(id)
{
    _lifeCounter = lifeCounter * 10; // [秒]->[step]
    _position.setXY(x, y);
}

