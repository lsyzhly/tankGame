/*
此模块实现了bumpchecker类的接口
本模块由于判断方式为像素级,对于检测速度对判断的分辨率是n^2的增长
保证使用时每个单位的大小不要超过10
一次移动距离不要大于5
否则将会影响刷新率
*/
#ifndef LSYbumpchecker_S
#define LSYbumpchecker_S
#include <iostream>
#include <memory>
#include <set>
#include <utility>
#include "item.h"
#ifdef CPP11
#include <pthread>
#include <mutex>
using std::mutex;
#endif

namespace bump{
	using item::pointer;
	using item::mpointer;
	//二维数组模板类
	template <typename T>
	class twoarray{
	public:
		int length;
		T *ptr;
		T *operator[](int size){
			return ptr + size*length;
		}
		twoarray(int length,int width){
			ptr = (T *)calloc(length*width, sizeof(T));
			this->length = length;
		}
	};

	class bumpchecker {
	public:
		int width;
		int hight;
#ifdef CPP11
		mutex lock;
#endif CPP11
		//二维数组
		twoarray<pointer> bmap;
		bumpchecker(int width,int hight);
		//判断是否出了边界
		bool is_out(pair<int, int> pos);
		//重写move方法
		virtual int move(mpointer a, direct drt, int size);
		//移动一个单位,返回碰撞类型
		virtual int move(mpointer a, direct drt);
		//重写add方法
		virtual pointer add(pointer a);
		//重写remove方法
		virtual void remove(pointer a);
		virtual ~bumpchecker();
	};
}
#endif