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
	playTankControl::playTankControl(item::Tank *tank,bool type):Control(tank->speed){
		this->tank=tank;
		this->type=type;
	}
	bool playTankControl::run(){
		if(count--)return false;
	}
}