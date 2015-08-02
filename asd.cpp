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
    int n;
    char path[100];
    sprintf(path,"D:\\log\\asd%d.txt",rand());
    fpi=fopen(path,"w");
	ChooseLevel(level);
    OnPlayerTank(false);
    OnPlayerTank(true);

}

void flush()
{
    static int n;
    fprintf(fpi,"ptr:%p,%p\n",ptanks[0],ptanks[0]->control);
    fprintf(fpi,"ptr:%p,%p\n",ptanks[1],ptanks[1]->control);
    fprintf(fpi,"runControls\n");
    fflush(fpi);
    runControls();
    fprintf(fpi,"ptr:%p,%p\n",ptanks[0],ptanks[0]->control);
    fprintf(fpi,"ptr:%p,%p\n",ptanks[1],ptanks[1]->control);
    fprintf(fpi,"rePaint\n");
    fflush(fpi);
    rePaint();
    fprintf(fpi,"ptr:%p,%p\n",ptanks[0],ptanks[0]->control);
    fprintf(fpi,"ptr:%p,%p\n",ptanks[1],ptanks[1]->control);
    fprintf(fpi,"clean\n");
    fflush(fpi);
    clean();
    fprintf(fpi,"ptr:%p,%p\n",ptanks[0],ptanks[0]->control);
    fprintf(fpi,"ptr:%p,%p\n",ptanks[1],ptanks[1]->control);
    fprintf(fpi,"addEnemyTank\n");
    fflush(fpi);
    addEnemyTank();
    fprintf(fpi,"ptr:%p,%p\n",ptanks[0],ptanks[0]->control);
    fprintf(fpi,"ptr:%p,%p\n",ptanks[1],ptanks[1]->control);
    fprintf(fpi,"finish\n");
    fflush(fpi);
}

void destory()
{

}
