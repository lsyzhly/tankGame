#include "fileReader.h"
#include "MainControl.h"
#include "control.h"
#include "view.h"
#include "item.h"
#include "BlockShow.h"
#include "WaterShow.h"
using namespace	view;
using namespace item;
using namespace Controler;

char *newMuchSquare(int x,int y,int size,unmoveType type,int state){
	char *a;
	unmoveSquare **b;
	x<<=4;
    y<<=4;
	size>>=1;
	if(state&0x4){
		a=(char *)malloc(4*sizeof(unmoveSquare *)+sizeof(char));
		*a++=4;
		b=(unmoveSquare **)a;
		*b++=new unmoveSquare(x,y,size,new BlockShow(2,type-1),type);
		*b++=new unmoveSquare(x+size,y,size,new BlockShow(2,type-1),type);
		*b++=new unmoveSquare(x+size,y+size,size,new BlockShow(2,type-1),type);
		*b++=new unmoveSquare(x,y+size,size,new BlockShow(2,type-1),type);
	}else{
		a=(char *)malloc(2*sizeof(unmoveSquare *)+sizeof(char));
		*a++=2;
		b=(unmoveSquare **)a;
		if((state&0x1)==0){
			*b++=new unmoveSquare(x,y,size,new BlockShow(2,type-1),type);
		}else{
			*b++=new unmoveSquare(x+size,y+size,size,new BlockShow(2,type-1),type);
		}
        state++;
        if(state&0x2){
            *b++=new unmoveSquare(x,y+size,size,new BlockShow(2,type-1),type);
        }else{
            *b++=new unmoveSquare(x+size,y,size,new BlockShow(2,type-1),type);
        }
	}
	return --a;
}

void addSqares(char *a,bool isTop){
    int n=*a++;
    unmoveSquare **b=(unmoveSquare **)a;
    while(n--){
        addItem(*b++,isTop);
    }
    free(--a);
}

void readFile(char *path){
	FILE *fp=fopen(path,"rb");
	fseek(fp,0,2);
	int n=ftell(fp);
	int m;
	rewind(fp);
	char *ptr=(char *)malloc(n);
	fread(ptr,1,n,fp);
	int i,j;
	for(i=0;i<13;i++){
		for(j=0;j<13;j++){
			if(n=*ptr++){
				if(n==6)
				{
					//addItem(new unmoveSquare(j<<5,i<<5,32,0,tie));
				}
				else if(4==n)
				{
					addItem(new unmoveSquare(j<<4,i<<4,32>>1,new WaterShow(2),(unmoveType)n));
				}
				else if(3==n)
				{
					char *pt=newMuchSquare(j,i,16,(unmoveType)n,4);
					addSqares(pt,true);
				}
				else{
					m=*ptr++;
					char *pt= newMuchSquare(j,i,16,(unmoveType)n,m);
					addSqares(pt);
				}
			}
		}
	}
}
