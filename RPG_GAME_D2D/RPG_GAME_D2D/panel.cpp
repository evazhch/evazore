#include "head.h"
#include "Panel.h"
#include "Fight.h"
#include "Task.h"

void Button::set(int x0, int y0, int w0, int h0, LPCWSTR nomal_path, LPCWSTR select_path, LPCWSTR press_path)
{
	x = x0;
	y = y0;
	b_nomal_path = nomal_path;
	b_select_path = select_path;
	b_press_path = press_path;
	w = w0;
	h = h0;
}
//加载
void Button::load()
{
	//加载
	if (b_nomal_path != NULL && b_nomal==NULL)
	{
		LoadBitmapFromFile(pRenderTarget, pWICFactory, b_nomal_path, 0, 0, &b_nomal);
	}
	if (b_select_path != NULL && b_select==NULL)
	{
		LoadBitmapFromFile(pRenderTarget, pWICFactory, b_select_path, 0, 0, &b_select);
	}
	if (b_press_path != NULL)
	{
		LoadBitmapFromFile(pRenderTarget, pWICFactory, b_press_path, 0, 0, &b_press);
	}
}
void Button::unload()
{
	//卸载
	SAFE_RELEASE(b_nomal);
	SAFE_RELEASE(b_select);
	SAFE_RELEASE(b_press);
}
//绘图
void Button::draw(ID2D1RenderTarget *pRenderTarget)
{
	load();
	if (isVist == 1)
	{
		if (status == NOMAL && b_nomal != NULL)
			pRenderTarget->DrawBitmap(
				b_nomal,
				D2D1::RectF(
					x,
					y,
					x + w,
					y + h),
				1.0f
			);
		if (status == SELECT && b_select != NULL)
			pRenderTarget->DrawBitmap(
				b_select,
				D2D1::RectF(
					x,
					y,
					x + w,
					y + h),
				1.0f
			);
		if (status == PRESS && b_press != NULL)
			pRenderTarget->DrawBitmap(
				b_press,
				D2D1::RectF(
					x,
					y,
					x + w,
					y + h),
				1.0f
			);
	}
	unload();
}
void Button::draw(float a)
{
	load();
	if (isVist == 1)
	{
		if (status == NOMAL && b_nomal != NULL)
			pRenderTarget->DrawBitmap(
				b_nomal,
				D2D1::RectF(
					x,
					y,
					x + w,
					y + h),
				a
			);
		if (status == SELECT && b_select != NULL)
			pRenderTarget->DrawBitmap(
				b_select,
				D2D1::RectF(
					x,
					y,
					x + w,
					y + h),
				a
			);
		if (status == PRESS && b_press != NULL)
			pRenderTarget->DrawBitmap(
				b_press,
				D2D1::RectF(
					x,
					y,
					x + w,
					y + h),
				a
			);
	}
	unload();
}
bool Button::is_collision(int collision_x, int collision_y)
{
	if (isVist == 1)
	{
		if (x < collision_x &&  collision_x < x + w && y < collision_y &&  collision_y < y + h)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

//设置
void Panel::set(int x0, int y0, LPCWSTR path,
	int num_start, int num_end)
{
	button_num_end = num_end;
	button_num_start = num_start;
	current_button = button_num_start;
	x = x0;
	y = y0;
	bitmap_path = path;
}
//载入
void Panel::init(ID2D1RenderTarget *pRenderTarget, Button button[])
{
	bitmap=nullptr;
	if (bitmap_path != NULL && bitmap==NULL)
	{
		LoadBitmapFromFile(pRenderTarget, pWICFactory, bitmap_path, 0, 0, &bitmap);
	}
	//背景图
	if (bitmap != NULL)
	{
		pRenderTarget->DrawBitmap(
			bitmap,
			D2D1::RectF(
				rc.left, rc.top, rc.right, rc.bottom
			),
			1.0f
		);
	}
	SAFE_RELEASE(bitmap);
	//按钮
	for (int i = button_num_start; i <= button_num_end; i++)
	{
		if (i == current_button)
		{
			button[i].status = button[i].SELECT;
		}
		if (button[i].b_nomal == nullptr)
		{
			button[i].load();
		}
		button[i].draw(pRenderTarget);
	}
}

void Panel::init(ID2D1RenderTarget *pRenderTarget, Button button[], int x, int y, int w, int h)
{
	bitmap = nullptr;
	if (bitmap_path != NULL && bitmap == NULL)
	{
		LoadBitmapFromFile(pRenderTarget, pWICFactory, bitmap_path, 0, 0, &bitmap);
	}
	//背景图
	if (bitmap != NULL)
	{
		pRenderTarget->DrawBitmap(
			bitmap,
			D2D1::RectF(
				x, y,x+ w, y+h
			),
			1.0f
		);
	}
	SAFE_RELEASE(bitmap);
	//按钮
	for (int i = button_num_start; i <= button_num_end; i++)
	{
		if (i == current_button)
		{
			button[i].status = button[i].SELECT;
		}
		else
		{
			button[i].status = button[i].NOMAL;
		}
		if (button[i].b_nomal == NULL)
		{
			button[i].load();
		}
		button[i].draw(pRenderTarget);
	}
}
void Panel::key_ctrl(HWND hwnd, WPARAM wParam, Button button[],Task task)
{
	switch (wParam)
	{
	case 0:
		GetCursorPos(&point);			// 获取鼠标指针位置（屏幕坐标）
		ScreenToClient(hwnd, &point);	// 将鼠标指针位置转换为窗口坐标
		for (int i = button_num_start; i <= button_num_end; i++)
		{
			if (button[i].is_collision(point.x, point.y))
			{
				button[current_button].status = button[current_button].NOMAL;
				current_button = i;
			}
		}
		break;
	case MK_LBUTTON:
		task.story_panel(current_panel, current_button, hwnd);
		break;
	case VK_SPACE:
		task.story_panel(current_panel, current_button, hwnd);
		break;
	case VK_UP:
		if (current_button < button_num_end)
		{
			button[current_button].status = button[current_button].NOMAL;
			current_button = current_button + 1;
			button[current_button].status = button[current_button].SELECT;
		}
		else
		{
			button[current_button].status = button[current_button].NOMAL;
			current_button = button_num_start;
			button[button_num_start].status = button[button_num_start].SELECT;
		}
		break;
	default:
		break;
	}
}
void Panel::fight_key(HWND hwnd, WPARAM wParam, Button button[],Fight *fight,Player player[], Task task)
{
	switch (wParam)
	{
	case 0:
		GetCursorPos(&point);			// 获取鼠标指针位置（屏幕坐标）
		ScreenToClient(hwnd, &point);	// 将鼠标指针位置转换为窗口坐标
		for (int i = button_num_start; i <= button_num_end; i++)
		{
			if (button[i].is_collision(point.x, point.y))
			{
				button[current_button].status = button[current_button].NOMAL;
				current_button = i;
				button[current_button].status = button[current_button].SELECT;
			}
		}
		break;
	case MK_LBUTTON:
		task.story_fight(current_panel, current_button,fight,player);
		break;
	case VK_SPACE:
		task.story_fight(current_panel, current_button,fight,player);
		break;
	case VK_UP:
		if (current_button < button_num_end)
		{
			button[current_button].status = button[current_button].NOMAL;
			current_button = current_button + 1;
			button[current_button].status = button[current_button].SELECT;
		}
		else
		{
			button[current_button].status = button[current_button].NOMAL;
			current_button = button_num_start;
			button[button_num_start].status = button[button_num_start].SELECT;
		}
		break;
	default:
		current_panel = 4;
		break;
	}
}