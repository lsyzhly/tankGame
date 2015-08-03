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
#include "bumpcheck.h"
extern UINT player1tank[5];//��ʾplayer1����������,fire�������ֵ
extern UINT player2tank[5];//��ʾplayer2����������,fire�������ֵ
namespace Controler
{
using std::map;
using std::vector;
using std::set;
using std::list;
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
    Control(int maxcount);
public:
    //�ƶ�һ�δ��鷽��
    virtual bool run() = 0;
    virtual void setNull()=0;
    virtual ~Control();
};
class TankControl :public Control{
    public:
    Tank *tank;
    TankControl(Tank *tank);
    virtual void setNull();
};

//̹���Զ�������,���ڿ�����ͨ�ط�̹��
//TODO ��ӿ�����
class autoTankControl :public TankControl
{
public:
    clock_t clo;
    autoTankControl(Tank *tank);
    virtual bool run();
    virtual ~autoTankControl();
};
class playTankControl:public TankControl
{
public:
    //int flg;//������־ˢ�µ�Ƶ������ʾ�ٶ�
    int type;//0��ʾplayer1,1��ʾplayer2
    playTankControl(Tank *tank,int type);
    clock_t clo;
    virtual bool run();
    virtual ~playTankControl();
};
class bulletControl:public Control
{
public:
    Bullet *bul;
    bulletControl(Bullet *bul);
    virtual void setNull();
    virtual ~bulletControl();
    virtual bool run();
};
class autoPlayTankControl:public playTankControl{
    public:
    autoPlayTankControl(Tank *tank,int type);
    virtual bool run();
};
}
#endif
