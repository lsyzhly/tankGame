#include <windows.h>
#include "main.h"
#include "mainControl.h"
#include "enemytankshow.h"
#include "fileReader.h"
#include <stdio.h>
#include "blockShow.h"
#include "control.h"
#include "item.h"
#include "PlayerTankShow.h"
#include "bumpcheck.h"
using namespace view;
using namespace item;
using namespace Controler;
using namespace bump;
Show *s;
void init(){
    mspf=10;
    int n;
	s=new PlayerTankShow(2,1);
    readFile("map\\level1.map");
    Tank *tank=new Tank(4<<4,12<<4,14,1,up,s,0,0,0,0,1);
    autoTankControl *b=new autoTankControl(tank);
    addControl(b);
    addItem(tank);
    bumpchecker *a=new bumpchecker(320,480);
    bindbumpchecker(a);
}

void flush(){
    runControls();
	rePaint();
}

void destory(){

}
