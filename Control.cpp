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
UINT player1tank[5]={VK_UP,VK_RIGHT,VK_DOWN,VK_LEFT,76};//表示player1的上下左右的虚拟键值up=0, down=2, left=3, right=1,L(fire)
UINT player2tank[5]={87,68,83,65,VK_SPACE};//表示player2的上下左右的虚拟键值 w,s,a,d,space
namespace Controler{
	Control::Control(int maxcount){
		this->maxcount=maxcount;
		this->count=maxcount;
	}
	Control::~Control(){
	}

	autoTankControl::autoTankControl(Tank *tank):Control(tank->speed){
		this->tank = tank;
		tank->control = this;
		printf("starting run%p,%p\n", this,this->tank);
	}

	bool autoTankControl::run(){
		if(count--)return false;
		srand(clock());
		unsigned int a = rand() % 4;
		//unsigned int b = rand() % 50;
		int c = checker->move(tank, tank->drt, tank->speed);
		if (c&bumpType::astop){
			checker->move(tank, (direct)a, tank->speed);
			tank->drt = (direct)a;
		}
		count=maxcount;
		return c&bumpType::abandonded;
	}
	playTankControl::playTankControl(item::Tank *tank,int type):Control(tank->speed){
		this->tank=tank;
		this->type=type;
	}
	bool playTankControl::run(){
		if(count--)return false;
	}

}