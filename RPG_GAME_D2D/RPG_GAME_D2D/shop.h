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
	int show_num[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }; //���۵���Ʒ���
	int select_num = 0; //�����б�ѡ�е�item
	int select_item = 0; //��ѡ�е�item
	int select_item_id = -1;
	Button button[10]; //0-4 ��Ʒѡ��ť 5-���� 6-���� 7-�ر�
	
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

