#ifndef ITEM_H
#define ITEM_H
#include <set>
#include "view.h"
#include "all.h"
using std::set;
using std::pair;
using Controler::cpointer;
typedef set<pair<int, int>> posSet;
namespace item{
	using view::Show;
	class Bullet;
	//���������,��������Ļ���,������
	class square{
	protected:
	public:
		//x,y��ʾ������λ�� sizeΪ�߳�
		int x;
		int y;
		int size;
		//��������
		posSet pos_set;
		//��ͼ��
		Show *draw;
		//ָ��������Ӧ���ָ��
		set<square**> occupy;

		square(int x, int y, int size, Show *draw);
		//��ȡ��������
		virtual posSet *getRange();
		virtual ~square();
	};
	//���ƶ�������
	class moveSquare :public square{
	public:
		//�ƶ�����
		direct drt;
		//�ƶ��ٶ�
		int speed;
		cpointer control;
		moveSquare(int x, int y, int size, Show *draw, direct drt, int speed);
		//��drt�����ƶ�һ����λ
		virtual void move(direct drt);
		//��ײ������,������ײ����
		virtual bumpType bump(square *a,direct drt) = 0;
		virtual ~moveSquare();
	};
	//�����ƶ�������
	class unmoveSquare :public square{
	public:
		//�����ƶ����� ����ʹtie��tu
		unmoveType utype;
		unmoveSquare(int x, int y, int size,Show *draw, unmoveType utype);
		virtual ~unmoveSquare();
	};

	//Tank��
	class Tank :public moveSquare{
	public:
		//������ӵ��ļ���
		set<Bullet *> bullet_set;
		//�����ӵ����������
		int maxbullets;
		int pvalue;//����ֵ
		//�ӵ���С
		int bullet_size;
		//�ӵ��ٶ�
		int bullet_speed;
		bool isPlayer;
		Tank(int x, int y, int size, int speed, direct drt,Show *draw,
			int maxbullets, int pvalue, int bullet_size, int bullet_speed,bool isPlayer);
		//��ײ������
		virtual bumpType bump(square *a,direct drt);
		virtual void reDirect(direct drt);
		//����
		Bullet *fire();
		virtual ~Tank();
	};

	class Bullet :public moveSquare{
	public:
		//��������ӵ���̹��
		Tank *t;
		Bullet(Tank *t, int x, int y, int size,int speed,Show *draw);
		virtual bumpType bump(square *a,direct drt);
		virtual ~Bullet();
	};
}
#endif
