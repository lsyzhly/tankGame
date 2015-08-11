#ifndef NBUMPCHECKER_H_INCLUDED
#define NBUMPCHECKER_H_INCLUDED
#include <vector>
#include <map>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include "all.h"
#include "item.h"
using namespace item;
namespace bump
{
class Cmd;
//΢ָ����
class Mcmd :public std::vector<pos>
{
public:
    //΢ָ����ָ���е�λ��
    unsigned int index;
#ifndef NDEBUG
    bool is_valid;
#endif
    //��Ӧ��ָ��
    Cmd *fatherCmd;
    Mcmd();
};
//�߳�����
template<typename T>
class varArray
{
protected:
    int size;
    T *ptr;
    varArray()
    {
        ptr=0;
    }
    varArray(int size)
    {
        this->size=size;
        ptr=new T[size];
    }
    void reSize(int size)
    {
        this->size=size;
        if(ptr) delete[] ptr;
        ptr=new T[size];
    }
    ~varArray()
    {
        if(ptr) delete[] ptr;
    }
public:
    T &operator[](int n)
    {
        if(n>=size)
        {
            throw n;
        }
        return ptr[n];
    }
};
//ָ��
class Cmd:public varArray<Mcmd>
{
public:
    //����Ŀ��
    mpointer target;
    //�ƶ�����
    direct drt:8;
    //�ƶ�����
    unsigned int msize:12;
    unsigned int rsize:12;
    bool isVaild;
    Cmd(mpointer target);
    //׼���ƶ�
    void move();
    //�����ƶ�ָ��
    void complie();
    //�����ƶ�ָ��
    void run();
};

template <typename T>
class twoarray
{
public:
    int length;
    int width;
    T *ptr;
    T *operator[](int size)
    {
        return ptr + size*length;
    }
    T &operator[](pos p)
    {
        return ptr[p.y*length+p.x];
    }
    twoarray(int length,int width)
    {
        ptr = (T *)calloc(sizeof(T),length*width);
        this->length = length;
        this->width=width;
    }
    void clear()
    {
        memset(ptr,0,sizeof(T)*length*width);
    }
    ~twoarray()
    {
        delete[] ptr;
    }
};
class bumpchecker
{
private:
    //ָ�����
    std::vector<Cmd> cmds;
    //������ά����
    twoarray<pointer> blockmap;
    twoarray<Mcmd *> movemap;
    //��ײ����
    std::map<std::pair<mpointer,pointer>,bool> bumpdata;
    std::set<mpointer > md_list;
    std::set<pointer > d_list;
public:
    bumpchecker(int width,int length);
    //��ʼ��ָ�����
    void init();
    //����ָ�����
    void complie();
    //����ָ�����
    void RunMcmd();
    //ִ��ָ�����
    void runCmd();

    //��ȫ�ƶ�ָ������е�Ԫ��
    void checker_move();

    //��ȡ��Ӧָ��
    Cmd &operator[](mpointer pointer);

    void remove(pointer );
    void remove(mpointer );

    void rdremove(pointer );
    void rdremove(mpointer );

    void add(pointer );
    void add(mpointer );
};
bool bumphandle(mpointer,pointer,bumpchecker *);
}
#endif // NBUMPCHECKER_H_INCLUDED