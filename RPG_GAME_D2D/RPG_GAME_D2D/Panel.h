#pragma once
class Task;
class Fight;

class  Button
{

public:
	//����panel 0--��ʼ���� 1--״̬��� 2--�̵� 3--�Ի���� 4--�洢���� 5--�����ȡ���� 6--���ý���
	//int panel = 0;

	//type ����
	int isVist = 1; //0-���ɷ��� 1-�ɷ���
	int type = 0; //0--��ͨ��������꾭�������仯�� 1--�ѱ�ѡ��״̬��״̬���䣩
	//λ��
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	//ͼƬ
	LPCWSTR  b_nomal_path;
	LPCWSTR  b_select_path;
	LPCWSTR  b_press_path;
	ID2D1Bitmap *b_nomal;
	ID2D1Bitmap *b_select;
	ID2D1Bitmap *b_press;
	//״̬
	enum Status
	{
		NOMAL = 1,
		SELECT = 2,
		PRESS = 3
	};
	Status  status = NOMAL;
	//ѡ�е���Ʒ���ܱ��
	int item_num;
	int skill_num;

	void set(int x0, int y0, int w0, int h0, LPCWSTR nomal_path, LPCWSTR select_path, LPCWSTR press_path);
	//����
	void load();
	void unload();
	//��ͼ
	void draw(ID2D1RenderTarget *pRenderTarget);
	void draw(float a);
	bool is_collision(int collision_x, int collision_y);
};
class Panel
{
public:
	int x=0;
	int y=0;

	//�����İ������
	int button_num_end = 3;
	int button_num_start = 0;

	//����ͼ
	LPCWSTR bitmap_path;
	ID2D1Bitmap *bitmap;

	int current_button = 0;

	//����
	void set(int x0, int y0, LPCWSTR path,
		int num_start, int num_end);
	//����
	void init(ID2D1RenderTarget *pRenderTarget, Button button[]);
	void init(ID2D1RenderTarget *pRenderTarget, Button button[], int x, int y, int w, int h);
	void key_ctrl(HWND hwnd, WPARAM wParam, Button button[],Task task);
	void fight_key(HWND hwnd, WPARAM wParam, Button button[], Fight *fight,Player player[],Task task);
};
