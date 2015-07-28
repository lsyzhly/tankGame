#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <stdio.h>
#include <d3d9.h>  
#include <d3dx9.h>
#define SCREENW 640  
#define SCREENH 480  
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
extern LPDIRECT3DSURFACE9 bonus[6];//奖励，依次是，0坦克，1定时，2铁铲，3炸弹，4星星，5安全帽
extern LPDIRECT3DSURFACE9 explode[2];//爆炸，两种规格，0表示28*28,子弹碰到墙，1表示64*64，子弹打到tank
#endif // MAIN_H_INCLUDED
