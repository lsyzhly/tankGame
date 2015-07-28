#include <windows.h>
#include "main.h"
#include "mainControl.h"
#include "enemytankshow.h"
#include "fileReader.h"
#include <stdio.h>
#include "blockShow.h"
#include "item.h"
using namespace view;
using namespace item;
Show *s;
void init(){
    mspf=10;
    int n;/*
	s=new TankBShow(true,2);
	s->move(32,32,(int)left);*//*
	char *a=newMuchSquare(3,4,32,tu,0);
	addSqares(a);
    a=newMuchSquare(2,3,32,tu,3);
	addSqares(a);
    a=newMuchSquare(3,2,32,cao,1);
	addSqares(a);
    a=newMuchSquare(4,3,32,cao,2);
	addSqares(a);
	a=newMuchSquare(3,3,32,qiang,4);
	addSqares(a);*/
    readFile("map\\level1.map");
}

void flush(){/*
	static int n=0;
	if(n&0x3==0x3){
		s->move(-1,-1,(int)(down|0x00));
	}
	s->Repaint();
	n++;*/
	if(!isKeyDown['W'])
        rePaint();

}

void destory(){

}
