#pragma once
#include "head.h"

//ȫ�ֱ������������
//==============directsound��ر���=========================
LPDIRECTSOUND pDS; //����DirectSound����ָ��,������������ָ��,�����μ�������ָ��
HRESULT result; //����HRESULT���ͱ���
LPDIRECTSOUNDBUFFER pPBuf, pSBuf[4];
DSBUFFERDESC desc; //���������ṹ
MMCKINFO ckRiff, ckInfo; //Riff��������������Ϣ
MMRESULT mmresult;
HMMIO hmmio; //�򿪵Ķ�ý���ļ�
DWORD size, bytesAudio; //ʵ�����ϵĴ�С,�洢��Ҫ�������ϵĳ���
LPVOID pAudio; //ָ�򻺳�����ʼ��¼���ϵĵ�ַ
WAVEFORMATEX swfmt;
//��BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)���������
									
//*****************�Զ��庯��*********************
LPDIRECTSOUNDBUFFER CreateBuffer(char * filename)
{
	LPDIRECTSOUNDBUFFER buf;
	hmmio = mmioOpen(filename, NULL, MMIO_ALLOCBUF | MMIO_READ);

	ckRiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');

	mmresult = mmioDescend(hmmio, &ckRiff, NULL, MMIO_FINDRIFF);
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmresult = mmioDescend(hmmio, &ckInfo, &ckRiff, MMIO_FINDCHUNK);
	mmioRead(hmmio, (HPSTR)&swfmt, sizeof(swfmt));
	mmresult = mmioAscend(hmmio, &ckInfo, 0);
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmresult = mmioDescend(hmmio, &ckInfo, &ckRiff, MMIO_FINDCHUNK);

	size = ckInfo.cksize;
	memset(&desc, 0, sizeof(desc));
	desc.dwSize = sizeof(desc);
	desc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	desc.dwBufferBytes = size;
	desc.lpwfxFormat = &swfmt;
	result = pDS->CreateSoundBuffer(&desc, &buf, NULL);
	result = buf->Lock(0, size, &pAudio, &bytesAudio, NULL, NULL, NULL);


	mmresult = mmioRead(hmmio, (HPSTR)pAudio, bytesAudio);


	result = buf->Unlock(pAudio, bytesAudio, NULL, NULL);


	mmioClose(hmmio, 0);
	return buf;
}

void loadSound(HWND hWnd)
{
	//=====================directsound��ʼ��==================
	result = DirectSoundCreate(NULL, &pDS, NULL); //����DirectSound����
	result = pDS->SetCooperativeLevel(hWnd, DSSCL_PRIORITY); //hWndΪӦ�ó���������
	memset(&desc, 0, sizeof(desc)); //��սṹ����
	desc.dwSize = sizeof(desc);
	desc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	desc.dwBufferBytes = 0;
	desc.lpwfxFormat = NULL;
	result = pDS->CreateSoundBuffer(&desc, &pPBuf, NULL);

	pSBuf[0] = CreateBuffer("source/music/1.wav"); //city
	pSBuf[1] = CreateBuffer("source/music/2.wav"); //panel
	pSBuf[2] = CreateBuffer("source/music/3.wav"); //win
	pSBuf[3] = CreateBuffer("source/music/4.wav"); //lose
}