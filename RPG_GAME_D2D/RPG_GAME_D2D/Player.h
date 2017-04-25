#pragma once
#include "Skill.h"
#include "Item.h"
class Skill;
class Item;
class Map;
class Player
{
public:

	int walk_type;

	int level=1; //等级--关系技能解锁
	int experience = 0; //经验关系升级

	int exmake[6];
	int upmake[6];
	int basehp;
	int basemp;
	int basestt;
	int basedef;
	int basefs;
	int baseftu;
	

	//队伍中角色i数目
	int length = 3;
	//是否激活--角色是否在队伍中
	int is_active = 0;
	//window上坐标
	int x = 0;
	int y = 0;
	//位置修正参数--角色图像的大小
	const int x_offset = 46;
	const int y_offset = 92;
	//角色在地图上的坐标
	int x_map ;
	int y_map ;
	//方向移动的朝向
	int face = 1;
	int target_x;
	int target_y;
	//行走参数
	long walk_interval = 100; //动画帧切换的速度（ms）
	int speed = 10; //速度


	ID2D1Bitmap *bitmap; //角色的图像接口
	 //状态
	int max_hp = 100; //血量
	int hp = 100;  
	int max_mp = 100; //技能法术量
	int mp = 100;

	int attack = 1000;     //攻击力
	int defense = 100;  //防御力
	int fspeed = 100; //攻击速度
	int fortune = 10;  //运气
	
	int equip_att = 0;    //攻击装备是否加载1--加载
	int equip_def = 0;   //防御装备是否加载1--加载

	long timeEnd;
	long timeBegin;
	//装备
	Item equip[2];
	//技能
    Skill skill[5];

	//战斗属性
	int fstatus = 0; //状态[0]一般 [1]击中 [2]--虚弱 [3]--死亡 [4]移动 [5]技能 [6]物品释放 [7]状态承受
	int fstatus_anm[9] = {1,2,3,4,5,6,7,8,9};//[0]一般  [1]击中  [2]--虚弱  [3]--死亡  [4]移动  [5]技能  [6]物品释放 [7]状态承受  [8]防御
	LPCWSTR fface_path = NULL;
	ID2D1Bitmap *fface = NULL;
	int anm_item;
	LPCWSTR name = L""; //角色名字


	//画角色
	void DrawPlayer(HWND hWnd, Player player, int face, int animation_ctrl, ID2D1RenderTarget *pRenderTarget);
	//设置角色
	void set_player(Player player[], int oldindex, int newindex);
	void change_player(Player player[]);
	//player属性升级
	void add_status(Item item);

	//player 对物品使用-----------------------------------------
	void add_item(int id, int num, Item item[],Item item2[]);
	void add_item(int id, int num, Item item[]);
	void use_item(int id, Item item[]);
	//level up
	void level_up(Item item);
	//卸载装备 type 卸载啥0--功 1--守
	void unequip(int type, Item item[]);
	void onequip(Item item[], int index);

	//player对技能操作------------------------------------------
	//通用事件 添加hp,使用value1
	 void add_hp(Skill skill);
	 //移动
	 void walk(int i);
	
};


