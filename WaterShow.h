#include "view.h"
namespace view
{
class WaterShow:public Show
{
public:
    WaterShow(int rat);
    int type; //type��ʾwater���࣬0,1��ʾ
    int count;
    virtual void Repaint() ;
    virtual void move(int x, int y,int n);//����λ�ö���Դ���г�ʼ����������type

};

}
