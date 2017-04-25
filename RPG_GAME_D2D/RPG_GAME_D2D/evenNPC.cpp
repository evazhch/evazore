#include "evenNPC.h"

void EvenNpc::set(int x,int y,int map,int item_id,int num,int anm_num)
{
	this->item_id = item_id;
	this->num = num;
	this->visible = true;
	this->x_map = x;
	this->y_map = y;
	this->map = map;
	this->bitmap_path = L"source/npc/change.png";
	this->anm_num = anm_num;
	this->anm_num2 = -2;
	this->collision = 0;
	this->anm_type = 0;
	this->currnt_anmtp = -1;
	this->w = 100;
	this->h = 100;
}

void EvenNpc::eventget(Player player[], Item item_player[], Item item[])
{
	is_anm = 1;
	player[current_player].add_item(item_id, num, item_player, item);
}
