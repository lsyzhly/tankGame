#ifndef BonusShow_HH
#define BonusShow_HH
#include "view.h"
namespace view
{
class BonusShow:public Show
{
public:
    BonusShow(int rat);
    int type;                           //type��ʾbouns���࣬0̹�ˣ�1��ʱ��2������3ը����4���ǣ�5��ȫñ
    virtual void Repaint() ;
    virtual void move(int x, int y,...);//����λ�ö���Դ���г�ʼ��,����type��ʾbouns����
    int count ;//BonusShow
	int maxcount ;
};

}
#endif
