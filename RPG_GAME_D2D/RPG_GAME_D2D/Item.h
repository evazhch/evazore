#pragma once
class Item
{
public:

	 //int  
	int id = -1; //��Ʒ��Ψһ���
	 int num = 0;   //��Ʒ������
	 LPCWSTR name = L""; //����
	 LPCWSTR description = L""; //����
	 LPCWSTR bitmap_str = L"";
	 ID2D1Bitmap *bitmap=NULL; //ͼ��
	 int isdepletion = 1;  //�Ƿ�������Ʒ1--����Ʒ 0--������Ʒ
	 int item_type = -1;     //װ������ -1��Ʒ 0--������װ�� 1--����Ʒ 2--����Ʒ
	
	//װ������
	 int value1 = 0;        //�����ӳ�
	 int value2 = 0;        //�����ӳ�
	 int value3 = 0;        //�ٶȼӳ�
	 int value4 = 0;        //�����ӳ�
	//��Ʒ����
	 int value5 = 0;         //��ѪhpЧ��
	 int value6 = 0;         //��mpЧ��
	 int value7 = 0;        //��maxhp
	 int value8 = 0;        //��maxmp

	 int cost = 100;             //�۸�
	 int sellcost = 100;   //���ۼ�
	 
	
	//ս����ʹ��
	 int canfuse = 0;
	 int fvalue1 = 0;
	 int fvalue2 = 0;

	 void show_num(int x, int y, int w, int h);
	 void show_name(int x, int y, int w, int h);
	 void show_description(int x, int y, int w, int h);
	 void set(int id, LPCWSTR name, LPCWSTR description, LPCWSTR bitmap_path,
		 int num, int item_type, int isdepletion, int value1, int value2, int value3, int value4, int value5, int value6, int value7, int value8, int cost);
};
