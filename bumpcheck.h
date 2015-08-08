/*
��ģ��ʵ����bumpchecker��Ľӿ�
��ģ�������жϷ�ʽΪ���ؼ�,���ڼ���ٶȶ��жϵķֱ�����n^2������
��֤ʹ��ʱÿ����λ�Ĵ�С��Ҫ����10
һ���ƶ����벻Ҫ����5
���򽫻�Ӱ��ˢ����
*/
#ifndef LSYbumpchecker_S
#define LSYbumpchecker_S
#include <iostream>
#include <memory>
#include <set>
#include <utility>
#include "item.h"
#ifdef CPP11
#include <pthread>
#include <mutex>
using std::mutex;
#endif

namespace bump
{
using item::pointer;
using item::sList;
using item::mpointer;
//��ά����ģ����
template <typename T>
class twoarray
{
public:
    int length;
    T *ptr;
    T *operator[](int size)
    {
        return ptr + size*length;
    }
    twoarray(int length,int width)
    {
        ptr = new T[length*width];
        this->length = length;
    }
    ~twoarray(){
        delete[] ptr;
    }
};

class bumpchecker
{
public:
    int width;
    int hight;
    //��ά����
    twoarray<sList> bmap;
    bumpchecker(int width,int hight);
    //�ж��Ƿ���˱߽�
    bool is_out(pair<int, int> pos);
    //��дmove����
    virtual int move(mpointer a, direct drt, int size);
    //�ƶ�һ����λ,������ײ����
    virtual int move(mpointer a, direct drt);
    //��дadd����
    virtual pointer add(pointer a);
    //��дremove����
    virtual void remove(pointer a);
    virtual ~bumpchecker();
};
}
#endif
