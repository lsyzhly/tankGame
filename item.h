#ifndef ITEM_H
#define ITEM_H
#include <set>
#include <list>
#include <vector>
#include "view.h"
#include "BulletShow.h"
#include "all.h"
#include "mainControl.h"
#include "square.h"
#define PLAY_TANK_LEVEL 1
#define ENEMY_TANK_LEVEL 3
#define HQ_LEVEL 4
#define WATER_LEVEL -1
#define CAO_LEVEL 5;
namespace item
{
//不可移动正方形
class unmoveSquare :public square
{
public:
    //不可移动类型 可以使tie或tu
    unmoveType utype;
    unmoveSquare(int x, int y, int size,view::Show *draw,
                 unmoveType utype,int level=0);
    virtual void reShow();
    virtual ~unmoveSquare();
    virtual posSet *getRange();
};

//Tank类
class Tank :public moveSquare
{
public:
    //发射出子弹的集合
    std::set<Bullet *> bullet_set;
    //发射子弹的最大数量
    int maxbullets;
    int nowBullets;//点钱子弹数量初始为0
    int pvalue;//生命值
    bool isPlayer;
    bool isStoppable;//设置坦克是否无敌true为是
    Tank(int x, int y, int size, int speed, direct drt,Show *draw,
         int pvalue, bool isPlayer,bool isStoppable=false,int level=0);
    //碰撞处理函数
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
    Bullet(Tank *t, int x, int y, int size,int speed,Show *draw,int level=0);
    virtual ~Bullet();
};
}
#endif
