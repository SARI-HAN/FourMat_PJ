#pragma once


#include "AccessPixel.h"

void FilterMean(ByteImage& imgSrc, ByteImage& imgDst);
void FilterWeightedMean(ByteImage& imgSrc, ByteImage& imgDst);
void FilterGaussian(ByteImage& imgSrc, FloatImage& imgDst, float sigma);

void FilterLaplacian(ByteImage& imgSrc, ByteImage& imgDst);
void FilterUnsharpMask(ByteImage& imgSrc, ByteImage& imgDst);
void FilterHighboost(ByteImage& imgSrc, ByteImage& imgDst, float alpha);

void NoiseGaussian(ByteImage& imgSrc, ByteImage& imgDst, int amount);
void NoiseSaltNPepper(ByteImage& imgSrc, ByteImage& imgDst, int amount);

void FilterMedian(ByteImage& imgSrc, ByteImage& imgDst);
void FilterDiffusion(ByteImage& imgSrc, FloatImage& imgDst, float lambda, float k, int iter);


