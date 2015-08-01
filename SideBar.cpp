#include "SideBar.h"
#include "stdarg.h"
void shownum(int n,RECT rec)
{
	do{
		d3ddev->StretchRect(num[n%10], NULL, backbuffer, &rec, D3DTEXF_NONE);
		n/=10;
		rec.left-=16;
		rec.right-=16;
	}while(n);

}
void drawsidebar()
{
	RECT rec;
	//show剩余地方tank数量
	rec.top=10;
	rec.left=40;
	rec.bottom=rec.top+14;
	rec.bottom=rec.top+14;
    for(int i=0;i<ertank;i++)
	{
		rec.top=10+16*(i/2);
		if(i&0x1)
            rec.left=40;
		else
			rec.left=56;
		rec.bottom=rec.top+14;
		rec.right=rec.left+14;
		d3ddev->StretchRect(misc[0], NULL, backbuffer, &rec, D3DTEXF_NONE);
	}
	//显示己方IPtank
	rec.top=210;
	rec.left=20;
	rec.bottom=224;
	rec.right=48;
    d3ddev->StretchRect(misc[2], NULL, backbuffer, &rec, D3DTEXF_NONE);
	rec.top=226;
	rec.left=20;
	rec.right=34;
	rec.bottom=240;
	d3ddev->StretchRect(misc[1], NULL, backbuffer, &rec, D3DTEXF_NONE);
	rec.top=226;
	rec.left=72;
	rec.bottom=242;
	rec.right=88;
	shownum(tanks[0]-1,rec);
	//显示己方IIPtank
	rec.top=300;
	rec.left=20;
	rec.bottom=314;
	rec.right=48;
	d3ddev->StretchRect(misc[3], NULL, backbuffer, &rec, D3DTEXF_NONE);
	rec.top=316;
	rec.left=20;
	rec.right=34;
	rec.bottom=330;
	d3ddev->StretchRect(misc[1], NULL, backbuffer, &rec, D3DTEXF_NONE);
	rec.top=316;
	rec.left=72;
	rec.right=88;
	rec.bottom=332;
	shownum(tanks[1]-1,rec);
	//显示旗帜
	rec.top=380;
	rec.left=10;
	rec.right=42;
	rec.bottom=412;
	d3ddev->StretchRect(flag, NULL, backbuffer, &rec, D3DTEXF_NONE);
	rec.left=76;
	rec.right=92;
	rec.bottom=412;
	rec.top=396;
	shownum(CLevel,rec);


}
