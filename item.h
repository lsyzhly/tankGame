#ifndef ITEM_H
#define ITEM_H
#include <set>
#include <list>
#include <vector>
#include "view.h"
#include "BulletShow.h"
#include "all.h"
#include "mainControl.h"
using std::set;
using std::pair;
using Controler::cpointer;
namespace item
{
using view::Show;
typedef std::vector<pos> posSet;
typedef std::list<pointer> sList;
//正方形组件,所有组件的基类,抽象类
class pos{
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
    bool isBump;
    //画图器
    Show *draw;

    square(int x, int y, int size, Show *draw);
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
    moveSquare(int x, int y, int size, Show *draw, direct drt, int speed);
    //向drt方向移动一个单位
    virtual void move(direct drt,int size);
    //碰撞处理函数,返回碰撞类型
    virtual bumpType bump(square *a,direct drt) = 0;
    virtual void reShow();
    virtual void reDirect(direct drt);
    virtual void moveDirect(direct drt,int size=1);
    virtual ~moveSquare();
};
//不可移动正方形
class unmoveSquare :public square
{
public:
    //不可移动类型 可以使tie或tu
    unmoveType utype;
    unmoveSquare(int x, int y, int size,Show *draw, unmoveType utype);
    virtual void reShow();
    virtual ~unmoveSquare();
    virtual posSet *getRange();
};

//Tank类
class Tank :public moveSquare
{
public:
    //发射出子弹的集合
    set<Bullet *> bullet_set;
    //发射子弹的最大数量
    int maxbullets;
    int nowBullets;//点钱子弹数量初始为0
    int pvalue;//生命值
    bool isPlayer;
	bool isStoppable;//设置坦克是否无敌true为是
    Tank(int x, int y, int size, int speed, direct drt,Show *draw,
         int maxbullets,int pvalue, bool isPlayer,bool isStoppable=false,int nowBullets=0);
    //碰撞处理函数
    virtual bumpType bump(square *a,direct drt);
    virtual void reShow();
    //开火
    Bullet *fire();
    virtual ~Tank();
};

class Bullet :public moveSquare
{
public:
    //发出这个子弹的坦克
    Tank *t;
    Bullet(Tank *t, int x, int y, int size,int speed,Show *draw);
    virtual bumpType bump(square *a,direct drt);
    virtual ~Bullet();
};
}
#endif
