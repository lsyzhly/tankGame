#include <windows.h>
#include "main.h"
#include "mainControl.h"
#include "enemytankshow.h"
#include "fileReader.h"
#include <stdio.h>
#include "blockShow.h"
#include "control.h"
#include "item.h"
using namespace view;
using namespace item;
using namespace Controler;
Show *s;
void init(){
    mspf=10;
    int n;
	s=new TankBShow(true,2);
	s->move(32,32,(int)left);
    readFile("map\\level1.map");
    Tank *tank=new Tank(0,0,16,1,up,s,0,0,0,0,1);
    playTankControl *b=new playTankControl(tank,0);
    addControl(b);
    addItem(tank);
}

void flush(){
    runControls();
	rePaint();
}

void destory(){

}
