#include "Teleporter.h"

void Teleporter::draw()
{
	if (bitmap != NULL)
	{
		// Draw bitmap
		pRenderTarget->DrawBitmap(
			bitmap,
			D2D1::RectF(
				x,
				y,
				x + region_x,
				y + region_y),
			1.0f
		);
	}
}

void Teleporter::set(int face, int gom, int gmx, int gmy, int gf)
{
	this->face = face;
	go_face = gf;
	go_map = gom;
	go_mapx = gmx;
	go_mapy = gmy;
}

bool Teleporter::is_collision(Player player)
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

		if (map == current_map)
		{
			int i = (x1 < x3 &&  x4 < x2 && y1 < y3 &&  y4 < y2); //Í¼ĞÎÅö×²
		
			if (i && player.face==face)
			{
					return 1;
			}
		}
		return 0;
}
void Teleporter::eventChange(Player player[])
{
	player[current_player].walk_type = 0;
	current_map = go_map;
	player[current_player].x_map = go_mapx;
	player[current_player].y_map = go_mapy;
	player[current_player].face = go_face;
}