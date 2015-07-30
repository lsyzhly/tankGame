#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "main.h"
#include <time.h>
#include <iostream>
#define LPCWSTR LPCSTR

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);



LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backbuffer = NULL;
LPDIRECT3DSURFACE9 enemy[8][8];
LPDIRECT3DSURFACE9 player1[4][8];
LPDIRECT3DSURFACE9 player2[4][8];
LPDIRECT3DSURFACE9 block[3];//0砖块，1铁块，2草地
LPDIRECT3DSURFACE9 water[2];//水的两种形态
LPDIRECT3DSURFACE9 headquarters[2];//司令部，两种形态，0表示沦陷，1表示存在
LPDIRECT3DSURFACE9 bonus[6];//奖励，依次是，0坦克，1定时，2铁铲，3炸弹，4星星，5安全帽
LPDIRECT3DSURFACE9 explode[2];//爆炸，两种规格，0表示28*28,子弹碰到墙，1表示64*64，子弹打到tank{还没开始写show}
LPDIRECT3DSURFACE9 bulletbmp[4];//子弹，上右下左

bool isKeyDown[256];
HWND hwnd;
int mspf=30;//miliseconds per Frame
int fps;
bool initdirectx();
void freedirectx();
bool TankInit(LPCWSTR f,LPDIRECT3DSURFACE9 *sur,int m,int n);//传入对应二维数组（enemy，player1，player2），对tank的surface初始化
bool BlockInit(LPCWSTR f,LPDIRECT3DSURFACE9 *bs);
bool WaterAndHeadquartersInit(LPCWSTR f,LPDIRECT3DSURFACE9 *wa,LPDIRECT3DSURFACE9 *hq);
bool BonusInit(LPCWSTR f,LPDIRECT3DSURFACE9 *bn);
bool ExplodeInit(LPCWSTR f1,LPCWSTR f2,LPDIRECT3DSURFACE9 *bn);
bool BulletbmpInit(LPCWSTR f,LPDIRECT3DSURFACE9 *bn);


bool BulletbmpInit(LPCWSTR f,LPDIRECT3DSURFACE9 *bn)
{
    HRESULT result;
    for(int i=0; i<4; i++)
    {
        result = d3ddev->CreateOffscreenPlainSurface(
                     8,                //width of the surface
                     8,                //height of the surface
                     D3DFMT_X8R8G8B8,    //surface format
                     D3DPOOL_DEFAULT,    //memory pool to use
                     bn + i,           //pointer to the surface  bo
                     NULL);
        if (!SUCCEEDED(result)) return false;
        RECT rec;
        rec.top=0;
        rec.bottom=rec.top+8;
        rec.left=i*8;
        rec.right=rec.left+8;
        result=D3DXLoadSurfaceFromFile(
                   *(bn+i),            //destination surface
                   NULL,               //destination palette
                   NULL,               //destination rectangle
                   f,                  //source filename
                   &rec,               //source rectangle
                   D3DX_DEFAULT,       //controls how image is filtered
                   0,                  //for transparency (0 for none)
                   NULL);

        if (!SUCCEEDED(result)) return false;
//     d3ddev->StretchRect(bulletbmp[i], NULL, backbuffer, &rec, D3DTEXF_NONE);
    }
    return true;
}



bool ExplodeInit(LPCWSTR f1,LPCWSTR f2,LPDIRECT3DSURFACE9 *bn)
{
    HRESULT result;
    result = d3ddev->CreateOffscreenPlainSurface(
                 28,                //width of the surface
                 28,                //height of the surface
                 D3DFMT_X8R8G8B8,    //surface format
                 D3DPOOL_DEFAULT,    //memory pool to use
                 bn,           //pointer to the surface  bo
                 NULL);
    if (!SUCCEEDED(result)) return false;
    RECT rec;
    rec.top=0;
    rec.bottom=rec.top+28;
    rec.left=0;
    rec.right=rec.left+28;
    result=D3DXLoadSurfaceFromFile(
               *(bn),            //destination surface
               NULL,               //destination palette
               NULL,               //destination rectangle
               f1,                  //source filename
               &rec,               //source rectangle
               D3DX_DEFAULT,       //controls how image is filtered
               0,                  //for transparency (0 for none)
               NULL);

    if (!SUCCEEDED(result)) return false;
    result = d3ddev->CreateOffscreenPlainSurface(
                 64,                //width of the surface
                 64,                //height of the surface
                 D3DFMT_X8R8G8B8,    //surface format
                 D3DPOOL_DEFAULT,    //memory pool to use
                 bn+1,           //pointer to the surface  bo
                 NULL);
    if (!SUCCEEDED(result)) return false;
    rec.top=0;
    rec.bottom=rec.top+64;
    rec.left=0;
    rec.right=rec.left+64;
    result=D3DXLoadSurfaceFromFile(
               *(bn+1),            //destination surface
               NULL,               //destination palette
               NULL,               //destination rectangle
               f2,                  //source filename
               &rec,               //source rectangle
               D3DX_DEFAULT,       //controls how image is filtered
               0,                  //for transparency (0 for none)
               NULL);

    if (!SUCCEEDED(result)) return false;
    //	  d3ddev->StretchRect(bonus[i], NULL, backbuffer, &rec, D3DTEXF_NONE);
    return true;
}


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;
    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "press w",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          SCREENW,
                          SCREENH,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);
    if(!initdirectx())
    {
        ;
    }
    init();
    /* program main loop */
    while (true)
    {
        clock_t start=clock();
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                break;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
        flush();
        d3ddev->Present(NULL, NULL, NULL, NULL);
        clock_t end=clock();
        end-=start;
        end*=1000;
        end/=CLOCKS_PER_SEC;
        if(end<mspf)
        {
            Sleep(mspf-end);
            end=mspf;
        }
        if(end)
            fps=1000/end;
        else
            fps=0;
    }
    freedirectx();
    destory();
    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

bool initdirectx()
{
    //initialize Direct3D
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (d3d == NULL)
    {
        return false;
    }

    //set Direct3D presentation parameters
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = SCREENW;
    d3dpp.BackBufferHeight = SCREENH;
    d3dpp.hDeviceWindow = hwnd;

    //create Direct3D device
    d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
                       D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

    if (!d3ddev)
    {
        return false;
    }

    //clear the backbuffer to black
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);

    //create pointer to the back buffer
    d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
    TankInit("graphics/player1.bmp",(LPDIRECT3DSURFACE9 *)player1,4,8);
    TankInit("graphics/player2.bmp",(LPDIRECT3DSURFACE9 *)player2,4,8);
    TankInit("graphics/enemy.bmp",(LPDIRECT3DSURFACE9 *)enemy,8,8);
    BlockInit("graphics/tile.bmp",(LPDIRECT3DSURFACE9 *)&block);
    WaterAndHeadquartersInit("graphics/tile.bmp",(LPDIRECT3DSURFACE9 *)&water,(LPDIRECT3DSURFACE9 *)&headquarters);
    BonusInit("graphics/bonus.bmp",(LPDIRECT3DSURFACE9 *)&bonus);
    ExplodeInit("graphics/explode1.bmp","graphics/explode2.bmp",(LPDIRECT3DSURFACE9 *)&explode);
    BulletbmpInit("graphics/bullet.bmp",(LPDIRECT3DSURFACE9 *)&bulletbmp);



    return true;
}

bool BonusInit(LPCWSTR f,LPDIRECT3DSURFACE9 *bn)
{
    HRESULT result;
    for(int i=0; i<6; i++)
    {
        result = d3ddev->CreateOffscreenPlainSurface(
                     28,                //width of the surface
                     28,                //height of the surface
                     D3DFMT_X8R8G8B8,    //surface format
                     D3DPOOL_DEFAULT,    //memory pool to use
                     bn + i,           //pointer to the surface  bo
                     NULL);
        if (!SUCCEEDED(result)) return false;
        RECT rec;
        rec.top=0;
        rec.bottom=rec.top+28;
        rec.left=i*30;
        rec.right=rec.left+30;
        result=D3DXLoadSurfaceFromFile(
                   *(bn+i),            //destination surface
                   NULL,               //destination palette
                   NULL,               //destination rectangle
                   f,                  //source filename
                   &rec,               //source rectangle
                   D3DX_DEFAULT,       //controls how image is filtered
                   0,                  //for transparency (0 for none)
                   NULL);

        if (!SUCCEEDED(result)) return false;
        //	  d3ddev->StretchRect(bonus[i], NULL, backbuffer, &rec, D3DTEXF_NONE);
    }
    return true;
}


bool WaterAndHeadquartersInit(LPCWSTR f,LPDIRECT3DSURFACE9 *wa,LPDIRECT3DSURFACE9 *hq)
{
    HRESULT result;
    RECT rec;
    for(int i=0; i<2; i++)
    {
        result = d3ddev->CreateOffscreenPlainSurface(
                     32,                //width of the surface
                     32,                //height of the surface
                     D3DFMT_X8R8G8B8,    //surface format
                     D3DPOOL_DEFAULT,    //memory pool to use
                     wa + i,           //pointer to the surface  bo
                     NULL);
        if (!SUCCEEDED(result)) return false;
        rec.top=0;
        rec.bottom=rec.top+32;
        rec.left=(i+3)*32;
        rec.right=rec.left+32;
        result=D3DXLoadSurfaceFromFile(
                   *(wa+i),            //destination surface
                   NULL,               //destination palette
                   NULL,               //destination rectangle
                   f,                  //source filename
                   &rec,               //source rectangle
                   D3DX_DEFAULT,       //controls how image is filtered
                   0,                  //for transparency (0 for none)
                   NULL);

        if (!SUCCEEDED(result)) return false;

//				  d3ddev->StretchRect(water[i], NULL, backbuffer, &rec, D3DTEXF_NONE);
        result = d3ddev->CreateOffscreenPlainSurface(
                     32,                //width of the surface
                     32,                //height of the surface
                     D3DFMT_X8R8G8B8,    //surface format
                     D3DPOOL_DEFAULT,    //memory pool to use
                     hq+ i,           //pointer to the surface  bo
                     NULL);
        if (!SUCCEEDED(result)) return false;
        rec.top=0;
        rec.bottom=rec.top+32;
        rec.left=(i+5)*32;
        rec.right=rec.left+32;
        result=D3DXLoadSurfaceFromFile(
                   *(hq+i),            //destination surface
                   NULL,               //destination palette
                   NULL,               //destination rectangle
                   f,                  //source filename
                   &rec,               //source rectangle
                   D3DX_DEFAULT,       //controls how image is filtered
                   0,                  //for transparency (0 for none)
                   NULL);

        if (!SUCCEEDED(result)) return false;
//				  d3ddev->StretchRect(headquarters[i], NULL, backbuffer, &rec, D3DTEXF_NONE);

    }
    return true;
}


bool TankInit(LPCWSTR f,LPDIRECT3DSURFACE9 *sur,int m,int n)
{
    HRESULT result;
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
        {
            result = d3ddev->CreateOffscreenPlainSurface(
                         28,                //width of the surface
                         28,                //height of the surface
                         D3DFMT_X8R8G8B8,    //surface format
                         D3DPOOL_DEFAULT,    //memory pool to use
                         sur + n*i + j,           //pointer to the surface  bo
                         NULL);
            if (!SUCCEEDED(result)) return false;
            RECT rec;
            rec.top=i*28;
            rec.bottom=rec.top+28;
            rec.left=j*28;
            rec.right=rec.left+28;
            result=D3DXLoadSurfaceFromFile(
                       *(sur + n*i + j),            //destination surface
                       NULL,               //destination palette
                       NULL,               //destination rectangle
                       f,                  //source filename
                       &rec,               //source rectangle
                       D3DX_DEFAULT,       //controls how image is filtered
                       0,                  //for transparency (0 for none)
                       NULL);

            if (!SUCCEEDED(result)) return false;
        }
    return true;

}
bool BlockInit(LPCWSTR f,LPDIRECT3DSURFACE9 *bs)
{
    HRESULT result;
    for(int i=0; i<3; i++)
    {
        result = d3ddev->CreateOffscreenPlainSurface(
                     16,                //width of the surface
                     16,                //height of the surface
                     D3DFMT_X8R8G8B8,    //surface format
                     D3DPOOL_DEFAULT,    //memory pool to use
                     bs + i,           //pointer to the surface  bo
                     NULL);
        if (!SUCCEEDED(result)) return false;
        RECT rec;
        rec.top=0;
        rec.bottom=rec.top+16;
        rec.left=i*32;
        rec.right=rec.left+16;
        result=D3DXLoadSurfaceFromFile(
                   *(bs+i),            //destination surface
                   NULL,               //destination palette
                   NULL,               //destination rectangle
                   f,                  //source filename
                   &rec,               //source rectangle
                   D3DX_DEFAULT,       //controls how image is filtered
                   0,                  //for transparency (0 for none)
                   NULL);

        if (!SUCCEEDED(result)) return false;
    }
    return true;
}

void freedirectx()
{
    if (d3ddev) d3ddev->Release();
    if (d3d) d3d->Release();
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
    {
        switch(wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        default:
            isKeyDown[wParam]=true;
            break;
        }
    }
    break;
    case WM_KEYUP:
        isKeyDown[wParam]=false;
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
