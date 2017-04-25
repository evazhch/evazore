#include "Astar.h"
class  Npc;
class Teleporter;
class FightNpc;
class Player;
class Map
{
public:

	//���
	int x_in;
	int y_in;
	//����
	int x_out;
	int y_out;

	int x = 0;
	int y = 0;
	int xr = 0;
	int yb = 0;

	int target_x;
	int target_y;
	//float x_offset=1; //x��������
	//float y_offset=1;//y��������
	//�Ż�
	const float w = 640;
	const float h = 480;
	
	LPCWSTR name;

	LPCWSTR map_path;
	ID2D1Bitmap *map;
	LPCWSTR shade_path;
	ID2D1Bitmap *shade;
	LPCWSTR  block_str;
	ID2D1Bitmap *block;
	ID2D1Bitmap *back;
	int blockmap[128][128];
	std::list<Point *> golist;

	void load();
	void unload();
	void drawMap(int x, int y, int w, int h);
	//���Ƶ�ͼ/��ɫ/npc
	void DrawMap(HWND hWnd, Player player[], Teleporter teleporter[], Npc npc[], FightNpc fightNpc[], int animation_ctrl, Animation npcAnm[]);
	void setMap(int inx,int iny,LPCWSTR map_p, LPCWSTR shade_p, LPCWSTR block_p);
	
	//��ͼ��ʾ����Ļ�ϵ�����
	D2D1_RECT_F map_rect(Player player[]);
	
	

	void makeBlockMap();
	std::list<Point*> getEndAStar(int sx, int sy, int ex, int ey);
	int get_blockcolor(int x, int y, int face, int speed, LPCWSTR url);
	
	int can_move(Player player);

	void move(Player player[]);

	void move(WPARAM wParam, Player player[]);
	//��ͼ�л�
	int change_map(Player player[], Teleporter Teleporter[]);
	
	//player�ڵ�ͼ�ϵ�һϵ�м��̲���
	void key_ctrl(HWND hwnd, WPARAM wParam, Player player[], Npc npc[],Task task);
};