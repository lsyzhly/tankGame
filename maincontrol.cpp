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
#define ARRAYSIZE 32
#define BUFFSIZE 64
std::map<pointer,int> to_delete;
int level=1;
MEMSTRUCT<BUFFSIZE>*OnTimeMap=(MEMSTRUCT<BUFFSIZE>*)calloc(sizeof(MEMSTRUCT<BUFFSIZE>),ARRAYSIZE);
typedef list<MEMSTRUCT<BUFFSIZE>*> Mlist;
int score[2];
Mlist OnTimelist;
std::map<cpointer,bool> controls;
std::set<pointer> hasdelete;
std::set<pointer> items;
std::set<pointer> hqitems;
bool is_run;
std::set<pointer> topLevelItem;
int tanks[2]={100,100};
int etanks=0;
int CLevel;

int ertank=20;
unsigned char etank[20];/*={   0,0,0,0,0,0,0,0,0,0,
                            0,0,0,1,1,1,1,2,2,2}*/;


bumpchecker *checker;
void newTank(Tank *tank,Show *a=0);
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
		a->draw->move(-1,-1,state|MOVELEVEL);

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
		if(tanks[1-type]==0)
		{
			setTankState(true,false);
			isgameover=true;
		}
        return;
    }else{
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

void addTanks(bool type){
    tanks[type]++;
}

void addControl(cpointer a)
{
    if(a==0){
        throw a;
    }
    controls[a]=true;
}

void bindbumpchecker(bumpchecker *checker)
{
    ::checker = checker;
    for (std::set<pointer>::iterator ai = items.begin(); ai != items.end(); ai++)
    {
        pointer a = *ai;
        checker->add(a);
    }
    for (std::set<pointer>::iterator ai = topLevelItem.begin();
            ai != topLevelItem.end(); ai++)
    {
        pointer a = *ai;
        checker->add(a);
    }
	//*********************
	 for (std::set<pointer>::iterator ai = hqitems.begin();
            ai != hqitems.end(); ai++)
    {
        pointer a = *ai;
        checker->add(a);
    }
   //*********************
}

void clean()
{
    fprintf(fpi,"cleanitem\n");
    fflush(fpi);
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
    fprintf(fpi,"OnTimeMap\n");
    fflush(fpi);
    for(int i=0; i<ARRAYSIZE; i++)
    {
        if(OnTimeMap[i].count)
            OnTimeMap[i]();
    }
    fprintf(fpi,"OnTimelist\n");
    fflush(fpi);
    for(Mlist::iterator a=OnTimelist.begin();a!=OnTimelist.end();){
        if((**a)()){
            fprintf(fpi,"runed\n");
            fflush(fpi);
            a=OnTimelist.erase(a);
        }else{
            fprintf(fpi,"pass\n");
            fflush(fpi);
            ++a;
        }
    }
    fprintf(fpi,"clean fin\n");
    fflush(fpi);
}

void runControls()
{
    fprintf(fpi,"start run control\n");
    fflush(fpi);
    std::list<cpointer> pset;
    for (std::map<cpointer,bool>::iterator a = controls.begin();
            a != controls.end(); a++)
    {
        if(a->second)
        {
            cpointer ai=a->first;
            TankControl *t=dynamic_cast<TankControl*>(ai);
            if(t){
                fprintf(fpi,"tankcontrol\n");
                fflush(fpi);
            }
            bulletControl *ti=dynamic_cast<bulletControl *>(ai);
            if(ti){
                fprintf(fpi,"BulletControl\n");
                fflush(fpi);
            }
            if(ai==0){
                continue;
            }
            if(ai->run())
            {
                fprintf(fpi,"runControls:remove %p\n",ai);
                fflush(fpi);
                pset.push_back(ai);
            }
        }
    }
    fprintf(fpi,"runControls:removing\n");
    fflush(fpi);
    for (std::list<cpointer>::iterator it = pset.begin();
            it != pset.end(); it++)
    {
        fprintf(fpi,"runControls:removing %p\n",*it);
        fflush(fpi);
        remove(*it);
        fprintf(fpi,"runControls:removed %p\n",*it);
        fflush(fpi);
    }
    fprintf(fpi,"finish runcontrol\n");
    fflush(fpi);
}

void rePaint()
{
    fprintf(fpi,"paint n\n");
    fflush(fpi);
        for (std::set<pointer>::iterator a = items.begin();
                a != items.end(); a++)
        {
            (*a)->draw->Repaint();

        }
    fprintf(fpi,"paint top\n");
    fflush(fpi);
        for (std::set<pointer>::iterator a = topLevelItem.begin();
                a != topLevelItem.end(); a++)
        {
            (*a)->draw->Repaint();

        }
    fprintf(fpi,"paint hq\n");
    fflush(fpi);
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
            if(b->control!=0)remove(b->control);
            b->control=0;
            checker->remove(a);
            addTimeFun((OnTime)reremove,10,a);
            buid++;
            hasdelete.insert(a);
        }else{
            //throw a;
        }
    }else if(c){
        if(hasdelete.find(a)==hasdelete.end()){
            delete c->draw;
            c->draw=new ExplodeShow(2,0);
            c->draw->move(c->x,c->y);
            if(c->control!=0)remove(c->control);
            c->control=0;
            checker->remove(a);
            addTimeFun((OnTime)reremove,5,a);
            taid++;
            hasdelete.insert(a);
        }else{
            //throw a;
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

void freeItem()
{
    for (std::set<pointer>::iterator ai = items.begin(); ai != items.end(); ai++)
    {
        delete *ai;
    }
    for (std::set<pointer>::iterator ai = topLevelItem.begin();
            ai != topLevelItem.end(); ai++)
    {
        delete *ai;
    }
    items.clear();
    topLevelItem.clear();
    OnTimelist.clear();
    delete checker;
}

void freeControl()
{
    for (std::map<cpointer,bool>::iterator a = controls.begin();
            a != controls.end(); a++)
    {
        delete a->first;
    }
    controls.clear();
}

void addTimeFun(unsigned char id,OnTime on,int n,...)
{
    va_list va;
    va_start(va,n);
    OnTimeMap[id].init(on,va,n);
}

void addTimeFun(OnTime on,int n,...)
{
    va_list va;
    va_start(va,n);
    MEMSTRUCT<BUFFSIZE> *a=new MEMSTRUCT<BUFFSIZE>();
    a->init(on,va,n);
    OnTimelist.push_back(a);
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
	theTank->draw->move(-1,-1,(int)stoppable|MOVESTATE);
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
                if(!b->isStoppable){
                    remove(b);
                    remove(b->control);
                }
            }
        }
    }
}

void newTank(Tank *tank,Show *a){
    if(a==0){
        addItem(tank);
        tank->isStoppable=true;
        Show *b=tank->draw;
        tank->draw=new BoreShow(2);
        tank->reShow();
        addTimeFun((OnTime)newTank,70,tank,b);
        ptanks[pcount++&0x1]=tank;
        fflush(fpi);
    }else{
        fprintf(fpi,"read tank%p\n",tank);
        fprintf(fpi,"new tanking\n");
        fflush(fpi);
        tank->isStoppable=false;
        if(tank->control==0){
            throw tank;
        }
        addControl(tank->control);
        fprintf(fpi,"delete draw\n");
        fflush(fpi);
        delete tank->draw;
        tank->draw=a;
        tank->reShow();
        fprintf(fpi,"finish tanking\n");
        fflush(fpi);
    }
}

void addEnemyTank(){
    if(etanks<4){
        fprintf(fpi,"etanks:%d,ertanks:%d\n",etanks,ertank);
        fflush(fpi);
        if(ertank==0){
            if(etanks==0){
                fprintf(fpi,"choosingd\n");
                fflush(fpi);
                addTimeFun(8,(OnTime)ChooseLevel,300,++level);
                etanks=-1;
                return;
            }else{
                return;
            }
        }
        static clock_t cl=clock();
        clock_t clo=clock();
        if(clo-cl>2000){
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
            if(type==2){
                s=new TankBShow(rand_red,2);
                pvalue=2;
                speed=1;
            }else{
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
