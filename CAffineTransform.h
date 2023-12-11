#pragma once

#include "AccessPixel.h"

void Translate(ByteImage& imgSrc, ByteImage& imgDst, int sx, int sy);

void ResizeNearest(ByteImage& imgSrc, ByteImage& imgDst, int nw, int nh);
void ResizeBilinear(ByteImage& imgSrc, ByteImage& imgDst, int nw, int nh);
void ResizeCubic(ByteImage& imgSrc, ByteImage& imgDst, int nw, int nh);
double cubic_interpolation(double v1, double v2, double v3, double v4, double d);

void Rotate(ByteImage& imgSrc, ByteImage& imgDst, double angle);
void Rotate90(ByteImage& imgSrc, ByteImage& imgDst);
void Rotate180(ByteImage& imgSrc, ByteImage& imgDst);
void Rotate270(ByteImage& imgSrc, ByteImage& imgDst);

void Mirror(ByteImage& imgSrc, ByteImage& imgDst);
void Flip(ByteImage& imgSrc, ByteImage& imgDst);

