#include "maincontrol.h"
#include "nbumpchecker.h"
#include "Control.h"
#include "fileReader.h"
#include "item.h"
#include "ExplodeShow.h"
#include "PlayerTankShow.h"
#include "enemytankshow.h"
#include "BoreShow.h"
#include "main.h"
#include <list>
#include <stdarg.h>
#define ARRAYSIZE 16
using std::map;
using std::bind;
using std::ptr_fun;
int level=1;
typedef std::pair<std::function<void (void)>,int> TimeFunc;
TimeFunc OnTimeMap[ARRAYSIZE];
int score[2];
std::list<TimeFunc> OnTimelist;
std::set<pointer> hqitems;
bool is_run;
std::set<pointer> topLevelItem;
int tanks[2]= {100,100};
int etanks=0;
int CLevel;

int ertank=20;
unsigned char etank[20];/*={   0,0,0,0,0,0,0,0,0,0,
                            0,0,0,1,1,1,1,2,2,2}*/;


bumpchecker *checker;
void newTank(Tank *tank,Show *a=0);
void add_to_delete(pointer a, int count)
{
    //to_delete[a] = count;
}
//*********************
void addHqItems(pointer a)
{
    hqitems.insert(a);
    if(checker)
        checker->add(a);
}
void setHqState(int state)
{
    std::set<pointer>::iterator ai = hqitems.begin();
    ai++;
    for (; ai != hqitems.end(); ai++)
    {
        pointer a = *ai;
        a->draw->move(-1,-1,state|MOVELEVEL);

    }

}
//*********************
void addItem(pointer a,bool isTop)
{
}

void OnPlayerTank(bool type)
{
    if(tanks[type]==0)
    {
        if(tanks[1-type]==0)
        {
            setTankState(true,false);
            isgameover=true;
        }
        return;
    }
    else
    {
        tanks[type]--;
        Show *s;
        Tank *tank;
        s=new PlayerTankShow(2,type);
        tank=new Tank(4<<type<<4,12<<4,14,2,up,s,1,0,true);
        new playTankControl(tank,type);
        newTank(tank);
        return;
    }
}

void addTanks(bool type)
{
    tanks[type]++;
}

void bindbumpchecker(bumpchecker *checker)
{
    ::checker = checker;
}

void clean()
{
    for(int i=0; i<ARRAYSIZE; i++)
    {
        if(!--OnTimeMap[i].second)
            OnTimeMap[i].first();
    }
    for(std::list<TimeFunc>::iterator a=OnTimelist.begin(); a!=OnTimelist.end();)
    {
        if(--a->second)
        {
            ++a;
        }
        else
        {
            a->first();
            a=OnTimelist.erase(a);
        }
    }
}

void rePaint()
{
}

void remove(pointer a)
{
}
void remove(cpointer a)
{
}

void freeItem()
{

}

void freeControl()
{
}

void addTimeFun(unsigned char id,std::function<void (void )> func,int n)
{
    OnTimeMap[id].first=func;
    OnTimeMap[id].second=n;
}

void addTimeFun(std::function<void (void )> func,int n)
{
    OnTimelist.push_back(make_pair(func,n));
}

void setCapTankState(Tank *theTank,bool stoppable)
{
    theTank->isStoppable=stoppable;
    theTank->draw->move(-1,-1,(int)stoppable|MOVESTATE);
}
void setTankState(bool type,bool is_run)
{
    //tank->control->setRun(is_run);
}
void deleteTank(bool type)
{/*
    for (std::set<pointer>::iterator a = items.begin();
            a != items.end(); a++)
    {
        Tank *b=dynamic_cast<Tank *>(*a);
        if(b)
        {
            if(b->isPlayer==type)
            {
                if(!b->isStoppable)
                {
                    remove(b);
                    remove(b->control);
                }
            }
        }
    }*/
}

void newTank(Tank *tank,Show *a)
{
    if(a==0)
    {
        //addItem(tank);
        tank->isStoppable=true;
        Show *b=tank->draw;
        tank->draw=new BoreShow(2);
        tank->reShow();
        addTimeFun(bind(ptr_fun(newTank),tank,b),70);
        ptanks[pcount++&0x1]=tank;
    }
    else
    {
        tank->isStoppable=false;
        if(tank->control==0)
        {
            throw tank;
        }
        delete tank->draw;
        tank->draw=a;
        tank->reShow();
    }
}

void addEnemyTank()
{
    if(etanks<4)
    {
        if(ertank==0)
        {
            if(etanks==0)
            {
                addTimeFun(8,bind(ptr_fun(ChooseLevel),++level),300);
                etanks=-1;
                return;
            }
            else
            {
                return;
            }
        }
        static clock_t cl=clock();
        clock_t clo=clock();
        if(clo-cl>2000)
        {
            etanks++;
            Show *s;
            Tank *tank;
            int rand_t=rand()%ertank;
            int rand_red=!(rand()&0x7);
            int n=rand()%3;
            int type=etank[rand_t];
            etank[rand_t]=etank[--ertank];
            int pvalue=0;
            int speed=2;
            if(type==2)
            {
                s=new TankBShow(rand_red,2);
                pvalue=2;
                speed=1;
            }
            else
            {
                s=new TankAShow(rand_red,2,type);
                speed+=type;
            }
            tank=new Tank((n*6)<<4,0,14,speed,up,s,1,pvalue,false);
            new autoTankControl(tank);
            newTank(tank);
            cl=clock();
        }
        return;
    }
}
