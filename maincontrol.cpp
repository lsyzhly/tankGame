#include "maincontrol.h"
#include "nbumpchecker.h"
#include "Control.h"
#include "fileReader.h"
#include <assert.h>
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


bumpchecker *checker=0;
void newTank(Tank *tank,Show *a=0);
void add_to_delete(pointer a, int count)
{
    //to_delete[a] = count;
}
template <typename ...Arg>
void addHqItems(Arg ...arg)
{
    new unmoveSquare(arg...,HQ_LEVEL);
}

void setHqState(unmoveType state)
{
    item::square *a=new item::square(HQ_LEVEL);
    auto b=item::square::squareSet.find(a);
    auto c=b;
    while(1){
        if(b==item::square::squareSet.end()) break;
        item::square *s=*b++;
        if(s->level!=HQ_LEVEL){
            break;
        }
        item::unmoveSquare *na=dynamic_cast<item::unmoveSquare *>(s);
        assert(na!=0);
        na->utype=state;
    }
}

void OnPlayerTank(bool type)
{
    if(tanks[type]==0)
    {
        if(tanks[!type]==0)
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
        tank=new Tank(4<<type<<4,12<<4,14,2,up,s,1,true);
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
    for(item::square *a:item::square::squareSet){
        checker->add(a);
    }
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

void addTimeFun(unsigned char id,std::function<void (void )> func,int n)
{
    assert(id<ARRAYSIZE);
    OnTimeMap[id].first=func;
    OnTimeMap[id].second=n;
}

void addTimeFun(std::function<void (void )> func,int n)
{
    OnTimelist.push_back(make_pair(func,n));
}

void setTankState(bool type,bool is_run)
{
    int level=type?PLAY_TANK_LEVEL:ENEMY_TANK_LEVEL;
    item::square *a=new item::square(level);
    auto b=item::square::squareSet.find(a);
    auto c=b;
    while(1){
        if(b==item::square::squareSet.end()) break;
        item::square *sa=*b++;
        if(sa->level!=level){
            break;
        }else{
            Tank *a=dynamic_cast<Tank *>(sa);
            assert(a!=0);
            a->control->setRun(is_run);
        }
    }
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
        tank->isStoppable=true;
        Show *b=tank->draw;
        tank->draw=new BoreShow(2);
        tank->reShow();
        addTimeFun(bind(ptr_fun(newTank),tank,b),70);
        tank->control->setRun(false);
    }
    else
    {
        tank->isStoppable=false;
        tank->control->setRun(true);
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
            //����
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
