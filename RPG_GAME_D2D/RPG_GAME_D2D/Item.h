#pragma once
class Item
{
public:

	 //int  
	int id = -1; //物品的唯一编号
	 int num = 0;   //物品的数量
	 LPCWSTR name = L""; //名称
	 LPCWSTR description = L""; //描述
	 LPCWSTR bitmap_str = L"";
	 ID2D1Bitmap *bitmap=NULL; //图像
	 int isdepletion = 1;  //是否是消耗品1--消耗品 0--非消耗品
	 int item_type = -1;     //装备类型 -1物品 0--攻击性装备 1--防御品 2--特殊品
	
	//装备属性
	 int value1 = 0;        //攻击加成
	 int value2 = 0;        //防御加成
	 int value3 = 0;        //速度加成
	 int value4 = 0;        //运气加成
	//物品属性
	 int value5 = 0;         //加血hp效果
	 int value6 = 0;         //加mp效果
	 int value7 = 0;        //加maxhp
	 int value8 = 0;        //加maxmp

	 int cost = 100;             //价格
	 int sellcost = 100;   //出售价
	 
	
	//战斗中使用
	 int canfuse = 0;
	 int fvalue1 = 0;
	 int fvalue2 = 0;

	 void show_num(int x, int y, int w, int h);
	 void show_name(int x, int y, int w, int h);
	 void show_description(int x, int y, int w, int h);
	 void set(int id, LPCWSTR name, LPCWSTR description, LPCWSTR bitmap_path,
		 int num, int item_type, int isdepletion, int value1, int value2, int value3, int value4, int value5, int value6, int value7, int value8, int cost);
};
