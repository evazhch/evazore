#include <windows.h>
#include <stdlib.h>
//#include <string.h>
#include <wincodec.h>
#include <D2D1.h>
#include<dwrite.h>
#include<iostream>
#include "Animation.h"
#include "Skill.h"
#include "Item.h"

void Item::set(int id, LPCWSTR name, LPCWSTR description, LPCWSTR bitmap_path,
	int num, int item_type, int isdepletion, int value1, int value2, int value3, int value4, int value5, int value6, int value7, int value8, int cost)
{
	this->id = id;
	this->name = name;
	this->description = description;
	this->bitmap_str = bitmap_path;
	this->num = num;
	this->item_type = item_type;

	this->isdepletion = isdepletion;
	this->value1 = value1;
	this->value2 = value2;
	this->value3 = value3;
	this->value4 = value4;
	this->value5 = value5;
	this->value6 = value6;
	this->value7 = value7;
	this->value8 = value8;
	this->cost = cost;
}
void Item::show_num(int x,int y,int w,int h)
{
	wchar_t str_1[10];
	_itow(
		num,
		str_1, 10);
	pRenderTarget->DrawText(
		str_1,           // Text to render
		wcslen(str_1),       // Text length
		g_pTextFormat,     // Text format
		D2D1::RectF(x,y,x+w,y+h),    // The region of the window where the text will be rendered
		pBlackBrush     // The brush used to draw the text
	);
}
void Item::show_name(int x, int y, int w, int h)
{
	if (name != NULL && num > 0)
	{
		pRenderTarget->DrawText(
			name,           // Text to render
			wcslen(name),       // Text length
			g_pTextFormat,     // Text format
			D2D1::RectF(x, y, x + w, y + h),    // The region of the window where the text will be rendered
			pBlueBrush      // The brush used to draw the text
		);
	}
}

void Skill::set(LPCWSTR name, LPCWSTR description, int mp, int type, int anm_id, int value1, int value2, int value3, int value4, int value5, int fvalue)
{
	this->name = name;
	this->description = description;

	this->mp = mp;
	this->type = type;
	this->anm_id = anm_id;

	this->value1 = value1;
	this->value2 = value2;
	this->value3 = value3;
	this->value4 = value4;
	this->value5 = value5;
	this->fvalue = fvalue;
}
void Item::show_description(int x, int y, int w, int h)
{
	if (description != NULL && num > 0)
	{
		pRenderTarget->DrawText(
			description,           // Text to render
			wcslen(description),       // Text length
			g_pTextFormat,     // Text format
			D2D1::RectF(x, y, x + w, y + h),    // The region of the window where the text will be rendered
			pBlueBrush      // The brush used to draw the text
		);
	}
}
void Skill::show_name(int x, int y, int w, int h)
{
	if (name != NULL && on_un == 1)
	{
		pRenderTarget->DrawText(
			name,           // Text to render
			wcslen(name),       // Text length
			g_pTextFormat,     // Text format
			D2D1::RectF(x,y,x+w,y+h),    // The region of the window where the text will be rendered
			pBlueBrush      // The brush used to draw the text
		);
	}
}
void Skill::show_describ(int x, int y, int w, int h)
{
	if (name != NULL && on_un == 1)
	{
		pRenderTarget->DrawText(
			description,           // Text to render
			wcslen(description),       // Text length
			g_pTextFormat,     // Text format
			D2D1::RectF(x, y, x + w, y + h),    // The region of the window where the text will be rendered
			pBlueBrush      // The brush used to draw the text
		);
	}
}
