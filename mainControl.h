#ifndef MAINCONTROL_H
#define MAINCONTROL_H
#include <map>
#include <set>
#include <functional>
#include <memory.h>
#include "all.h"
using namespace bump;
using namespace item;
using namespace view;
using namespace Controler;

extern int tanks[];
extern bumpchecker *checker;
extern int score[];
extern int etanks;
extern unsigned char etank[20];
extern int ertank;
extern int CLevel;
extern int etanks;
extern int level;

//绑定碰撞检测系统
void bindbumpchecker(bumpchecker *checker);
//清理待删除组件

//*********************
void clean();

void runControls();

void rePaint();

//注册时间事件
//n为事件id OnTime事件响应函数,n为响应时间
//自定义参数总大小不能大于64字节
void addTimeFun(unsigned char id,std::function<void (void )> func,int n);
void addTimeFun(std::function<void (void )> func,int n);
//设置某阵营坦克状态 is为要设置的坦克阵营
//is_run为要设置的状态
void setTankState(bool is,bool is_run);
void setCapTankState(Tank *theTank,bool stoppable);
void deleteTank(bool type);
void OnPlayerTank(bool type);
void addEnemyTank();
#endif
