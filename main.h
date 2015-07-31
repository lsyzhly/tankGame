#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <stdio.h>
#include <d3d9.h>
#include <iostream>

//#include <d3dx9.h>
void init();
void flush();
void destory();
extern bool isKeyDown[];
extern int fps;
extern int mspf;
extern HWND hwnd;

extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;
extern LPDIRECT3DSURFACE9 enemy[8][8];
extern LPDIRECT3DSURFACE9 player1[4][8];
extern LPDIRECT3DSURFACE9 player2[4][8];
extern LPDIRECT3DSURFACE9 block[3];
extern LPDIRECT3DSURFACE9 water[2];
extern LPDIRECT3DSURFACE9 headquarters[2];
extern LPDIRECT3DSURFACE9 bonus[6];//�����������ǣ�0̹�ˣ�1��ʱ��2������3ը����4���ǣ�5��ȫñ
extern LPDIRECT3DSURFACE9 explode[2];//��ը�����ֹ��0��ʾ28*28,�ӵ�����ǽ��1��ʾ64*64���ӵ���tank
extern LPDIRECT3DSURFACE9 bulletbmp[4];//�ӵ�����������
#endif // MAIN_H_INCLUDED
