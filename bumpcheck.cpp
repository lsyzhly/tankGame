/*
���ļ���bumpchecker.h�ļ���ģ�庯����ʵ��
*/
#ifndef bumpchecker_HPP
#define bumpchecker_HPP
#include "bumpcheck.h"
#include "assert.h"
#include <algorithm>
namespace bump
{
bumpchecker::bumpchecker(int width, int hight) :bmap(width,hight)
{
    this->width = width;
    this->hight = hight;
    bmap[0][0].push_back(0);
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
    posSet *pp = a->getRange();
    set<pointer> ignore;
    bool is_ouf = true;
    for(posSet::iterator bi=(*pp).begin(); bi!=(*pp).end(); bi++)
    {
        posSet::const_reference b=*bi;
        //�ж��Ƿ���߽�
        if (is_out(b))
        {
            continue;
        }
        sList &pt = bmap[b.second][b.first];
        ignore.insert(pt.begin(),pt.end());
    }
    ignore.erase(0);
    //���ƶ�һ����λ
    a->move(drt);
    set<pointer> p;
    //��ȡa������
    pp = a->getRange();
    is_ouf = true;
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
                break;
            }
            p.insert(*i);
        }
    }
    int n = bumpType::through;
    for(set<pointer>::iterator ci=(ignore).begin(); ci!=(ignore).end(); ci++)
    {
        p.erase(*ci);
    }
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
        c.push_back(a);
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
        sList::iterator bf=b->begin();
        while(bf!=b->end()){
            fprintf(fpi,"removeing\n");
            fflush(fpi);
            if(*bf==a){
                b->erase(bf);
                break;
            }
            bf++;
        }
    }
    a->occupy.clear();
}
bumpchecker::~bumpchecker() {}
}
#endif
