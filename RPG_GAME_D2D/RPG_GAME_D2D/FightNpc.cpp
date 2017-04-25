#include "head.h"
#include "FightNpc.h"

void FightNpc::set(int map, int x, int y, int que1,int que2,int que3)
{
	this->visible = true;
	this->x_map = x;
	this->y_map = y;
	this->map = map;
	this->bitmap_path = L"source/npc/change.png";
	this->anm_num = -1;
	this->anm_num2 = -2;
	this->collision = 0;
	this->anm_type = 0;
	this->currnt_anmtp = -1;
	this->que[0] = que1;
	this->que[1] = que2;
	this->que[2] = que3;
	this->visible = 1;
	this->w = 100;
	this->h = 100;
}

void FightNpc::is_collision(Player player)
{
	//player×ø±ê
	int x0 = player.x_map + player.x_offset / 2;
	int y0 = player.y_map - player.y_offset / 2;
	//npcÅö×²·¶Î§
	int x1 = x_map;
	int x2 = x_map + region_x;
	int y1 = y_map;
	int y2 = y_map + region_y;
	//player Ì½Õë
	int y3 = y0;
	int y4 = y0;
	int x3 = x0;
	int x4 = x0;

	if (map == current_map &&visible==true)
	{
		int i = (x1 < x3 &&  x4 < x2 && y1 < y3 &&  y4 < y2); //Í¼ĞÎÅö×²

		if (i)
		{
			eventFight();
		}
	}
}

void FightNpc::eventFight()
{
	visible = false;
	fenemy_num[0] = que[0];
	fenemy_num[1] = que[1];
	fenemy_num[2] = que[2];
	status = 5;
}
