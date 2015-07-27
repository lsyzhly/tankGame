#include "BlockShow.h"
#include "stdarg.h"
namespace view
{
	BlockShow::BlockShow(int rat,int type):Show(rat)
	{
		this->rat = rat ;
		this->type = type;
	}
	void BlockShow::move(int x, int y, ...)
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
			rec.bottom=y+16;
			rec.right=x+16;
		}
	}
	void BlockShow::Repaint()
	{
         d3ddev->StretchRect(block[type], NULL, backbuffer, &rec, D3DTEXF_NONE);
	}

}