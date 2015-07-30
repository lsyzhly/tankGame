#include "PlayerTankShow.h"
#include "stdarg.h"
namespace view
{
	PlayerTankShow::PlayerTankShow(int rat):Show(int rat)
	{
          this->rat = rat;
	}
	void PlayerTankShow::move(int x,int y,...)
	{
		va_list va;
		va_start(va,y);
		 RECT rec;
		 RECT prec;
		 switch(dir){
			case up:
				rec.top=y-dis;
				rec.left=x;
				prec.top=0;
				break;
			case down:
				rec.top=y+dis;
				rec.left=x;
				prec.top=56;
				break;
			case left:
				rec.top=y;
				rec.left=x-dis;
				prec.top=84;
				break;
			case right:
				rec.top=y;
				rec.left = x+dis;
				prec.top=28;
				break
			default:
				break;
		}
		rec.right=rec.left+size;
		rec.bottom=rec.top+size;

	  // d3ddev->StretchRect(ConstSurface, NULL, backbuffer, &rec, D3DTEXF_NONE);
	}
	void PlayerTankShow::Repaint(){
	}
}