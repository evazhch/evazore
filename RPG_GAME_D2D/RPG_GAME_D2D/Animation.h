#pragma once
#include "head.h"

class Animation
{
public:
	//static Animation anm[];
	int target_x;
	int target_y;
	int x;
	int y;
	int w;
	int h;
	long time1;
	long time2;
	int next;
	int RACE=300; //播放速度ms
	int runType = 0; //0-循环播放，1-单次播放

	LPCWSTR gif_path = NULL;
	IWICBitmapDecoder *aDecoder = NULL; //资源
	ID2D1Bitmap *bitmap = NULL;
	int current_frame=0;
	UINT frame_num = 0;

	HRESULT loadGIF(ID2D1RenderTarget *pRenderTarget,
		IWICImagingFactory *pIWICFactory);
	
	HRESULT getFrame(int frame, IWICImagingFactory *pIWICFactory, ID2D1RenderTarget *pRenderTarget, UINT destinationWidth,
		UINT destinationHeight);

	void drawAnm(int x, int y, int w, int h);

	void setAnmPoint(int x, int y,int w,int h);
	int drawAnm();
	int drawAnmOne();
	int drawAnmSkill(Animation anm1, Animation anm2);
	void drawAnmLoop();
	void unload();
};