#pragma once
class Enemy
{
public :
	//��������
	int fstatus = 0; //״̬0--׼��  1--���� 2--���� 3--����
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
	 //�������
	 int anm_nor=1;
	 int anm_att=2;
	 int anm_skill=2;
	 int anm_hurt =3;

	 //����
	 LPCWSTR itemname = L"��ҩˮ";
	 int item_id=1;

	 void set(int maxhp,int attack,int defense,int fspeed,int fortune,int many ,int anm_nor ,int anm_att,int anm_skill,int anm_hurt, LPCWSTR itemname,int item_id);
};