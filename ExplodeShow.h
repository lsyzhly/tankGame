#include "view.h"
namespace view
{
class ExplodeShow:public Show
{
public:
    ExplodeShow(int rat,int type);
    int type;                           //type��ʾExplode���࣬0��ʾС��ը��1��ʾ��ը
    virtual void Repaint() ;
    virtual void move(int x, int y,int n);//����λ�ö���Դ���г�ʼ��

};

}
