#include "Astar.h"
class  Npc;
class Teleporter;
class FightNpc;
class Player;
class Map
{
public:

	//入口
	int x_in;
	int y_in;
	//出口
	int x_out;
	int y_out;

	int x = 0;
	int y = 0;
	int xr = 0;
	int yb = 0;

	int target_x;
	int target_y;
	//float x_offset=1; //x修正参数
	//float y_offset=1;//y修正参数
	//优化
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
	//绘制地图/角色/npc
	void DrawMap(HWND hWnd, Player player[], Teleporter teleporter[], Npc npc[], FightNpc fightNpc[], int animation_ctrl, Animation npcAnm[]);
	void setMap(int inx,int iny,LPCWSTR map_p, LPCWSTR shade_p, LPCWSTR block_p);
	
	//地图显示在屏幕上的区域
	D2D1_RECT_F map_rect(Player player[]);
	
	

	void makeBlockMap();
	std::list<Point*> getEndAStar(int sx, int sy, int ex, int ey);
	int get_blockcolor(int x, int y, int face, int speed, LPCWSTR url);
	
	int can_move(Player player);

	void move(Player player[]);

	void move(WPARAM wParam, Player player[]);
	//地图切换
	int change_map(Player player[], Teleporter Teleporter[]);
	
	//player在地图上的一系列键盘操作
	void key_ctrl(HWND hwnd, WPARAM wParam, Player player[], Npc npc[],Task task);
};