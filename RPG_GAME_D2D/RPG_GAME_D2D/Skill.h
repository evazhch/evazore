#pragma once
#include "Animation.h"
class Skill
{
public :

	 int on_un = 0; //0--未学习 1--已学系
	 int mp = 10;  //消耗

	 LPCWSTR name =L""; //名称
	 LPCWSTR description = L""; //描述

	 int  anm_id; //图片
	 int type;//类型0--攻击 1--回复

	 //回复属性
	 int value1 = 0; //hp
	 int value2 = 0; //mp
	 int value3 = 0; //att
	 int value4 = 0; //def
	 int value5 = 0; //speed
	 int value6 = 0; //future
	//攻击属性
	 int fvalue = 0; //att
	 //int fvalue2 = 0; //
	 

	void show_describ(int x, int y, int w, int h);
	void show_name(int x, int y, int w, int h);
	void set(LPCWSTR name, LPCWSTR description, int mp,int type ,int anm_id ,int value1, int value2, int value3, int value4, int value5,int fvalue);
};