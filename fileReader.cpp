#include "fileReader.h"
#include "MainControl.h"
#include "control.h"
#include "view.h"
#include "item.h"
#include "blockview.h"
using namespace	view;
using namespace item;
using namespace Controler;

char *newMuchSquare(int x,int y,int size,unmoveType type,int state){
	char *a;
	unmoveSquare *b;
	x<<=5;
	y<<=5;
	size>>=1;
	if(state&0x4){
		a=(char *)malloc(4*sizeof(unmoveSquare *)+sizeof(char));
		*a++=4;
		b=(unmoveSquare *)a;
		*b++=new unmoveSquare(x,y,size,,type);
		*b++=new unmoveSquare(x+size,y,size,,type);
		*b++=new unmoveSquare(x+size,y+size,size,,type);
		*b++=new unmoveSquare(x,y+size,size,,type);
	}else{
		a=(char *)malloc(2*sizeof(unmoveSquare *)+sizeof(char));
		*a++=2;
		b=(unmoveSquare *)a;
		if(state&0x1==0){
			*b++=new unmoveSquare(x,y,size,,type);
		}else if(state&0x1){
			*b++=new unmoveSquare(x+size,y+size,size,,type);
		}else {
			state++;
			if(state&0x3){
				*b++=new unmoveSquare(x,y+size,size,,type);
			}else{
				*b++=new unmoveSquare(x+size,y,size,,type);
			}
			
		}
	}
	return 0;
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
	for(i=0;i<15;i++){
		for(j=0;j<15;j++){
			if(n=*ptr++){
				if(n==6){
					//addItem(new unmoveSquare(j<<5,i<<5,32,0,tie));
				}else{
					m=*ptr++;
					char *ptr= newMuchSquare(j,i,32,n,m);
					int n=*ptr;
					for(n--){
						;
					}
				}
			}
		}
	}
}