#include "view.h"
namespace view
{
class ExplodeShow:public Show
{
public:
    ExplodeShow(int rat,int type);
    int type;                           //type表示Explode种类，0表示小爆炸，1表示大爆炸
    virtual void Repaint() ;
    virtual void move(int x, int y,int n);//传进位置对资源进行初始化

};

}
