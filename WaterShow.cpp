#include "WaterShow.h"
#include "stdarg.h"
namespace view
{
	WaterShow::WaterShow(int rat,int type):Show(rat)
	{
		this->rat = rat ;
		this->type = type;
	}
	void WaterShow::move(int x, int y, ...)
	{
		if(-1==x&&-1==y)
		{
			//
		}
		else
		{
			va_list va;
			va_start(va,y);
			type=va_arg(va,int);
			va_end(va);
			rec.left=x;
			rec.top=y;
			rec.bottom=y+32;
			rec.right=x+32;
		}
	}
	void WaterShow::Repaint()
	{
         d3ddev->StretchRect(water[type], NULL, backbuffer, &rec, D3DTEXF_NONE);
	}

}