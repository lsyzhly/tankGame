#ifndef BLOCKVIEW_H
#define BLOCKVIEW_H
#include "view.h"

namespace view{
	class Blockview:public Show{
		unmoveType utype;
		virtual void move(int x,int y,...);
		virtual void Repaint();
	};
}

#endif