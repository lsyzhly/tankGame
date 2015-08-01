#ifndef MAINCONTROL_H
#define MAINCONTROL_H
#include <map>
#include <set>
#include <memory.h>
#include "all.h"
using namespace bump;
using namespace item;
using namespace view;
using namespace Controler;

extern int tanks[];
extern bumpchecker *checker;
extern int etanks;
extern unsigned char etank[20];
extern int ertank;
extern int etanks;
extern int level;

//添加组件到删除列表,该组件将会在count次屏幕刷新后删除
void add_to_delete(pointer a, int count);
//添加组件
void addItem(pointer a,bool isTop=false);
//添加控制器
void addControl(cpointer a);
//绑定碰撞检测系统
void bindbumpchecker(bumpchecker *checker);
//清理待删除组件

//*********************
void addHqItems(pointer a);
void setHqState(int state);

//*********************
void clean();

void runControls();

void rePaint();

void remove(pointer a);
void remove(cpointer a);

void freeControl();
void freeItem();

typedef void (*OnTime)(...);

template <int size>
class MEMSTRUCT
{
public:
    char a[size];
    OnTime func;
    int count;
    void init(OnTime fun,char *ptr,int count)
    {
        func=fun;
        memcpy(a,ptr,size);
        this->count=count;
    }
    bool operator()()
    {
        if(--count==0){
            func(*this);
            return true;
        }
		return false;
    }
};
//注册时间事件
//n为事件id OnTime事件响应函数,n为响应时间,...为自定义参数
//自定义参数总大小不能大于64字节
void addTimeFun(unsigned char id,OnTime on,int n,...);
void addTimeFun(OnTime on,int n,...);
//设置某阵营坦克状态 is为要设置的坦克阵营
//is_run为要设置的状态
void setTankState(bool is,bool is_run);
void setCapTankState(Tank *theTank,bool stoppable);
void deleteTank(bool type);
void OnPlayerTank(bool type);
void addEnemyTank();
#endif
