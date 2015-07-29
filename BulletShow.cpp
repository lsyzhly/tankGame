#include "BulletShow.h"
#include "stdarg.h"
namespace view
{
	BulletShow::BulletShow(int rat,int type):Show(rat)
	{
		this->rat = rat ;
		this->type = type;
	}
	void BulletShow::move(int x, int y, ...)
	{
		if(x!=-1&&y!=-1){
            x*=rat;
            y*=rat;
			rec.left=x;
			rec.top=y;
			rec.bottom=y+8;
			rec.right=x+8;
		}
  
        movedrt(type,rec,rat);
	}
	void BulletShow::Repaint()
	{
         d3ddev->StretchRect(bulletbmp[type], NULL, backbuffer, &rec, D3DTEXF_NONE);
	}

}
