/*
���ļ���bumpchecker.h�ļ���ģ�庯����ʵ��
*/
#ifndef bumpchecker_HPP
#define bumpchecker_HPP
#include "bumpcheck.h"
#include "assert.h"
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
        sList &pt = bmap[b.second][b.first];
        for(sList::iterator i=pt.begin();i!=pt.end();i++){
            if(*i==a){
                goto st1;
            }
        }
        for(sList::iterator i=pt.begin();i!=pt.end();i++){
            p.insert(*i);
        }
        st1:;
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
        remove(a);
        add(a);
    }
    return n;
}

//����֮ǰ��move�����ƶ�a
int bumpchecker::move(mpointer a, direct drt, int size)
{
    int m=0;
    while (size--)
    {
        int n = move(a, drt);
        if (n&bumpType::astop)
        {
            a->moveDirect(drt,m);
            return n;
        }
        m++;
    }
    a->moveDirect(drt,m);
    return bumpType::through;
}

//������ײ���
pointer bumpchecker::add(pointer a)
{
    int flag=1;
    posSet *p = a->getRange();
    a->occupy.clear();
    for(posSet::iterator bi=(*p).begin(); bi!=(*p).end(); bi++)
    {
        posSet::value_type b=*bi;
        if(is_out(b))continue;
        sList &c = bmap[b.second][b.first];
        c.push_front(a);
        a->occupy.insert(&c);
    }
    return a;
}
//����ײ���ϵͳ���Ƴ������
void bumpchecker::remove(pointer a)
{
    for(set<sList *>::iterator bi=(a->occupy).begin(); bi!=(a->occupy).end(); bi++)
    {
        sList *b=*bi;
        sList::iterator bfi=b->before_begin();
        sList::iterator bbi=bfi++;
        while(bfi!=b->end()){
            if(*bfi==a){
                b->erase_after(bbi);
                break;
            }
            ++bbi;
            ++bfi;
        }
    }
    a->occupy.clear();
}
bumpchecker::~bumpchecker() {}
}
#endif
