#include <windows.h>
#include "main.h"
#include <stdio.h>
void init(){
    mspf=30;
}

void flush(){
    //make sure the Direct3D device is valid  
    if (!d3ddev) return;  
	static int n=0;
    //start rendering  
    if (d3ddev->BeginScene())  
    {  
			RECT recti;
		if(n==0){

			recti.left = SCREENW/5;  
			recti.right = SCREENW/5+224;  
			recti.top = SCREENH/5;  
			recti.bottom = SCREENH/5+112; 
			HRESULT resul=D3DXLoadSurfaceFromFile(  
			ConstSurface,            //destination surface  
			NULL,               //destination palette  
			NULL,               //destination rectangle  
			"D:\\banana.bmp",     //source filename  
			NULL,               //source rectangle  
			D3DX_DEFAULT,       //controls how image is filtered  
			0,                  //for transparency (0 for none)  
			NULL);
			if(!SUCCEEDED(resul)){
				OutputDebugString("wrong!\n");
			}
			d3ddev->StretchRect(ConstSurface, NULL, backbuffer, &recti, D3DTEXF_NONE);  
		}
        //fill the surface with random color  
        int r = rand() % 255;  
        int g = rand() % 255;  
        int b = rand() % 255;  
        d3ddev->ColorFill(surface, NULL, D3DCOLOR_XRGB(r,g,b));  
  
        //copy the surface to the backbuffer  
        RECT rect;  
        rect.left = 0;  
        rect.right = SCREENW/4;  
        rect.top = 0;  
        rect.bottom = SCREENH/4;  
        d3ddev->StretchRect(surface, NULL, backbuffer, &rect, D3DTEXF_NONE);  
      
		d3ddev->StretchRect(ConstSurface, NULL, backbuffer, &recti, D3DTEXF_NONE);  
        //stop rendering  
        d3ddev->EndScene();  
  
        //display the back buffer on the screen  
        d3ddev->Present(NULL, NULL, NULL, NULL);  
    }  
}

void destory(){

}
