#ifndef VIEW_H
#define VIEW_H
#include "all.h"

namespace view{
	//显示器类,抽象类
	//只负责显示,
	class Show{
	public:
		int x;
		int y;
		//下面两个变量针对opengl,对于directx可以修改
		//缩放率,表示组件虚拟大小和实际显示大小的比例
		int rat;
		Show(int rat);
		//在制定位置绘制图像
		virtual void Repaint() = 0;
		//设置位置和方向
		virtual void move(int x, int y,...)=0;
		virtual ~Show();
	};
}


#endif