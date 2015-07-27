#include "PlayerTankShow.h"
#include "stdarg.h"
namespace view
{
	PlayerTankShow::PlayerTankShow(int rat,int rank,int player):Show(rat)
	{
          this->rat = rat;
		  this->flag=0;
		  this->rank=0;
		  this->player=1;
	}
	void PlayerTankShow::move(int x,int y,...)
	{
		if(x==-1&&y==-1){
			va_list va;
			va_start(va,y);
			dir=va_arg(va,direct);
			va_end(va);
			movedrt(dir,rec,rat);
			 flag=(flag+1)%2;
		}else{
			rec.left=x;
			rec.top=y;
			rec.bottom=y+28;
			rec.right=x+28;
			va_list va;
			va_start(va,y);
			dir=va_arg(va,direct);
			va_end(va);
		}

	  // d3ddev->StretchRect(ConstSurface, NULL, backbuffer, &rec, D3DTEXF_NONE);
	}
	void PlayerTankShow::Repaint()
	{
		 if(1==player)
             d3ddev->StretchRect(player1[dir][(rank<<1)+flag], NULL, backbuffer, &rec, D3DTEXF_NONE);
		 else if(2==player)
			 d3ddev->StretchRect(player2[dir][(rank<<1)+flag], NULL, backbuffer, &rec, D3DTEXF_NONE);
		 else
			 return;
   
	}
}