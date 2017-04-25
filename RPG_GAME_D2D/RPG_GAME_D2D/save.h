#pragma once
class Map;
class Player;

class Save
{
public:
	LPCWSTR back1_str = L"source/status/4.bmp";
	LPCWSTR back2_str = L"source/status/3.bmp";
	ID2D1Bitmap *back1;
	ID2D1Bitmap *back2;

	Button button[5];
	int current_button;
	char* filename = NULL;
	int sourcelis[12];
	void makeList(int source[]);
	void buttonEvent(WPARAM wParam, Player player[], Item item_player[], Item item[], Save save[]);
	void buttonStatus();
	void key_ctrl(HWND hwnd, WPARAM wParam, Player player[], Item item_player[], Item item[], Save save[]);
	void showRead(Player player[],Map map[],Save save[]);
	void showSave(Player player[], Item item_player[], Map map[], Save save[]);
	int saveG(Item item_player[], Player player[]);
	int readG(Player player[], Item player_item[], Item Item[]);
};

