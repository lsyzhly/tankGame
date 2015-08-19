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
#include "nbumpchecker.h"
#include "BulletShow.h"
#include "WaterShow.h"
#include "BoreShow.h"
using namespace view;
using namespace item;
using namespace Controler;
using namespace bump;
Show *s;
BulletShow *bs;
BoreShow *aaa;
//WaterShow *ws;
FILE *fpi;
void init()
{
    srand(time(NULL));
    mspf=30;
    readFile("map\\level1.map");
    bumpchecker *a=new bumpchecker(13<<4,13<<4);
    bindbumpchecker(a);
    ChooseLevel(level);
    OnPlayerTank(false);
    OnPlayerTank(true);

}

void flush()
{
    square::rePaint();
    clean();
    checker->checker_move();
    //addEnemyTank();
}

void destory()
{

}
