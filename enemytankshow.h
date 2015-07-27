#ifndef EME_H
#define EME_H
#include "view.h"

namespace view{
	class TankAShow:public Show{
	public:
		bool is_red;
		bool is_fast;
		int counts;
		int countss;
		direct drt;
		TankAShow(bool is_red,int rat,bool is_fast);
		virtual void Repaint();
		virtual void move(int x, int y,...);
	};
}
#endif