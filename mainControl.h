#ifndef MAINCONTROL_H
#define MAINCONTROL_H
#include <map>
#include <set>
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

#endif
