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
    }  
}

void destory(){

}
