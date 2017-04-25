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

//当前的panel 编号 0--开始面板 1--保存面板 2--设置 3--结束确认 4--战斗chose1 5--战斗chose2 6--skill 7--item  8--end
extern int current_panel ;
//动作步骤
extern int animation_ctrl ;
//当前角色
extern  int current_player ;
//当前地图
extern  int current_map ;
//事件触发NPC
extern int event_npc ;
//选择的player
extern int select_player ;
//角色背包里的物品数量
extern int player_item_num;
//显示状态0--开始面板  1--地图  2--退出面板 3--对话系统 4--状态面板
extern int status ;
extern int fenemy_num[3];
extern int money;
//要显示的对话
extern int talk_type;
extern wchar_t *talk ;
extern RECT rc;

extern float w_offset;
extern float h_offset;


extern int play_x;
extern int play_y;

extern double start ;//旧时间
extern double end ;//新时间
extern POINT point; //鼠标
extern ID2D1Factory*			pD2DFactory ;	// Direct2D factory
extern ID2D1HwndRenderTarget*	pRenderTarget ;	// Render target
extern IWICImagingFactory *pWICFactory ; //WIC工厂
extern ID2D1SolidColorBrush* pBlackBrush ; //单色画刷话对话框
extern ID2D1SolidColorBrush* pRedBrush ; //单色画刷话对话框
extern ID2D1SolidColorBrush* pBlueBrush ; //单色画刷话对话框

extern IDWriteFactory* g_pDWriteFactory ; //用于写文字

extern IDWriteTextFormat* g_pTextFormat ;
extern IDWriteTextFormat* g_pTextFormat1;//文字类型2

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
