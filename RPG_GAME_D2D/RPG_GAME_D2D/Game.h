#pragma once

Task task;
Player player[3];       //主角队伍
Map map[11];            //地图

Teleporter teleporter[25];  //传送点
Npc npc[21];           //剧情NPC
FightNpc fightNpc[31]; //战斗传送点

Panel panel_start;    //开始面板
Panel panel_end;     //结束确认面板
Panel panel_talk;     //对话面板
Button button_start[4];   //开始面板按钮
Button button_end[2];    //结束面板按钮
Button button_save;       //保存面板
StatusMenu statusMenu; //状态面板

Item item_player[100];     //角色背包里的物品

Item item[100];               //所有物品Animation npcAnm[20];

Animation playerAnm[100];  //角色动画
Animation npcAnm[20];
Animation enemyAnm[100]; //敌人动画
Enemy  enemy[100];
Fight fight;
Save save[5];


VOID CreateResource(HWND hWnd)
{
	HRESULT hr;
	//创建工厂
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "Create D2D factory failed!", "Error", 0);
		return;
	}

	// Obtain the size of the drawing area
	RECT rc;
	GetClientRect(hWnd, &rc);

	// Create a Direct2D render target
	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
		),
		&pRenderTarget
	);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "Create render target failed!", "Error", 0);
		return;
	}
	// Create a brush
	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black),
		&pBlackBrush
	);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "Create brush failed!", "Error", 0);
		return;
	}
	pBlackBrush->SetOpacity(0.3f);
	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red),
		&pRedBrush
	);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "Create brush1 failed!", "Error", 0);
		return;
	}

	pBlackBrush->SetOpacity(0.3f);
	hr = pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue),
		&pBlueBrush
	);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "Create brush1 failed!", "Error", 0);
		return;
	}



	// Create DirectWrite Factory
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&g_pDWriteFactory)
	);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Create DirectWrite factory failed!", "Error", 0);
		return;
	}


	hr = g_pDWriteFactory->CreateTextFormat(
		L"微软雅黑",                   // Font family name
		NULL,                          // Font collection(NULL sets it to the system font collection)
		DWRITE_FONT_WEIGHT_BLACK,    // Weight
		DWRITE_FONT_STYLE_OBLIQUE,      // Style
		DWRITE_FONT_STRETCH_NORMAL,    // Stretch
		20.0f,                         // Size    
		L"en-us",                      // Local
		&g_pTextFormat                 // Pointer to recieve the created object
	);

	hr = g_pDWriteFactory->CreateTextFormat(
		L"微软雅黑",                   // Font family name
		NULL,                          // Font collection(NULL sets it to the system font collection)
		DWRITE_FONT_WEIGHT_MEDIUM,    // Weight
		DWRITE_FONT_STYLE_OBLIQUE,      // Style
		DWRITE_FONT_STRETCH_NORMAL,    // Stretch
		10.0f,                         // Size    
		L"en-us",                      // Local
		&g_pTextFormat1                // Pointer to recieve the created object
	);

	if (FAILED(hr))
	{
		MessageBox(NULL, "Create IDWriteTextFormat failed!", "Error", 0);
		return;
	}

	//creat bitmap from file
	// Create WIC factory
	hr = CoCreateInstance(
		CLSID_WICImagingFactory1,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		reinterpret_cast<void **>(&pWICFactory)
	);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "Create render target failed!", "Error", 0);
		return;
	}
}



HRESULT LoadBitmapFromFile(
	ID2D1RenderTarget *pRenderTarget,
	IWICImagingFactory *pIWICFactory,
	PCWSTR uri,
	UINT destinationWidth,
	UINT destinationHeight,
	ID2D1Bitmap **ppBitmap
)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

	hr = pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr))
	{

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SAFE_RELEASE(pDecoder);
	SAFE_RELEASE(pSource);
	SAFE_RELEASE(pStream);
	SAFE_RELEASE(pConverter);
	SAFE_RELEASE(pScaler);

	return hr;
}

void drawtext(wchar_t *str, ID2D1SolidColorBrush *brush, int x, int y, int w, int h)
{
	g_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pRenderTarget->DrawText(
		str,
		wcslen(str),
		g_pTextFormat,
		D2D1::RectF(x, y, x + w, y + h),
		brush
	);
}
void drawnum(int num, ID2D1SolidColorBrush *brush, int x, int y, int w, int h)
{
	wchar_t str[10];
	_itow(num, str, 10);
	g_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pRenderTarget->DrawText(
		str,
		wcslen(str),
		g_pTextFormat,
		D2D1::RectF(x, y, x + w, y + h),
		brush
	);
}

VOID Begindraw()
{
	pRenderTarget->BeginDraw();
}
VOID Enddraw()
{
	HRESULT hr = pRenderTarget->EndDraw();
	if (FAILED(hr))
	{
		MessageBox(NULL, "Draw failed!", "Error", 0);

		return;
	}
}
VOID Cleanup()
{
	SAFE_RELEASE(pBlackBrush); 
	SAFE_RELEASE(pBlueBrush);
	SAFE_RELEASE(pRedBrush);
	SAFE_RELEASE(g_pDWriteFactory);
	SAFE_RELEASE(g_pTextFormat);
	SAFE_RELEASE(pWICFactory);
	SAFE_RELEASE(pRenderTarget);
	SAFE_RELEASE(pD2DFactory);
}
void loadenemy()
{
	//set(int maxhp, int attack, int defense, int fspeed, int fortune, int many, int anm_nor, int anm_att, int anm_skill, int anm_hurt, LPCWSTR itemname, int item_id);

	enemy[1].set(100, 10, 10, 10, 10, 10, 1, 2, 3, 4, L"老头", 1);
	enemy[2].set(100, 10, 10, 10, 10, 10, 1, 2, 3, 4, L"老头", 1);
	/*enemy[2].set();
	enemy[3].set();
	enemy[4].set();
	enemy[5].set();
	enemy[6].set();
	enemy[7].set();
	enemy[8].set();
	enemy[9].set();*/
}
void loadFightNpc()
{
	
	//1
	fightNpc[0].set(2, 130, 330, 1, 2, 3);
	fightNpc[1].set(2, 330, 330, 1, 2, 3);
	//2
	fightNpc[2].set(3, 750, 1000, 1, 2, 3);
	fightNpc[3].set(3, 510, 930, 1, 2, 3);
	fightNpc[4].set(3, 170, 1050, 1, 2, 3);
	fightNpc[5].set(3, 550, 240, 1, 2, 3);
	fightNpc[6].set(3, 770, 270, 1, 2, 3);
	fightNpc[7].set(3, 470, 1080, 1, 2, 3);
	//3
	fightNpc[8].set(4, 130, 430, 1, 2, 3);
	fightNpc[9].set(4, 330, 430, 1, 2, 3);
	fightNpc[10].set(4, 130, 430, 1, 2, 3);
	fightNpc[11].set(4, 330, 430, 1, 2, 3);
	fightNpc[12].set(4, 130, 430, 1, 2, 3);
	fightNpc[13].set(4, 330, 430, 1, 2, 3);
	//4
	fightNpc[14].set(5, 130, 430, 1, 2, 3);
	fightNpc[15].set(5, 330, 430, 1, 2, 3);
	fightNpc[16].set(5, 130, 430, 1, 2, 3);
	fightNpc[17].set(5, 330, 430, 1, 2, 3);
	fightNpc[18].set(5, 130, 430, 1, 2, 3);
	fightNpc[19].set(5, 330, 430, 1, 2, 3);
	//ye
	fightNpc[20].set(1, 130, 430, 1, 2, 3);
	fightNpc[21].set(1, 330, 430, 1, 2, 3);
	fightNpc[22].set(1, 130, 430, 1, 2, 3);

}

void loadNpc()
{
	//mark---------
	LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/mark1.png", 0, 0, &npc[0].bitmap);
	npc[0].npc_type = 0;
	npc[0].map = 0;
	npc[0].x_map = -1;
	npc[0].y_map = -1;


	//--------------------------------------NPC-------------------------------------------------------------------
	//地图对话npc
	//set(int map, int x_map, int y_map, LPCWSTR bitmap_path, bool visible, int story_num, int collision, int is_anm, int anm_num)
	
	//city
	npc[1].set(0, 520, 1100, L"source/npc/change.png", 1, 1, 0, 0, 0); //空白--开始对话

	npc[2].set(0, 540, 620, L"source/npc/npc1.png", 1, 1, 2, 1, 14); //游人
	npc[2].set(1, 1, 0, 540, 1200, -1, -1, 14, -1);
	npc[2].currnt_anmtp = 1;

	npc[3].set(0, 40, 700, L"source/npc/npc1.png", 1, 1, 1, 1, 7); //赌钱输光
    
	npc[4].set(0, 730, 610, L"source/npc/npc1.png", 1, 1, 1, 1, 1); //狗
	npc[4].set(1, 2, 0, 730, 550, 730, 700, 2, 1);

	npc[5].set(0, 500, 650, L"source/npc/npc1.png", 1, 1, 1, 1, 3); //猫
	npc[5].set(1, 2, 0, 400, 330, 400, 700, 4, 3);
	
	npc[6].set(0, 190, 630, L"source/npc/npc1.png", 1, 1, 1, 1, 5); //老头看药
    
	npc[7].set(0, 50, 666, L"source/npc/npc1.png", 1, 1, 1, 1, 6); //瞎趟的小孩
	npc[7].set(1, 2, 0, 200, 666, 750, 666, 6, 7);

	npc[8].set(0, 620, 750, L"source/npc/npc1.png", 1, 1, 1, 1, 8); //站着的老头

	npc[9].set(0, 150, 700, L"source/npc/npc1.png", 1, 1, 1, 1, 9); //图操大叔
	npc[9].set(1, 2, 0, 200, 700, 750, 700, 9, 10);
	npc[10].set(0, 400, 750, L"source/npc/npc1.png", 1, 1, 1, 1, 11); //小孩看衣服
	
	npc[20].set(-1, 0, 0, NULL, 1, 1, 1);
	npc[20].set(1, 0, 0, 0, 0, 0, 0, 0, 0);
	npc[20].npc_type = 1;
	npc[20].anm_num = 20;
	npc[20].x = rc.right - 30;
	npc[20].y = 0;
	npc[20].x_offset = 30;
	npc[20].y_offset = 30;

}
void loadPlayer()
{
	//player
	LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/player/player1.png", 0, 0, &player[0].bitmap);
	player[0].is_active = 1;
	player[0].face = 4;
	player[0].x_map = 580;
	player[0].y_map = 1160;

	LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/player/player2.png", 0, 0, &player[1].bitmap);
	player[1].is_active = 1;
	LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/player/player3.png", 0, 0, &player[2].bitmap);
	player[2].is_active = -1;

}
void loadMap()
{
	//城镇
	map[0].setMap(0, 0, L"source/map/city.bmp", L"source/map/city_shade.png", L"source/map/city_block.bmp");
	//野外
	map[1].setMap(0, 0, L"source/map/map1.png", L"source/map/shade1.png", L"source/map/block1.png");
	//路线1
	map[2].setMap(0, 0, L"source/map/1.bmp", L"source/map/s1.png", L"source/map/b1.bmp");
	//路线2
	map[3].setMap(0, 0, L"source/map/2.bmp", L"source/map/s2.png", L"source/map/b2.bmp");
	//路线3
	map[4].setMap(0, 0, L"source/map/3.bmp", L"source/map/s3.png", L"source/map/b3.bmp");
	//路线4
	map[5].setMap(0, 0, L"source/map/4.bmp", L"source/map/s4.png", L"source/map/b4.bmp");
	//路线5
	map[6].setMap(0, 0, L"source/map/5.bmp", L"source/map/s5.png", L"source/map/b5.bmp");
	//路线6
	map[7].setMap(0, 0, L"source/map/6.bmp", L"source/map/s6.png", L"source/map/b6.bmp");
	//药店
	map[8].setMap(0, 0, L"source/shop/shop_y.bmp", NULL, L"source/shop/shop_y_block.bmp");
	//兵器店
	map[9].setMap(0, 0, L"source/shop/shop_w.bmp", NULL, L"source/shop/shop_w_block.bmp");
	//旅店
	map[10].setMap(0, 0, L"source/shop/shop_l.bmp",NULL, L"source/shop/shop_l_b.bmp");

}
void loadTeleporter()
{
	//city
	//第一地图切换点--野外
	teleporter[1].Npc::set(0, -30, 300, L"source/panel/change3.png", 1, 0, 0, 1, 0);
	teleporter[1].set(2, 1, 100, 400, 3);
	//第二地图切换点--野外
	teleporter[2].Npc::set(0, 300, 100, L"source/panel/change3.png", 1, 1, 0, 1, 0);
	teleporter[2].set(2, 1, 1200, 400, 2);
	//第三地图切换点--上山
	teleporter[3].Npc::set(0, 410, -40, L"source/panel/change1.png", 1, 1, 0, 1, 0);
	teleporter[3].set(4, 2, 300, 450, 4);
	//第四地图切换点--药店
	teleporter[4].Npc::set(0, 240, 480, L"source/panel/change1.png", 1, 1, 0, 0, 0);
	teleporter[4].set(4, 8, 230, 340, 4);
	//第五地图切换点--旅店
	teleporter[5].Npc::set(0, 600, 510, L"source/panel/change1.png", 1, 1, 0, 0, 0);
	teleporter[5].set(4, 10, 250, 380, 4);
	//第六地图切换点--武器店
	teleporter[6].Npc::set(0, 850, 560, L"source/panel/change4.png", 1, 1, 0, 0, 0);
	teleporter[6].set(3, 9, 260, 350, 4);
	//野外
	//回城1
	teleporter[7].Npc::set(1, 0, 372, L"source/panel/change2.png", 1, 1, 0, 1, 0);
	teleporter[7].set(1, 0, 40, 380, 3);
	//回城2
	teleporter[8].Npc::set(1, 1200, 300, L"source/panel/change3.png", 1, 1, 0, 1, 0);
	teleporter[8].set(3, 0, 400, 200, 3);
	//路线一
	//1->city
	teleporter[9].Npc::set(2, 270, 450, L"source/panel/change2.png", 1, 1, 0, 1, 0);
	teleporter[9].set(1, 0, 450, 150, 1);
	//1->2
	teleporter[10].Npc::set(2, 150, 200, L"source/panel/change1.png", 1, 1, 0, 1, 0);
	teleporter[10].set(4, 3, 780, 1250, 4);
	//路线2
	//2-1
	teleporter[11].Npc::set(3, 780, 1200, L"source/panel/change2.png", 1, 1, 0, 1, 0);
	teleporter[11].set(1, 2, 170, 300, 1);
	//2-3-1
	teleporter[12].Npc::set(3, 880, 850, L"source/panel/change4.png", 1, 1, 0, 1, 0);
	teleporter[12].set(3, 4, 80, 880, 3);
	//2-3-2
	teleporter[13].Npc::set(3, 850, 300, L"source/panel/change4.png", 1, 1, 0, 1, 0);
	teleporter[13].set(3, 4, 0, 340, 3);
	//路线3
	//3-2-1
	teleporter[14].Npc::set(4, 0, 850, L"source/panel/change3.png", 1, 1, 0, 1, 0);
	teleporter[14].set(2, 3, 880, 900, 3);
	//3-2-2
	teleporter[15].Npc::set(4, 0, 300, L"source/panel/change3.png", 1, 1, 0, 1, 0);
	teleporter[15].set(2, 3, 850, 340, 2);
	//3-4
	teleporter[16].Npc::set(4, 710, 0, L"source/panel/change1.png", 1, 1, 0, 1, 0);
	teleporter[16].set(4, 5, 30, 640, 4);
	//路线4
	//4-3
	teleporter[17].Npc::set(5, 0, 600, L"source/panel/change2.png", 1, 1, 0, 1, 0);
	teleporter[17].set(1, 4, 10, 730, 1);
	//4-5
	teleporter[18].Npc::set(5, 1600, 0, L"source/panel/change1.png", 1, 1, 0, 1, 0);
	teleporter[18].set(4, 6, 230, 440, 4);
	//路线5
	//5-4
	teleporter[19].Npc::set(6, 210, 400, L"source/panel/change2.png", 1, 1, 0, 1, 0);
	teleporter[19].set(1, 5, 720, 10, 1);
	//5-6
	teleporter[20].Npc::set(6, 310, 140, L"source/panel/change1.png", 1, 1, 0, 1, 0);
	teleporter[20].set(2, 7, 800, 430, 2);
	//y->c
	teleporter[21].Npc::set(8, 150, 300, L"source/panel/change2.png", 1, 1, 0, 0, 0);
	teleporter[21].set(1, 0, 280, 600, 1);
	//l->c
	teleporter[22].Npc::set(10, 200, 340, L"source/panel/change2.png", 1, 1, 0, 0, 0);
	teleporter[22].set(1, 0, 650, 620, 1);
	//w->c
	teleporter[23].Npc::set(9, 200, 300, L"source/panel/change3.png", 1, 1, 0, 0, 0);
	teleporter[23].set(2, 0, 800, 700, 2);
}

void loadPlayerGif()
{
	//player1
	playerAnm[1].gif_path = L"source/anm/playerAnm/1_1.Gif"; //准备
	playerAnm[2].gif_path = L"source/anm/playerAnm/1_2.gif";//受伤
	playerAnm[3].gif_path = L"source/anm/playerAnm/1_3.gif";//虚弱
	playerAnm[4].gif_path = L"source/anm/playerAnm/1_4.gif";//死亡
	playerAnm[5].gif_path = L"source/anm/playerAnm/1_5.gif";//防御
	playerAnm[6].gif_path = L"source/anm/playerAnm/1_6.gif";//普击
	playerAnm[7].gif_path = L"source/anm/playerAnm/1_7.gif";//物品使用
	playerAnm[8].gif_path = L"source/anm/playerAnm/1_8.gif";//物品/技能承受
	playerAnm[9].gif_path = L"source/anm/playerAnm/1_9.gif"; //技能1
	playerAnm[10].gif_path = L"source/anm/playerAnm/1_10.gif"; //技能2
	playerAnm[11].gif_path = L"source/anm/playerAnm/1_11.gif"; //技能3
	playerAnm[12].gif_path = L"source/anm/playerAnm/1_12.gif"; //技能4
	playerAnm[13].gif_path = L"source/anm/playerAnm/1_13.gif"; //技能5
															   //player2
	playerAnm[14].gif_path = L"source/anm/playerAnm/1_1.Gif"; //准备
	playerAnm[15].gif_path = L"source/anm/playerAnm/1_2.gif";//受伤
	playerAnm[16].gif_path = L"source/anm/playerAnm/1_3.gif";//虚弱
	playerAnm[17].gif_path = L"source/anm/playerAnm/1_4.gif";//死亡
	playerAnm[18].gif_path = L"source/anm/playerAnm/1_5.gif";//防御
	playerAnm[19].gif_path = L"source/anm/playerAnm/1_6.gif";//普击
	playerAnm[20].gif_path = L"source/anm/playerAnm/1_7.gif";//物品使用
	playerAnm[21].gif_path = L"source/anm/playerAnm/1_8.gif";//物品/技能承受
	playerAnm[22].gif_path = L"source/anm/playerAnm/1_9.gif"; //技能1
	playerAnm[23].gif_path = L"source/anm/playerAnm/1_10.gif"; //技能2
	playerAnm[24].gif_path = L"source/anm/playerAnm/1_11.gif"; //技能3
	playerAnm[25].gif_path = L"source/anm/playerAnm/1_12.gif"; //技能4
	playerAnm[26].gif_path = L"source/anm/playerAnm/1_13.gif"; //技能5
															   //player3
	playerAnm[27].gif_path = L"source/anm/playerAnm/1_1.Gif"; //准备
	playerAnm[28].gif_path = L"source/anm/playerAnm/1_2.gif";//受伤
	playerAnm[29].gif_path = L"source/anm/playerAnm/1_3.gif";//虚弱
	playerAnm[30].gif_path = L"source/anm/playerAnm/1_4.gif";//死亡
	playerAnm[31].gif_path = L"source/anm/playerAnm/1_5.gif";//防御
	playerAnm[32].gif_path = L"source/anm/playerAnm/1_6.gif";//普击
	playerAnm[33].gif_path = L"source/anm/playerAnm/1_7.gif";//物品使用
	playerAnm[34].gif_path = L"source/anm/playerAnm/1_8.gif";//物品/技能承受
	playerAnm[35].gif_path = L"source/anm/playerAnm/1_9.gif"; //技能1
	playerAnm[36].gif_path = L"source/anm/playerAnm/1_10.gif"; //技能2
	playerAnm[37].gif_path = L"source/anm/playerAnm/1_11.gif"; //技能3
	playerAnm[38].gif_path = L"source/anm/playerAnm/1_12.gif"; //技能4
	playerAnm[39].gif_path = L"source/anm/playerAnm/1_13.gif"; //技能5
}
void loadGif()
{
	loadPlayerGif();
	//enemy

	//e1
	enemyAnm[1].gif_path = L"source/anm/enemyAnm/1.gif"; //普通
	enemyAnm[2].gif_path = L"source/anm/enemyAnm/1_2.gif"; //攻击
	enemyAnm[3].gif_path = L"source/anm/enemyAnm/1_2.gif"; //技能
	enemyAnm[4].gif_path = L"source/anm/enemyAnm/1_3.gif"; //被击中
	
	//e2
	enemyAnm[5].gif_path = L"source/anm/enemyAnm/2_1.gif"; //普通
	enemyAnm[6].gif_path = L"source/anm/enemyAnm/2_2.gif"; //攻击
	enemyAnm[7].gif_path = L"source/anm/enemyAnm/2_2.gif"; //技能
	enemyAnm[8].gif_path = L"source/anm/enemyAnm/2_3.gif"; //被击中
	
	//e3
	enemyAnm[9].gif_path = L"source/anm/enemyAnm/3_1.gif"; //普通
	enemyAnm[10].gif_path = L"source/anm/enemyAnm/3_2.gif"; //攻击
	enemyAnm[11].gif_path = L"source/anm/enemyAnm/3_2.gif"; //技能
	enemyAnm[12].gif_path = L"source/anm/enemyAnm/3_3.gif"; //被击
	
	//e4
	enemyAnm[13].gif_path = L"source/anm/enemyAnm/4_1.gif"; //普通
	enemyAnm[14].gif_path = L"source/anm/enemyAnm/4_2.gif"; //攻击
	enemyAnm[15].gif_path = L"source/anm/enemyAnm/4_2.gif"; //技能
	enemyAnm[16].gif_path = L"source/anm/enemyAnm/4_3.gif"; //被击
	//e5
	enemyAnm[17].gif_path = L"source/anm/enemyAnm/5_1.gif"; //普通
	enemyAnm[18].gif_path = L"source/anm/enemyAnm/5_2.gif"; //攻击
	enemyAnm[19].gif_path = L"source/anm/enemyAnm/5_2.gif"; //技能
	enemyAnm[20].gif_path = L"source/anm/enemyAnm/5_3.gif"; //被击
	//e6
	enemyAnm[21].gif_path = L"source/anm/enemyAnm/6_1.gif"; //普通
	enemyAnm[22].gif_path = L"source/anm/enemyAnm/6_2.gif"; //攻击
	enemyAnm[23].gif_path = L"source/anm/enemyAnm/6_2.gif"; //技能
	enemyAnm[24].gif_path = L"source/anm/enemyAnm/6_3.gif"; //被击
	//e7
	enemyAnm[25].gif_path = L"source/anm/enemyAnm/7_1.gif"; //普通
	enemyAnm[26].gif_path = L"source/anm/enemyAnm/7_2.gif"; //攻击
	enemyAnm[27].gif_path = L"source/anm/enemyAnm/7_2.gif"; //技能
	enemyAnm[28].gif_path = L"source/anm/enemyAnm/7_3.gif"; //被击
	//e8
	enemyAnm[29].gif_path = L"source/anm/enemyAnm/8_1.gif"; //普通
	enemyAnm[30].gif_path = L"source/anm/enemyAnm/8_2.gif"; //攻击
	enemyAnm[31].gif_path = L"source/anm/enemyAnm/8_2.gif"; //技能
	enemyAnm[32].gif_path = L"source/anm/enemyAnm/8_3.gif"; //被击
	//e9
	enemyAnm[33].gif_path = L"source/anm/enemyAnm/9_1.gif"; //普通
	enemyAnm[34].gif_path = L"source/anm/enemyAnm/9_2.gif"; //攻击
	enemyAnm[35].gif_path = L"source/anm/enemyAnm/9_2.gif"; //技能
	enemyAnm[36].gif_path = L"source/anm/enemyAnm/9_3.gif"; //被击

	//npc
	//切换点
	npcAnm[0].gif_path = L"source/npc/tele.gif";
	npcAnm[1].gif_path = L"source/anm/npcAnm/dog1.gif";
	npcAnm[2].gif_path = L"source/anm/npcAnm/dog4.gif";
	npcAnm[3].gif_path = L"source/anm/npcAnm/cat1.gif";
	npcAnm[4].gif_path = L"source/anm/npcAnm/cat4.gif";
	npcAnm[5].gif_path = L"source/anm/npcAnm/6.gif";
	npcAnm[6].gif_path = L"source/anm/npcAnm/1.gif";
	npcAnm[7].gif_path = L"source/anm/npcAnm/1_2.gif";
	npcAnm[8].gif_path = L"source/anm/npcAnm/16.gif";

	npcAnm[9].gif_path = L"source/anm/npcAnm/18.gif";
	npcAnm[10].gif_path = L"source/anm/npcAnm/18_2.gif";
	
	npcAnm[11].gif_path = L"source/anm/npcAnm/23.gif";
	npcAnm[12].gif_path = L"source/anm/npcAnm/13.gif";
	npcAnm[13].gif_path = L"source/anm/npcAnm/14.gif";
	npcAnm[14].gif_path = L"source/anm/npcAnm/15.gif";
	npcAnm[15].gif_path = L"source/anm/npcAnm/16.gif";
	npcAnm[16].gif_path = L"source/anm/npcAnm/17.gif";
	npcAnm[17].gif_path = L"source/anm/npcAnm/17.gif";
	npcAnm[18].gif_path = L"source/anm/npcAnm/19.gif";
	npcAnm[19].gif_path = L"source/anm/npcAnm/20.gif";
	npcAnm[20].gif_path = L"source/anm/npcAnm/status.gif";

}

void loadPanel()
{
	//开始面板
	panel_start.set(0, 0, L"source/start/start_panel.bmp", 0, 3);
	button_start[0].set(rc.right / 5, rc.bottom / 3 * 2, 50, 50, L"source/start/start_1.png", L"source/start/start.png", L"");
	button_start[1].set(rc.right / 5 * 2, rc.bottom / 3 * 2, 50, 50, L"source/start/continu_1.png", L"source/start/continu.png", L"");
	button_start[2].set(rc.right / 5 * 3, rc.bottom / 3 * 2, 50, 50, L"source/start/set_1.png", L"source/start/set.png", L"");
	button_start[3].set(rc.right / 5 * 4, rc.bottom / 3 * 2, 50, 50, L"source/start/end_1.png", L"source/start/end.png", L"");

	//结束面板
	panel_end.set(0, 0, L"source/start/start_panel.png", 0, 1);
	button_end[0].set(rc.right/3, rc.bottom/3*2, rc.right / 10, rc.right / 10, L"source/start/continu_1.png", L"source/start/continu.png", L"");
	button_end[1].set(rc.right/3*2, rc.bottom/3*2, rc.right / 10, rc.right / 10, L"source/start/end_1.png", L"source/start/end.png",L"");

	//状态面板------------------------------------------------------------------
	LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/status/0.png", 0, 0, &statusMenu.backgrand);
	LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/status/1.bmp", 0, 0, &statusMenu.backgrand1);
	LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/status/2.bmp", 0, 0, &statusMenu.backgrand2);
	LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/status/5.bmp", 0, 0, &statusMenu.backgrand3);
	LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/status/que.bmp", 0, 0, &statusMenu.button_que);

	statusMenu.playerstatus_str[0] = L"source/status/playerstatus1.png";
	statusMenu.playerstatus_str[1] = L"source/status/playerstatus2.png";
	statusMenu.playerstatus_str[2] = L"source/status/playerstatus3.png";
}
void loadTalkback()
{
	LoadBitmapFromFile(pRenderTarget, pWICFactory, L"source/panel/tip.png", 0, 0, &panel_talk.bitmap);
}

void loadItem()
{
	//物品------------------------------------------------------------------------
	/*void set      (Item *item, int id, LPCWSTR name, LPCWSTR description, LPCWSTR bitmap_path,
	int num, int equip_type, int isdepletion, int value1, int value2, int value3, int value4, int value5, int value6, int cost)*/

	item[0].set(1, L"红药水", L"回复100hp", L"source/item/item1.png", 0, -1, 1, 0, 0, 0, 0, 100, 0, 0, 0, 0);
	item[1].set(2, L"橙药水", L"回复100mp", L"source/item/item2.png", 0, -1, 1, 0, 0, 0, 0, 0, 10, 0, 0, 0);
	item[2].set(3, L"黄药水", L"回复少量hp/mp", L"source/item/item1.png", 0, -1, 1, 0, 0, 0, 0, 10, 10, 0, 0, 0);
	item[3].set(4, L"绿药水", L"攻击力增加1", L"source/item/item2.png", 0, -1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0);
	item[4].set(5, L"青药水", L"防御力加1", L"source/item/item1.png", 0, -1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0);
	item[5].set(6, L"蓝药水", L"速度加1", L"source/item/item1.png", 0, -1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0);
	item[6].set(7, L"紫药水", L"运气加1", L"source/item/item1.png", 0, -1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0);

	item[7].set(8, L"木剑", L"攻击装备", L"source/item/item1.png", 0, 0, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0);
	item[8].set(9, L"布衣", L"防御装备", L"source/item/item1.png", 0, 1, 1, 0, 10, 0, 0, 0, 0, 0, 0, 0);

	item_player[0].set(1, L"红药水", L"回复100hp", L"source/item/item1.png", 1, -1, 1, 0, 0, 0, 0, 100, 0, 0, 0, 0);
	item_player[1].set(2, L"橙药水", L"回复100mp", L"source/item/item2.png", 1, -1, 1, 0, 0, 0, 0, 0, 10, 0, 0, 0);
	item_player[2].set(3, L"黄药水", L"回复少量hp/mp", L"source/item/item1.png", 1, -1, 1, 0, 0, 0, 0, 10, 10, 0, 0, 0);
	item_player[3].set(4, L"绿药水", L"攻击力增加1", L"source/item/item2.png", 1, -1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0);
	item_player[4].set(5, L"青药水", L"防御力加1", L"source/item/item1.png", 1, -1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0);
	item_player[5].set(6, L"蓝药水", L"速度加1", L"source/item/item1.png", 1, -1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0);
	item_player[6].set(7, L"紫药水", L"运气加1", L"source/item/item1.png", 1, -1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0);

	item_player[7].set(8, L"木剑", L"攻击装备", L"source/item/item1.png", 1, 0, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0);
	item_player[8].set(9, L"布衣", L"防御装备", L"source/item/item1.png", 1, 1, 1, 0, 10, 0, 0, 0, 0, 0, 0, 0);
	player_item_num = 9;
}
void loadSkill()
{
	//player[0].skill[0].set();
	//player[0].skill[1].set();
	//player[0].skill[2].set();
	//player[0].skill[3].set();
	//player[0].skill[4].set();

	//player[1].skill[0].set();
	//player[1].skill[1].set();
	//player[1].skill[2].set();
	//player[1].skill[3].set();
	//player[1].skill[4].set();

	//player[0].skill[0].set();
	//player[0].skill[1].set();
	//player[0].skill[2].set();
	//player[0].skill[3].set();
	//player[0].skill[4].set();
}

VOID Form_Load() //游戏初始化
{
	save[0].filename = "save/0.txt";
	save[1].filename = "save/1.txt";
	save[2].filename = "save/2.txt";
	save[3].filename = "save/3.txt";
	save[4].filename = "save/4.txt";
	status = 0;
	current_panel = 0;
	current_map = 0;
	//地图系统
	//-------------------fightanm------------------------------------
	loadGif();
	//-------------------panel----------------------------------------
	loadPanel();
	loadTalkback();
	//-------------------map-----------------------------------------
	loadMap();
	//------------------teleporter------------------------------------
	loadTeleporter();
	//------------------npc------------------------------------------
	loadNpc();
	loadFightNpc();
	//-------------------player---------------------------------------
	loadPlayer();
    //------------------ Item-----------------------------------------
	loadItem();
	//技能------------------------------------------------------------------------
	
}

long time() //取时间间隔
{
	long time_space;
	time_space = GetTickCount();
	return  time_space;
}
void pain_panel()
{
	switch (current_panel)
	{
	case 0:
		Begindraw();
		panel_start.init(pRenderTarget, button_start);
		Enddraw();
		break;
	case 1:
		Begindraw();
		save[0].showRead(player, map, save);
		Enddraw();
		break;
	case 2:
		Begindraw();
		save[0].showSave(player,item_player,map,save);
		Enddraw();
		break;
	case 3:
		Begindraw();
		panel_end.init(pRenderTarget, button_end);
		Enddraw();
		break;
	default:
		current_panel = 0;
		break;
	}
}
void pain_talk()
{
	//对话框
	if (talk_type != 0)
	{
		pRenderTarget->DrawBitmap(
			panel_talk.bitmap,
			D2D1::RectF(0, rc.bottom/5*4, rc.right, rc.bottom),
			0.3f
		);
		//draw name

		if (talk_type == 1)
		{
			drawtext(talk, pRedBrush, 20, rc.bottom / 5*4+20, rc.right, rc.bottom / 5);
		}
		else
		{
			drawtext(talk, pBlueBrush, 20, rc.bottom / 5 * 4+20, rc.right, rc.bottom / 5);
		}
	}
}
void panel_ctl(HWND hwnd,WPARAM wParam)
{
	switch (current_panel)
	{
	case 0:
		panel_start.key_ctrl(hwnd, wParam, button_start, task);
		break;
	case 1:
		save[0].key_ctrl(hwnd, wParam, player, item_player, item, save);
		break;
	case 2:
		save[0].key_ctrl(hwnd, wParam, player, item_player, item, save);
		break;
	case 3:
		panel_end.key_ctrl(hwnd, wParam, button_end, task);
		break;
	case 4:
		break;
	default:
		break;
	}
}
