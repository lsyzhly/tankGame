#include "item.h"
#include "Control.h"
#include "maincontrol.h"
#include "enemytankshow.h"
#include "BonusShow.h"
#ifndef LSY_GCC
#include "sound.h"
#else
#include "lsy_sound.h"
#endif
namespace item
{
square::square(int x, int y, int size,Show *draw)
{
    this->x = x;
    this->y = y;
    this->size = size;
    this->draw = draw;
    draw->move(x, y,0);
    isBump=true;
    fflush(fpi);
}
posSet *square::getRange()
{
    fflush(fpi);
    pos_set.clear();
    fflush(fpi);
    if(isBump){
        for (int i = 0; i < size; i++)
        {
            pos_set.insert(std::make_pair(x + i, y));
            pos_set.insert(std::make_pair(x + i, y + size - 1));
        }
        for (int i = 0; i < size; i++)
        {
            pos_set.insert(std::make_pair(x, y + i));
            pos_set.insert(std::make_pair(x + size - 1, y + i));
        }
    }
    return &pos_set;
}
void square::reShow(){
    draw->move(x, y,0);
}
square::~square()
{
    delete draw;
}
moveSquare::moveSquare(int x, int y, int size,Show *draw, direct drt, int speed) :square(x,y,size,draw)
{
    this->drt = drt;
    this->speed = speed;
    this->control = 0;
    draw->move(-1,-1,MOVESETDIRECT|drt);
}
void moveSquare::move(direct drt)
{
    switch (drt)
    {
    case up:
        y--;
        break;
    case down:
        y++;
        break;
    case left:
        x--;
        break;
    case right:
        x++;
        break;
    default:
        break;
    }
}
void moveSquare::reShow(){
    square::reShow();
    draw->move(-1,-1,MOVESETDIRECT|drt);
}
moveSquare::~moveSquare()
{
    if (control) control->setNull();
}
unmoveSquare::unmoveSquare(int x, int y, int size,Show *draw, unmoveType utype):square(x,y,size,draw)
{
    draw->move(-1,-1,MOVELEVEL|utype);
    this->utype=utype;
}

void unmoveSquare::reShow(){
    square::reShow();
    draw->move(-1,-1,MOVELEVEL|utype);
}

posSet *unmoveSquare::getRange()
{
    if(utype==cao)
    {
        return &pos_set;
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
           int maxbullets, int pvalue, bool isPlayer,bool isStoppable,int nowBullets)
    :moveSquare(x,y,size,draw,drt,speed)
{
    this->maxbullets = maxbullets;
    this->pvalue = pvalue;
    this->isPlayer=isPlayer;
    this->nowBullets=nowBullets;
	this->isStoppable=false;
    draw->move(-1,-1,MOVELEVEL|pvalue);
}
bumpType Tank::bump(square *a,direct drt)
{
    if (a == 0)
    {
        return bumpType::stop;
    }
    unmoveSquare *b=dynamic_cast<unmoveSquare *>(a);//b=0 转换不可移动的墙土失败
    if(b!=0)
    {
        if(b->utype==tu||b->utype==qiang||shui==b->utype||boss==b->utype)
        {
            return bumpType::stop;
        }
        else if (b->utype==cao)
        {
            return bumpType::through;
        }//未进行调试的碰撞道具部分
        else if(b->utype==star)//star part
        {
            if(this->isPlayer==true && this->pvalue<3)
            {
                this->pvalue=this->pvalue+1;
                add_to_delete(a,1);
				std::string tempSound="sound/Fanfare.wav";
		        GameSound(hwnd,tempSound);
                this->draw->move(-1,-1,MOVELEVEL|this->pvalue);
                return bumpType::through;
            }
            else if(this->isPlayer==false && this->pvalue<2)
            {
                //加强敌方坦克
                this->pvalue=this->pvalue+1;
                add_to_delete(a,1);
				std::string tempSound="sound/Fanfare.wav";
		        GameSound(hwnd,tempSound);
                this->draw->move(-1,-1,MOVELEVEL|this->pvalue);
                return bumpType::through;
            }
            else
            {
                add_to_delete(a,1);
                return bumpType::through;
            }
        }
        else if(b->utype==tank)
        {
              std::string tempSound="sound/Fanfare.wav";
		      GameSound(hwnd,tempSound);
			  add_to_delete(a,1);
			  if(this->isPlayer==true)
			  {
				 playTankControl *b=dynamic_cast<playTankControl *>(this->control);
			      if(b)
				  {
					  int temp=b->type;
					  tanks[temp]++;
				  }
			  }
			  return bumpType::through;
        }
        else if(b->utype==myclock)
        {
			add_to_delete(a,1);
			if(this->isPlayer==true)
			{
				setTankState(false,false);
				addTimeFun(0,(OnTime)setTankState,150,false,true);
				std::string tempSound="sound/Fanfare.wav";
		        GameSound(hwnd,tempSound);
                return bumpType::through;
			}
			else
			{
                setTankState(true,false);
				addTimeFun(0,(OnTime)setTankState,150,true,true);
				std::string tempSound="sound/Fanfare.wav";
		        GameSound(hwnd,tempSound);
                return bumpType::through;
			}
        }
        else if(b->utype==cap)
        { //缺少通知图片更改的操作
			add_to_delete(a,1);
            setCapTankState(this,true);
            addTimeFun(1,(OnTime)setCapTankState,150,this,false);
			std::string tempSound="sound/Fanfare.wav";
		    GameSound(hwnd,tempSound);
			return bumpType::through;
        }
        else if(b->utype==shovel)
        {
			if(this->isPlayer==true)
			{
			add_to_delete(a,1);
          //  addTimeFun(3,(OnTime)setBossHome,150);
			std::string tempSound="sound/Fanfare.wav";
		    GameSound(hwnd,tempSound);
			setHqState(qiang);
            addTimeFun(1,(OnTime)setHqState,250,tu);

			return bumpType::through;
			}
			else
            return bumpType::through;
        }
        else
        {
			if(this->isPlayer==true)
			{
			  add_to_delete(a,1);
			  deleteTank(false);
			  std::string tempSound="sound/bang.wav";
		      GameSound(hwnd,tempSound);
              return bumpType::through;
			}
			else
			{
			  add_to_delete(a,1);
			  deleteTank(true);
			  std::string tempSound="sound/bang.wav";
		      GameSound(hwnd,tempSound);
              return bumpType::through;
			}
        }
    }
    Tank *c=dynamic_cast<Tank *>(a);//碰撞的为坦克的转换
    if(c)
    {
        return bumpType::stop;
    }
    Bullet *d=dynamic_cast<Bullet *>(a);//碰撞为子弹的转换未处理子弹碰到无敌坦克
    if(d)
    {
        if(d->t->isPlayer==true && this->isPlayer==true && this->isStoppable==false)
        {
			if(this==d->t)
				return bumpType::through;
			else
			{
                add_to_delete(a,1);
                setTankState(true,false);
                addTimeFun(4,(OnTime)setTankState,100,true,true);
                return bumpType::stop;//暂时将己方定位停止
			}

        }
		if(d->t->isPlayer!=this->isPlayer && this->isStoppable==false)
        {
            //add_to_delete(this,1);
            //add_to_delete(a,1);
            this->pvalue=this->pvalue-1;
            if(this->pvalue==-1)
            {
                add_to_delete(this,1);
                add_to_delete(a,1);
                return bumpType::abandonded;//消失
            }
            else
            {
                add_to_delete(a,1);
                return bumpType::stop;//降级
            }
        }
        if(d->t->isPlayer==false && this->isPlayer==false)
        {
            return bumpType::through;
        }
    }
    return stop;
}
void Tank::reShow(){
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
        addItem(myBullet,true);
        bulletControl *myControl=new bulletControl(myBullet);
        addControl(myControl);
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

void moveSquare::reDirect(direct drt)
{
    this->drt=drt;
    draw->move(-1,-1,MOVESETDIRECT|drt);
}

void moveSquare::moveDirect(direct drt,int size)
{
    this->drt=drt;
    draw->move(-1,-1,MOVEDIRECT|drt|(size<<4));
}
Tank::~Tank()
{
}
Bullet::Bullet(Tank *t, int x, int y, int size, int speed, Show *draw)
    :moveSquare(x, y, size, draw, t->drt, speed)
{
    this->t = t;
}
bumpType Bullet::bump(square *a,direct drt)
{
    if (a == 0)
    {
        add_to_delete(this,1);
        return bumpType::abandonded;
    }
    unmoveSquare *b=dynamic_cast<unmoveSquare *>(a);//b=0 转换不可移动的墙土失败
    if(b)
    {
        if(b->utype==tu)//击中土后消失的情况
        {
            add_to_delete(this,1);
            add_to_delete(a,1);
			std::string tempSound="sound/bang.wav";
		    GameSound(hwnd,tempSound);
            return bumpType::abandonded;
        }
        if(b->utype==qiang && this->t->pvalue==3)//最高等级坦克击中铁
        {
            add_to_delete(this,1);
            add_to_delete(a,1);
			std::string tempSound="sound/bang.wav";
		    GameSound(hwnd,tempSound);
            return bumpType::abandonded;
        }
        if(b->utype==shui || b->utype==cao)
        {
            return bumpType::through;
        }
        if(b->utype==boss)
        {
            add_to_delete(this,1);
			b->draw->move(-1,-1,1|MOVESTATE);
			std::string tempSound="sound/bang.wav";
		    GameSound(hwnd,tempSound);
            return bumpType::abandonded;
        }
        if(b->utype==qiang && this->t->pvalue!=3)
        {
            add_to_delete(this,1);
			std::string tempSound="sound/hit.wav";
		    GameSound(hwnd,tempSound);
            return bumpType::abandonded;
        }
		if(b->utype==star||b->utype==tank||b->utype==bomp||b->utype==myclock||b->utype||b->utype==cap||b->utype==shovel)
			return bumpType::through;
    }
    Tank *c=dynamic_cast<Tank *>(a);//子弹碰到坦克
    if(c)
    {
		if(this->t->isPlayer==true && c->isPlayer==true)
        {
			if(this->t!=c)
			{
                add_to_delete(this,1);
                setTankState(true,false);
                addTimeFun(4,(OnTime)setTankState,100,true,true);
                std::string tempSound="sound/hit.wav";
                GameSound(hwnd,tempSound);
                return bumpType::abandonded;

			}else
                  return bumpType::through;
        }
        if(this->t->isPlayer==false && c->isPlayer==false)
        {
            return bumpType::through;
        }
		if(this->t->isPlayer!=c->isPlayer && c->isStoppable==false)// enemy and player reduce HP
        {
			TankAShow *p1=dynamic_cast<TankAShow *>(c->draw);
            TankBShow *p2=dynamic_cast<TankBShow *>(c->draw);
			if(p1||p2)
			{
				int tempX=(c->x)-30;
				int tempY=(c->y)+20;
				int tempB=rand()%6+6;
				if(tempX<0)
				{
                    tempX=0;
				}
				if(tempY>168)
				{
					tempY=168;
				}
				if(p1!=0)
				{
                if(p1->is_red==true)
				{
					p1->is_red=false;
					BonusShow *tempBonusShow=new BonusShow(2);
				    unmoveSquare *tempBonus=new unmoveSquare (tempX,tempY,16,tempBonusShow,(unmoveType)tempB);
				    addItem(tempBonus,true);
				}
				}
				if(p2!=0)
				{
				if(p2->is_red==true)
				{
					p2->is_red=false;
					BonusShow *tempBonusShow=new BonusShow(2);
				    unmoveSquare *tempBonus=new unmoveSquare (tempX,tempY,16,tempBonusShow,(unmoveType)tempB);
				    addItem(tempBonus);
				}
				}

			}
            c->pvalue=c->pvalue-1;
            if(c->pvalue==-1)
            {
                add_to_delete(this,1);
                add_to_delete(a,1);
				std::string tempSound="sound/bang.wav";
		        GameSound(hwnd,tempSound);
                return bumpType::abandonded;
            }

            add_to_delete(this,1);
			std::string tempSound="sound/hit.wav";
		    GameSound(hwnd,tempSound);
            c->draw->move(-1,-1,MOVELEVEL|c->pvalue);
            return bumpType::abandonded;
        }
		if(this->t->isPlayer!=c->isPlayer && c->isStoppable==true)
		{
           add_to_delete(this,1);
		   std::string tempSound="sound/hit.wav";
		   GameSound(hwnd,tempSound);
		   return bumpType::abandonded;
		}
    }
    Bullet *d=dynamic_cast<Bullet *>(a);
    if(d)
    {
        if(this->t->isPlayer==d->t->isPlayer)// same side
        {
            return bumpType::through;
        }
        else
        {
            add_to_delete(this,1);
            add_to_delete(a,1);
            return bumpType::abandonded;
        }
    }
    return stop;
}

Bullet::~Bullet()
{
    t->nowBullets--;
}
}
Tank *ptanks[2];
