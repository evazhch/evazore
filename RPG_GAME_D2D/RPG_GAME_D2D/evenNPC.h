#pragma once

#include "Npc.h"
class Npc;
//����ᴥ����Ʒ���
class  EvenNpc :public Npc
{
public:
	int item_id;
	int num;

	
	void set(int x, int y, int map, int item_id, int num, int anm_num);
	void eventget(Player player[],Item item_player[],Item item[]);
};