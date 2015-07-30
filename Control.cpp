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
UINT player1tank[5]= {VK_UP,VK_RIGHT,VK_DOWN,VK_LEFT,76}; //表示player1的上下左右的虚拟键值up=0, down=2, left=3, right=1,L(fire)
UINT player2tank[5]= {'W','D','S','A',VK_SPACE}; //表示player2的上下左右的虚拟键值 w,s,a,d,space
namespace Controler
{
Control::Control(int maxcount)
{
    this->maxcount=maxcount;
}
Control::~Control()
{
}

autoTankControl::autoTankControl(Tank *tank):Control(tank->speed)
{
    tank->control=this;
    this->tank = tank;
    tank->control = this;
    printf("starting run%p,%p\n", this,this->tank);
    clo=clock();
}

bool autoTankControl::run()
{
    srand(clock());
    unsigned int a = rand()%4;
    unsigned int b = rand() % 50;
    int c = checker->move(tank, tank->drt,maxcount);
    tank->moveDirect((direct)a,c>>8);
    clock_t cloi=clock();
    int n=cloi-clo;
    if(n<200)
    {
        return false;
    }
    clo=clock();
    tank->fire();
    return false;
    if (c&bumpType::astop || b==0)
    {
        c=checker->move(tank, (direct)a,maxcount);
    }
    if(c&bumpType::abandonded)
    {
        return true;
    }
    return false;
}
autoTankControl::~autoTankControl(){
    tank->control=0;
}
playTankControl::playTankControl(item::Tank *tank,int type):Control(tank->speed)
{
    tank->control=this;
    this->tank=tank;
    this->type=type;
    clo=clock();
}
bool playTankControl::run()
{
    direct dir=(direct)-1;
    bool re=false;
    UINT *tmp;
    if(0==type) tmp=player1tank;
    else tmp=player2tank;
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
    if(isKeyDown[tmp[4]])
    {
        clock_t cloi=clock();
        int n=cloi-clo;
        if(n<200)
        {
            return false;
        }
        clo=clock();
        tank->fire();
        return false;
    }
    if(-1!=dir)
    {
        int sta=checker->move(tank,dir,maxcount);
        if(sta&bumpType::abandonded)
        {
            return true;
        }
        return false;
    }
    return false;
}

playTankControl::~playTankControl(){
    tank->control=0;
}
bulletControl::bulletControl(Bullet *a):Control(a->speed)
{
    a->control=this;
    this->bul=a;
}
bool bulletControl::run()
{
    int sta=checker->move(bul,bul->drt,maxcount<<1);
    if(sta&bumpType::abandonded)
    {
        return true;
    }
    return false;
}
bulletControl::~bulletControl()
{
    bul->control=0;
}
}
