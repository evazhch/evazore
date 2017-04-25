#pragma once
class Task;
class Fight;

class  Button
{

public:
	//所在panel 0--开始界面 1--状态面板 2--商店 3--对话面板 4--存储界面 5--保存读取界面 6--设置界面
	//int panel = 0;

	//type 类型
	int isVist = 1; //0-不可访问 1-可访问
	int type = 0; //0--普通（会因鼠标经过产生变化） 1--已被选中状态（状态不变）
	//位置
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	//图片
	LPCWSTR  b_nomal_path;
	LPCWSTR  b_select_path;
	LPCWSTR  b_press_path;
	ID2D1Bitmap *b_nomal;
	ID2D1Bitmap *b_select;
	ID2D1Bitmap *b_press;
	//状态
	enum Status
	{
		NOMAL = 1,
		SELECT = 2,
		PRESS = 3
	};
	Status  status = NOMAL;
	//选中的物品或技能编号
	int item_num;
	int skill_num;

	void set(int x0, int y0, int w0, int h0, LPCWSTR nomal_path, LPCWSTR select_path, LPCWSTR press_path);
	//加载
	void load();
	void unload();
	//绘图
	void draw(ID2D1RenderTarget *pRenderTarget);
	void draw(float a);
	bool is_collision(int collision_x, int collision_y);
};
class Panel
{
public:
	int x=0;
	int y=0;

	//包含的按键序号
	int button_num_end = 3;
	int button_num_start = 0;

	//背景图
	LPCWSTR bitmap_path;
	ID2D1Bitmap *bitmap;

	int current_button = 0;

	//设置
	void set(int x0, int y0, LPCWSTR path,
		int num_start, int num_end);
	//载入
	void init(ID2D1RenderTarget *pRenderTarget, Button button[]);
	void init(ID2D1RenderTarget *pRenderTarget, Button button[], int x, int y, int w, int h);
	void key_ctrl(HWND hwnd, WPARAM wParam, Button button[],Task task);
	void fight_key(HWND hwnd, WPARAM wParam, Button button[], Fight *fight,Player player[],Task task);
};
