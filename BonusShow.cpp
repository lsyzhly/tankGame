#include "BonusShow.h"
#include "stdlib.h"
#include "stdarg.h"
#include "time.h"


namespace view
{
BonusShow::BonusShow(int rat):Show(rat)
{
    this->rat = rat ;
	srand(time(NULL));
    type = rand()%6;
	count =0;
	maxcount =5;

}
void BonusShow::move(int x, int y, ...)
{
    if(-1==x&&-1==y)
    {
         //  
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
