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
LPDIRECT3DSURFACE9 surface = NULL;  
LPDIRECT3DSURFACE9 ConstSurface = NULL;  


bool isKeyDown[256];
int mspf=30;//miliseconds per Frame
int fps;
HWND hwnd;
bool initdirectx();
void freedirectx();

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
  
    //create surface  
	HRESULT result = d3ddev->CreateOffscreenPlainSurface(  
        100,                //width of the surface  
        100,                //height of the surface  
        D3DFMT_X8R8G8B8,    //surface format  
        D3DPOOL_DEFAULT,    //memory pool to use  
        &ConstSurface,           //pointer to the surface  
        NULL);              //reserved (always NULL)  
  
    if (!SUCCEEDED(result)) return false;  
    result = d3ddev->CreateOffscreenPlainSurface(  
        100,                //width of the surface  
        100,                //height of the surface  
        D3DFMT_X8R8G8B8,    //surface format  
        D3DPOOL_DEFAULT,    //memory pool to use  
        &surface,           //pointer to the surface  
        NULL);              //reserved (always NULL)  
    if (!SUCCEEDED(result)) return false; 
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
