#include "head.h"
#include "time.h"
#include "Item.h"
#include "Skill.h"
#include "Player.h"
#include "Map.h"

//绘制player
void Player::DrawPlayer(HWND hWnd, Player player, int face, int animation_ctrl, ID2D1RenderTarget *pRenderTarget)
{
	D2D1_SIZE_F size = player.bitmap->GetSize();
	// Draw bitmap
	pRenderTarget->DrawBitmap(
		player.bitmap,
		D2D1::RectF(
			player.x,
			player.y - player.y_offset,
			player.x + size.width / 4*w_offset,
			player.y - player.y_offset + size.height / 4*h_offset),   //D2D::RectF 要在屏幕上绘制的区域
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(
		(animation_ctrl % 4)*(size.width / 4),
			size.height / 4 * (face - 1),
			(animation_ctrl % 4)*(size.width / 4) + size.width / 4,
			size.height / 4 * (face - 1) + size.height / 4)  //角色图片上的区域
	);
}
//player 成员之间传递属性
void Player::set_player(Player player[], int oldindex, int newindex)
{
	player[newindex].x_map = player[oldindex].x_map;
	player[newindex].y_map = player[oldindex].y_map;
	player[newindex].face = player[oldindex].face;

	current_player = newindex;
}
//TAB--队伍切换
void Player::change_player(Player player[])
{
	for (int i = current_player + 1; i < player[current_player].length; i++)
	{
		if (player[i].is_active == 1)
		{
			set_player(player, current_player, i);
			return;
		}
	}
	for (int i = 0; i < current_player; i++)
	{
		if (player[i].is_active == 1)
		{
			set_player(player, current_player, i);
			return;
		}
	}
}
//player背包物品增加----id寻找
void Player::add_item(int id, int num, Item item[],Item item2[])
{
	int i = 0;
	for ( i = 0; i<player_item_num; i++)
	{
		if (item[i].id == id)
		{
			item[i].num += num;
			if (item[i].num < 0)
				item[i].num = 0;
			break;
		}
	}
	if (i == player_item_num)
	{
		for (int j = 0; j < 99; j++)
		{
			if (id == item2[j].id)
			{
				item[player_item_num] = item2[j];
				item[player_item_num].num+=num;
				player_item_num++;
				break;
			}
		}
	}
	if (item[i].num == 0)
	{
		for (int j = i; j < player_item_num; j++)
		{
			item[j] = item[j + 1];
		}
		player_item_num--;
	}
}
void Player::add_item(int id, int num, Item item[])
{
	int i = 0;
	for (i = 0; i<player_item_num; i++)
	{
		if (item[i].id == id)
		{
			item[i].num += num;
			if (item[i].num < 0)
				item[i].num = 0;
			break;
		}
	}
	if (item[i].num == 0)
	{
		for (int j = i; j < player_item_num; j++)
		{
			item[j] = item[j + 1];
		}
		player_item_num--;
	}
}
//player属性提升
void Player::add_status(Item item)
{
	/* //装备属性
	int value1 = 0;        //攻击加成
	int value2 = 0;        //防御加成
	int value3 = 0;        //速度加成
	int value4 = 0;        //运气加成
	//物品属性
	int value5 = 0;         //加血hp效果
	int value6 = 0;         //加mp效果
	int value7 = 0;        //加maxhp
	int value8 = 0;        //加maxmp
	*/
	this->hp += item.value5;
	if (this->hp > this->max_hp)
		this->hp = this->max_hp;
	if (this->hp < 0)
		this->hp = 0;

	this->mp += item.value6;
	if (this->mp > this->max_mp)
		this->mp = this->max_mp;
	if (this->mp < 0)
		this->mp = 0;

	this->attack += item.value1;
	this->defense += item.value2;
	this->fspeed += item.value3;
	this->fortune += item.value4;
	this->max_hp += item.value7;
	this->max_mp += item.value8;
}
//level up
void Player::level_up(Item item)
{
	//hp,mp增加
	this->max_hp += item.value5;
	this->hp = this->max_hp;
	this->max_mp += item.value6;
	this->mp += this->max_mp;
	//战斗属性增加
	this->attack += item.value1;
	this->defense += item.value2;
	this->fspeed += item.value3;
	this->fortune += item.value4;
}
//卸载装备 type 卸载啥0--功 1--守
void Player::unequip(int type, Item item[])
{
	Item item0;
	Item item1 = this->equip[0];
	Item item2 = this->equip[1];
	//获取index
	int index;
	if (type == 0 && this->equip_att != -1)
	{
		index = item1.id;
		this->equip[0] = item0;
		this->equip_att = -1;

	}
	else if (type == 1 && this->equip_def != -1)
	{
		index = item2.id;
		this->equip[1] = item0;
		this->equip_def = -1;
	}
	else return;
	add_item(index, 1, item);
}
void Player::onequip(Item item[], int index)
{
	unequip(item[index].item_type, item);
	if (item[index].item_type == 0)
	{
		this->equip_att = item[index].id;
		this->equip[0] = item[index];
		add_item(item[index].id, -1, item);
	}
	else if (item[index].item_type == 1)
	{
		this->equip_def = item[index].id;
		this->equip[1] = item[index];
		add_item(item[index].id, -1, item);
	}

}
void Player::use_item(int id, Item item[])
{
	int select_item = -1;
	for (int i = 0; i < player_item_num; i++)
	{
		if (item[i].id == id)
		{
			select_item = i;
			break;
		}
	}
	if (item[select_item].num > 0)
	{
		switch (item[select_item].item_type)
		{
		case -1:
			add_status(item[select_item]);
			add_item(item[select_item].id, -1, item);
			break;
		case 0:
			onequip(item, select_item);
			break;
		case 1:
			onequip(item, select_item);
			break;
		default:
			break;
		}
	}
}
void Player::add_hp(Skill skill)
{
	//Player player = Form1.player[Player.select_player];
	this->hp += skill.value1;
	if (this->hp > this->max_hp)
		this->hp = this->max_hp;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::walk(int i)
{
	timeEnd= GetTickCount();
	if (timeEnd - timeBegin > walk_interval)
	{
		animation_ctrl++;
		timeBegin = timeEnd;
		switch (face)
		{
		case 1:
			if (walk_type == 1)
			{
				y_map = y_map + i;
				if (y_map > target_y)
				{
					y_map = target_y;
				}
			}
			else
			{
				y_map = y_map + i;
			}
			
			break;
		case 4:
			if (walk_type == 1)
			{
				y_map = y_map - i;
				if (y_map < target_y)
				{
					y_map = target_y;
				}
			}
			else
			{
				y_map = y_map - i;
			}
			break;
		case 2:
			if (walk_type == 1)
			{
				x_map = x_map - i;
				if (x_map < target_x)
				{
					x_map = target_x;
				}
			}
			else
			{
				x_map = x_map - i;
			}
			break;
		case 3:
			if (walk_type == 1)
			{
				x_map = x_map + i;
				if (x_map > target_x)
				{
					x_map = target_x;
				}
			}
			else
			{
				x_map = x_map + i;
			}
			break;
		}
	}
}