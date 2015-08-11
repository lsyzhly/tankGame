#ifndef MAINCONTROL_H
#define MAINCONTROL_H
#include <map>
#include <set>
#include <functional>
#include <memory.h>
#include "all.h"
using namespace bump;
using namespace item;
using namespace view;
using namespace Controler;

extern int tanks[];
extern bumpchecker *checker;
extern int score[];
extern int etanks;
extern unsigned char etank[20];
extern int ertank;
extern int CLevel;
extern int etanks;
extern int level;

//����ײ���ϵͳ
void bindbumpchecker(bumpchecker *checker);
//�����ɾ�����

//*********************
void clean();

void runControls();

void rePaint();

//ע��ʱ���¼�
//nΪ�¼�id OnTime�¼���Ӧ����,nΪ��Ӧʱ��
//�Զ�������ܴ�С���ܴ���64�ֽ�
void addTimeFun(unsigned char id,std::function<void (void )> func,int n);
void addTimeFun(std::function<void (void )> func,int n);
//����ĳ��Ӫ̹��״̬ isΪҪ���õ�̹����Ӫ
//is_runΪҪ���õ�״̬
void setTankState(bool is,bool is_run);
void setCapTankState(Tank *theTank,bool stoppable);
void deleteTank(bool type);
void OnPlayerTank(bool type);
void addEnemyTank();
#endif
