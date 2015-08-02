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
//微指令类
class Mcmd :public std::vector<pos>{
public:
    //微指令在指令中的位置
    unsigned int index;
    //对应的指令
    Cmd *fatherCmd;
    Mcmd();
};
//边长数组
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
//指令
class Cmd:public varArray<Mcmd>{
public:
    //操作目标
    mpointer target;
    //移动方向
    direct drt:8;
    //移动距离
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
    //指令队列
    std::vector<Cmd> cmds;
    //两个二维数组
    twoarray<pointer> blockmap;
    twoarray<Mcmd *> movemap;
    //碰撞缓存
    std::map<std::pair<mpointer,pointer>,bool> bumpdata;
public:
    bumpchecker(int width,int length);
    //执行指令队列
    void run_deque();
    //编译指令队列
    void complie();
    //添加到指令队列
    void add_to_deque(mpointer );
    //删除队列
    std::vector<int> deleteIndex;
    //获取
    Cmd &operator[](mpointer pointer);
    std::vector<pointer> blockList;
};
bool bumphandle(mpointer,pointer,bumpchecker *);

#endif // NBUMPCHECKER_H_INCLUDED
