#pragma once
#include "Animation.h"
class Skill
{
public :

	 int on_un = 0; //0--δѧϰ 1--��ѧϵ
	 int mp = 10;  //����

	 LPCWSTR name =L""; //����
	 LPCWSTR description = L""; //����

	 int  anm_id; //ͼƬ
	 int type;//����0--���� 1--�ظ�

	 //�ظ�����
	 int value1 = 0; //hp
	 int value2 = 0; //mp
	 int value3 = 0; //att
	 int value4 = 0; //def
	 int value5 = 0; //speed
	 int value6 = 0; //future
	//��������
	 int fvalue = 0; //att
	 //int fvalue2 = 0; //
	 

	void show_describ(int x, int y, int w, int h);
	void show_name(int x, int y, int w, int h);
	void set(LPCWSTR name, LPCWSTR description, int mp,int type ,int anm_id ,int value1, int value2, int value3, int value4, int value5,int fvalue);
};