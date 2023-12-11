#include "stdafx.h"
#include "CConvertDataType.h"

void FourMatDIBToImage(CFourMatDIB& dib, ByteImage& img)
{
	assert(dib.IsValid());
	assert(dib.GetBitCount() == 8); // 8비트 받기 

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int ws = (w + 3) & ~3;
	BYTE* pDIBits = dib.GetDIBitsAddr();

	img.CreateImage(w, h);
	BYTE** pixels = img.GetPixels2D();

	for (int i = 0; i < h; i++)
	{
		memcpy(pixels[i], &pDIBits[(h - 1 - i) * ws], w); //h 행  w 열픽셀을 memcopy   
	}
}


void FourMatDIBToByteImage(const CFourMatDIB& dib, ByteImage& img)
{
	assert(dib.IsValid());
	assert(dib.GetBitCount() == 24); // 24bit받아서 

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int ws1 = (w + 3) & ~3;
	int ws2 = (w * 3 + 3) & ~3; // 보수 처리 하고 
	BYTE* pDIBits = dib.GetDIBitsAddr();

	img.CreateImage(w, h);
	BYTE** pixels = img.GetPixels2D(); // 2d 의 픽셀 접근 해서  

	for (int i = 0; i < h; i++)
	{
		for (int j=0;j<w;j++) {
			pixels[i][j] = byte(0.3 * pDIBits[(h - 1 - i) * ws2 + j * 3] +
				0.59 * pDIBits[(h - 1 - i) * ws2 + j * 3 + 1] +
				0.11 * pDIBits[(h - 1 - i) * ws2 + j * 3 + 2]);
		}//h 행  w 열픽셀을 memcopy   
	}
}



void FourMatGrayToDIBImage(const ByteImage& img, CFourMatDIB& dib)
{
	assert(dib.IsValid());
	assert(dib.GetBitCount() == 24); //24 비트 확인 

	int w = dib.GetWidth(); // w 
	int h = dib.GetHeight();// h 

	int ws = (w * 3 + 3) & ~3; // 이미지 보수 처리 4의 배수, 패딩 
	BYTE* pDIBits = dib.GetDIBitsAddr(); //dib 주소 값 
	BYTE** pixels = img.GetPixels2D(); //2d pixel data 구하기 

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++) {
			pDIBits[(h - 1 - i) * ws + j * 3 + 0] = pixels[i][j]; //R
			pDIBits[(h - 1 - i) * ws + j * 3 + 1] = pixels[i][j]; //G
			pDIBits[(h - 1 - i) * ws + j * 3 + 2] = pixels[i][j]; //B? 
		}
	}
}

void ByteImageToFourMatDIB(ByteImage& img, CFourMatDIB& dib)
{
	assert(img.IsValid());

	int w = img.GetWidth();
	int h = img.GetHeight();
	int ws = (w + 3) & ~3;
	BYTE** pixels = img.GetPixels2D();

	dib.CreateGrayBitmap(w, h);
	BYTE* pDIBits = dib.GetDIBitsAddr();

	for (int i = 0; i < h; i++)
	{
		memcpy(&pDIBits[(h - 1 - i) * ws], pixels[i], w);
	}
}

void FloatImageToFourMatDIB(FloatImage& img, CFourMatDIB& dib)
{
	assert(dib.IsValid());
	assert(dib.GetBitCount() == 24);

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int ws = (w * 3 + 3) & ~3; // 이미지 보수 처리 
	BYTE* pDIBits = dib.GetDIBitsAddr(); //dib 주소 값 
	float** pixels = img.GetPixels2D(); //2d pixel data 구하기 

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++) {
			pDIBits[(h - 1 - i) * ws + j * 3 + 0] = static_cast<BYTE>(limit(pixels[i][j] + 0.5f));
			pDIBits[(h - 1 - i) * ws + j * 3 + 1] = static_cast<BYTE>(limit(pixels[i][j] + 0.5f));
			pDIBits[(h - 1 - i) * ws + j * 3 + 2] = static_cast<BYTE>(limit(pixels[i][j] + 0.5f));
		}
	}
}
