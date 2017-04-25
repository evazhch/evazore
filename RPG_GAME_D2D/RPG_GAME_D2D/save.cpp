#include "head.h"
#include "Map.h"
#include "Player.h"
#include "save.h"

using namespace std;
void Save::makeList(int source[])
{
	ifstream in(filename);
	if (!in.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	while (!in.eof())
	{
		in >> source[0];
		in >> source[1];
		in >> source[2];
		in >> source[3];
		in >> source[4];
		//角色基本状态
		for (int i = 0; i < 3; i++)
		{
			in >> source[6 + i * 2];
			in >> source[7 + i * 2];
		}
		in.close();
	}
}

void Save::showRead(Player player[], Map map[],Save save[])
{
	LoadBitmapFromFile(pRenderTarget, pWICFactory, back1_str, 0, 0, &back1);
	//背景
	pRenderTarget->DrawBitmap(
		back1,
		D2D1::RectF(
			0,
			0,
			rc.right,
			rc.bottom
		),
		1.0f
	);
		for (int i = 0; i < 4; i++)
		{
			save[i].makeList(save[i].sourcelis);
			if (save[i].sourcelis[0] == 1)
			{
				//被使用
				map[save[i].sourcelis[2]].drawMap(rc.left + 10,  rc.bottom / 5 * (i+1)+20, rc.bottom / 5, rc.bottom / 6);
				for (int j = 0; j < 3; j++)
				{
					if (save[i].sourcelis[6 + j * 2] == 1)
					{
						switch (j)
						{
						case 0:
							SAFE_RELEASE(back1);
							LoadBitmapFromFile(pRenderTarget, pWICFactory, L"save/01.png", 0, 0, &back1);
							break;
						case 1:
							SAFE_RELEASE(back1);
							LoadBitmapFromFile(pRenderTarget, pWICFactory, L"save/02.png", 0, 0, &back1);
							break;
						case 2:
							SAFE_RELEASE(back1);
							LoadBitmapFromFile(pRenderTarget, pWICFactory, L"save/03.png", 0, 0, &back1);
							break;
						default:
							break;
						}
						pRenderTarget->DrawBitmap(
							back1,
							D2D1::RectF(
								rc.left + 10 + (j + 1)*rc.bottom / 5,
								rc.bottom / 5 * (i + 1)+10,
								rc.left + 10 + (j+1)*rc.bottom / 5 + rc.bottom / 5,
								rc.bottom / 5 * (i + 1) + rc.bottom / 5
							),
							1.0f
						);
					}
				}
				button[i].set(rc.left + 10, 10 + rc.bottom / 5 * (i + 1), rc.bottom - 20, rc.bottom / 5, L"save/1.bmp", L"source/fight/change.png", L"source/fight/change.png");
				button[i].draw(0.5);
			}
			else
			{
				button[i].set(rc.left + 10, 10 + rc.bottom / 5 * (i+1), rc.bottom - 20, rc.bottom / 6, L"save/1.bmp", L"source/fight/change1.png", L"source/fight/change1.png");
				button[i].draw(0.5);
			}
	     }
		SAFE_RELEASE(back1);
}

void Save::showSave(Player player[], Item item_player[],Map map[],Save save[])
{
	LoadBitmapFromFile(pRenderTarget, pWICFactory, back2_str, 0, 0, &back2);
	//背景
	pRenderTarget->DrawBitmap(
		back2,
		D2D1::RectF(
			0,
			0,
			rc.right,
			rc.bottom
		),
		1.0f
	);
	for (int i = 0; i < 4; i++)
	{
		save[i].makeList(save[i].sourcelis);
		if (save[i].sourcelis[0] == 1)
		{
			//被使用
			map[save[i].sourcelis[2]].drawMap(rc.left + 10, rc.bottom / 5 * (i + 1) + 20, rc.bottom / 5, rc.bottom / 6);
			for (int j = 0; j < 3; j++)
			{
				if (save[i].sourcelis[6 + j * 2] == 1)
				{
					switch (j)
					{
					case 0:
						SAFE_RELEASE(back2);
						LoadBitmapFromFile(pRenderTarget, pWICFactory, L"save/01.png", 0, 0, &back2);
						break;
					case 1:
						SAFE_RELEASE(back2);
						LoadBitmapFromFile(pRenderTarget, pWICFactory, L"save/02.png", 0, 0, &back2);
						break;
					case 2:
						SAFE_RELEASE(back2);
						LoadBitmapFromFile(pRenderTarget, pWICFactory, L"save/03.png", 0, 0, &back2);
						break;
					default:
						break;
					}
					pRenderTarget->DrawBitmap(
						back2,
						D2D1::RectF(
							rc.left + 10 + (j + 1)*rc.bottom / 5,
							rc.bottom / 5 * (i + 1) + 10,
							rc.left + 10 + (j + 1)*rc.bottom / 5 + rc.bottom / 5,
							rc.bottom / 5 * (i + 1) + rc.bottom / 5
						),
						1.0f
					);
				}
			}
			button[i].set(rc.left + 10, 10 + rc.bottom / 5 * (i + 1), rc.bottom - 20, rc.bottom / 5, L"save/1.bmp", L"source/fight/change.png", L"source/fight/change.png");
			button[i].draw(0.5);
		}
		else
		{
			button[i].set(rc.left + 10, 10 + rc.bottom / 5 * (i + 1), rc.bottom - 20, rc.bottom / 6, L"save/1.bmp", L"source/fight/change1.png", L"source/fight/change1.png");
			button[i].draw(0.5);
		}
	}
	SAFE_RELEASE(back2);
}


int Save::saveG(Item item_player[],Player player[])
{
	ofstream out(filename);
	if (out.is_open())
	{
		out << 1 << '\n'; //存档已使用
		out << 1 << '\n'; // 地图
		out << current_map<<'\n';  //所在地图
		out << current_player<<'\n'; //领队
		out << money << '\n';
		//角色基本状态
		for (int i = 0; i < 3; i++)
		{
			out << player[i].is_active << '\n';
			out << player[i].level << '\n';
		}
		//player 坐标
		out << player[current_player].x_map << '\n';
		out << player[current_player].y_map << '\n';
		out << player_item_num << '\n'; //背包物品
		for (int i = 0; i < player_item_num; i++)
		{
			out << item_player[i].id << '\n';
			out << item_player[i].num << '\n';
		}
		for (int i = 0; i < 3; i++)
		{
			out << player[i].experience << '\n';
			out << player[i].attack << '\n';
			out << player[i].defense << '\n';
			out << player[i].fortune << '\n';
			out << player[i].fspeed << '\n';
			out << player[i].equip_att << '\n';
			out << player[i].equip_def << '\n';
		}
		out.close();
	}
	return 0;
}

int Save::readG(Player player[],Item item_player[],Item item[])
{
	ifstream in(filename);
	if (!in.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	while (!in.eof())
	{
		int a;//无关
		in >> a;

		in >> status;
		in >> current_map;
		in >> current_player;
		in >> money;
		//角色基本状态
		for (int i = 0; i < 3; i++)
		{
			in >> player[i].is_active ;
			in >> player[i].level;
		}
		//player 坐标
		in >> player[current_player].x_map;
		in >> player[current_player].y_map;

		int itemNum;
		in >> itemNum; //背包物品
		player_item_num = 0;
		for (int i = 0; i < itemNum; i++)
		{
			in >> item_player[i].id;
			in >> item_player[i].num;
			player[current_player].add_item(item_player[i].id, item_player[i].num, item_player, item);
		}
		for (int i = 0; i < 3; i++)
		{
			in >> player[i].experience;
			in >> player[i].attack;
			in >> player[i].defense;
			in >> player[i].fortune;
			in >> player[i].fspeed;
			in >> player[i].equip_att;
			in >> player[i].equip_def;
		}
		in.close();
	}
	return 0;
}

void Save::key_ctrl(HWND hwnd, WPARAM wParam, Player player[], Item item_player[], Item item[], Save save[])
{
	switch (wParam)
	{
	case 0:
		GetCursorPos(&point);			// 获取鼠标指针位置（屏幕坐标）
		ScreenToClient(hwnd, &point);	// 将鼠标指针位置转换为窗口坐标
		buttonStatus();
		break;
	case MK_LBUTTON:
		buttonEvent(wParam,player,item_player,item,save);
		break;
	case VK_SPACE: //物品技能使用
		buttonEvent(wParam, player, item_player, item, save);
		break;
	case VK_ESCAPE:
		status = 1;
		break;
	default:
		break;
	}

}

void Save::buttonStatus()
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

void Save::buttonEvent(WPARAM wParam, Player player[], Item item_player[], Item item[], Save save[])
{
	if(current_panel==1)
		save[current_button].readG(player, item_player, item);
	else if(current_panel==2)
	{
		save[current_panel].saveG(item_player, player);
	}
}