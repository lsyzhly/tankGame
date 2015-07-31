
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
    LPDIRECTSOUNDBUFFER pPbuf;//������������ָ��
	DSBUFFERDESC desc;//�����ṹ
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
		//���ø�ʽ
	WAVEFORMATEX pwfmt;
	memset(&pwfmt,0,sizeof(pwfmt));
	pwfmt.wFormatTag=WAVE_FORMAT_PCM;
	pwfmt.nChannels=2;//��������
	pwfmt.nSamplesPerSec=44100;//����Ƶ��
	pwfmt.wBitsPerSample=16;//λ
	pwfmt.nBlockAlign=pwfmt.wBitsPerSample/8*pwfmt.nChannels;
	pwfmt.nAvgBytesPerSec=pwfmt.nSamplesPerSec*pwfmt.nBlockAlign;
	hr=pPbuf->SetFormat(&pwfmt);
	if(hr!=DS_OK)
	{
		TRACE("���Ÿ�ʽ");
	}
	//read music file
	WAVEFORMATEX swfmt;
	MMCKINFO ckRiff;
	MMCKINFO ckInfo;//��������Ϣ
	MMRESULT mmresult;
	HMMIO hmmio;//file
	DWORD size;//ʵ�����ϴ�С
	hmmio=mmioOpen((char*)path.c_str(),NULL,MMIO_ALLOCBUF|MMIO_READ);
	if(hmmio==NULL)
	{
		TRACE("NULL NULL NULL ");
	}
	ckRiff.fccType=mmioFOURCC('W', 'A', 'V', 'E');//�趨�ļ�����
 mmresult = mmioDescend(hmmio, &ckRiff, NULL, MMIO_FINDRIFF); 
 if(mmresult != MMSYSERR_NOERROR)
 {
	 TRACE("�ļ���ʽ����1");
 }
        //��������
 ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');//�趨��������
 mmresult = mmioDescend(hmmio, &ckInfo, &ckRiff, MMIO_FINDCHUNK);
        if(mmresult != MMSYSERR_NOERROR)
		{
			TRACE("MMRESULT  FAIL");
		}
 
 if(mmioRead(hmmio, (HPSTR)&swfmt, sizeof(swfmt)) == -1)
 {
            TRACE("��ȡ��ʽʧ�ܣ�");
 }

 mmresult = mmioAscend(hmmio, &ckInfo, 0);   //����������

        //��������
 ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
 mmresult = mmioDescend(hmmio, &ckInfo, &ckRiff, MMIO_FINDCHUNK);
 if(mmresult != MMSYSERR_NOERROR)
 {
	 TRACE("�ļ���ʽ����2");
 }

 size = ckInfo.cksize;
// mmioClose(hmmio,0);
//�ر�ʹ����ϵ������ļ�
 //LPDIRECTSOUND lpds2;
 LPDIRECTSOUNDBUFFER pSbuf;
  memset(&desc, 0, sizeof(desc));   //��սṹ����
 desc.dwSize = sizeof(desc);             //���������ṹ��С
 desc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLPAN | 
             DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;   //???
 desc.dwBufferBytes =size;
 desc.lpwfxFormat =&swfmt;
hr = lpds->CreateSoundBuffer(&desc, &pSbuf, NULL);
 if(hr!= DS_OK)
 {
	 TRACE("�����λ�����ʧ��");
 }
 LPVOID pAudio;
 DWORD  bytesAudio;
hr= pSbuf->Lock(0,size, &pAudio, &bytesAudio, NULL, NULL, NULL);
 if(hr != DS_OK)
 {
   TRACE("����������ʧ��!");
 }

mmresult = mmioRead(hmmio, (HPSTR)pAudio,bytesAudio);
 if(mmresult== -1)
   {
   TRACE("��ȡʧ��!");
 }
hr = pSbuf->Unlock(pAudio, bytesAudio, NULL, NULL);

 if(hr!= DS_OK)
 {
   TRACE("���������ʧ��!");
 }

 mmioClose(hmmio, 0);
  pSbuf->Play(0,0,0);
 
	 
 
 
 TRACE("���� ���� ���� ����!");
}
