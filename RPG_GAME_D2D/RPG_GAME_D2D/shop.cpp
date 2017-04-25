#include "head.h"
#include "Item.h"
#include "Player.h"
#include "Skill.h"
#include "shop.h"

void Shop::init()
{
	//背景图
	if (backgrand != NULL)
	{
		pRenderTarget->DrawBitmap(
			backgrand,
			NULL,
			1.0f
		);
	}
	//画面板

}

void Shop::buy(Player player,Item item_player[],Item item)
{
	money -= item.cost;
	player.add_item(item.id, 1,item_player,&item);
}

void Shop::sell(Player player, Item item_player[], Item item)
{
	money += item.sellcost;
	player.add_item(item.id, -1, item_player);
}

void Shop::key_ctrl(HWND hwnd, WPARAM wParam,Player player,Item item_player[],Item item[])
{
	switch (wParam)
	{
	case 0:
		GetCursorPos(&point);			// 获取鼠标指针位置（屏幕坐标）
		ScreenToClient(hwnd, &point);	// 将鼠标指针位置转换为窗口坐标
		for (int i = 0; i <= 4; i++)
		{
			if (button[i].is_collision(point.x, point.y) && button[i].type == 0)
			{
				button[i].status = button[i].SELECT;
			}
			else if (button[i].type == 0)
			{
				button[i].status = button[i].NOMAL;
			}
		}
		break;
	case MK_LBUTTON:
		for (int i = 0; i <= 4; i++)
		{
			if (button[i].is_collision(point.x, point.y) && button[i].type == 0)
			{
				button[i].status = button[i].SELECT;
				button[i].type = 1;
			}
		}
		if (button[5].is_collision(point.x, point.y))
		{
			buyButtonEvent(player, item_player, item);
		}
		else if(button[6].is_collision(point.x,point.y))
		{
		
		}
		else if(button[7].is_collision(point.x,point.y))
		{

		}
		break;
	case MK_RBUTTON:
		for (int i = 0; i <= 4; i++)
		{
			if (button[i].is_collision(point.x, point.y) && button[i].type == 1)
			{
				button[i].status = button[i].NOMAL;
				button[i].type = 0;
			}
		}
		break;
	default:
			break;
	}
}

void Shop::buyButtonEvent(Player player, Item item_player[], Item item[])
{
	if (button[5].status == button[5].SELECT)
	{
		for (int i = 0; i <= 4; i++)
		{
			if (button[i].status = button[i].SELECT)
			{
				buy(player,item_player,item[button[i].item_num]);
			}
		}
	}
}

void Shop::sellButtonEvent(Player player, Item item_player[], Item item[])
{
	if (button[6].status == button[5].SELECT)
	{
		for (int i = 0; i <= 4; i++)
		{
			if (button[i].status = button[i].SELECT)
			{
				sell(player, item_player, item[button[i].item_num]);
			}
		}
	}
}