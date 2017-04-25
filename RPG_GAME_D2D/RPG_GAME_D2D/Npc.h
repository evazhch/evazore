#pragma once
#include "Animation.h"
class  Animation;
class Player;
class Npc
{
public:
	int npc_type = 0;  //显示类型 0--有地图关系 1--无地图关系

	//碰撞区域
	 int region_x = 100;
	 int region_y = 100;
	
	 //位置
	 int map = -1;
	 int x = 0; 
	 int y = 0;
	 int w = 50;
	 int h = 50;
     int x_offset = 47;
	 int y_offset = 95;
	 int x_map =0;
	 int y_map =0;
	
	 //显示
	 LPCWSTR bitmap_path;
	 ID2D1Bitmap *bitmap;
	 bool visible = true;  //是否显示

	 //story
	 //int enemyQue[3] = { 1,-1,-1 };
	 int story_num = 0;
	 int collision = 0; //碰撞类型  0--直接触发 1--需要按空格 2--鼠标点击
	 //动画
	 bool is_anm = 0; //是否有动画
	 int anm_type = 0;//0--静止动画，1--单项移动 2--双向移动
	 int currnt_anmtp = 0; //状态变化中间量
	 int face = 0;//方向
	 int xMove[2] = { -1,-1};
	 int yMove[2] = { -1,-1};
	 int anm_num=-1; //动画编号
	 int anm_num2 = -1;
	 long timetag=0;

	 //加载
	 void load();
	 //卸载
	 void unload();
	 void move(int x, int y);
	 //移动
	 void move(int x, int y, int x1, int y1);
	 //设置坐标
	 void set(int map, int x_map, int y_map, LPCWSTR bitmap_path, bool visible, int story_num, int collision);
	 void set(int map,int x_map, int y_map, LPCWSTR bitmap_path, bool visible, int story_num,int collision,int is_anm,int anm_num);
	 void set(int is_anm, int anm_type, int face, int x, int y, int x1, int y1, int anm1, int anm2);

	 //坐标处理
	 int can_draw_npc(int current_map, D2D1_RECT_F map_size, int y);
	 //绘图
	 void drawNpc(Animation npcAnm[]);
	 //
	 void drawNpc();
	 void mark_collision(Player player, int cannot);

	 bool is_collision(Player player, Npc *npc1);
	 
	 int collision_act(Npc npc[], Player player, int num);
};
 
