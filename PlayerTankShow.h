#ifndef LYplayertankshow_S
#define LYplayertankshow_S
#include "view.h"
namespace view
{
class PlayerTankShow:public Show
{
public:
    int dir;//tank的方向
    //int dis;//tank移动的距离
    int rank;//tank的等级,赋值0，1,2,3
    int count;//tank所应用的图片，0标志第一张，1表示第二张
    int player;//tank所属玩家，0表示玩家一，1表示玩家二
    PlayerTankShow(int rat,int player);
    virtual void Repaint() ;
    virtual void move(int x, int y,int n);//需要传进来的参数有资源的x,y,tank移动的方向,tank等级
    int isshield;
    int cc;//用来表示盾的闪烁

};

}
#endif
