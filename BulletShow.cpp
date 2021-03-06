#include "BulletShow.h"
#include "stdarg.h"
namespace view
{
BulletShow::BulletShow(int rat):Show(rat)
{
    this->rat = rat ;
}
void BulletShow::move(int x, int y, int n)
{
    if(x!=-1&&y!=-1){
#ifndef NDEBUG
            assert(n==0);
#endif // NDEBUG
        x*=rat;
        y*=rat;
        rec.left=x;
        rec.top=y;
        rec.bottom=y+8;
        rec.right=x+8;
    }else{
        if(n&MOVEDIRECT)
        {
            int m=(n&MOVEVALUE);
            type=m&0xf;
            m>>=4;
            movedrt(type,rec,(rat*m));
        }
        else if(n&MOVESETDIRECT)
        {
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
}
void BulletShow::Repaint()
{
    if(FAILED(d3ddev->StretchRect(bulletbmp[type], NULL, backbuffer, &rec, D3DTEXF_NONE))){
        throw rec;
    }
}
}
