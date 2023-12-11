#pragma once
#include "AccessPixel.h"
#include "CFourMatDIB.h"

void FourMatDIBToImage(CFourMatDIB& dib, ByteImage& img);
void FourMatDIBToByteImage(const CFourMatDIB& dib, ByteImage& img);
void FourMatGrayToDIBImage(const ByteImage& img, CFourMatDIB& dib);

void ByteImageToFourMatDIB(ByteImage& img, CFourMatDIB& dib);
void FloatImageToFourMatDIB(FloatImage& img, CFourMatDIB& dib);


