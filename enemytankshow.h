#ifndef EME_H
#define EME_H
#include "view.h"

namespace view
{
class TankAShow:public Show
{
public:
    bool is_red;
    bool is_fast;
    int counts;
    int countss;
    int drt;
    TankAShow(bool is_red,int rat,bool is_fast);
    virtual void Repaint();
    //...is the direct of tank(int)
    virtual void move(int x, int y,int n);
};
class TankBShow:public Show
{
public:
    bool is_red;
    int counts;
    int countss;
    int drt;
    unsigned char pvalue;
    TankBShow(bool is_red,int rat);
    virtual void Repaint();
    //... is int the first 4 bits is direct
    //and the second 4 bits is level
    virtual void move(int x, int y,int n);
};
}
#endif
