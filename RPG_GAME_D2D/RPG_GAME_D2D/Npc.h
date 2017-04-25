#pragma once
#include "Animation.h"
class  Animation;
class Player;
class Npc
{
public:
	int npc_type = 0;  //��ʾ���� 0--�е�ͼ��ϵ 1--�޵�ͼ��ϵ

	//��ײ����
	 int region_x = 100;
	 int region_y = 100;
	
	 //λ��
	 int map = -1;
	 int x = 0; 
	 int y = 0;
	 int w = 50;
	 int h = 50;
     int x_offset = 47;
	 int y_offset = 95;
	 int x_map =0;
	 int y_map =0;
	
	 //��ʾ
	 LPCWSTR bitmap_path;
	 ID2D1Bitmap *bitmap;
	 bool visible = true;  //�Ƿ���ʾ

	 //story
	 //int enemyQue[3] = { 1,-1,-1 };
	 int story_num = 0;
	 int collision = 0; //��ײ����  0--ֱ�Ӵ��� 1--��Ҫ���ո� 2--�����
	 //����
	 bool is_anm = 0; //�Ƿ��ж���
	 int anm_type = 0;//0--��ֹ������1--�����ƶ� 2--˫���ƶ�
	 int currnt_anmtp = 0; //״̬�仯�м���
	 int face = 0;//����
	 int xMove[2] = { -1,-1};
	 int yMove[2] = { -1,-1};
	 int anm_num=-1; //�������
	 int anm_num2 = -1;
	 long timetag=0;

	 //����
	 void load();
	 //ж��
	 void unload();
	 void move(int x, int y);
	 //�ƶ�
	 void move(int x, int y, int x1, int y1);
	 //��������
	 void set(int map, int x_map, int y_map, LPCWSTR bitmap_path, bool visible, int story_num, int collision);
	 void set(int map,int x_map, int y_map, LPCWSTR bitmap_path, bool visible, int story_num,int collision,int is_anm,int anm_num);
	 void set(int is_anm, int anm_type, int face, int x, int y, int x1, int y1, int anm1, int anm2);

	 //���괦��
	 int can_draw_npc(int current_map, D2D1_RECT_F map_size, int y);
	 //��ͼ
	 void drawNpc(Animation npcAnm[]);
	 //
	 void drawNpc();
	 void mark_collision(Player player, int cannot);

	 bool is_collision(Player player, Npc *npc1);
	 
	 int collision_act(Npc npc[], Player player, int num);
};
 
