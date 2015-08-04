#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <stdio.h>
#include <d3d9.h>
#include <iostream>

//#include <d3dx9.h>
void init();
void flush();
void destory();
void TRACE(LPCTSTR format,...);
extern bool isKeyDown[];
extern int fps;
extern int mspf;
extern HWND hwnd;

extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;
extern LPDIRECT3DSURFACE9 backbuffer1;
extern LPDIRECT3DSURFACE9 enemy[8][8];
extern LPDIRECT3DSURFACE9 player1[4][8];
extern LPDIRECT3DSURFACE9 player2[4][8];
extern LPDIRECT3DSURFACE9 block[3];
extern LPDIRECT3DSURFACE9 water[2];
extern LPDIRECT3DSURFACE9 headquarters[2];
extern LPDIRECT3DSURFACE9 bonus[6];//奖励，依次是，0坦克，1定时，2铁铲，3炸弹，4星星，5安全帽
extern LPDIRECT3DSURFACE9 explode[2];//爆炸，两种规格，0表示28*28,子弹碰到墙，1表示64*64，子弹打到tank
extern LPDIRECT3DSURFACE9 bulletbmp[4];//子弹，上右下左
extern LPDIRECT3DSURFACE9 bore[4];
extern LPDIRECT3DSURFACE9 flag;
extern LPDIRECT3DSURFACE9 misc[4];
extern LPDIRECT3DSURFACE9 gameover;
extern LPDIRECT3DSURFACE9 num[10];
extern LPDIRECT3DSURFACE9 shield[2];
#endif // MAIN_H_INCLUDED
