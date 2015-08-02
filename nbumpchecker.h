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
class pos{
public:
    int x:16;
    int y:16;
    pos(int x,int y);
};
class Cmd;
//΢ָ����
class Mcmd :public std::vector<pos>{
public:
    //΢ָ����ָ���е�λ��
    unsigned int index;
    //��Ӧ��ָ��
    Cmd *fatherCmd;
    Mcmd();
};
//�߳�����
template<typename T>
class varArray{
protected:
    int size;
    T *ptr;
    varArray(){
        ptr=0;
    }
    varArray(int size){
        this->size=size;
        ptr=new T[size];
    }
    void reSize(int size){
        this->size=size;
        if(ptr) delete[] ptr;
        ptr=new T[size];
    }
    ~varArray(){
        if(ptr) delete[] ptr;
    }
public:
    T &operator[](int n){
        if(n>=size){
            throw n;
        }
        return ptr[n];
    }
};
//ָ��
class Cmd:public varArray<Mcmd>{
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
    void complie();
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
    void clear(){
        delete[] ptr;
        ptr = new T[length*width];
    }
    ~twoarray(){
        delete[] ptr;
    }
};
class bumpchecker{
private:
    //ָ�����
    std::vector<Cmd> cmds;
    //������ά����
    twoarray<pointer> blockmap;
    twoarray<Mcmd *> movemap;
    //��ײ����
    std::map<std::pair<mpointer,pointer>,bool> bumpdata;
public:
    bumpchecker(int width,int length);
    //ִ��ָ�����
    void run_deque();
    //����ָ�����
    void complie();
    //��ӵ�ָ�����
    void add_to_deque(mpointer );
    //ɾ������
    std::vector<int> deleteIndex;
    //��ȡ
    Cmd &operator[](mpointer pointer);
    std::vector<pointer> blockList;
};
bool bumphandle(mpointer,pointer,bumpchecker *);

#endif // NBUMPCHECKER_H_INCLUDED
