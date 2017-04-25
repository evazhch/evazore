#pragma once
#include "head.h"

//全局变量声明中添加
//==============directsound相关变量=========================
LPDIRECTSOUND pDS; //声明DirectSound对象指针,声明主缓冲区指针,声明次级缓冲区指针
HRESULT result; //声明HRESULT类型变量
LPDIRECTSOUNDBUFFER pPBuf, pSBuf[4];
DSBUFFERDESC desc; //声明描述结构
MMCKINFO ckRiff, ckInfo; //Riff区块和子区块的信息
MMRESULT mmresult;
HMMIO hmmio; //打开的多媒体文件
DWORD size, bytesAudio; //实际资料的大小,存储区要存入资料的长度
LPVOID pAudio; //指向缓冲区开始记录资料的地址
WAVEFORMATEX swfmt;
//在BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)函数中添加
									
//*****************自定义函数*********************
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
	//=====================directsound初始化==================
	result = DirectSoundCreate(NULL, &pDS, NULL); //建立DirectSound对象
	result = pDS->SetCooperativeLevel(hWnd, DSSCL_PRIORITY); //hWnd为应用程序主窗口
	memset(&desc, 0, sizeof(desc)); //清空结构内容
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