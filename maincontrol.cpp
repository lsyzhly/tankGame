#include "maincontrol.h"
#include "bumpcheck.h"
#include "Control.h"
#include "item.h"
#include "ExplodeShow.h"
#include "PlayerTankShow.h"
#include "enemytankshow.h"
#include <list>
#include <stdarg.h>
#define ARRAYSIZE 16
#define BUFFSIZE 64
std::map<pointer,int> to_delete;
MEMSTRUCT<BUFFSIZE>*OnTimeMap=(MEMSTRUCT<BUFFSIZE>*)calloc(sizeof(MEMSTRUCT<BUFFSIZE>),ARRAYSIZE);
std::map<cpointer,bool> controls;
std::set<pointer> hasdelete;
std::set<pointer> items;
std::set<pointer> hqitems;
bool is_run;
std::set<pointer> topLevelItem;
int tanks[2]={100,100};
int etanks=0;
unsigned char etank[20]={   0,0,0,0,0,0,0,0,0,0,
                            0,0,0,1,1,1,1,2,2,2};
int ertank=20;
bumpchecker *checker;
void add_to_delete(pointer a, int count)
{
    to_delete[a] = count;
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
	 for (;ai != hqitems.end(); ai++)
    {
        pointer a = *ai;
		a->draw->move(-1,-1,state);

    }

}
//*********************
void addItem(pointer a,bool isTop)
{
    if (isTop)
    {
        topLevelItem.insert(a);
    }
    else
    {
        items.insert(a);
    }
    if (checker)
    {
        checker->add(a);
    }
}

void OnPlayerTank(bool type){
    if(tanks[type]==0){
        return;
    }else{
        tanks[type]--;
        Show *s;
        Tank *tank;
        Control *b;
        s=new PlayerTankShow(2,type);
        tank=new Tank(4<<type<<4,12<<4,14,2,up,s,1,0,true);
        b=new playTankControl(tank,type);
        addControl(b);
        addItem(tank);
        return;
    }
}

void addTanks(bool type){
    tanks[type]++;
}

void addControl(cpointer a)
{
    controls[a]=true;
}

void bindbumpchecker(bumpchecker *checker)
{
    ::checker = checker;
    for (std::set<pointer>::iterator ai = items.begin(); ai != items.end(); ai++)
    {
        pointer a = *ai;
        if(!checker->add(a))
        {
            throw a;
        }
    }
    for (std::set<pointer>::iterator ai = topLevelItem.begin();
            ai != topLevelItem.end(); ai++)
    {
        pointer a = *ai;
        if(!checker->add(a))
        {
            throw a;
        }
    }
	//*********************
	 for (std::set<pointer>::iterator ai = hqitems.begin();
            ai != hqitems.end(); ai++)
    {
        pointer a = *ai;
        if(!checker->add(a))
        {
            throw a;
        }
    }
   //*********************
}

void clean()
{
    std::list<pointer> pset;
    for (std::map<pointer, int>::iterator it = to_delete.begin();
            it != to_delete.end(); it++)
    {
        if (--it->second<=0)
        {
            pset.push_back(it->first);
        }
    }
    for (std::list<pointer>::iterator it = pset.begin();
            it != pset.end(); it++)
    {
        to_delete.erase(*it);
        remove(*it);
    }
    for(int i=0; i<ARRAYSIZE; i++)
    {
        if(OnTimeMap[i].count)
            OnTimeMap[i]();
    }
}

void runControls()
{
    std::list<cpointer> pset;
    for (std::map<cpointer,bool>::iterator a = controls.begin();
            a != controls.end(); a++)
    {
        if(a->second)
        {
            cpointer ai=a->first;
            if(ai->run())
            {
                pset.push_back(ai);
            }
        }
    }
    for (std::list<cpointer>::iterator it = pset.begin();
            it != pset.end(); it++)
    {
        remove(*it);
    }
}

void rePaint()
{
    for (std::set<pointer>::iterator a = items.begin();
            a != items.end(); a++)
    {
        (*a)->draw->Repaint();
    }
    for (std::set<pointer>::iterator a = topLevelItem.begin();
            a != topLevelItem.end(); a++)
    {
        (*a)->draw->Repaint();
    }
	//*********************
     for (std::set<pointer>::iterator a = hqitems.begin();
            a != hqitems.end(); a++)
    {
        (*a)->draw->Repaint();
    }
	//*********************

}

void reremove(pointer a){
    items.erase(a);
    topLevelItem.erase(a);
	//*********************
	//*********************
    checker->remove(a);
    delete a;
    hasdelete.erase(a);
}

void remove(pointer a)
{
    a->isBump=false;
    Tank *b=dynamic_cast<Tank *>(a);
    Bullet *c=dynamic_cast<Bullet *>(a);
    static int buid=0;
    static int taid=0;
    if(b){
        if(hasdelete.find(a)==hasdelete.end()){
            delete b->draw;
            b->draw=new ExplodeShow(2,1);
            b->draw->move(b->x,b->y);
            remove(b->control);
            if(b->control!=0)remove(b->control);
            checker->remove(a);
            addTimeFun(buid&3|8|4,(OnTime)reremove,10,a);
            buid++;
            hasdelete.insert(a);
        }
    }else if(c){
        if(hasdelete.find(a)==hasdelete.end()){
            delete c->draw;
            c->draw=new ExplodeShow(2,0);
            c->draw->move(c->x,c->y);
            if(c->control!=0)remove(c->control);
            checker->remove(a);
            addTimeFun(taid&3|8,(OnTime)reremove,5,a);
            taid++;
            hasdelete.insert(a);
        }
    }else{
        items.erase(a);
        topLevelItem.erase(a);
		hqitems.erase(a);
        checker->remove(a);
        delete a;
    }
}
void remove(cpointer a)
{
    controls.erase(a);
    delete a;
}

void freeAll()
{
    delete checker;
}

void addTimeFun(unsigned char id,OnTime on,int n,...)
{
    va_list va;
    va_start(va,n);
    OnTimeMap[id].init(on,va,n);
}

void setTankState(bool is,bool is_run)
{
    for (std::set<pointer>::iterator a = items.begin();
            a != items.end(); a++)
    {
        Tank *b=dynamic_cast<Tank *>(*a);
        if(b)
        {
            if(b->isPlayer==is)
            {
                controls[b->control]=is_run;
            }
        }
    }
}
void setCapTankState(Tank *theTank,bool stoppable)
{
	theTank->isStoppable=stoppable;
	//theTank->draw->move(-1,-1,)
}
void setTankState(Tank *tank,bool is_run){
    controls[tank->control]=is_run;
}
void deleteTank(bool type){
    for (std::set<pointer>::iterator a = items.begin();
            a != items.end(); a++)
    {
        Tank *b=dynamic_cast<Tank *>(*a);
        if(b)
        {
            if(b->isPlayer==type)
            {
                delete b->control;
                delete b;
            }
        }
    }
}

void addEnemyTank(){
    if(etanks<4){
        if(ertank==0){
            //TODO OnWin
            return;
        }
        static clock_t cl=clock();
        clock_t clo=clock();
        if(clo-cl>2000){
            etanks++;
            Show *s;
            Tank *tank;
            Control *b;
            int rand_t=rand()%ertank;
            int rand_red=!(rand()&0x7);
            int n=rand()%3;
            int type=etank[rand_t];
            etank[rand_t]=etank[--ertank];
            int pvalue=0;
            int speed=2;
            if(type==2){
                s=new TankBShow(rand_red,2);
                pvalue=2;
                speed=1;
            }else{
                s=new TankAShow(rand_red,2,type);
                speed+=type;
            }
            tank=new Tank((n*6)<<4,0,14,speed,up,s,1,pvalue,false);
            b=new autoTankControl(tank);
            addControl(b);
            addItem(tank);
            cl=clock();
        }
        return;
    }
}
