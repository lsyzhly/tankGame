#ifndef BoreShow_HH
#define BoreShow_HH
#include "view.h"
namespace view
{
class BoreShow:public Show
{
public:
    BoreShow(int rat);
    int type;                           //type��ʾblock���࣬0��ʾשͷ��1��ʾ���飬2��ʾ�ݴ�
    virtual void Repaint() ;
    virtual void move(int x, int y,int n);//����λ�ö���Դ���г�ʼ��,����type��ʾbore����
    int count;//����ʹ��
    int maxcount;//ÿ�ػ����λ�һ��
};

}
#endif
