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
extern LPDIRECT3DSURFACE9 surface;  
extern LPDIRECT3DSURFACE9 ConstSurface;  

#endif // MAIN_H_INCLUDED
