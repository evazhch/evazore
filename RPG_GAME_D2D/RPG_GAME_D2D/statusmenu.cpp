
#include "head.h"
#include "Item.h"
#include "Player.h"
#include "Skill.h"
#include "Status.h"

void StatusMenu::load()
{
	button[0].set(20, rc.bottom / 30, rc.bottom/12, rc.bottom / 12, L"source/status/b0n.png", L"source/status/b0s.png", L"source/status/b0s.png");
	button[1].set(20+ rc.right / 12, rc.bottom / 30, rc.bottom / 12, rc.bottom / 12, L"source/status/b1n.png", L"source/status/b0s.png", L"source/status/b0s.png");
	button[2].set(20 + rc.right / 12*2, rc.bottom / 30, rc.bottom / 12, rc.bottom / 12, L"source/status/b1n.png", L"source/status/b0s.png", L"source/status/b0s.png");

	button[3].set(rc.right/3, rc.bottom / 40, rc.bottom / 9, 3*rc.bottom / 40, L"", L"source/status/bitem.bmp", L"source/status/bitem.bmp");
	button[4].set(rc.right / 9*5, rc.bottom / 40, rc.bottom / 9, 3*rc.bottom / 40, L"", L"source/status/bskill.bmp", L"source/status/bskill.bmp");
	button[5].set(rc.right / 9*8, rc.bottom / 40, rc.bottom / 9, 3*rc.bottom / 40, L"", L"source/status/bsave.bmp", L"source/status/bsave.bmp");

	button[6].set(rc.right / 3, rc.bottom / 4  , 100, 20, L"source/fight/change.png", L"source/fight/change1.png", L"source/fight/change1.png");
	button[7].set(rc.right / 3, rc.bottom / 4 + 20 * 1, 100, 20, L"source/fight/change.png", L"source/fight/change1.png", L"source/fight/change1.png");
	button[8].set(rc.right / 3, rc.bottom / 4 + 20 * 2, 100, 20, L"source/fight/change.png", L"source/fight/change1.png", L"source/fight/change1.png");
	button[9].set(rc.right / 3, rc.bottom / 4 + 20 * 3, 100, 20, L"source/fight/change.png", L"source/fight/change1.png", L"source/fight/change1.png");
	button[10].set(rc.right / 3, rc.bottom / 4 + 20 *4, 100, 20, L"source/fight/change.png", L"source/fight/change1.png", L"source/fight/change1.png");
	button[11].set(rc.right / 3, rc.bottom / 4 + 20 * 5, 100, 20, L"source/fight/change.png", L"source/fight/change1.png", L"source/fight/change1.png");
	button[12].set(rc.right / 3, rc.bottom / 4 + 20 * 6, 100, 20, L"source/fight/change.png", L"source/fight/change1.png", L"source/fight/change1.png");
	button[13].set(rc.right / 3, rc.bottom / 4 + 20 * 7, 100, 20, L"source/fight/change.png", L"source/fight/change1.png", L"source/fight/change1.png");
	button[14].set(rc.right / 3, rc.bottom / 4 + 20 * 8, 100, 20, L"source/fight/change.png", L"source/fight/change1.png", L"source/fight/change1.png");
	button[15].set(rc.right / 3, rc.bottom / 4 + 20 * 9, 100, 20, L"source/fight/change.png", L"source/fight/change1.png", L"source/fight/change1.png");

	button[16].set(rc.right / 3, rc.bottom / 4 + 20 * 10, 100, 20, L"", L"source/status/bskill.bmp", L"source/status/bskill.bmp");
	button[17].set(rc.right / 3, rc.bottom / 4 + 20 * 11, 100, 20, L"", L"source/status/bsave.bmp", L"source/status/bsave.bmp");



}
void StatusMenu::draw_back()
{
	switch (menu)
	{
	case 0: //啥也没有
		if (backgrand != NULL)
		{
			pRenderTarget->DrawBitmap(
				backgrand,
				D2D1::RectF(
					rc.left, rc.top, rc.right, rc.bottom
				),
				1.0f
			);
		}
		for (int i = 0; i <= 5; i++)
		{
			button[i].isVist = 1;
		}
		for (int i = 6; i <= 16; i++)
		{
			button[i].isVist = 0;
		}
		break;
	case 1://物品
		if (backgrand1 != NULL)
		{
			pRenderTarget->DrawBitmap(
				backgrand1,
				D2D1::RectF(
					rc.left, rc.top, rc.right, rc.bottom
				),
				1.0f
			);
		}
		for (int i = 0; i <= 15; i++)
		{
			button[i].isVist = 1;
		}
		break;
	case 2://技能
		if (backgrand != NULL)
		{
			pRenderTarget->DrawBitmap(
				backgrand,
				D2D1::RectF(
					rc.left, rc.top, rc.right, rc.bottom
				),
				1.0f
			);
		}
		if (backgrand2 != NULL)
		{
			pRenderTarget->DrawBitmap(
				backgrand2,
				D2D1::RectF(
					rc.bottom/3, rc.bottom/10, rc.right, rc.bottom
				),
				1.0f
			);
		}
		break;
	case 3://天书
		if (backgrand3 != NULL)
		{
			pRenderTarget->DrawBitmap(
				backgrand3,
				D2D1::RectF(
					rc.left, rc.top, rc.right, rc.bottom
				),
				1.0f
			);
		}
		break;
	default:
		break; 
	}
	LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/status/que.bmp", 0, 0, &button_que);
	if (button_que != NULL)
	{
		pRenderTarget->DrawBitmap(
			button_que,
			D2D1::RectF(
				rc.left, rc.bottom/40, rc.right, rc.bottom/10
			),
			1.0f
		);
		SAFE_RELEASE(button_que);
	}

}
void StatusMenu::drawtext(wchar_t str[], ID2D1SolidColorBrush *brush,int x,int y,int w,int h)
{
	pRenderTarget->DrawText(
		str,          
		wcslen(str),       
		g_pTextFormat,     
		D2D1::RectF(x, y, x+w, y+h),    
		brush  
	);
}
void StatusMenu::drawtext1(wchar_t str[], ID2D1SolidColorBrush *brush, int x, int y, int w, int h)
{
	pRenderTarget->DrawText(
		str,
		wcslen(str),
		g_pTextFormat1,
		D2D1::RectF(x, y, x + w, y + h),
		brush
	);
}
void StatusMenu::drawtext(LPCWSTR str, ID2D1SolidColorBrush *brush, int x, int y, int w, int h)
{
	pRenderTarget->DrawText(
		str,
		wcslen(str),
		g_pTextFormat,
		D2D1::RectF(x, y, x + w, y + h),
		brush
	);
}
void StatusMenu::drawtext1(LPCWSTR str, ID2D1SolidColorBrush *brush, int x, int y, int w, int h)
{
	pRenderTarget->DrawText(
		str,
		wcslen(str),
		g_pTextFormat1,
		D2D1::RectF(x, y, x + w, y + h),
		brush
	);
}
void StatusMenu::drawPlayersta(Player player[])
{
	for (int i = 0; i < 3; i++)
	{
		if (player[i].is_active == -1)
		{
			button[i].isVist = 0;
		}
	}
	//人物详细资料
	
	LoadBitmapFromFile(pRenderTarget, pWICFactory, playerstatus_str[select_player], 0, 0, &select_player_menu);
	pRenderTarget->DrawBitmap(
		select_player_menu,
		D2D1::RectF(
			10,
			10,
			10 + rc.right/4,
			rc.bottom-10),
		1.0f
	);
	SAFE_RELEASE(select_player_menu);
	//血量
	_itow(player[select_player].hp, str_1, 10);
	_itow(player[select_player].max_hp, str_2, 10);
	wcscat(str_1, L"/");
	wcscat(str_1, str_2);
	drawtext(str_1, pRedBrush, rc.right/8+10, 100, 100, 100);

	//mp
	_itow(player[select_player].mp, str_1, 10);
	_itow(player[select_player].max_mp, str_2, 10);
	wcscat(str_1, L"/");
	wcscat(str_1, str_2);
	drawtext(str_1, pBlueBrush, rc.right / 8 + 10, 120, 100, 380);

	//攻防速运
	int att = player[select_player].attack + player[select_player].equip[0].value1 + player[select_player].equip[1].value1;//攻
	int def = player[select_player].defense + player[select_player].equip[0].value2 + player[select_player].equip[1].value2;//防
	int spd = player[select_player].fspeed + player[select_player].equip[0].value3 + player[select_player].equip[1].value3;//速
	int fot = player[select_player].fortune + player[select_player].equip[0].value4 + player[select_player].equip[1].value4;//运

	wcscpy(str_1, L"攻：");
	_itow(att, str_2, 10);
	wcscat(str_1, str_2);
	drawtext(str_1, pBlueBrush, 20, 170, rc.right / 4, 310);
	wcscpy(str_1, L"防：");
	_itow(def, str_2, 10);
	wcscat(str_1, str_2);
	drawtext(str_1, pBlueBrush, 20, 200, rc.right / 4, 280);
	wcscpy(str_1, L"速：");
	_itow(spd, str_2, 10);
	wcscat(str_1, str_2);
	drawtext(str_1, pBlueBrush, 20, 230, rc.right / 4, 250);
	wcscpy(str_1, L"运：");
	_itow(fot, str_2, 10);
	wcscat(str_1, str_2);
	drawtext(str_1, pBlueBrush, 20, 260, rc.right / 4, 220);
	wcscpy(str_1, L"武器：");
	if (player[select_player].equip_att == 1)
	{
		wcscpy(str_2, player[select_player].equip[0].name);
	}
	else
	{
		wcscpy(str_2, L"未装备");
	}
	wcscat(str_1, str_2);
	drawtext(str_1, pBlueBrush, 20, 290, rc.right / 4, 190);

	wcscpy(str_1, L"防具：");
	if (player[select_player].equip_def == 1)
	{
		wcscpy(str_2, player[select_player].equip[1].name);
	}
	else
	{
		wcscpy(str_2, L"未装备");
	}
	wcscat(str_1, str_2);
	drawtext(str_1, pBlueBrush, 20, 320, rc.right / 4, 30);
}
void StatusMenu::drawItem(Item item[])
{

	//页数
	_itow(item_page,str_1, 10);
	drawtext(str_1, pBlueBrush, rc.right / 3 + rc.bottom / 4, rc.bottom-rc.bottom / 4, 100, 100);
	int i = item_page*10;
	int j = 0;
	for (; i < item_page*10+10; i++)
	{
		if (item[i].num > 0)
		{
		   
			if (j == select_num || button[j+6].status==button[j+6].SELECT)
			{
				select_item = i;
				drawtext(item[i].name, pRedBrush, rc.right/3, rc.bottom/4 + 20 * j, 100, 20);
				_itow(item[i].num,str_1, 10);
				drawtext(str_1, pBlueBrush, rc.right /3+rc.bottom/4, rc.bottom / 4 + 20 * j, 100, 20);
				if (item[i].bitmap == NULL)
				{
					LoadBitmapFromFile(pRenderTarget, pWICFactory, item[i].bitmap_str, 0, 0, &item[i].bitmap);
				}
				pRenderTarget->DrawBitmap(
					item[i].bitmap,
					D2D1::RectF(rc.right/5*4,rc.bottom/10*2, rc.right-20, rc.bottom-rc.bottom/10*2),
					1.0f
				);
				drawtext(item[i].description, pBlueBrush, rc.right / 3, rc.bottom - rc.bottom / 11, 1000, 20);
			}
			else
			{
				drawtext(item[i].name, pBlueBrush, rc.right / 3, rc.bottom / 4 + 20 * j, 100, 20);
				_itow(item[i].num,str_1, 10);
				drawtext(str_1, pBlueBrush, rc.right / 3 + rc.bottom / 4, rc.bottom / 4 + 20 * j, 100, 20);
			}
			j = j + 1;
		}
	}
}
void StatusMenu::drawSkill(Player player[])
{
	for (int i = 0; i < 5; i++)
	{
		if (player[select_player].skill[i].name != L"")
		{
			if (i == select_item)
			{
				drawtext(player[select_player].skill[i].name, pRedBrush, rc.right / 3, rc.bottom / 10 + 20 * i, 100, 20);
				drawtext(player[select_player].skill[i].description, pRedBrush, rc.right / 3,rc.bottom- rc.bottom / 10, 1000, 20);

			/*	if (player[select_player].skill[i].bitmap == NULL)
				{
					LoadBitmapFromFile(pRenderTarget, pWICFactory, player[select_player].skill[i].bitmap_str, 0, 0, &player[select_player].skill[i].bitmap);
				}
				if (player[select_player].skill[i].bitmap != NULL)
					pRenderTarget->DrawBitmap(
						player[select_player].skill[i].bitmap,
						D2D1::RectF(420, 10, 620, 410),
						1.0f
					);*/
			}
			else
			{
				drawtext(player[select_player].skill[i].name, pBlueBrush, rc.right / 3, rc.bottom / 10 + 20 * i, 100, 20);
			}
		}
	}
}
void StatusMenu::draw_statusmenu(HWND hWnd, Player player[], ID2D1RenderTarget *pRenderTarget, Item item[])
{
	load();
	//背景图
	draw_back();
	//人物属性
	drawPlayersta(player);

	if (menu == 1) //物品
	{
		drawItem(item);
	}
	else if (menu == 2)//奇术
	{
		drawSkill(player);
	}
	for (int i = 0; i <= 16; i++)
	{
		if (button[i].isVist == 1)
		{
			button[i].draw(pRenderTarget);
		}
	}
}
void StatusMenu::key_ctrl(HWND hwnd, WPARAM wParam, Player player[], Item item[])
{
	switch (wParam)
	{
	case 0:
		GetCursorPos(&point);			// 获取鼠标指针位置（屏幕坐标）
		ScreenToClient(hwnd, &point);	// 将鼠标指针位置转换为窗口坐标
		buttonStatus();
		break;
	case MK_LBUTTON:
		buttonEvent(wParam);
		break;
	case VK_SPACE: //物品技能使用
		player[select_player].use_item(item[select_item].id, item);
		break;
	case VK_TAB:
		for(int i=select_player+1;i<=2;i++)
		{
			if (player[i].is_active == 1)
			{
				select_player = i;
				break;
			}
			if (i == 2)
			{
				for (int j = 0; j<= select_player ; j++)
				{
					if (player[j].is_active == 1)
					{
						select_player = j;
						break;
					}
				}
			}
		}
		break;
	case VK_RIGHT:
		switch (menu)
		{
		case 0:
			item[select_item + item_page * 5].bitmap = nullptr;
			break;
		case1:
			//player[select_player].skill[select_item].bitmap = nullptr;
			break;
		default:
			break;
		}
		item_page = item_page + 1;
		if (item_page > 9)
			item_page = 0;
		break;
	case VK_LEFT:
		switch (menu)
		{
		case 0:
			item[select_item].bitmap = nullptr;
			break;
		case 1:
			//player[select_player].skill[select_item].bitmap = nullptr;
			break;
		default:
			break;
		}
		item_page = item_page - 1;
		if (item_page < 0)
			item_page = 9;
		break;
	case VK_UP:
		switch (menu)
		{
		case 0:
			item[select_item].bitmap = nullptr;
			break;
		case 1:
			//player[select_player].skill[select_item].bitmap = nullptr;
			break;
		default:
			break;
		}
		select_num = select_num - 1;
		if (select_num < 0)
		{
			if (item_page - 1 < 0)
			{
				item_page = 0;
				select_num = 0;
			}
			else
			{
				item_page = item_page - 1;
				select_num = 9;
			}
		}
		break;
	case VK_DOWN:
		switch (menu)
		{
		case 0:
			item[select_item].bitmap = nullptr;
			break;
		case 1:
			//player[select_player].skill[select_item].bitmap = nullptr;
			break;
		default:
			break;
		}
		select_num = select_num + 1;
		if (select_num > 9)
		{
			if (item_page + 1 > 9)
			{
				item_page = 9;
				select_num = 9;
			}
			else
			{
				item_page = item_page + 1;
				select_num = 0;
			}
		}
		else
		{
			//*select_item = *select_item + 1;
		}
		break;
	case VK_SHIFT:
		switch (menu)
		{
		case 0:
			menu = 1;
			break;
		case 1:
			menu = 2;
			break;
		case 2:
			menu = 3;
			break;
		default:
			break;
		}
		break;
	case VK_ESCAPE:
		status = 1;
		break;
	default:
		break;
	}

}
void StatusMenu::buttonStatus()
{
	for (int i = 0; i <= 16; i++)
	{
		if (button[i].isVist == 1)
		{
			if (button[i].is_collision(point.x, point.y))
			{
				   button[current_button].status = button[current_button].NOMAL;
				current_button = i;
				button[current_button].status = button[current_button].PRESS;
				break;
			}
			else
			{
				if (button[i].status != button[i].SELECT)
					button[i].status = button[current_button].NOMAL;
			}
		}
	}
}
void StatusMenu::buttonEvent(WPARAM wParam)
{
	if (wParam == MK_LBUTTON)
	{
		switch (current_button)
		{
		case 0:
			select_player = 0;
			break;
		case 1:
			select_player = 1;
			break;
		case 2:
			select_player = 2;
			break;
		case 3:
			menu = 1;
			break;
		case 4:
			menu = 2;
			break;
		case 5:
			menu = 3;
			break;
		case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
			select_num = current_button - 6;
			button[current_button].status = button[current_button].SELECT;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (current_button)
		{
		case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
			select_num = current_button - 6;
			button[current_button].status = button[current_button].NOMAL;
			break;
		default:
			break;
		}
	}
}