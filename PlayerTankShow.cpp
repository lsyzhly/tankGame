#include "PlayerTankShow.h"
#include "stdarg.h"
namespace view
{
PlayerTankShow::PlayerTankShow(int rat,int player):Show(rat)
{
    this->rat = rat;
    this->player=player;
	cc=0;
	isshield=0;
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
	else if(n&MOVESTATE)
	{
		isshield=n&MOVESTATE;
	}
    else
    {
        throw n;
    }
}
void PlayerTankShow::Repaint()
{
	if(isshield==0)
	{
		if(0==player)
            d3ddev->StretchRect(player1[dir][(rank<<1)+(count&0x1)], NULL, backbuffer, &rec, D3DTEXF_NONE);
        else if(1==player)
            d3ddev->StretchRect(player2[dir][(rank<<1)+(count&0x1)], NULL, backbuffer, &rec, D3DTEXF_NONE);
        else
            return;
	}
	else
	{
		if(cc&0x8)
			d3ddev->StretchRect(shield[0], NULL, backbuffer, &rec, D3DTEXF_NONE);
		else
			d3ddev->StretchRect(shield[1], NULL, backbuffer, &rec, D3DTEXF_NONE);
		cc++;
	}


}
}