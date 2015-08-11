#ifndef BoreShow_HH
#define BoreShow_HH
#include "view.h"
namespace view
{
class BoreShow:public Show
{
public:
    BoreShow(int rat);
    int type;                           //type表示block种类，0表示砖头，1表示铁块，2表示草丛
    virtual void Repaint() ;
    virtual void move(int x, int y,int n);//传进位置对资源进行初始化,传进type表示bore类型
    int count;//计数使用
    int maxcount;//每重绘三次换一个
};

}
#endif
