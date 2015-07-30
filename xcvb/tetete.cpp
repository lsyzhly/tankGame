#include <fstream>
#include <iostream>
#define SCREENW 1024   
#define SCREENH 768 
using namespace std;
    LPDIRECT3D9 d3d = NULL;   
    LPDIRECT3DDEVICE9 d3ddev = NULL;   
    LPDIRECT3DSURFACE9 backbuffer = NULL; 
    LPDIRECT3DSURFACE9 enemy[8][8];
	LPDIRECT3DSURFACE9 player1[4][8];
	LPDIRECT3DSURFACE9 player2[4][8];
	bool TankInit(fstream &f,LPDIRECT3DSURFACE9 **sur,int m,int n)
	{
		HRESULT result
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
			{
			      result = d3ddev->CreateOffscreenPlainSurface(  
                                 100,                //width of the surface  
                                 100,                //height of the surface  
                                 D3DFMT_X8R8G8B8,    //surface format  
                                 D3DPOOL_DEFAULT,    //memory pool to use  
                                 sur + n*i + j;,           //pointer to the surface  bo
                                 NULL);
				  if (!SUCCEEDED(result)) return false;
				  RECT rec;
				  rec.top=i*28;
				  rec.bottom=top+28;
				  rec.left=j*28;
				  rec.right=rec.left+28;
				  resul=D3DXLoadSurfaceFromFile(  
				        *(sur + n*i + j),            //destination surface  
				        NULL,               //destination palette  
				        NULL,               //destination rectangle  
				        f,                  //source filename  
				        &rec,               //source rectangle  
				        D3DX_DEFAULT,       //controls how image is filtered  
				        0,                  //for transparency (0 for none)  
				        NULL);
				  d3ddev->StretchRect(*(sur + n*i + j), NULL, backbuffer, &rec, D3DTEXF_NONE);
			}
			d3ddev->EndScene();  
      
            //display the back buffer on the screen  
            d3ddev->Present(NULL, NULL, NULL, NULL);  
	}