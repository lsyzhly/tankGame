#include "WaterShow.h"
#include "stdarg.h"
namespace view
{
	WaterShow::WaterShow(int rat):Show(rat)
	{
		this->rat = rat ;
		this->type = 0;
	}
	void WaterShow::move(int x, int y, ...)
	{
		if(-1==x&&-1==y)
		{
			//
		}
		else
		{
	        x*=rat;
            y*=rat;
			/*va_list va;
			va_start(va,y);
			type=va_arg(va,int);
			va_end(va);*/
			rec.left=x;
			rec.top=y;
			rec.bottom=y+32;
			rec.right=x+32;
		}
	
	}
	void WaterShow::Repaint()
	{
		count++;
		if(count&0x8)
			type=1;
		else
			type=0;
         d3ddev->StretchRect(water[type], NULL, backbuffer, &rec, D3DTEXF_NONE);
	}

}