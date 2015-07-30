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
        pointer pt = bmap[b.second][b.first];
        //�ж��Ƿ���ײ
        while(pt!=0){
            if(pt!=a){
                p.insert(pt);
            }
            pt=pt->next;
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
        pointer *c = &bmap[b.second][b.first];
        fprintf(fpi,"inserting %p to %p\n",a,c);
        a->next=*c;
        *c=a;
        fprintf(fpi,"answer:\n");
        for(pointer f=bmap[b.second][b.first];f!=0;f=f->next){
            fprintf(fpi,"%p\n",f);
        }
        fflush(fpi);
        a->occupy.insert(&bmap[b.second][b.first]);
        for(pointer q=bmap[b.second][b.first];q!=0;q=q->next){
            if(q==a){
                goto st1;
            }
        }
        throw a;
        st1:;
    }
    return a;
}
//����ײ���ϵͳ���Ƴ������
void bumpchecker::remove(pointer a)
{
    for(set<pointer*>::iterator bi=(a->occupy).begin(); bi!=(a->occupy).end(); bi++)
    {
        pointer *b=*bi;
        int n=b-bmap.ptr;
        fprintf(fpi,"removing %p from %p\n",a,b);
        fflush(fpi);
        if(*b==0){
            throw a;
        }else if((*b)->next==0){
            if(*b==a){
                *b=0;
            }else{
                fprintf(fpi,"in %p:\n",b);
                for(pointer pa=*b;pa!=0;pa=pa->next){
                    fprintf(fpi,"%p\n",pa);
                }
                fflush(fpi);
                throw a;
            }
        }else{
            pointer c=*b,d=c->next;
            while(d!=0){
                if(d==a){
                    c->next=d->next;
                    goto st3;
                }
                c=d;
                d=d->next;
            }
            throw a;
            st3:;
        }
        fprintf(fpi,"answer:\n");
        for(pointer f=*b;f!=0;f=f->next){
            fprintf(fpi,"%p\n",f);
        }
        fflush(fpi);
    }
    a->occupy.clear();
}
bumpchecker::~bumpchecker() {}
}
#endif
