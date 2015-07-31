#include "enemytankshow.h"
#include "stdarg.h"
#include "main.h"

namespace view
{
TankAShow::TankAShow(bool is_red, int rat,bool is_fast):Show(rat)
{
    this->is_red=is_red;
    this->is_fast=is_fast;
}
void TankAShow::move(int x, int y, ...)
{
    if(x!=-1&&y!=-1)
    {
        x*=rat;
        y*=rat;
        rec.left=x;
        rec.top=y;
        rec.bottom=y+28;
        rec.right=x+28;
    }
    va_list va;
    va_start(va,y);
    int n=va_arg(va,int);
    va_end(va);
    if(n&MOVEDIRECT)
    {
        countss++;
        int m=(n&MOVEVALUE);
        drt=m&0xf;
        m>>=4;
        movedrt(drt,rec,(rat*m));
    }
    else if(n&MOVESETDIRECT)
    {
        drt=(direct)(n&MOVEVALUE);
    }
    else if((n&MOVEFLAG)==0)
    {
        return;
    }
    else if(n&MOVELEVEL){

    }else
    {
        throw n;
    }
    if(rec.left<0 || rec.top<0){
        throw rec;
    }
}
void TankAShow::Repaint()
{
    int n=0;
    if(is_red && counts&0x08)
    {
        n|=0x2;
    }
    if(countss&0x1)
    {
        n|=0x1;
    }
    if(is_fast)
    {
        n|=0x4;
    }
    if(FAILED(d3ddev->StretchRect(enemy[drt][n],NULL,backbuffer,&rec,D3DTEXF_NONE))){
        throw rec;
    }
    counts++;
}
TankBShow::TankBShow(bool is_red, int rat):Show(rat)
{
    this->is_red=is_red;
}
void TankBShow::move(int x, int y,...)
{
    if(x!=-1&&y!=-1)
    {
        if(x<0 || y<0){
            throw x;
        }
        x*=rat;
        y*=rat;
        rec.left=x;
        rec.top=y;
        rec.bottom=y+28;
        rec.right=x+28;
    }
    va_list va;
    va_start(va,y);
    int n=va_arg(va,int);
    va_end(va);
    if(n&MOVEDIRECT)
    {
        countss++;
        int m=(n&MOVEVALUE);
        drt=m&0xf;
        m>>=4;
        movedrt(drt,rec,(rat*m));
    }
    else if(n&MOVELEVEL)
    {
        pvalue=n&MOVEVALUE;
    }
    else if(n&MOVESETDIRECT)
    {
        drt=(direct)(n&MOVEVALUE);
    }
    else if((n&MOVEFLAG)==0)
    {
        return;
    }
    else
    {
        throw n;
    }
    if(rec.left<0 || rec.top<0){
        throw rec;
    }
}
void TankBShow::Repaint()
{
    int n=0;
    if(is_red && counts&0x08)
    {
        n=0x3;
    }
    else
    {
        n=2-pvalue;
    }
    n<<=1;
    if(countss&0x1)
    {
        n|=0x1;
    }
    if(FAILED(d3ddev->StretchRect(enemy[drt|0x4][n],NULL,backbuffer,&rec,D3DTEXF_NONE))){
        throw rec;
    }
    counts++;
}
}
