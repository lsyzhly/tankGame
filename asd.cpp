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
void init()
{
    mspf=80;
    int n;
    Tank *tank;
    readFile("map\\level1.map");
    s=new PlayerTankShow(2,1);
    tank=new Tank(4<<4,12<<4,14,3,up,s,0,0,0,0,1);
    playTankControl *b=new playTankControl(tank,0);
    addControl(b);
    addItem(tank);
    s=new PlayerTankShow(2,0);
    tank=new Tank(8<<4,12<<4,14,1,up,s,0,0,0,0,1);
    b=new playTankControl(tank,1);
    addControl(b);
    addItem(tank);
    bumpchecker *a=new bumpchecker(13<<4,13<<4);
    bindbumpchecker(a);
}

void flush()
{
    static int n;
    runControls();
    rePaint();
    n++;
}

void destory()
{

}
