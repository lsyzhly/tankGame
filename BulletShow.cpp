//#include "BulletShow.h"
//#include "stdarg.h"
//namespace view
//{
//	BulletShow::Bullethow(int rat,int type):Show(rat)
//	{
//		this->rat = rat ;
//		this->type = type;
//	}
//	void BulletShow::move(int x, int y, ...)
//	{
//		if(-1==x&&-1==y)
//		{
//			va_list va;
//			va_start(va,y);
//			type=va_arg(va,int);
//			va_end(va);
//		}
//		else
//		{
//		    x*=rat;
//		    y*=rat;
//			rec.left=x;
//			rec.top=y;
//			rec.bottom=y+8;
//			rec.right=x+8;
//		}
//	}
//	void BlockShow::Repaint()
//	{
//         d3ddev->StretchRect(bullet[type], NULL, backbuffer, &rec, D3DTEXF_NONE);
//	}
//
//}
