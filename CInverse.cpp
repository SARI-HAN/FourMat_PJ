#include "stdafx.h"
#include "CInverse.h"

void CInverse(RgbImage& img)
{
	int size = img.GetSize();
	RGBBYTE* p = img.GetPixels();
	for (int i = 0; i < size; i++)
	{
		p[i].r = 255 - p[i].r;
		p[i].g = 255 - p[i].g;
		p[i].b = 255 - p[i].b;
	}
}