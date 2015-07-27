#include "enemytankshow.h"
#include "stdarg.h"

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
		}else{
			this->x=x;
			this->y=y;
		}
	}
	void TankAShow::Repaint(){
		
	}
}