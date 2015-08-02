#include "ExplodeShow.h"
#include "stdarg.h"
namespace view
{
ExplodeShow::ExplodeShow(int rat,int type):Show(rat)
{
    this->rat = rat ;
    this->type = type;
}
void ExplodeShow::move(int x, int y, ...)
{
    if(-1==x&&-1==y)
    {
          //
    }
    else
    {
        x*=rat;
        y*=rat;
		if(0==type)
		{
			rec.top=y-10;
			rec.left=x-10;
			rec.bottom =rec.top+28;
			rec.right = rec.left+28;
            if(rec.right>SCREENW){
                rec.right=SCREENW;
            }
            if(rec.top<0){
                rec.top=0;
            }
            if(rec.left<0){
                rec.left=0;
            }
            if(rec.bottom>SCREENH){
                rec.bottom=SCREENH;
            }
		}
		else
		{
			rec.top=y-18;
			rec.left=x-18;
			rec.bottom =rec.top+64;
			rec.right = rec.left+64;
            if(rec.right>SCREENW){
                rec.right=SCREENW;
            }
            if(rec.top<0){
                rec.top=0;
            }
            if(rec.left<0){
                rec.left=0;
            }
            if(rec.bottom>SCREENH){
                rec.bottom=SCREENH;
            }
		}
    }
}
void ExplodeShow::Repaint()
{
    if(FAILED(d3ddev->StretchRect(explode[type], NULL, backbuffer, &rec, D3DTEXF_NONE))){
        fprintf(fpi,"ExplodeShow:%d,%d,%d,%d,%d\n",type,rec.bottom,rec.left,rec.right,rec.top);
        fflush(fpi);
        throw rec;
    }
}

}
