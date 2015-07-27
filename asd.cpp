#include <windows.h>
#include "main.h"
#include "enemytankshow.h"
#include <stdio.h>
using namespace view;
Show *s;
void init(){
    mspf=10;
	s=new TankBShow(true,2);
	s->move(32,32,left);
}

void flush(){
	static int n=0;/*
	if(n&0x3==0x3){
		s->move(-1,-1,down|0x00);
	}*/
	s->Repaint();
	n++;
}

void destory(){

}
