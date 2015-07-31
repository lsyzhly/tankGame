#ifndef BonusShow_HH
#define BonusShow_HH
#include "view.h"
namespace view
{
class BonusShow:public Show
{
public:
    BonusShow(int rat);
    int type;                           //type表示bouns种类，0坦克，1定时，2铁铲，3炸弹，4星星，5安全帽
    virtual void Repaint() ;
    virtual void move(int x, int y,...);//传进位置对资源进行初始化,传进type表示bouns类型
    int count ;//BonusShow
	int maxcount ;
};

}
#endif
