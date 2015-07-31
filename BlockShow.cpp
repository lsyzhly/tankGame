#include "BlockShow.h"
#include "stdarg.h"
namespace view
{
BlockShow::BlockShow(int rat):Show(rat)
{
    this->rat = rat ;
}
void BlockShow::move(int x, int y, ...)
{
    if(-1==x&&-1==y)
    {
        va_list va;
        va_start(va,y);
        int n=va_arg(va,int);
        va_end(va);
        if(n&MOVELEVEL)
        {
            type=n&MOVEVALUE;
            if(type<3){
                type--;
            }
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
        rec.bottom=y+16;
        rec.right=x+16;
    }
}
void BlockShow::Repaint()
{
    d3ddev->StretchRect(block[type], NULL, backbuffer, &rec, D3DTEXF_NONE);
}

}
