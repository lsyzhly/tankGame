#ifndef CONTROL_H
#define CONTROL_H
#include <map>
#ifdef CPP11
#include <mutex>
#include <thread>
using std::thread;
using std::mutex;
#endif
#include <list>
#include <time.h>
#include <vector>
#include <set>
#include "item.h"
#include "nbumpchecker.h"
extern UINT player1tank[5];//��ʾplayer1����������,fire�������ֵ
extern UINT player2tank[5];//��ʾplayer2����������,fire�������ֵ
namespace Controler
{
using item::Tank;
using item::mpointer;
using item::pointer;
using item::Bullet;
using bump::bumpchecker;
//������������
//movesquare�������ƶ�
//Control�ฺ������ƶ�
class Control
{
protected:
    int maxcount;
    bool is_run;
    Control(int maxcount);
public:
    //�ƶ�һ�δ��鷽��
    virtual void run() = 0;
    void setRun(bool);
    void control();
    virtual ~Control();
};
class TankControl :public Control
{
public:
    Tank *tank;
    TankControl(Tank *tank);
};

//̹���Զ�������,���ڿ�����ͨ�ط�̹��
//TODO ��ӿ�����
class autoTankControl :public TankControl
{
public:
    clock_t clo;
    autoTankControl(Tank *tank);
    virtual void run();
    virtual ~autoTankControl();
};
class playTankControl:public TankControl
{
public:
    //int flg;//������־ˢ�µ�Ƶ������ʾ�ٶ�
    int type;//0��ʾplayer1,1��ʾplayer2
    playTankControl(Tank *tank,int type);
    clock_t clo;
    virtual void run();
    virtual ~playTankControl();
};
class bulletControl:public Control
{
public:
    Bullet *bul;
    bulletControl(Bullet *bul);
    virtual ~bulletControl();
    virtual void run();
};
}
#endif
