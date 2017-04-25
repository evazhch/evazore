#pragma once

#include "Npc.h"
class Npc;

class  Teleporter:public Npc
{
public:
	int face;
	int go_map = -1;
	int go_mapx = -1;
	int go_mapy = -1;
	int go_face;

	void draw();
	void set(int face, int gom, int gmx, int gmy, int gf);
	bool is_collision(Player player);
	void eventChange(Player player[]);
};