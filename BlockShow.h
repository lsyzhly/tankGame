#include "view.h"
namespace view
{
class BlockShow:public Show
{
public:
    BlockShow(int rat,int type);
    int type;                           //type��ʾblock���࣬0��ʾשͷ��1��ʾ���飬2��ʾ�ݴ�
    virtual void Repaint() ;
    virtual void move(int x, int y,...);//����λ�ö���Դ���г�ʼ��,����type��ʾblock����

};

}
