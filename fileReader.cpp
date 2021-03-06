#include "fileReader.h"
#include "MainControl.h"
#include "control.h"
#include "view.h"
#include "item.h"
#include "BlockShow.h"
#include "WaterShow.h"
#include "HeadquartersShow.h"
#include <fstream>
#include <iostream>
using namespace	view;
using namespace item;
using namespace Controler;
using namespace std;

char *newMuchSquare(int x,int y,int size,unmoveType type,int state)
{
    char *a;
    unmoveSquare **b;
    x<<=4;
    y<<=4;
    size>>=1;
    if(state&0x4)
    {
        a=(char *)malloc(4*sizeof(unmoveSquare *)+sizeof(char));
        *a++=4;
        b=(unmoveSquare **)a;
        *b++=new unmoveSquare(x,y,size,new BlockShow(2),type);
        *b++=new unmoveSquare(x+size,y,size,new BlockShow(2),type);
        *b++=new unmoveSquare(x+size,y+size,size,new BlockShow(2),type);
        *b++=new unmoveSquare(x,y+size,size,new BlockShow(2),type);
    }
    else
    {
        a=(char *)malloc(2*sizeof(unmoveSquare *)+sizeof(char));
        *a++=2;
        b=(unmoveSquare **)a;
        if((state&0x1)==0)
        {
            *b++=new unmoveSquare(x,y,size,new BlockShow(2),type);
        }
        else
        {
            *b++=new unmoveSquare(x+size,y+size,size,new BlockShow(2),type);
        }
        state++;
        if(state&0x2)
        {
            *b++=new unmoveSquare(x,y+size,size,new BlockShow(2),type);
        }
        else
        {
            *b++=new unmoveSquare(x+size,y,size,new BlockShow(2),type);
        }
    }
    return --a;
}

void addSqares(char *a,bool isTop)
{
    free(a);
}

void readFile(char *path)
{
    FILE *fp=fopen(path,"rb");
    fseek(fp,0,2);
    int n=ftell(fp);
    int m;
    rewind(fp);
    char *ptr=(char *)malloc(n);
    fread(ptr,1,n,fp);
    int i,j;
    for(i=0; i<13; i++)
    {
        for(j=0; j<13; j++)
        {
            if(n=*ptr++)
            {
                if(n==6)
                {
                    int m=j<<4;
                    int n=i<<4;
                    new unmoveSquare(m,n,32>>1,new HeadquartersShow(2),boss);
                    new unmoveSquare(m-8,n+8,16>>1,new BlockShow(2),tu);
                    new unmoveSquare(m-8,n,16>>1,new BlockShow(2),tu);
                    new unmoveSquare(m-8,n-8,16>>1,new BlockShow(2),tu);
                    new unmoveSquare(m,n-8,16>>1,new BlockShow(2),tu);
                    new unmoveSquare(m+8,n-8,16>>1,new BlockShow(2),tu);
                    new unmoveSquare(m+16,n-8,16>>1,new BlockShow(2),tu);
                    new unmoveSquare(m+16,n,16>>1,new BlockShow(2),tu);
                    new unmoveSquare(m+16,n+8,16>>1,new BlockShow(2),tu);


                    //addItem(new unmoveSquare(j<<5,i<<5,32,0,(unmoveType)0));
                }
                else if(4==n)
                {
                    new unmoveSquare(j<<4,i<<4,32>>1,new WaterShow(2),(unmoveType)n);
                }
                else if(3==n)
                {
                    char *pt=newMuchSquare(j,i,16,(unmoveType)n,4);
                    addSqares(pt,true);
                }
                else
                {
                    m=*ptr++;
                    char *pt= newMuchSquare(j,i,16,(unmoveType)n,m);
                    addSqares(pt);
                }
            }
        }
    }
}
void ChooseLevel(int lev)
{
    CLevel = lev;
    if(lev>=20)
    {
        MessageBox(hwnd,L"win!",L"win!",0);
        exit(0);
        //TODO GAME OVER
        return ;
    }
    tanks[0]++;
    tanks[1]++;
    bumpchecker *a=new bumpchecker(13<<4,13<<4);
    bindbumpchecker(a);
    char filename[20];
    ifstream f;
    ertank=20;
    etanks=0;
    f.open("etank.map",ios::in|ios::binary);
    f.seekg((lev-1)*20);
    f.read((char *)etank, sizeof(char)*20);
    f.close();
    sprintf(filename,"map\\level%d.map",lev);
    readFile(filename);
}

