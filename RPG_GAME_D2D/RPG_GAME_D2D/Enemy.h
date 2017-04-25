#pragma once
class Enemy
{
public :
	//基本属性
	int fstatus = 0; //状态0--准备  1--攻击 2--技能 3--死亡
	LPCWSTR  name=NULL;
	LPCWSTR fbitmap_path=NULL;
	ID2D1Bitmap *fbitmap=NULL;

	 int maxhp = 100;
	 int hp = 80;
	 int attack = 10;
	 int defense = 10;
	 int fspeed = 80;
	 int fortune = 10;
	 int many=100;
	 //动画编号
	 int anm_nor=1;
	 int anm_att=2;
	 int anm_skill=2;
	 int anm_hurt =3;

	 //奖励
	 LPCWSTR itemname = L"红药水";
	 int item_id=1;

	 void set(int maxhp,int attack,int defense,int fspeed,int fortune,int many ,int anm_nor ,int anm_att,int anm_skill,int anm_hurt, LPCWSTR itemname,int item_id);
};