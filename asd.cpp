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
#include "BulletShow.h"
#include "WaterShow.h"
using namespace view;
using namespace item;
using namespace Controler;
using namespace bump;
Show *s;
BulletShow *bs;
//WaterShow *ws;
FILE *fpi;
void init()
{
    mspf=30;
    int n;
    Tank *tank;
    fpi=fopen("D:\\asd.txt","w");
    readFile("map\\level1.map");
    s=new PlayerTankShow(2,0);
    tank=new Tank(4<<4,12<<4,14,3,up,s,4,0,3,0,0,1);
    playTankControl *b=new playTankControl(tank,0);
    addControl(b);
    addItem(tank);
    s=new TankBShow(1,2);
    tank=new Tank(8<<4,12<<4,14,1,up,s,1,0,2,0,0,0);
    autoTankControl *bi=new autoTankControl(tank);
    addControl(bi);
    addItem(tank);
    bumpchecker *a=new bumpchecker(13<<4,13<<4);
    bindbumpchecker(a);
    //bs = new BulletShow(2,1);
    //tank->drt=right;
    //Bullet *ads=new Bullet(tank,0,16,1,2,bs);
    //bulletControl *qwea=new bulletControl(ads);
    //addItem(ads);
    //addControl(qwea);
	//ws=new WaterShow(2);
	//ws->move(0,0);

}

void flush()
{
	//ws->move(-1,-1);
	//ws->Repaint();
    static int n;
    runControls();
    rePaint();
    clean();
    n++;
}

void destory()
{

}
