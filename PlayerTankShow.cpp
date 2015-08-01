#include "PlayerTankShow.h"
#include "stdarg.h"
namespace view
{
PlayerTankShow::PlayerTankShow(int rat,int player):Show(rat)
{
    this->rat = rat;
    this->player=player;
}
void PlayerTankShow::move(int x,int y,...)
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
        count++;
        int m=(n&MOVEVALUE);
        dir=m&0xf;
        m>>=4;
        movedrt(dir,rec,(rat*m));
    }
    else if(n&MOVELEVEL)
    {
        rank=n&MOVEVALUE;
    }
    else if(n&MOVESETDIRECT)
    {
        dir=(direct)(n&MOVEVALUE);
    }
    else if((n&MOVEFLAG)==0)
    {
        return;
    }
    else
    {
        throw n;
    }
}
void PlayerTankShow::Repaint()
{
    HRESULT res;
    if(0==player)
        res=d3ddev->StretchRect(player1[dir][(rank<<1)+(count&0x1)], NULL, backbuffer, &rec, D3DTEXF_NONE);
    else if(1==player)
        res=d3ddev->StretchRect(player2[dir][(rank<<1)+(count&0x1)], NULL, backbuffer, &rec, D3DTEXF_NONE);
    else
        return;
    if(FAILED(res)){
        fprintf(fpi,"PlayerTankShow:%d,%d,%d,%d,%d,%d\n",dir,rank,rec.bottom,rec.left,rec.right,rec.top);
        fflush(fpi);
        throw rec;
    }

}
}
