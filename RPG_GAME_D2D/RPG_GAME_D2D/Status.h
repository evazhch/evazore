#pragma once
class Player;
class Item;
class Button;

class StatusMenu
{
public:
	int item_page = 0; //�ڼ�ҳ��Ʒ
	int menu = 0;//1--��Ʒ��2--���� 3--����
	LPCWSTR playerstatus_str[3];
	wchar_t str_1[10];
	wchar_t str_2[10];
	int select_player = 0;
	int show_num[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; //ÿҳ����ʼ
	int select_num = 0; //�����б�ѡ�е�item/skill
	int select_item = 0; //��ѡ�е�item
	int select_skill = 0; //��ѡ�е�skill
	int select_item_id = -1;
 	ID2D1Bitmap *select_player_menu = NULL;
	ID2D1Bitmap *backgrand = NULL;
	ID2D1Bitmap *backgrand1 = NULL;
	ID2D1Bitmap *backgrand2 = NULL;
	ID2D1Bitmap *backgrand3 = NULL;
	ID2D1Bitmap *button_que = NULL;
	ID2D1Bitmap *item = NULL;
	ID2D1Bitmap *skill = NULL;
	Button button[20];
	int current_button = 0;

	//������Դ
	void load();
	//������Դ
	void unload();
	void buttonStatus();
	void buttonEvent(WPARAM wParam);
	void draw_back();
	void drawPlayersta(Player player[]);
	void drawItem(Item item[]);
	void drawSkill(Player player[]);
	void drawtext(wchar_t str[], ID2D1SolidColorBrush *brush, int x, int y, int w, int h);
	void drawtext1(wchar_t str[], ID2D1SolidColorBrush *brush, int x, int y, int w, int h);
	void drawtext(LPCWSTR str, ID2D1SolidColorBrush *brush, int x, int y, int w, int h);
	void drawtext1(LPCWSTR str, ID2D1SolidColorBrush *brush, int x, int y, int w, int h);
	void draw_statusmenu(HWND hWnd, Player player[], ID2D1RenderTarget *pRenderTarget, Item item[]);
	void key_ctrl(HWND hwnd, WPARAM wParam, Player player[], Item item[]);
};