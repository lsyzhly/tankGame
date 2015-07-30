#ifndef ITEM_H
#define ITEM_H
#include <set>
#include "view.h"
#include "BulletShow.h"
#include "all.h"
using std::set;
using std::pair;
using Controler::cpointer;
typedef set<pair<int, int>> posSet;
namespace item
{
using view::Show;
class Bullet;
//正方形组件,所有组件的基类,抽象类
class square
{
protected:
public:
    //x,y表示正方形位置 size为边长
    int x;
    int y;
    int size;
    bool is_bump;
    //轮廓集合
    posSet pos_set;
    //画图器
    Show *draw;
    //指向轮廓对应点的指针
    set<square**> occupy;

    square(int x, int y, int size, Show *draw);
    //获取对象轮廓
    virtual posSet *getRange();
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
    moveSquare(int x, int y, int size, Show *draw, direct drt, int speed);
    //向drt方向移动一个单位
    virtual void move(direct drt);
    //碰撞处理函数,返回碰撞类型
    virtual bumpType bump(square *a,direct drt) = 0;
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
    //子弹大小
    int bullet_size;
    //子弹速度
    int bullet_speed;
    bool isPlayer;
    Tank(int x, int y, int size, int speed, direct drt,Show *draw,
         int maxbullets,int nowBullets,int pvalue, int bullet_size, int bullet_speed,bool isPlayer);
    //碰撞处理函数
    virtual bumpType bump(square *a,direct drt);
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
