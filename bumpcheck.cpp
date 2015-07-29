/*
此文件是bumpchecker.h文件中模板函数的实现
*/
#ifndef bumpchecker_HPP
#define bumpchecker_HPP
#include "bumpcheck.h"
namespace bump
{
bumpchecker::bumpchecker(int width, int hight) :bmap(width,hight)
{
    this->width = width;
    this->hight = hight;
}

bool bumpchecker::is_out(pair<int, int> pos)
{
    if (pos.first >= width) return true;
    if (pos.second >= hight) return true;
    if (pos.first < 0) return true;
    if (pos.second < 0) return true;
    return false;
}

int bumpchecker::move(mpointer a, direct drt)
{
    //先移动一个单位
    a->move(drt);
    set<pointer> p;
    //获取a的轮廓
    posSet *pp = a->getRange();
    pointer pti = 0;
    bool is_ouf = true;
    //遍历轮廓
    for(posSet::iterator bi=(*pp).begin(); bi!=(*pp).end(); bi++)
    {
        posSet::const_reference b=*bi;
        //判断是否出边界
        if (is_out(b))
        {
            if (is_ouf)
            {
                p.insert(0);
                is_ouf = false;
            }
            continue;
        }
        pointer *pt = &bmap[b.second][b.first];
        //判断是否碰撞
        if (*pt != 0 && *pt != a)
        {
            p.insert((*pt));
        }
    }
    int n = bumpType::through;
    //检测是否有碰撞
    for(set<pointer>::iterator ci=(p).begin(); ci!=(p).end(); ci++)
    {
        pointer b=*ci;
        n |= a->bump(b,drt);
    }
    if (n&bumpType::astop)
    {
        //如果碰撞应该停止移回原位
        a->move(!drt);
    }
    else
    {
#ifdef CPP11
        lock.lock();
#endif
        //移除碰撞系统
        remove(a);
#ifndef CPP11
        add(a);
#endif // CPP11
#ifdef CPP11
        //如果加入失败再退一步重新加入
        while (add(a) == 0)
        {
            for(set<pointer *>::iterator di=(a->occupy).begin(); di!=(a->occupy).end(); di++)
            {
                pointer *b=*di;
                *b = 0;
            }
            a->occupy.clear();
            a->move(!drt);
        }
        lock.unlock();
#endif
    }
    return n;
}

//调用之前的move函数移动a
int bumpchecker::move(mpointer a, direct drt, int size)
{
    while (size--)
    {
        int n = move(a, drt);
        if (n&bumpType::astop)
        {
            return n;
        }
    }
    return bumpType::through;
}

//加入碰撞检测
pointer bumpchecker::add(pointer a)
{
    int flag=1;
    posSet *p = a->getRange();
    for(posSet::iterator bi=(*p).begin(); bi!=(*p).end(); bi++)
    {
        posSet::value_type b=*bi;
        pointer *c = &bmap[b.second][b.first];
        //如果加入冲突的组件 返回null
        //不进行错误处理
        if (*c != 0) flag=0;
        else
        {
            *c = a;
            a->occupy.insert(c);
        }
    }
    if(flag==0)
        return 0;
    return a;
}
//从碰撞检测系统中移除该组件
void bumpchecker::remove(pointer a)
{
    //printf("removeing %p\n");
    for(set<pointer*>::iterator bi=(a->occupy).begin(); bi!=(a->occupy).end(); bi++)
    {
        pointer *b=*bi;
        *b = 0;
    }
    for (int i = 0; i < hight; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (bmap[i][j] == a)
            {
                printf("");
                getchar();
            }
        }
    }
    a->occupy.clear();
}
bumpchecker::~bumpchecker() {}
}
#endif
