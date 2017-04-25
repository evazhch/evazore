#include "head.h"
#include "Item.h"
#include "Skill.h"
#include "Npc.h"
#include "Teleporter.h"
#include "FightNpc.h"
#include "Player.h"
#include "Task.h"
#include "Map.h"
#include "Panel.h"
#include "Status.h"
#include "Animation.h"
#include "Enemy.h"
#include "Fight.h"
#include "music.h"
#include "save.h"
#include "Game.h"
#include <mmsystem.h>

//当前的panel 编号 0--开始面板 1--保存面板 2--设置 3--结束确认 4--战斗chose1 5--战斗chose2 6--skill 7--item  8--end
 int current_panel = 0;
//动作步骤
 int animation_ctrl = 0;
//当前角色
  int current_player = 0;
//当前地图
  int current_map = 0;
//事件触发NPC
 int event_npc = -1;
//选择的player
 int select_player = 0;
 //角色背包里的物品数量
 int player_item_num = 0;
//显示状态0--面板  1--地图系统   3--对话系统 4--状态面板
 int status = 0;
 //敌人队列
 int fenemy_num[3] = { 1,1,1 }; //敌人编号
//要显示的对话
 int talk_type;//0--捡到东西等等 1--角色 2--npc
 wchar_t *talk = NULL;
 //角色资金
 int money=100;

 float w_offset=1;
 float h_offset=1;

 int play_x;
 int play_y;

 RECT rc;
 double start = 0;//旧时间
 double end = 0;//新时间
 POINT point; //鼠标

 ID2D1Factory*			pD2DFactory = NULL;	// Direct2D factory
 ID2D1HwndRenderTarget*	pRenderTarget = NULL;	// Render target
 IWICImagingFactory *pWICFactory = NULL; //WIC工厂
 ID2D1SolidColorBrush* pBlackBrush = NULL; //单色画刷话对话框
 ID2D1SolidColorBrush* pRedBrush = NULL; //单色画刷话对话框
 ID2D1SolidColorBrush* pBlueBrush = NULL; //单色画刷话对话框

 IDWriteFactory* g_pDWriteFactory = NULL; //用于写文字
 IDWriteTextFormat* g_pTextFormat = NULL; //文字类型1
 IDWriteTextFormat* g_pTextFormat1 = NULL;//文字类型2
 ID2D1Bitmap *mouseBitmap = NULL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rc);
		loadSound(hwnd);
		
		break;
	case WM_SIZE:
		RECT rc1;
		GetClientRect(hwnd, &rc1);
		if (rc1.right != rc.right || rc1.bottom != rc.bottom)
		{
			w_offset = (float)rc1.right / (float)640;
			h_offset = (float)rc1.bottom / (float)480;
			rc = rc1;
			pRenderTarget->Resize(D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top));
			loadPanel();
			npc[20].set(-1, 0, 0, NULL, 1, 1, 1);
			npc[20].set(1, 0, 0, 0, 0, 0, 0, 0, 0);
			npc[20].npc_type = 1;
			npc[20].anm_num = 20;
			npc[20].x = rc.right - 30;
			npc[20].y = 0;
			npc[20].x_offset = 30;
			npc[20].y_offset = 30;
		}
		break;
	case   WM_PAINT:   //Draw
		end = GetTickCount();
		//获取窗口
		if (!pRenderTarget) //创建D2D工厂
		{
			CreateResource(hwnd);
			Form_Load();
			LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/mouse.bmp", 0, 0, &mouseBitmap);
		}
		else
		{
			switch (status)
			{
			case 0: //面板
				pSBuf[0]->Stop();
				pSBuf[1]->Play(0, 0, 0);
				pSBuf[2]->Stop();
				pSBuf[3]->Stop();
				pain_panel();
				break;	
			case 1: //地图状态
				pSBuf[0]->Stop();
				pSBuf[1]->Play(0, 0, 0);
				pSBuf[2]->Stop();
				pSBuf[3]->Stop();
				Begindraw();
				map[current_map].DrawMap(hwnd, player, teleporter, npc,fightNpc,animation_ctrl,npcAnm);
				Enddraw();
				break;
			case 3://对话
				Begindraw();
				map[current_map].DrawMap(hwnd, player, teleporter, npc, fightNpc,animation_ctrl, npcAnm);
				pain_talk();
				Enddraw();
				break;
			case 4://状态面板
				Begindraw();
				save[0].saveG(item_player, player);
				statusMenu.draw_statusmenu(hwnd, player, pRenderTarget,item_player);
				Enddraw();
				break;
			case 5: //战斗
				pSBuf[1]->Stop();
				pSBuf[0]->Play(0, 0, 0);
				pSBuf[2]->Stop();
				pSBuf[3]->Stop();
				Begindraw();
				fight.run(player, playerAnm, enemyAnm, enemy,item_player,item,pSBuf);
				Enddraw();
				break;
			case 6://商店
				break;
			default:
				break;
			}	
		}
		return 0;
		break;
	case WM_KEYDOWN:case WM_LBUTTONDOWN:case WM_MOUSEMOVE:case WM_RBUTTONDOWN:
	{
		switch (status)
		{
		case 0:
			panel_ctl(hwnd, wParam);
			break;
		case 1: //地图状态
				if(map[current_map].change_map(player, teleporter)==0)
				         map[current_map].key_ctrl(hwnd, wParam, player, npc,task);
			break;
		case 3://谈话
			end = GetTickCount();
			if (end - start > 500 &&( (message==WM_LBUTTONDOWN )|| (message == WM_KEYDOWN)))
			{
   				task.story_npctalk(event_npc, player, npc);
				start = end;
			}
			break;
		case 4://状态面板
			statusMenu.key_ctrl(hwnd, wParam,player,item_player);
			break;
		case 5:
			fight.key_ctrl(hwnd, wParam, player, enemy, task, fight);
			break;
		default:
			break;
		}
	}
	break;

	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{

	WNDCLASSEX winClass;

	winClass.lpszClassName = "Direct2D";
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = WndProc;
	winClass.hInstance = hInstance;
	winClass.hIcon = NULL;
	winClass.hIconSm = NULL;
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = NULL;
	winClass.lpszMenuName = NULL;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;


	if (!RegisterClassEx(&winClass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), "error", MB_ICONERROR);
		return 0;
	}

	HWND hwnd = CreateWindowEx(NULL,
		"Direct2D",					// window class name
		"九里坡剑神",			// window caption
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 		// window style
		CW_USEDEFAULT,				// initial x position
		CW_USEDEFAULT,				// initial y position
		650,						// initial x size
		500,						// initial y size
		NULL,						// parent window handle
		NULL,						// window menu handle
		hInstance,					// program instance handle
		NULL);						// creation parameters

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	MSG    msg;
	ZeroMemory(&msg, sizeof(msg));

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
