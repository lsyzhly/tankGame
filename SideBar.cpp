#include "SideBar.h"
#include "stdarg.h"
void shownum(int n,RECT rec)
{
	do{
		d3ddev->StretchRect(num[n%10], NULL, backbuffer, &rec, D3DTEXF_NONE);
		n/=10;
		rec.left-=14;
		rec.right-=14;
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
	rec.left=4;
	rec.bottom=224;
	rec.right=32;
    d3ddev->StretchRect(misc[2], NULL, backbuffer, &rec, D3DTEXF_NONE);
	rec.right=102;
	rec.left=88;
	shownum(score[0],rec);
	rec.top=226;
	rec.left=4;
	rec.right=18;
	rec.bottom=240;
	d3ddev->StretchRect(misc[1], NULL, backbuffer, &rec, D3DTEXF_NONE);
	rec.top=226;
	rec.left=72;
	rec.bottom=240;
	rec.right=86;
	shownum(tanks[0]-1,rec);
	//显示己方IIPtank
	rec.top=300;
	rec.left=4;
	rec.bottom=314;
	rec.right=32;
	d3ddev->StretchRect(misc[3], NULL, backbuffer, &rec, D3DTEXF_NONE);
	rec.left=88;
	rec.right=102;
	shownum(score[1],rec);
	rec.top=316;
	rec.left=4;
	rec.right=18;
	rec.bottom=330;
	d3ddev->StretchRect(misc[1], NULL, backbuffer, &rec, D3DTEXF_NONE);
	rec.top=316;
	rec.left=72;
	rec.right=86;
	rec.bottom=330;
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
void ongameover()
{
	RECT rec;
	rec.top=128;
	rec.bottom=288;
	rec.left=84;
	rec.right=332;
    d3ddev->StretchRect(gameover, NULL, backbuffer, &rec, D3DTEXF_NONE);
}
void onsplash(int playernum)
{
	RECT rec;
	rec.left=40;
	rec.right=72;
	rec.top=325;
	rec.bottom=357;
	if(1==playernum)
	{rec.top=384;rec.bottom=416;}
	RECT rec1;
	rec1.left =0;
	rec1.right=376;
	rec1.top=0;
	rec1.bottom=222;
	d3ddev->StretchRect(splash, NULL, backbuffer, NULL, D3DTEXF_NONE);
	d3ddev->StretchRect(player1[1][1], NULL, backbuffer, &rec, D3DTEXF_NONE);
     
}
