#include "BoreShow.h"
#include "stdarg.h"

namespace view
{
BoreShow::BoreShow(int rat):Show(rat)
{
    this->rat = rat ;
    type = 0;
    count=0;
    maxcount=6;

}
void BoreShow::move(int x, int y, int n)
{
    if(-1==x&&-1==y)
    {
#ifndef NDEBUG
        assert(n==0);
#endif // NDEBUG
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
void BoreShow::Repaint()
{
    if(count==maxcount)
    {
        type=(type+1)%4;
        count = 0;
        d3ddev->StretchRect(bore[type], NULL, backbuffer, &rec, D3DTEXF_NONE);
    }
    else
    {
        d3ddev->StretchRect(bore[type], NULL, backbuffer, &rec, D3DTEXF_NONE);
        count ++;
    }
}

}
