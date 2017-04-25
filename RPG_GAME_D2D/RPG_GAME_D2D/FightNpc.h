#pragma once
#include "Npc.h"

class Npc;

class FightNpc:public Npc
{
public:
	int type = 0;
	int que[3];
	

	void set(int map, int x, int y, int que1, int que2, int que3);
	void is_collision(Player player);
	void eventFight();
};
