#include "enemytankshow.h"
#include "stdarg.h"
#include "main.h"

namespace view{
	TankAShow::TankAShow(bool is_red, int rat):Show(rat){
		this->is_red=is_red;
	}
	void TankAShow::move(int x, int y, ...){
		if(x==-1&&y==-1){
			va_list va;
			va_start(va,y);
			this->drt=va_arg(va,direct);
			va_end(va);
			countss++;
		}else{
			this
		}
	}
	void TankAShow::Repaint(){
		if(is_red && counts&0x1){
			RECT r;
			movedrt(drt,r,1);
		}
	}
}