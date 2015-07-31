
#include "sound.h"
void GameSound(HWND myHwnd,string path)
{
	LPDIRECTSOUND lpds;
    HRESULT hr = DirectSoundCreate(NULL, &lpds, NULL);
	if(hr!=DS_OK)
	{
		exit(0);
	}
	//xiugai
	hr=lpds->SetCooperativeLevel(myHwnd,DSSCL_PRIORITY );
	if(hr!=DS_OK)
	{
		TRACE("set");
	}
	DSCAPS dscaps;
    dscaps.dwSize = sizeof(DSCAPS);
    hr =lpds->GetCaps(&dscaps);
	if(hr!=DS_OK)
	{
		TRACE("get");
	}
    LPDIRECTSOUNDBUFFER pPbuf;//声明主缓存区指针
	DSBUFFERDESC desc;//描述结构
	memset(&desc,0,sizeof(desc));
	desc.dwSize=sizeof(desc);
	desc.dwFlags=DSBCAPS_PRIMARYBUFFER;//DSBCAPS_GLOBALFOCUS// | DSBCAPS_CTRLPOSITIONNOTIFY |DSBCAPS_GETCURRENTPOSITION2;DSBCAPS_PBJMARYBUFFER;
	desc.dwBufferBytes=0;
	desc.lpwfxFormat=NULL;
	hr=lpds->CreateSoundBuffer(&desc,&pPbuf,NULL);
	if(hr!=DS_OK)
	{
		TRACE("creat");
	}
		//设置格式
	WAVEFORMATEX pwfmt;
	memset(&pwfmt,0,sizeof(pwfmt));
	pwfmt.wFormatTag=WAVE_FORMAT_PCM;
	pwfmt.nChannels=2;//播放声道
	pwfmt.nSamplesPerSec=44100;//播放频率
	pwfmt.wBitsPerSample=16;//位
	pwfmt.nBlockAlign=pwfmt.wBitsPerSample/8*pwfmt.nChannels;
	pwfmt.nAvgBytesPerSec=pwfmt.nSamplesPerSec*pwfmt.nBlockAlign;
	hr=pPbuf->SetFormat(&pwfmt);
	if(hr!=DS_OK)
	{
		TRACE("播放格式");
	}
	//read music file
	WAVEFORMATEX swfmt;
	MMCKINFO ckRiff;
	MMCKINFO ckInfo;//子区快信息
	MMRESULT mmresult;
	HMMIO hmmio;//file
	DWORD size;//实际资料大小
	hmmio=mmioOpen((char*)path.c_str(),NULL,MMIO_ALLOCBUF|MMIO_READ);
	if(hmmio==NULL)
	{
		TRACE("NULL NULL NULL ");
	}
	ckRiff.fccType=mmioFOURCC('W', 'A', 'V', 'E');//设定文件类型
 mmresult = mmioDescend(hmmio, &ckRiff, NULL, MMIO_FINDRIFF); 
 if(mmresult != MMSYSERR_NOERROR)
 {
	 TRACE("文件格式错误1");
 }
        //搜索区块
 ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');//设定区块类型
 mmresult = mmioDescend(hmmio, &ckInfo, &ckRiff, MMIO_FINDCHUNK);
        if(mmresult != MMSYSERR_NOERROR)
		{
			TRACE("MMRESULT  FAIL");
		}
 
 if(mmioRead(hmmio, (HPSTR)&swfmt, sizeof(swfmt)) == -1)
 {
            TRACE("读取格式失败！");
 }

 mmresult = mmioAscend(hmmio, &ckInfo, 0);   //跳出子区块

        //搜索区块
 ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
 mmresult = mmioDescend(hmmio, &ckInfo, &ckRiff, MMIO_FINDCHUNK);
 if(mmresult != MMSYSERR_NOERROR)
 {
	 TRACE("文件格式错误2");
 }

 size = ckInfo.cksize;
// mmioClose(hmmio,0);
//关闭使用完毕的音乐文件
 //LPDIRECTSOUND lpds2;
 LPDIRECTSOUNDBUFFER pSbuf;
  memset(&desc, 0, sizeof(desc));   //清空结构内容
 desc.dwSize = sizeof(desc);             //配制描述结构大小
 desc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLPAN | 
             DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;   //???
 desc.dwBufferBytes =size;
 desc.lpwfxFormat =&swfmt;
hr = lpds->CreateSoundBuffer(&desc, &pSbuf, NULL);
 if(hr!= DS_OK)
 {
	 TRACE("建立次缓冲区失败");
 }
 LPVOID pAudio;
 DWORD  bytesAudio;
hr= pSbuf->Lock(0,size, &pAudio, &bytesAudio, NULL, NULL, NULL);
 if(hr != DS_OK)
 {
   TRACE("锁定缓冲区失败!");
 }

mmresult = mmioRead(hmmio, (HPSTR)pAudio,bytesAudio);
 if(mmresult== -1)
   {
   TRACE("读取失败!");
 }
hr = pSbuf->Unlock(pAudio, bytesAudio, NULL, NULL);

 if(hr!= DS_OK)
 {
   TRACE("解除缓冲区失败!");
 }

 mmioClose(hmmio, 0);
  pSbuf->Play(0,0,0);
 
	 
 
 
 TRACE("结束 结束 结束 结束!");
}
