#include "enemytankshow.h"
#include "stdarg.h"
#include "main.h"

namespace view{
	TankAShow::TankAShow(bool is_red, int rat,bool is_fast):Show(rat){
		this->is_red=is_red;
		this->is_fast=is_fast;
	}
	void TankAShow::move(int x, int y, ...){
		if(x==-1&&y==-1){
			va_list va;
			va_start(va,y);
			drt=va_arg(va,direct);
			va_end(va);
			countss++;
			movedrt(drt,rec,rat);
		}else{
			rec.left=x;
			rec.top=y;
			rec.bottom=y+28;
			rec.right=x+28;
			va_list va;
			va_start(va,y);
			drt=va_arg(va,direct);
			va_end(va);
		}
	}
	void TankAShow::Repaint(){
		int n=0;
		if(is_red && counts&0x08){
			n|=0x2;
		}
		if(countss&0x1){
			n|=0x1;
		}
		if(is_fast){
			n|=0x4;
		}
		d3ddev->StretchRect(enemy[drt][n],NULL,backbuffer,&rec,D3DTEXF_NONE);
		counts++;
	}
	TankBShow::TankBShow(bool is_red, int rat):Show(rat){
		this->is_red=is_red;
	}
	void TankBShow::move(int x, int y,...){
		if(x==-1&&y==-1){
			va_list va;
			va_start(va,y);
			drt=(direct)va_arg(va,int);
			va_end(va);
			countss++;
			movedrt(drt&0x3,rec,rat);
		}else{
			rec.left=x;
			rec.top=y;
			rec.bottom=y+28;
			rec.right=x+28;
			va_list va;
			va_start(va,y);
			drt=(direct)va_arg(va,int);
			va_end(va);
		}
	}
	void TankBShow::Repaint(){
		int n=0;
		if(is_red && counts&0x08){
			n|=0x3;
		}else{
			n|=drt>>4;
		}
		n<<=1;
		if(countss&0x1){
			n|=0x1;
		}
		d3ddev->StretchRect(enemy[drt&0x3|0x4][n],NULL,backbuffer,&rec,D3DTEXF_NONE);
		counts++;
	}
}
