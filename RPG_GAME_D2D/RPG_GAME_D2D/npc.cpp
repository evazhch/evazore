#include"head.h"
#include "Animation.h"
#include "Player.h"
#include "Map.h"
#include"Npc.h"

class Map;

void Npc::load()
{
	if (bitmap == NULL && bitmap_path != NULL)
		LoadBitmapFromFile(pRenderTarget, pWICFactory, bitmap_path, 0, 0, &bitmap);
}
void Npc::unload()
{
	SAFE_RELEASE(bitmap);
}

void Npc::move(int x, int y)
{
	if (end-timetag>100)
	{
		timetag = end;
		if (this->x_map != x)
		{
			if (this->x_map <= x)
			{
				this->x_map = this->x_map + 5;
				if (this->x_map >= x)
					this->x_map = x;
			}
			else
			{
				this->x_map = this->x_map - 5;
				if (this->x_map <= x)
				{
					this->x_map = x;
				}
			}
		}

		if (this->y_map != y)
		{
			if (this->y_map <= y)
			{
				this->y_map = this->y_map + 5;
				if (this->y_map >= y)
					this->y_map = y;
			}
			else
			{
				this->y_map = this->y_map - 5;
				if (this->y_map <= y)
				{
					this->y_map = y;
				}
			}
		}
	}
}

void Npc::move(int x, int y, int x1, int y1)
{
	if (1)
	{
		//timetag = end;

		if (face == 1)
		{
			move(x1, y1);
			if (this->x_map == x1 && this->y_map == y1)
			{
				face = 0;
			}
		}
		else if (face == 0)
		{
			move(x, y);
			if (this->x_map == x && this->y_map == y)
			{
				face = 1;
			}
		}
	}
}
//¾²Ì¬
void Npc::set(int map, int x_map, int y_map, LPCWSTR bitmap_path, bool visible, int story_num, int collision)
{
	this->map = map;
	this->x_map = x_map;
	this->y_map = y_map;
	this->bitmap_path = bitmap_path;
	this->visible = visible;
	this->story_num = story_num;
	this->collision = collision;
}
//¾²Ì¬¶¯»­
void Npc::set(int map, int x_map, int y_map, LPCWSTR bitmap_path, bool visible, int story_num, int collision, int is_anm, int anm_num)
{
	this->map = map;
	this->x_map = x_map;
	this->y_map = y_map;
	this->bitmap_path = bitmap_path;
	this->visible = visible;
	this->story_num = story_num;
	this->collision = collision;
	this->is_anm = is_anm;
	this->anm_num = anm_num;
}
//Ñ­»·ÒÆ¶¯¶¯»­
void Npc::set(int is_anm, int anm_type, int face, int x, int y, int x1, int y1, int anm1, int anm2)
{
	this->anm_num = anm1;
	this->anm_num2 = anm2;
	this->is_anm = is_anm;
	this->anm_type = anm_type;
	this->xMove[0] = x;
	this->xMove[1] = x1;
	this->yMove[0] = y;
	this->yMove[1] = y1;
}

//ÊÇ·ñ»æÍ¼
int Npc::can_draw_npc(int current_map, D2D1_RECT_F map_size, int leve)
{
	if (map == current_map && visible==true)
	{
		if (x_map > map_size.left - x_offset &&
			x_map <map_size.right &&
			y_map >map_size.top - y_offset &&
			y_map < map_size.bottom)
		{
			x = (x_map - map_size.left)*w_offset;
			y = (y_map - map_size.top)*h_offset;
			if (y_map > leve) //±»ÕÚµ²
				return 2;
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}
}
//»æÍ¼
void Npc::drawNpc(Animation npcAnm[])
{
	if (is_anm == 0)
	{
		if (visible != true)
			return;
		drawNpc();
	}
	else
	{
		if (anm_type == 0)
			npcAnm[anm_num].drawAnm(x, y, x_offset, y_offset);
		else if(anm_type==1)  //µ¥ÏòÒÆ¶¯
		{
			move(xMove[0], yMove[0]);
			npcAnm[anm_num].drawAnm(x, y, x_offset, y_offset);
		}
		else if (anm_type == 2)//Ë«ÏòÒÆ¶¯
		{
			move(xMove[0], yMove[0], xMove[1], yMove[1]);
			if (face == 0)
			{
				npcAnm[anm_num].drawAnm(x, y, x_offset, y_offset);
			}
			else
			{
				npcAnm[anm_num2].drawAnm(x, y, x_offset, y_offset);
			}
		}
	}
}
void Npc::drawNpc()
{
	if (bitmap != NULL)
	{
		// Draw bitmap
		pRenderTarget->DrawBitmap(
			bitmap,
			D2D1::RectF(
				x,
				y,
				x + w,
				y + h),
			1.0f
		);
	}
}
//Åö×²ÌáÊ¾
void Npc::mark_collision(Player player, int type)
{
	switch (type)
	{
	case 0: //ÎŞ
		x = -100;
		y = -100;
		npc_type = 0;
		break;
	case 1: //Åö×²
		npc_type = 2;
		x = player.x + player.x_offset / 2;
		y = player.y - player.y_offset;
		break;
	case 2: //Êó±ê
		npc_type = 2;
		x = point.x;
		y = point.y;
		break;
	default:
		break;
	}
}
//ÊÇ·ñÅö×²
bool Npc::is_collision(Player player, Npc *npc1)
{
	//player×ø±ê
	int x0 = player.x;
	int y0 = player.y;
	//npcÅö×²·¶Î§
	int x1 = x;
	int x2 = x + region_x;
	int y1 = y;
	int y2 = y + region_y;
	//player Ì½Õë
	int y3 = y0;
	int y4 = y0;
	int x3 = x0;
	int x4 = x0;
	if (npc_type == 1)
	{
		int j = (x < point.x && point.x < x + x_offset && y < point.y &&  point.y < y + y_offset);//Êó±êÅö×²
		if (j)
		{
			npc1->mark_collision(player, 0);
			return 2;
		}
	}

	if (map == current_map)
	{
		int i = (x1 < x3 &&  x4 < x2 && y1 < y3 &&  y4 < y2); //Í¼ĞÎÅö×²
		int j = (x < point.x && point.x < x + x_offset && y < point.y &&  point.y < y + y_offset);//Êó±êÅö×²
		if (i)
		{
			//Á¢¿Ì´¥·¢
			if (collision == 0)
			{
				npc1->mark_collision(player, 0);
				return 1;
			}
			if (collision == 1) //¸´ºÏ
			{
				if (j)
				{
					npc1->mark_collision(player, 2);
					return 2;
				}
				else
				{
					npc1->mark_collision(player, 1);
					return 1;
				}
			}
		}
		if (collision == 2) //Êó±êµã»÷
		{
			if (j)
			{
				anm_type = 0;
				npc1->mark_collision(player, 2);
				return 2;
			}
			else
			{
				anm_type = currnt_anmtp;
			}
		}

		npc1->mark_collision(player, 0);
		return 0;
	}
}
//Åö×²²Ù×÷
int Npc::collision_act(Npc npc[], Player player, int num)
{
	for (int i = 1; i <= num; i++)
	{
		if (npc[i].visible == true)
		{
			if (npc[i].is_collision(player, &npc[0]) != 0)
			{
				return i;
			}
		}
	}
	return -1;
}

