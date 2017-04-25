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
	int status = 0; //状态 0--一般 1--选择面板
	int select_target1=-1;  //选中的目标1
	int target1_status=-1; 
	int select_target2=-1;  //选中的目标2
	int target2_status=-1;
	int getMany=0;
	//
	int select_skill;
	int select_item;
	int item_page=0;
	long time1;
	long time2;

	ID2D1Bitmap *back_grand=NULL; // 背景
	ID2D1Bitmap *back_grand1 = NULL; // 背景
	
	int fight_que[7] = {0,0,0,0,0,0,0}; //时间队列

	//int fenemy_num[3] = { 1,1,1 }; //敌人编号
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
	
	//加载战斗的图片资源
	void init(Player player[], 
		Animation playerAnm[], Animation enemyAnm[],  
		int fenemy[], Enemy enemy[]);
	void unload();
	//一般状态
	void normal(Player player[], Animation playerAnm[], Animation enemyAnm[],Enemy enemy[],Item item[]);
	//队列
	void makeQue(Player player[], Enemy enemy[]);
	//战斗动画
	void playerFight(Player player[], Animation playerAnm[], Animation enemyAnm[], Enemy enemy[]);
	//敌人攻击
	void enemyFight(Player player[], Animation playerAnm[], Animation enemyAnm[], Enemy enemy[]);
	//伤害计算
	void math(Player player[]);
	//胜负判定
	 int win_lose(Player player[]);
	//状态判断
	void judgPlayerStatus(Player player[]);
	void judgStatus(Enemy enemy[]);
	//战斗循环
	void run(Player player[], Animation playerAnm[], Animation enemyAnm[], Enemy enemy[], Item item[],Item item2[],LPDIRECTSOUNDBUFFER psbuf[]);
	void key_ctrl(HWND hwnd, WPARAM wParam, Player player[],Enemy enemy[],Task task,Fight fight);
	
};
