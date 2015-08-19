#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

#include <set>
#include <list>
#include <vector>
#include "all.h"
#include "view.h"
using Controler::cpointer;
namespace item
{
typedef std::vector<pos> posSet;
typedef std::list<pointer> sList;
//���������,��������Ļ���,������
class pos
{
public:
    int x:16;
    int y:16;
    pos(int x,int y);
};
class square
{
protected:
public:
    //x,y��ʾ������λ�� sizeΪ�߳�
    int x;
    int y;
    int size;
    int level;
    //��ͼ��
    view::Show *draw;
    static std::set<square*> squareSet;
    static void rePaint();
    static void deleteAll();
    square(int x, int y, int size, view::Show *draw,int level=0);
    square(int level);
    //��ȡ��������
    virtual posSet *getRange();
    virtual void reShow();
    virtual ~square();
};
//���ƶ�������
class moveSquare :public square
{
public:
    //�ƶ�����
    direct drt;
    //�ƶ��ٶ�
    int speed;
    cpointer control;
    int cmdIndex;
    moveSquare(int x, int y, int size, view::Show *draw, direct drt, int speed,int level=0);
    //��drt�����ƶ�һ����λ
    void move(direct drt,int size);
    virtual void reShow();
    virtual ~moveSquare();
};
}

namespace std{
template <>
class less<item::square *>
{
public:
    bool operator()(const item::square *a,const item::square *b){
        if(a->level!=b->level){
            return a->level<b->level;
        }else{
            return a->draw<b->draw;
        }
    }
};
}
#endif // SQUARE_H_INCLUDED
