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
//�����ƶ�������
class unmoveSquare :public square
{
public:
    //�����ƶ����� ����ʹtie��tu
    unmoveType utype;
    unmoveSquare(int x, int y, int size,view::Show *draw,
                 unmoveType utype,int level=0);
    virtual void reShow();
    virtual ~unmoveSquare();
    virtual posSet *getRange();
};

//Tank��
class Tank :public moveSquare
{
public:
    //������ӵ��ļ���
    std::set<Bullet *> bullet_set;
    //�����ӵ����������
    int maxbullets;
    int nowBullets;//��Ǯ�ӵ�������ʼΪ0
    int pvalue;//����ֵ
    bool isPlayer;
    bool isStoppable;//����̹���Ƿ��޵�trueΪ��
    Tank(int x, int y, int size, int speed, direct drt,Show *draw,
         int pvalue, bool isPlayer,bool isStoppable=false,int level=0);
    //��ײ������
    virtual void reShow();
    //����
    Bullet *fire();
    virtual ~Tank();
};

class Bullet :public moveSquare
{
public:
    //��������ӵ���̹��
    Tank *t;
    Bullet(Tank *t, int x, int y, int size,int speed,Show *draw,int level=0);
    virtual ~Bullet();
};
}
#endif
