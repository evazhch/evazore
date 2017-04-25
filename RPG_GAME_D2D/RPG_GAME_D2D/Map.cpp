#include "head.h"
#include <vector>
#include <list>
#include "Map.h"
#include "Player.h"
#include "Npc.h"
#include "FightNpc.h"
#include "Teleporter.h"
#include "Task.h"
#include "Astar.h"

using namespace std;

void Map::load()
{
	LoadBitmapFromFile(pRenderTarget, pWICFactory, map_path, 0, 0,&map);
	LoadBitmapFromFile(pRenderTarget, pWICFactory, shade_path, 0, 0, &shade);

	D2D1_SIZE_F size = map->GetSize();
	xr = size.width;
	yb = size.height;

	makeBlockMap();
}
void Map::unload()
{
	SAFE_RELEASE(map);
	SAFE_RELEASE(shade);
	SAFE_RELEASE(block);
	SAFE_RELEASE(back);
}

D2D1_RECT_F Map::map_rect(Player player[])
{
	if (player[current_player].x_map < w/ 2)
	{
		player[current_player].x = player[current_player].x_map*w_offset;
		x = 0;
	}
	 if (player[current_player].x_map >= w/ 2 && player[current_player].x_map < xr - w / 2 )
	{
		player[current_player].x = w / 2*w_offset;

		x = player[current_player].x_map - w / 2;
	}
	 if (player[current_player].x_map >= xr - w / 2)
	{
		player[current_player].x = (player[current_player].x_map - xr + w)*w_offset;

		x = xr - w;
	}
	if (player[current_player].y_map < h / 2)
	{
		player[current_player].y = player[current_player].y_map*w_offset;
		y = 0;
	}
	 if (player[current_player].y_map >= h / 2 && player[current_player].y_map < yb - h / 2)
	{
		player[current_player].y = h / 2 *h_offset;

		y = player[current_player].y_map - h / 2;
	}
	 if (player[current_player].y_map >= yb - h / 2)
	{
		player[current_player].y = (player[current_player].y_map - (yb - h))*h_offset;
		y = yb - h;
	}

	

	D2D1_RECT_F map_size = D2D1::RectF(x, y, x+w, y+h);//地图区域
	return map_size;
}

void Map::setMap(int inx, int iny, LPCWSTR map_p, LPCWSTR shade_p, LPCWSTR block_p)
{
	this->x_in = inx;
	this->y_in = iny;
	this->map_path = map_p;
	this->shade_path = shade_p;
	this->block_str = block_p;
}
//绘制地图/角色/npc
void Map::drawMap(int x, int y, int w, int h)
{
	if (this->map == NULL)
	{
		LoadBitmapFromFile(pRenderTarget, pWICFactory, map_path, 0, 0, &map);
	}
	if (this->map != nullptr)
	{
		pRenderTarget->DrawBitmap(
			this->map,
			D2D1::RectF(
				x,
				y,
				x + w,
				y + h),
			1.0f
		);
	}
	SAFE_RELEASE(map);
}
void Map::DrawMap(HWND hWnd,Player player[], Teleporter teleporter[], Npc npc[],FightNpc fightNpc[],int animation_ctrl,Animation npcAnm[])
{
	play_x = player[current_player].x_map;
	play_y = player[current_player].y_map;

	if (this->map == NULL)
	{
		load();
	}
	D2D1_RECT_F window_size = D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom);//屏幕区域
	D2D1_RECT_F map_size = map_rect(player); //地图将要绘制区域

	//显示地图
	if (map != nullptr)
	{
		pRenderTarget->DrawBitmap(
			map,
			window_size,
			1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			map_size
		);
	}
	//加载传送点
	for (int i = 0; i < 30; i++)
	{
		teleporter[i].load();
		if (teleporter[i].can_draw_npc(current_map, map_size,player[current_player].y_map-player[current_player].y_offset) != 1)
		{
			teleporter[i].draw();
		}
	}
	//加载战斗Npc
	for (int i = 0; i < 30; i++)
	{
		fightNpc[i].load();
		if (fightNpc[i].can_draw_npc(current_map, map_size, player[current_player].y_map - player[current_player].y_offset) != 1)
		{
			fightNpc[i].is_collision(player[current_player]);
			fightNpc[i].drawNpc();
		}
	}
	//显示NPC
	for (int i = 1; i < 20; i++)
	{
		if (npc[i].can_draw_npc(current_map, map_size, player->y_map-player->y_offset) == 0)
		{
			npc[i].load();
			npc[i].drawNpc(npcAnm);
		}
	}
	//显示角色
	if (player[current_player].walk_type == 1)
	{
		move(player);
     }
	player[current_player].DrawPlayer(hWnd, player[current_player], player[current_player].face, animation_ctrl, pRenderTarget);
	//显示NPC
	for (int i = 1; i < 20; i++)
	{
		if (npc[i].can_draw_npc(current_map, map_size,player->y_map-player->y_offset) == 2)
		{
			npc[i].load();
			npc[i].drawNpc(npcAnm);
		}
	}
	//显示遮挡层
	if (shade != nullptr)
	{
		pRenderTarget->DrawBitmap(
			shade,
			window_size,
			1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			map_size
		);
	}
	if (npc[0].npc_type == 2)
	{
		npc[0].load();
		npc[0].drawNpc();
	}
	npc[20].drawNpc(npcAnm);
	//显示经济
	drawnum(money, pRedBrush, rc.right - 50, rc.bottom - 50, 50, 50);
	if (status == 1)
	{
		event_npc = npc->collision_act(npc, player[current_player], 20);
	}
}
void Map::makeBlockMap()
{
	IWICImagingFactory *pIWICFactory = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode*pSource = NULL;
	IWICBitmap* pWIC = NULL;
	IWICFormatConverter*pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;
	UINT originalWidth = 0;
	UINT originalHeight = 0;

	for(int i=0;i<128;i++)
		for (int  j = 0; j < 128; j++)
		{
			blockmap[j][i] = 1;
		}
	// 1.加载IWICBitmap对象
	HRESULT hr = S_OK;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory1,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		reinterpret_cast<void **>(&pIWICFactory)
	);
	hr = pIWICFactory->CreateDecoderFromFilename(
	    block_str,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		hr = pSource->GetSize(&originalWidth, &originalHeight);
	}

	if (SUCCEEDED(hr))
	{
		hr = pIWICFactory->CreateBitmapFromSourceRect(
			pSource, 0, 0, (UINT)originalWidth, (UINT)originalHeight, &pWIC);
	}
	// 2.从IWICBitmap对象读取像素数据
	IWICBitmapLock *pILock = NULL;

	for (int i = 0; i < originalWidth/10; i++)
		for (int j = 0; j < originalHeight/10; j++)
		{
			hr = S_OK;	
			WICRect rcLock = { i*10, j*10, 1, 1 };
			hr = pWIC->Lock(&rcLock, WICBitmapLockWrite, &pILock);

			if (SUCCEEDED(hr))
			{
				UINT cbBufferSize = 0;
				BYTE *pv = NULL;

				if (SUCCEEDED(hr))
				{
					// 获取锁定矩形中左上角像素的指针
					hr = pILock->GetDataPointer(&cbBufferSize, &pv);
				}
				// 3.进行像素计算
				if (pv[0] != 0 || pv[1] != 0 || pv[2] != 0)
				{
					blockmap[i][j] = 0;
				}
				SAFE_RELEASE(pILock);
			}
		}
	SAFE_RELEASE(pIWICFactory);
	SAFE_RELEASE(pDecoder);
	SAFE_RELEASE(pSource);
	SAFE_RELEASE(pWIC);
	SAFE_RELEASE(pConverter);
	SAFE_RELEASE(pScaler);
	SAFE_RELEASE(pILock);
}
std::list<Point*> Map::getEndAStar(int sx, int sy, int ex, int ey)
{
	vector<vector<int>> maze(129, vector<int>(129));
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			maze[i][j] = blockmap[i][j];
		}
	}
	Astar astar;
	astar.InitAstar(maze);
	Point start(sx/10, sy/10);
	Point end(ex/10, ey/10);
	list<Point *> path = astar.GetPath(start, end, false);
	    
	return path;
}
int Map::get_blockcolor(int x, int y, int face,int speed, LPCWSTR url)
{
	IWICImagingFactory *pIWICFactory = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode*pSource = NULL;
	IWICBitmap* pWIC = NULL;
	IWICFormatConverter*pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;
	UINT originalWidth = 0;
	UINT originalHeight = 0;

	// 1.加载IWICBitmap对象
	HRESULT hr = S_OK;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory1,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		reinterpret_cast<void **>(&pIWICFactory)
	);
	hr = pIWICFactory->CreateDecoderFromFilename(
		url,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		hr = pSource->GetSize(&originalWidth, &originalHeight);
	}

	if (SUCCEEDED(hr))
	{
		hr = pIWICFactory->CreateBitmapFromSourceRect(
			pSource, 0, 0, (UINT)originalWidth, (UINT)originalHeight, &pWIC);
	}
	// 2.从IWICBitmap对象读取像素数据
	IWICBitmapLock *pILock = NULL;
	int step;//能走几步

	switch (face)
	{
	case 1://xia
		for (int i = 0; i <= speed; i++)
		{
			WICRect rcLock = { x, y+i, 1, 1 };
			hr = pWIC->Lock(&rcLock, WICBitmapLockWrite, &pILock);

			if (SUCCEEDED(hr))
			{
				UINT cbBufferSize = 0;
				BYTE *pv = NULL;

				if (SUCCEEDED(hr))
				{
					// 获取锁定矩形中左上角像素的指针
					hr = pILock->GetDataPointer(&cbBufferSize, &pv);
				}
				// 3.进行像素计算
				if (pv[0] == 0 && pv[1] == 0 && pv[2] == 0)
				{
					step = i - 1;
					SAFE_RELEASE(pILock);
					break;
				}
				else
				{
					SAFE_RELEASE(pILock);
					step = i;
				}

			}
		}
		break;
	case 2://zuo
		for (int i = 0; i <= speed; i++)
		{
			WICRect rcLock = { x - i, y, 1, 1 };
			hr = pWIC->Lock(&rcLock, WICBitmapLockWrite, &pILock);

			if (SUCCEEDED(hr))
			{
				UINT cbBufferSize = 0;
				BYTE *pv = NULL;

				if (SUCCEEDED(hr))
				{
					// 获取锁定矩形中左上角像素的指针
					hr = pILock->GetDataPointer(&cbBufferSize, &pv);
				}
				// 3.进行像素计算
				if (pv[0] == 0 && pv[1] == 0 && pv[2] == 0)
				{
					step = i - 1;
					SAFE_RELEASE(pILock);
					break;
				}
				else
				{
					SAFE_RELEASE(pILock);
					step = i;
				}
			}
		}
		break;
	case 3://you
		for (int i = 0; i <= speed; i++)
		{
			WICRect rcLock = { x+46 + i, y, 1, 1 };
			hr = pWIC->Lock(&rcLock, WICBitmapLockWrite, &pILock);

			if (SUCCEEDED(hr))
			{
				UINT cbBufferSize = 0;
				BYTE *pv = NULL;

				if (SUCCEEDED(hr))
				{
					// 获取锁定矩形中左上角像素的指针
					hr = pILock->GetDataPointer(&cbBufferSize, &pv);
				}
				// 3.进行像素计算
				if (pv[0] == 0 && pv[1] == 0 && pv[2] == 0)
				{
					step = i - 1;
					SAFE_RELEASE(pILock);
					break;
				}
				else
				{
					SAFE_RELEASE(pILock);
					step = i;
				}
			}
		}
		break;
	case 4://shang
		for (int i = 0; i <= speed; i++)
		{
			WICRect rcLock = { x, y-i, 1, 1 };
			hr = pWIC->Lock(&rcLock, WICBitmapLockWrite, &pILock);

			if (SUCCEEDED(hr))
			{
				UINT cbBufferSize = 0;
				BYTE *pv = NULL;

				if (SUCCEEDED(hr))
				{
					// 获取锁定矩形中左上角像素的指针
					hr = pILock->GetDataPointer(&cbBufferSize, &pv);
				}
				// 3.进行像素计算
				if (pv[0] == 0 && pv[1] == 0 && pv[2] == 0)
				{
					step = i - 1;
					SAFE_RELEASE(pILock);
					break;
				}
				else
				{
					SAFE_RELEASE(pILock);
					step = i;
				}
			}
		}
		break;
	default:
		break;
	}
	SAFE_RELEASE(pIWICFactory);
	SAFE_RELEASE(pDecoder);
	SAFE_RELEASE(pSource);
	SAFE_RELEASE(pWIC);
	SAFE_RELEASE(pConverter);
	SAFE_RELEASE(pScaler);
	SAFE_RELEASE(pILock);
	return step;
}

//判断角色是否可以移动
int Map::can_move(Player player)
{
	D2D1_SIZE_F size = map->GetSize();//地图大小
	D2D1_SIZE_F size1 = player.bitmap->GetSize();//人物大小

	return get_blockcolor(player.x_map+player.x_offset/2, player.y_map, player.face, player.speed, block_str);
}

void Map::move(Player player[])
{
	if ((player[current_player].x_map >= target_x+10 || player[current_player].x_map <= target_x - 10)
		|| (player[current_player].y_map >= target_y+10|| player[current_player].y_map <= target_y - 10))
	{
		player[current_player].timeEnd = GetTickCount();
		if (player[current_player].timeEnd - player[current_player].timeBegin > player[current_player].walk_interval)
		{
			if (golist.empty())
			{
				golist = getEndAStar(player[current_player].x_map, player[current_player].y_map, target_x, target_y);
			}
			Point p = *(golist.front());
			golist.pop_front();
			animation_ctrl++;
			player[current_player].timeBegin = player[current_player].timeEnd;
			if (p.x*10 > player[current_player].x_map)
			{
				player[current_player].face = 3;
			}
			else if (p.x*10 < player[current_player].x_map)
			{
				player[current_player].face = 2;
			}
			else if (p.y*10 < player[current_player].y_map)
			{
				player[current_player].face = 4;
			}
			else
			{
				player[current_player].face = 1;
			}
			player[current_player].x_map = p.x*10;
			player[current_player].y_map = p.y*10;
		}
	}
}

void Map::move(WPARAM wParam,Player player[])
{
	switch (wParam)
	{
	case VK_DOWN:
		if (player[current_player].face == 1)
		{
			player[current_player].walk(can_move(player[current_player]));
		}
		else
		{
			player[current_player].face = 1;
		}
		break;
		
	case VK_UP://上移
		if (player[current_player].face == 4)
		{
			player[current_player].walk(can_move(player[current_player]));
		}
		else
		{
			player[current_player].face = 4;
		}
		break;
		//左移
	case VK_LEFT:
		if (player[current_player].face == 2)
		{
			player[current_player].walk(can_move(player[current_player]));
		}
		else
		{
			player[current_player].face = 2;
		}
		break;
		//右移
	case VK_RIGHT:

		if (player[current_player].face == 3)
		{
			player[current_player].walk(can_move(player[current_player]));
		}
		else
		{
			player[current_player].face = 3;
		}
		break;
	default:
		break;
	}
	
}
//地图切换
int Map::change_map(Player player[],Teleporter teleporter[])
{
	for (int i = 0; i <= 30; i++)
	{
		if (teleporter[i].map == current_map)
		{
			if (teleporter[i].is_collision(player[current_player])==1)
			{
				teleporter[i].eventChange(player);
				return 1;
			}
		}
	}
	return 0;
}
//player在地图上的一系列键盘操作
void Map::key_ctrl(HWND hwnd, WPARAM wParam, Player player[], Npc npc[],Task task)
{
	event_npc = npc->collision_act(npc, player[current_player], 20);
	switch (wParam)
	{
	case 0: //鼠标移动
		GetCursorPos(&point);			// 获取鼠标指针位置（屏幕坐标）
		ScreenToClient(hwnd, &point);	// 将鼠标指针位置转换为窗口坐标
		event_npc = npc->collision_act(npc, player[current_player], 20);
		break;
	case MK_LBUTTON: case VK_SPACE://单击左键
		if (event_npc != -1)
		{
			task.story_npctalk(event_npc, player, npc);
		}
		break;
	case MK_RBUTTON: //右键

		if (player[current_player].walk_type == 0)
		{
			target_x = x + point.x;
			target_y = y + point.y;
			player[current_player].target_x = target_x;
			player[current_player].target_y = target_y;
			player[current_player].walk_type = 1;
			golist.clear();
		}
		else
		{
			player[current_player].walk_type = 0;
			golist.clear();
		}
		break;
	//领队切换
	case VK_TAB:
	{
		player->change_player(player);
	}
	break;
	//移动
	case VK_DOWN:case VK_UP:case VK_RIGHT:case VK_LEFT:
		player[current_player].walk_type = 0;
		if (npc[event_npc].collision == 0 && event_npc!=-1)
		{
			task.story_npctalk(event_npc, player, npc);
		}
		else
		{
			move(wParam, player);
		}
		break;
		//加速/减速
	case VK_SHIFT:
		if (player[current_player].speed == 20)
		{
			player[current_player].speed = 10;
			player[current_player].walk_interval = 100;
		}
		else
		{
			player[current_player].speed = 20;
			player[current_player].walk_interval = 50;
		}
		break;
		//状态面板
	case VK_END:
		status = 4;
		break;
		//结束
	case VK_ESCAPE:
		status = 0;
		current_panel = 3;
		break;
	default:
		break;
	}
}




