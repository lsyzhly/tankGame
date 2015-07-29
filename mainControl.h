#ifndef MAINCONTROL_H
#define MAINCONTROL_H
#include <map>
#include <set>
#include "all.h"
using namespace bump;
using namespace item;
using namespace view;
using namespace Controler;

extern bumpchecker *checker;

//添加组件到删除列表,该组件将会在count次屏幕刷新后删除
void add_to_delete(pointer a, int count);
//添加组件
void addItem(pointer a,bool isTop=false);
//添加控制器
void addControl(cpointer a);
//绑定碰撞检测系统
void bindbumpchecker(bumpchecker *checker);
//清理待删除组件
void clean();

void runControls();

void rePaint();

void remove(pointer a);
void remove(cpointer a);

void freeAll();

typedef (*Ontiem)(...);
typedef (*is_do)(pointer *a);
//指定n次刷新自后调用该函数
void addTimeFun(Ontiem on,int n);
//设置某阵营坦克状态
void setTankState(bool is,bool is_run);

#endif
