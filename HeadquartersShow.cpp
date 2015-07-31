#include "HeadquartersShow.h"
#include "stdarg.h"
namespace view
{
HeadquartersShow::HeadquartersShow(int rat):Show(rat)
{
    this->rat = rat ;
    this->type=0;
}
void HeadquartersShow::move(int x, int y, ...)
{
    if(-1==x&&-1==y)
    {
        va_list va;
        va_start(va,y);
        int n=va_arg(va,int);
        va_end(va);
        if(n&MOVELEVEL)
        {
        }
        else if((n&MOVESTATE)){
            type=n&MOVEVALUE;
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
void HeadquartersShow::Repaint()
{
    d3ddev->StretchRect(headquarters[type], NULL, backbuffer, &rec, D3DTEXF_NONE);
}

}
