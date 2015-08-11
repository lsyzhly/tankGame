#include "BlockShow.h"
#include "stdarg.h"
namespace view
{
BlockShow::BlockShow(int rat):Show(rat)
{
    this->rat = rat ;
}
void BlockShow::move(int x, int y, int n)
{
    if(-1==x&&-1==y)
    {
        if(n&MOVELEVEL)
        {
            type=n&MOVEVALUE;
            if(type<4)
            {
                type--;
            }
            else
            {
                throw n;
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
    if(FAILED(d3ddev->StretchRect(block[type], NULL, backbuffer, &rec, D3DTEXF_NONE)))
    {
        throw rec;
    }
}

}
