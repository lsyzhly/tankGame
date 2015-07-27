#include "view.h"

namespace view{
	class TankAShow:public Show{
		bool is_red;
		int counts;
		int countss;
		direct drt;
		TankAShow(bool is_red,int rat);
		virtual void Repaint();
		virtual void move(int x, int y,...);
	};
}