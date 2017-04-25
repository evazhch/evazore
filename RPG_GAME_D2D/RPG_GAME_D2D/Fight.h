#pragma once
#include "Panel.h"
#include "Enemy.h"

class Animation;
class  Player;
class  Skill;
class Enemy;
class Button;
class Panel;

class  Fight
{
public:
	int status = 0; //״̬ 0--һ�� 1--ѡ�����
	int select_target1=-1;  //ѡ�е�Ŀ��1
	int target1_status=-1; 
	int select_target2=-1;  //ѡ�е�Ŀ��2
	int target2_status=-1;
	int getMany=0;
	//
	int select_skill;
	int select_item;
	int item_page=0;
	long time1;
	long time2;

	ID2D1Bitmap *back_grand=NULL; // ����
	ID2D1Bitmap *back_grand1 = NULL; // ����
	
	int fight_que[7] = {0,0,0,0,0,0,0}; //ʱ�����

	//int fenemy_num[3] = { 1,1,1 }; //���˱��
	Enemy fenemy[3];

	int fight_type=-1;

	Panel chose_panel;
	Button chose_button[5];
	Panel chose2_panel;
	Button chose2_button[9];
	Panel skill_panel;
	Button skill_button[5];
	Panel item_panel;
	Button item_button[5];

	Panel win_panel;
	Button win_button[2];

	Panel end_panel;
	Button end_button[2];
	
	//����ս����ͼƬ��Դ
	void init(Player player[], 
		Animation playerAnm[], Animation enemyAnm[],  
		int fenemy[], Enemy enemy[]);
	void unload();
	//һ��״̬
	void normal(Player player[], Animation playerAnm[], Animation enemyAnm[],Enemy enemy[],Item item[]);
	//����
	void makeQue(Player player[], Enemy enemy[]);
	//ս������
	void playerFight(Player player[], Animation playerAnm[], Animation enemyAnm[], Enemy enemy[]);
	//���˹���
	void enemyFight(Player player[], Animation playerAnm[], Animation enemyAnm[], Enemy enemy[]);
	//�˺�����
	void math(Player player[]);
	//ʤ���ж�
	 int win_lose(Player player[]);
	//״̬�ж�
	void judgPlayerStatus(Player player[]);
	void judgStatus(Enemy enemy[]);
	//ս��ѭ��
	void run(Player player[], Animation playerAnm[], Animation enemyAnm[], Enemy enemy[], Item item[],Item item2[],LPDIRECTSOUNDBUFFER psbuf[]);
	void key_ctrl(HWND hwnd, WPARAM wParam, Player player[],Enemy enemy[],Task task,Fight fight);
	
};
