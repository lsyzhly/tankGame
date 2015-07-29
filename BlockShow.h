#include "view.h"
namespace view
{
class BlockShow:public Show
{
public:
    BlockShow(int rat,int type);
    int type;                           //type表示block种类，0表示砖头，1表示铁块，2表示草丛
    virtual void Repaint() ;
    virtual void move(int x, int y,...);//传进位置对资源进行初始化,传进type表示block类型

};

}
