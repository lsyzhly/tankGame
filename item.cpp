#include "item.h"
#include "Control.h"
#include "maincontrol.h"
namespace item{
	square::square(int x, int y, int size,Show *draw){
		this->x = x;
		this->y = y;
		this->size = size;
		this->draw = draw;
		draw->move(x, y,0);
	}
	posSet *square::getRange(){
		pos_set.clear();
		for (int i = 0; i < size; i++){
			pos_set.insert(std::make_pair(x + i, y));
			pos_set.insert(std::make_pair(x + i, y + size - 1));
		}
		for (int i = 0; i < size; i++){
			pos_set.insert(std::make_pair(x, y + i));
			pos_set.insert(std::make_pair(x + size - 1, y + i));
		}
		return &pos_set;
	}
	square::~square(){}
	moveSquare::moveSquare(int x, int y, int size,Show *draw, direct drt, int speed) :square(x,y,size,draw){
		this->drt = drt;
		this->speed = speed;
		this->control = 0;
		draw->move(-1,-1,MOVESETDIRECT|drt);
	}
	void moveSquare::move(direct drt){
		switch (drt)
		{
		case up:
			y++;
			break;
		case down:
			y--;
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
	moveSquare::~moveSquare(){
		if (control) delete control;
	}
	unmoveSquare::unmoveSquare(int x, int y, int size,Show *draw, unmoveType utype):square(x,y,size,draw)
	{
        this->utype=utype;
	}
	unmoveSquare::~unmoveSquare(){
	}
	Tank::Tank(int x, int y, int size, int speed, direct drt, Show *draw,
        int maxbullets, int pvalue, int bullet_size, int bullet_speed,bool isPlayer)
		:moveSquare(x,y,size,draw,drt,speed)
	{
		this->maxbullets = maxbullets;
		this->pvalue = pvalue;
		this->bullet_size = bullet_size;
		this->bullet_speed = bullet_speed;
		this->isPlayer=isPlayer;
	}
	bumpType Tank::bump(square *a,direct drt){
		if (a == 0){
			return bumpType::stop;
		}
		unmoveSquare *b=dynamic_cast<unmoveSquare *>(a);//b=0 ת�������ƶ���ǽ��ʧ��
		if(b!=0)
		{
			if(b->utype==tu||b->utype==qiang||shui==b->utype||boss==b->utype)
			{
				return bumpType::stop;
			}
			else// (b->utype==cao)
			{
				return bumpType::through;
			}
		}
		Tank *c=dynamic_cast<Tank *>(a);//��ײ��Ϊ̹�˵�ת��
		if(c)
		{
            return bumpType::stop;
		}
        Bullet *d=dynamic_cast<Bullet *>(a);//��ײΪ�ӵ���ת��
		if(d)
		{
			if(d->t->isPlayer==true && this->isPlayer==true)
			{
				add_to_delete(a,1);
				return bumpType::stop;//��ʱ��������λֹͣ
			}
			if(d->t->isPlayer!=this->isPlayer)
			{
				//add_to_delete(this,1);
				//add_to_delete(a,1);
				this->pvalue=this->pvalue-1;
				if(this->pvalue==-1)
				{
					add_to_delete(this,1);
					add_to_delete(a,1);
					return bumpType::abandonded;//��ʧ
				}
				else
				{
					add_to_delete(a,1);
                    return bumpType::stop;//����
				}		
			}
			if(d->t->isPlayer==false && this->isPlayer==false)
			{
               return bumpType::through;
			}
		}
		return stop;
	}

	Bullet *Tank::fire(){
		return new Bullet(this,x+size/2-bullet_size/2,y+size/2-bullet_size/2,bullet_size,bullet_speed,0);
	}

    void Tank::reDirect(direct drt){
        this->drt=drt;
        draw->move(-1,-1,(pvalue<<4)|drt);
    }

	Tank::~Tank(){
		for (set<Bullet *>::iterator ai=bullet_set.begin();ai!=bullet_set.end();ai++){
			Bullet *a=*ai;
			delete a;
		}
	}
	Bullet::Bullet(Tank *t, int x, int y, int size, int speed, Show *draw)
		:moveSquare(x, y, size, draw, t->drt, speed)
	{
		this->t = t;
	}
	bumpType Bullet::bump(square *a,direct drt)
	{
		if (a == 0){
			add_to_delete(this,1);
			return bumpType::abandonded;
		}
       unmoveSquare *b=dynamic_cast<unmoveSquare *>(a);//b=0 ת�������ƶ���ǽ��ʧ��
	   if(b)
	   {
		   if(b->utype==tu)//����������ʧ�����
		   {
			 add_to_delete(this,1);
			 add_to_delete(a,1);
             return bumpType::abandonded;
		   }
		   if(b->utype==qiang && this->t->pvalue==3)//��ߵȼ�̹�˻�����
		   {
              add_to_delete(this,1);
			  add_to_delete(a,1);
              return bumpType::abandonded;
		   }
		   if(b->utype==shui && b->utype==cao)
		   {
			   return bumpType::through;
		   }
		   if(b->utype==boss)
		   {
             add_to_delete(this,1);
			 add_to_delete(a,1);
             return bumpType::abandonded;
		   }
		   if(b->utype==qiang && this->t->pvalue!=3)
		   {
               add_to_delete(this,1);
			   return bumpType::abandonded;
		   }
	   }
	   Tank *c=dynamic_cast<Tank *>(a);//�ӵ�����̹��
	   if(c)
	   {
		   if(this->t->isPlayer==true && c->isPlayer==true)
		   {
			   add_to_delete(this,1);
			   //todo ��̹�˵Ĵ���ȫ
               return bumpType::abandonded;
		   }
		   if(this->t->isPlayer==false && c->isPlayer==false)
		   {
			   return bumpType::through;
		   }
		   if(this->t->isPlayer!=c->isPlayer)// enemy and player reduce HP
		   {
			   c->pvalue=c->pvalue-1;
			   if(c->pvalue==-1)
			   {
				   add_to_delete(this,1);
				   add_to_delete(a,1);
                   return bumpType::abandonded;
			   }
			  
			   add_to_delete(this,1);
			   c->draw->move(-1,-1,MOVELEVEL|c->pvalue);
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

	Bullet::~Bullet(){
		t->bullet_set.erase(this);
	}
}
