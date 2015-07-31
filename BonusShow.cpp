#include "BonusShow.h"
#include "stdlib.h"
#include "stdarg.h"
#include "time.h"


namespace view
{
BonusShow::BonusShow(int rat):Show(rat)
{
    this->rat = rat;
	count =0;
	maxcount =5;

}
void BonusShow::move(int x, int y, ...)
{
    if(-1==x&&-1==y)
    {
		va_list va;
        va_start(va,y);
        int n=va_arg(va,int);
        va_end(va);
        if(n&MOVELEVEL)
        {
            type=(n&MOVEVALUE)-6;
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
    else
    {
        x*=rat;
        y*=rat;
        rec.left=x;
        rec.top=y;
        rec.bottom=y+32;
        rec.right=x+32;
    }
}
void BonusShow::Repaint()
{
	if(count&0x8)
	{
		d3ddev->StretchRect(bonus[type], NULL, backbuffer, &rec, D3DTEXF_NONE);
	}

	count++;


}

}
