#include "Control.h"
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <istream>
#include "main.h"
#include <iterator>
#include <fstream>
#include "maincontrol.h"
#include "view.h"
#include "item.h"
#include <Windows.h>
#include  <list>
using std::bind;
using std::ptr_fun;
UINT player1tank[5]= {VK_UP,VK_RIGHT,VK_DOWN,VK_LEFT,76}; //表示player1的上下左右的虚拟键值up=0, down=2, left=3, right=1,L(fire)
UINT player2tank[5]= {'W','D','S','A',VK_SPACE}; //表示player2的上下左右的虚拟键值 w,s,a,d,space
namespace Controler
{
Control::Control(int maxcount)
{
    this->maxcount=maxcount;
}

void Control::setRun(bool is_run){
    this->is_run=is_run;
}

void Control::control(){
    if(is_run){
        run();
    }
}

Control::~Control()
{
}

TankControl::TankControl(Tank *tank):Control(tank->speed)
{
    this->tank=tank;
    tank->control=this;
}

autoTankControl::autoTankControl(Tank *tank):TankControl(tank)
{
    clo=clock();
}

void autoTankControl::run()
{
    unsigned int a = rand()%3;
    unsigned int b = rand() % 500;
    unsigned int d=rand()%5;
    if(d==1)
    {
        tank->fire();
    }
    Cmd &cmd=(*checker)[tank];
    if(cmd.msize!=cmd.rsize){
        if(a>=tank->drt){
            tank->drt=(direct)++a;
        }else{
            tank->drt=(direct)a;
        }
    }
    cmd.msize=maxcount;
}

autoTankControl::~autoTankControl()
{
    etanks--;
    if(tank)
    {
        assert(0);
        tank->control=0;
    }
}

playTankControl::playTankControl(item::Tank *tank,int type):TankControl(tank)
{
    this->type=type;
    clo=clock();
}

void playTankControl::run()
{

    direct dir=wrong;
    UINT *tmp;
    if(0==type) tmp=player1tank;
    else tmp=player2tank;
    if(isKeyDown[tmp[4]])
    {
       clock_t cloi=clock();
       int n=cloi-clo;
       if(n>200)
       {
           clo=clock();
           tank->fire();
       }
    }
    if(isKeyDown[tmp[up]])
    {
       dir=up;
    }
    else if(isKeyDown[tmp[down]])
    {
       dir=down;
    }
    else if(isKeyDown[tmp[left]])
    {
       dir= left;
    }
    else if(isKeyDown[tmp[right]])
    {
       dir=right;
    }
    if(-1!=dir)
    {
       Cmd &a=(*checker)[tank];
       a.drt=dir;
       a.msize=maxcount;
    }
}

playTankControl::~playTankControl()
{
    if(tank)
    {
        tank->control=0;
    }
    static int n=0;
    addTimeFun(n++&0x1,bind(ptr_fun(OnPlayerTank),type),10);
}
bulletControl::bulletControl(Bullet *a):Control(a->speed)
{
    a->control=this;
    this->bul=a;
}

void bulletControl::run()
{
    Cmd &a=(*checker)[bul];
    a.drt=bul->drt;
    a.msize=maxcount=3;
}
bulletControl::~bulletControl()
{
    if(bul)
    {
        bul->control=0;
    }
}
}
