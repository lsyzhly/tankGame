#include "maincontrol.h"
#include "bumpcheck.h"
#include "Control.h"
#include "item.h"
#include <list>
#include <stdarg.h>
#include <tuple>
#define ARRAYSIZE 16
#define BUFFSIZE 64
std::map<pointer,int> to_delete;
MEMSTRUCT<BUFFSIZE>*OnTimeMap=(MEMSTRUCT<BUFFSIZE>*)calloc(sizeof(MEMSTRUCT<BUFFSIZE>),ARRAYSIZE);
std::map<cpointer,bool> controls;
std::set<pointer> items;
bool is_run;
std::set<pointer> topLevelItem;
bumpchecker *checker;
void add_to_delete(pointer a, int count)
{
    to_delete[a] = count;
}

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

}
void remove(pointer a)
{
    items.erase(a);
    topLevelItem.erase(a);
    checker->remove(a);
    delete a;
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
