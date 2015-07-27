#include <windows.h> 
#include <d3d9.h>  
#include <d3dx9.h>
#include "main.h"
#include <time.h>
#include <iostream>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);



LPDIRECT3D9 d3d = NULL;   
LPDIRECT3DDEVICE9 d3ddev = NULL;   
LPDIRECT3DSURFACE9 backbuffer = NULL;  
LPDIRECT3DSURFACE9 enemy[8][8];
LPDIRECT3DSURFACE9 player1[4][8];
LPDIRECT3DSURFACE9 player2[4][8];



bool isKeyDown[256];
int mspf=30;//miliseconds per Frame
int fps;
HWND hwnd;
bool initdirectx();
void freedirectx();
bool TankInit(LPCWSTR f,LPDIRECT3DSURFACE9 *sur,int m,int n);//传入对应二维数组（enemy，player1，player2），对tank的surface初始化

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
    wcex.lpszClassName = L"GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;
    /* create main window */
    hwnd = CreateWindowEx(0,
                          L"GLSample",
                          L"press w",
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
	if(!initdirectx()){
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
        flush();
		d3ddev->Present(NULL, NULL, NULL, NULL);  
        clock_t end=clock();
        end-=start;
        end*=1000;
        end/=CLOCKS_PER_SEC;
        if(end<mspf){
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

bool initdirectx(){
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
	TankInit(L"graphics/player1.bmp",(LPDIRECT3DSURFACE9 *)player1,4,8);
	TankInit(L"graphics/player2.bmp",(LPDIRECT3DSURFACE9 *)player2,4,8);
	TankInit(L"graphics/enemy.bmp",(LPDIRECT3DSURFACE9 *)enemy,8,8);

  
 
    return true;  
}
	bool TankInit(LPCWSTR f,LPDIRECT3DSURFACE9 *sur,int m,int n)
	{
		HRESULT result;
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
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

void freedirectx(){  
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
