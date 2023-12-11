#pragma once
#include "stdafx.h"
#include <vector>
#include "AccessPixel.h"

class Point
{
public:
	int x;
	int y;

public:
	Point() : x(0), y(0) {}
	Point(int _x, int _y) : x(_x), y(_y) {}
};
class LabelInfo
{
public:
	std::vector<Point> pixels;
	int cx, cy;
	int minx, miny, maxx, maxy;

public:
	LabelInfo() : cx(0), cy(0), minx(9999), miny(9999), maxx(0), maxy(0)
	{
		pixels.clear();
	}
};
void EdgeCanny(ByteImage& imgSrc, ByteImage& imgEdge, float sigma, float th_low, float th_high);
void HarrisCorner(ByteImage& img, std::vector<Point>& corners, double th);

void MorphologyErosion(ByteImage& imgSrc, ByteImage& imgDst);
void MorphologyDilation(ByteImage& imgSrc, ByteImage& imgDst);
void MorphologyOpening(ByteImage& imgSrc, ByteImage& imgDst);
void MorphologyClosing(ByteImage& imgSrc, ByteImage& imgDst);

void MorphologyGrayErosion(ByteImage& imgSrc, ByteImage& imgDst);
void MorphologyGrayDilation(ByteImage& imgSrc, ByteImage& imgDst);
void MorphologyGrayOpening(ByteImage& imgSrc, ByteImage& imgDst);
void MorphologyGrayClosing(ByteImage& imgSrc, ByteImage& imgDst);