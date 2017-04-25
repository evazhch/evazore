#pragma once
#include <windows.h>
#include <stdlib.h>
#include <wincodec.h>
#include <D2D1.h>
#include<dwrite.h>
#include<dsound.h>
#include <mmsystem.h>
#include<iostream>
#include <fstream>
#include "Task.h"

#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}

//��ǰ��panel ��� 0--��ʼ��� 1--������� 2--���� 3--����ȷ�� 4--ս��chose1 5--ս��chose2 6--skill 7--item  8--end
extern int current_panel ;
//��������
extern int animation_ctrl ;
//��ǰ��ɫ
extern  int current_player ;
//��ǰ��ͼ
extern  int current_map ;
//�¼�����NPC
extern int event_npc ;
//ѡ���player
extern int select_player ;
//��ɫ���������Ʒ����
extern int player_item_num;
//��ʾ״̬0--��ʼ���  1--��ͼ  2--�˳���� 3--�Ի�ϵͳ 4--״̬���
extern int status ;
extern int fenemy_num[3];
extern int money;
//Ҫ��ʾ�ĶԻ�
extern int talk_type;
extern wchar_t *talk ;
extern RECT rc;

extern float w_offset;
extern float h_offset;


extern int play_x;
extern int play_y;

extern double start ;//��ʱ��
extern double end ;//��ʱ��
extern POINT point; //���
extern ID2D1Factory*			pD2DFactory ;	// Direct2D factory
extern ID2D1HwndRenderTarget*	pRenderTarget ;	// Render target
extern IWICImagingFactory *pWICFactory ; //WIC����
extern ID2D1SolidColorBrush* pBlackBrush ; //��ɫ��ˢ���Ի���
extern ID2D1SolidColorBrush* pRedBrush ; //��ɫ��ˢ���Ի���
extern ID2D1SolidColorBrush* pBlueBrush ; //��ɫ��ˢ���Ի���

extern IDWriteFactory* g_pDWriteFactory ; //����д����

extern IDWriteTextFormat* g_pTextFormat ;
extern IDWriteTextFormat* g_pTextFormat1;//��������2

VOID CreateResource(HWND hWnd);

HRESULT LoadBitmapFromFile(
	ID2D1RenderTarget *pRenderTarget,
	IWICImagingFactory *pIWICFactory,
	PCWSTR uri,
	UINT destinationWidth,
	UINT destinationHeight,
	ID2D1Bitmap **ppBitmap
);

void drawtext(wchar_t *str, ID2D1SolidColorBrush *brush, int x, int y, int w, int h);
void drawnum(int num, ID2D1SolidColorBrush *brush, int x, int y, int w, int h);
long time();
