#include "item.h"
#include "Control.h"
#include "maincontrol.h"
#include <assert.h>
#include "enemytankshow.h"
#include "BonusShow.h"
#ifndef LSY_GCC
#include "sound.h"
#else
#include "lsy_sound.h"
#endif
using std::bind;
using std::ptr_fun;
namespace item
{
unmoveSquare::unmoveSquare(int x, int y, int size,Show *draw, unmoveType utype,int level):square(x,y,size,draw,level)
{
    draw->move(-1,-1,MOVELEVEL|utype);
    this->utype=utype;
}

void unmoveSquare::reShow()
{
    square::reShow();
    draw->move(-1,-1,MOVELEVEL|utype);
}

posSet *unmoveSquare::getRange()
{
    if(utype==cao)
    {
        return new posSet();
    }
    else
    {
        return square::getRange();
    }
}
unmoveSquare::~unmoveSquare()
{
}
Tank::Tank(int x, int y, int size, int speed, direct drt, Show *draw,
        int pvalue, bool isPlayer,bool isStoppable,int level)
    :moveSquare(x,y,size,draw,drt,speed,level)
{
    this->maxbullets = maxbullets;
    this->pvalue = pvalue;
    this->isPlayer=isPlayer;
    this->nowBullets=nowBullets;
    this->isStoppable=false;
    draw->move(-1,-1,MOVELEVEL|pvalue);
}
void Tank::reShow()
{
    moveSquare::reShow();
    draw->move(-1,-1,MOVELEVEL|pvalue);
}
Bullet *Tank::fire()
{
    int TempBulletSpeed=0;
    int tempx=0;
    int tempy=0;
    int tempType=0;
    this->nowBullets=this->nowBullets+1;
    if(isPlayer) maxbullets=(pvalue>>1)+1;
    if(this->nowBullets<=this->maxbullets)
    {
        if(this->isPlayer==true && this->pvalue!=0)
        {
            TempBulletSpeed=1;
        }
        else
        {
            TempBulletSpeed=2;
        }
        Show *temp;

        if(this->drt==up)
        {
            tempx=x+size/2-BULLETSIZE/2;
            tempy=y;
            if(tempy<=0)
            {
                this->nowBullets=this->nowBullets-1;
                return NULL;
            }

            tempType=0;
            //return new Bullet(this,x+size/2-BULLETSIZE/2,y,BULLETSIZE,TempBulletSpeed,temp);
        }
        else if(this->drt==down)
        {
            tempx=x+size/2-BULLETSIZE/2;
            tempy=y+size-BULLETSIZE;
            tempType=2;
            if(tempy+BULLETSIZE>=207)
            {
                this->nowBullets=this->nowBullets-1;
                return NULL;
            }

            //return new Bullet(this,x+size/2-BULLETSIZE/2,y+size,BULLETSIZE,TempBulletSpeed,temp);
        }
        else if(this->drt==left)
        {
            tempx=x;
            tempy=y+size/2-BULLETSIZE/2;
            if(tempx<=0)
            {
                this->nowBullets=this->nowBullets-1;
                return NULL;
            }

            tempType=3;
            //  return new Bullet(this,x,y+size/2-BULLETSIZE/2,BULLETSIZE,TempBulletSpeed,temp);
        }
        else
        {
            tempx=x+size-BULLETSIZE;
            tempy=y+size/2-BULLETSIZE/2;
            if(tempx+BULLETSIZE>=207)
            {
                this->nowBullets=this->nowBullets-1;
                return NULL;
            }
            tempType=1;
            //  return new Bullet(this,x+size,y+size/2-BULLETSIZE/2,BULLETSIZE,TempBulletSpeed,temp);
        }
        temp=new BulletShow(2);//需要new出一个bulletshow指针
        Bullet *myBullet;
        myBullet=new Bullet(this,tempx,tempy,BULLETSIZE,TempBulletSpeed,temp);
        //addItem(myBullet,true);
        bulletControl *myControl=new bulletControl(myBullet);
        std::string tempSound="sound/Gunfire.wav";
        GameSound(hwnd,tempSound);
        // return new Bullet(this,tempx,tempy,BULLETSIZE,TempBulletSpeed,temp);
        return myBullet;
    }
    else
    {
        this->nowBullets=this->nowBullets-1;
    }
}

Tank::~Tank()
{
}

Bullet::Bullet(Tank *t, int x, int y, int size, int speed, Show *draw,int level)
    :moveSquare(x, y, size, draw, t->drt, speed,level)
{
    this->t = t;
}

Bullet::~Bullet()
{
    t->nowBullets--;
}
}
Tank *ptanks[2];
