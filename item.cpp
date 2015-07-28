#include "item.h"
#include "Control.h"
#include "maincontrol.h"
namespace item{
	square::square(int x, int y, int size,Show *draw){
		this->x = x;
		this->y = y;
		this->size = size;
		this->draw = draw;
		draw->move(x, y,up);
		draw = 0;
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
		draw->move(x, y, drt);
		this->control = 0;
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
		int maxbullets, int pvalue, int bullet_size, int bullet_speed)
		:moveSquare(x,y,size,draw,drt,speed)
	{
		this->maxbullets = maxbullets;
		this->pvalue = pvalue;
		this->bullet_size = bullet_size;
		this->bullet_speed = bullet_speed;
	}
	bumpType Tank::bump(square *a,direct drt){
		if (a == 0){
			add_to_delete(this, 1);
			return bumpType::abandonded;
		}
		//TODO judge the bump type
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
	bumpType Bullet::bump(square *a,direct drt){
		//TODO judge the bump type
		return stop;
	}

	Bullet::~Bullet(){
		t->bullet_set.erase(this);
	}
}
