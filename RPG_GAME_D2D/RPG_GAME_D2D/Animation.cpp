#include "head.h"
#include "Animation.h"



void Animation::setAnmPoint(int x, int y,int w,int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}
HRESULT Animation::loadGIF(ID2D1RenderTarget *pRenderTarget,
	IWICImagingFactory *pIWICFactory)
{
	HRESULT hr = S_OK;
	if (aDecoder == NULL)
	{
		hr = pIWICFactory->CreateDecoderFromFilename(
			gif_path,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&aDecoder
		);
		if (SUCCEEDED(hr))
		{
			aDecoder->GetFrameCount(&frame_num);
		}
		return hr;
	}
}
void Animation::unload()
{
	SAFE_RELEASE(aDecoder);
	SAFE_RELEASE(bitmap);
}
HRESULT Animation::getFrame(int frame, IWICImagingFactory *pIWICFactory, ID2D1RenderTarget *pRenderTarget, UINT destinationWidth,
	UINT destinationHeight)
{
	HRESULT hr = S_OK;

	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

	if (aDecoder != NULL)
	{
		// Create the initial frame.
		hr = aDecoder->GetFrame(frame, &pSource);

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
				&bitmap
			);
		}

	}

	SAFE_RELEASE(pSource);
	SAFE_RELEASE(pStream);
	SAFE_RELEASE(pConverter);
	SAFE_RELEASE(pScaler);

	return hr;
}
void Animation::drawAnm(int x, int y,int w,int h)
{
	time2 = end;
	if (current_frame != -1)
	{
		if (aDecoder == NULL && gif_path != NULL)
		{
			loadGIF(pRenderTarget, pWICFactory);
		}
		SAFE_RELEASE(bitmap);

		getFrame(current_frame, pWICFactory, pRenderTarget, 0, 0);
		
		pRenderTarget->DrawBitmap(
			bitmap,
			D2D1::RectF(
				x,
				y,
				x +w*w_offset,
				y + h*h_offset
			),
			1.0f
		);
		if (time2 - time1 > RACE)
		{
			current_frame = current_frame + 1;
			if (current_frame >= frame_num)
			{
				current_frame = 0;
			}
			time1 = time2;
		}
	}
}
void Animation::drawAnmLoop()
{
	time2 = end;
	SAFE_RELEASE(aDecoder)
	if (current_frame != -1)
	{
		if (aDecoder == NULL && gif_path != NULL)
		{
			loadGIF(pRenderTarget, pWICFactory);
		}
		SAFE_RELEASE(bitmap);

		getFrame(current_frame, pWICFactory, pRenderTarget, 0, 0);
		pRenderTarget->DrawBitmap(
			bitmap,
			D2D1::RectF(
				x,
				y,
				x + w,
				y + h
			),
			1.0f
		);
		if (time2 - time1 > RACE)
		{
			current_frame = current_frame + 1;
			if (current_frame >= frame_num)
			{
				current_frame = 0;
			}
			time1 = time2;
		}
	}

}
int Animation::drawAnm()
{
	time2 = end;

	if (current_frame != -1)
	{
		if (aDecoder == NULL && gif_path != NULL)
		{
			loadGIF(pRenderTarget, pWICFactory);
		}
		SAFE_RELEASE(bitmap);

		getFrame(current_frame, pWICFactory, pRenderTarget, 0, 0);
		D2D_SIZE_F size = bitmap->GetSize();
		pRenderTarget->DrawBitmap(
			bitmap,
			D2D1::RectF(
				x,
				y,
				x + w*w_offset,
				y + h*h_offset
			),
			1.0f
		);
		if (time2 - time1 > RACE)
		{
			current_frame = current_frame + 1;
			if (current_frame >= frame_num)
			{
				current_frame = 0;
				return 1;
			}
			time1 = time2;
		}
		return 0;
	}

}
int Animation::drawAnmOne()
{
	time2 = end;

	if (current_frame != -1)
	{
		if (aDecoder == NULL && gif_path != NULL)
		{
			loadGIF(pRenderTarget, pWICFactory);
		}
		SAFE_RELEASE(bitmap);

		getFrame(current_frame, pWICFactory, pRenderTarget, 0, 0);
		D2D_SIZE_F size = bitmap->GetSize();
		pRenderTarget->DrawBitmap(
			bitmap,
			D2D1::RectF(
				x,
				y,
				x + w*w_offset,
				y + h*h_offset
			),
			1.0f
		);
		if (time2 - time1 > RACE)
		{
			current_frame = current_frame + 1;
			if (current_frame >= frame_num)
			{
				current_frame = frame_num-1;
				return 1;
			}
			time1 = time2;
		}
		return 0;
	}
}
int Animation::drawAnmSkill(Animation anm1,Animation anm2)
{
	if (anm1.drawAnmOne())
	{
		return anm2.drawAnmOne();
	}
	else
	{
		return 0;
	}
}
