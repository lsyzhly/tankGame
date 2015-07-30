#ifndef MAINCONTROL_H
#define MAINCONTROL_H
#include <map>
#include <set>
#include <memory.h>
#include "all.h"
using namespace bump;
using namespace item;
using namespace view;
using namespace Controler;

extern bumpchecker *checker;

//��������ɾ���б�,�����������count����Ļˢ�º�ɾ��
void add_to_delete(pointer a, int count);
//������
void addItem(pointer a,bool isTop=false);
//��ӿ�����
void addControl(cpointer a);
//����ײ���ϵͳ
void bindbumpchecker(bumpchecker *checker);
//�����ɾ�����
void clean();

void runControls();

void rePaint();

void remove(pointer a);
void remove(cpointer a);

void freeAll();

typedef void (*OnTime)(...);

template <int size>
class MEMSTRUCT
{
public:
    char a[size];
    OnTime func;
    int count;
    void init(OnTime fun,char *ptr,int count)
    {
        func=fun;
        memcpy(a,ptr,size);
        this->count=count;
    }
    bool operator()()
    {
        if(--count==0)
            func(*this);
		return count;
    }
};
//ע��ʱ���¼�
//nΪ�¼�id OnTime�¼���Ӧ����,nΪ��Ӧʱ��,...Ϊ�Զ������
//�Զ�������ܴ�С���ܴ���64�ֽ�
void addTimeFun(unsigned char id,OnTime on,int n,...);
//����ĳ��Ӫ̹��״̬ isΪҪ���õ�̹����Ӫ
//is_runΪҪ���õ�״̬
void setTankState(bool is,bool is_run);
void setCapTankState(Tank *theTank,bool stoppable);
void deleteTank(bool type);
void OnPlayerTank(bool type);
#endif
