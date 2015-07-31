#ifndef ITEM_H
#define ITEM_H
#include <set>
#include <list>
#include <forward_list>
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
typedef set<pair<int, int>> posSet;
typedef std::forward_list<square *> sList;
//���������,��������Ļ���,������
class square
{
protected:
public:
    //x,y��ʾ������λ�� sizeΪ�߳�
    int x;
    int y;
    int size;
    bool isBump;
    //��������
    posSet pos_set;
    //��ͼ��
    Show *draw;
    //ָ��������Ӧ���ָ��
    set<sList *> occupy;

    square(int x, int y, int size, Show *draw);
    //��ȡ��������
    virtual posSet *getRange();
    virtual ~square();
};
//���ƶ�������
class moveSquare :public square
{
public:
    //�ƶ�����
    direct drt;
    //�ƶ��ٶ�
    int speed;
    cpointer control;
    moveSquare(int x, int y, int size, Show *draw, direct drt, int speed);
    //��drt�����ƶ�һ����λ
    virtual void move(direct drt);
    //��ײ������,������ײ����
    virtual bumpType bump(square *a,direct drt) = 0;
    virtual void reDirect(direct drt);
    virtual void moveDirect(direct drt,int size=1);
    virtual ~moveSquare();
};
//�����ƶ�������
class unmoveSquare :public square
{
public:
    //�����ƶ����� ����ʹtie��tu
    unmoveType utype;
    unmoveSquare(int x, int y, int size,Show *draw, unmoveType utype);
    virtual ~unmoveSquare();
    virtual posSet *getRange();
};

//Tank��
class Tank :public moveSquare
{
public:
    //������ӵ��ļ���
    set<Bullet *> bullet_set;
    //�����ӵ����������
    int maxbullets;
    int nowBullets;//��Ǯ�ӵ�������ʼΪ0
    int pvalue;//����ֵ
    bool isPlayer;
	bool isStoppable;//����̹���Ƿ��޵�trueΪ��
    Tank(int x, int y, int size, int speed, direct drt,Show *draw,
         int maxbullets,int pvalue, bool isPlayer,bool isStoppable=false);
    //��ײ������
    virtual bumpType bump(square *a,direct drt);
    //����
    Bullet *fire();
    virtual ~Tank();
};

class Bullet :public moveSquare
{
public:
    //��������ӵ���̹��
    Tank *t;
    Bullet(Tank *t, int x, int y, int size,int speed,Show *draw);
    virtual bumpType bump(square *a,direct drt);
    virtual ~Bullet();
};
}
#endif
