#include "HeadquartersShow.h"
#include "stdarg.h"
namespace view
{
HeadquartersShow::HeadquartersShow(int rat,int type):Show(rat)
{
    this->rat = rat ;
    this->type = type;
}
void HeadquartersShow::move(int x, int y, ...)
{
    if(-1==x&&-1==y)
    {
        //
    }
    else
    {
        x*=rat;
        y*=rat;
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
void HeadquartersShow::Repaint()
{
    d3ddev->StretchRect(headquarters[type], NULL, backbuffer, &rec, D3DTEXF_NONE);
}

}
