#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

#include <set>
#include <list>
#include <vector>
#include "all.h"
#include "view.h"
using Controler::cpointer;
namespace item
{
typedef std::vector<pos> posSet;
typedef std::list<pointer> sList;
//正方形组件,所有组件的基类,抽象类
class pos
{
public:
    int x:16;
    int y:16;
    pos(int x,int y);
};
class square
{
protected:
public:
    //x,y表示正方形位置 size为边长
    int x;
    int y;
    int size;
    int level;
    //画图器
    view::Show *draw;
    static std::set<square*> squareSet;
    static void rePaint();
    static void deleteAll();
    square(int x, int y, int size, view::Show *draw,int level=0);
    square(int level);
    //获取对象轮廓
    virtual posSet *getRange();
    virtual void reShow();
    virtual ~square();
};
//可移动正方形
class moveSquare :public square
{
public:
    //移动方向
    direct drt;
    //移动速度
    int speed;
    cpointer control;
    int cmdIndex;
    moveSquare(int x, int y, int size, view::Show *draw, direct drt, int speed,int level=0);
    //向drt方向移动一个单位
    void move(direct drt,int size);
    virtual void reShow();
    virtual ~moveSquare();
};
}

namespace std{
template <>
class less<item::square *>
{
public:
    bool operator()(const item::square *a,const item::square *b){
        if(a->level!=b->level){
            return a->level<b->level;
        }else{
            return a->draw<b->draw;
        }
    }
};
}
#endif // SQUARE_H_INCLUDED
