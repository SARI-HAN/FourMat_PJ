#pragma once
#include "AccessPixel.h"

void Inverse(ByteImage& img);
void Brightness(ByteImage& img, int n);
void Contrast(ByteImage& img, int n);
void GammaCorrection(ByteImage& img, float gamma);
void Histogram(ByteImage& img, float histo[256]);
void HistogramStretching(ByteImage& img);
void HistogramEqualization(ByteImage& img);

bool Add(ByteImage& img1, ByteImage& img2, ByteImage& img3);
bool Sub(ByteImage& img1, ByteImage& img2, ByteImage& img3);
bool Ave(ByteImage& img1, ByteImage& img2, ByteImage& img3);
bool Diff(ByteImage& img1, ByteImage& img2, ByteImage& img3);
bool AND(ByteImage& img1, ByteImage& img2, ByteImage& img3);
bool OR(ByteImage& img1, ByteImage& img2, ByteImage& img3);
void BitPlane(ByteImage& img1, ByteImage& img2, int bit);

