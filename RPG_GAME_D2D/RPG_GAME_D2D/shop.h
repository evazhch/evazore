#pragma once
class Player;
class Player;
class Item;
class Button;

class Shop
{
public:
	wchar_t str_1[10];
	wchar_t str_2[10];
	int show_num[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }; //出售的物品编号
	int select_num = 0; //画面中被选中的item
	int select_item = 0; //被选中的item
	int select_item_id = -1;
	Button button[10]; //0-4 物品选择按钮 5-购买 6-出售 7-关闭
	
	ID2D1Bitmap *select_player_menu = NULL;

	ID2D1Bitmap *backgrand = NULL;
	
	ID2D1Bitmap *item = NULL;

	void buyButtonEvent(Player player, Item item_player[], Item item[]);
	void sellButtonEvent(Player player, Item item_player[], Item item[]);
	void init();
	void buy(Player player, Item item_player[], Item item);
	void sell(Player player, Item item_player[], Item item);
	void key_ctrl(HWND hwnd, WPARAM wParam, Player player, Item item_player[], Item item[]);
};

