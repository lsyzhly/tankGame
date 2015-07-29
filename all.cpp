#include "all.h"
direct operator!(direct drt)
{
    switch (drt)
    {
    case up:
        return down;
        break;
    case down:
        return up;
        break;
    case left:
        return right;
        break;
    case right:
        return left;
        break;
    default:
        break;
    }
}
