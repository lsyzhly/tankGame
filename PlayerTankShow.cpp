#include "PlayerTankShow.h"
#include "stdarg.h"
namespace view
{
	PlayerTankShow::PlayerTankShow(int rat,int player):Show(rat)
	{
          this->rat = rat;
		  this->flag=0;
		  this->player=player;
	}
	void PlayerTankShow::move(int x,int y,...)
	{
		if(x!=-1&&y!=-1){
            x*=rat;
            y*=rat;
			rec.left=x;
			rec.top=y;
			rec.bottom=y+28;
			rec.right=x+28;
		}
        va_list va;
        va_start(va,y);
        int n=va_arg(va,int);
        va_end(va);
        if(n&MOVEDIRECT){
            flag++;
            flag&=0x1;
            dir=(direct)(n&MOVEVALUE);
            movedrt(dir,rec,rat);
        }else if(n&MOVELEVEL){
            rank=n&MOVEVALUE;
        }else if(n&MOVESETDIRECT){
            dir=(direct)(n&MOVEVALUE);
        }else if((n&MOVEFLAG)==0){
            return;
        }else{
            throw n;
        }

	  // d3ddev->StretchRect(ConstSurface, NULL, backbuffer, &rec, D3DTEXF_NONE);
	}
	void PlayerTankShow::Repaint()
	{
		 if(0==player)
             d3ddev->StretchRect(player1[dir][(rank<<1)+flag], NULL, backbuffer, &rec, D3DTEXF_NONE);
		 else if(1==player)
			 d3ddev->StretchRect(player2[dir][(rank<<1)+flag], NULL, backbuffer, &rec, D3DTEXF_NONE);
		 else
			 return;

	}
}
