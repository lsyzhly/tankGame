/*
���ļ���bumpchecker.h�ļ���ģ�庯����ʵ��
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
    //���ƶ�һ����λ
    a->move(drt);
    set<pointer> p;
    //��ȡa������
    posSet *pp = a->getRange();
    pointer pti = 0;
    bool is_ouf = true;
    //��������
    for(posSet::iterator bi=(*pp).begin(); bi!=(*pp).end(); bi++)
    {
        posSet::const_reference b=*bi;
        //�ж��Ƿ���߽�
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
        //�ж��Ƿ���ײ
        if (*pt != 0 && *pt != a)
        {
            p.insert((*pt));
        }
    }
    int n = bumpType::through;
    //����Ƿ�����ײ
    for(set<pointer>::iterator ci=(p).begin(); ci!=(p).end(); ci++)
    {
        pointer b=*ci;
        n |= a->bump(b,drt);
    }
    if (n&bumpType::astop)
    {
        //�����ײӦ��ֹͣ�ƻ�ԭλ
        a->move(!drt);
    }
    else
    {
#ifdef CPP11
        lock.lock();
#endif
        //�Ƴ���ײϵͳ
        remove(a);
#ifndef CPP11
        add(a);
#endif // CPP11
#ifdef CPP11
        //�������ʧ������һ�����¼���
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

//����֮ǰ��move�����ƶ�a
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

//������ײ���
pointer bumpchecker::add(pointer a)
{
    int flag=1;
    posSet *p = a->getRange();
    for(posSet::iterator bi=(*p).begin(); bi!=(*p).end(); bi++)
    {
        posSet::value_type b=*bi;
        pointer *c = &bmap[b.second][b.first];
        //��������ͻ����� ����null
        //�����д�����
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
//����ײ���ϵͳ���Ƴ������
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
