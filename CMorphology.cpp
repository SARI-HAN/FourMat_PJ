#include "stdafx.h"
#include "CMorphology.h"
#include "CImprovement.h"
#include "CFilter.h"
#include <map>

const double PI = 3.14159265358979323846;
const float  PI_F = 3.14159265358979323846f;

#define CHECK_WEAK_EDGE(x, y) \
	if (pEdge[y][x] == WEAK_EDGE) { \
		pEdge[y][x] = STRONG_EDGE; \
		strong_edges.push_back(Point(x, y)); \
	}
void EdgeCanny(ByteImage& imgSrc, ByteImage& imgEdge, float sigma, float th_low, float th_high)
{
	register int i, j;

	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	// 1. 가우시안 필터링

	FloatImage imgGaussian(w, h);
	FilterGaussian(imgSrc, imgGaussian, sigma);

	// 2. 그래디언트 구하기 (크기 & 방향)

	FloatImage imgGx(w, h); // gradient of x
	FloatImage imgGy(w, h); // gradient of y
	FloatImage imgMag(w, h); // magnitude of gradient

	float** pGauss = imgGaussian.GetPixels2D();
	float** pGx = imgGx.GetPixels2D();
	float** pGy = imgGy.GetPixels2D();
	float** pMag = imgMag.GetPixels2D();

	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			pGx[j][i] = -pGauss[j - 1][i - 1] - 2 * pGauss[j][i - 1] - pGauss[j + 1][i - 1]
				+ pGauss[j - 1][i + 1] + 2 * pGauss[j][i + 1] + pGauss[j + 1][i + 1];
			pGy[j][i] = -pGauss[j - 1][i - 1] - 2 * pGauss[j - 1][i] - pGauss[j - 1][i + 1]
				+ pGauss[j + 1][i - 1] + 2 * pGauss[j + 1][i] + pGauss[j + 1][i + 1];

			pMag[j][i] = sqrt(pGx[j][i] * pGx[j][i] + pGy[j][i] * pGy[j][i]);
		}

	// 3. 비최대 억제
	// 국지적 최대를 구함과 동시에 이중 임계값을 적용하여 strong edge와 weak edge를 구한다.

	imgEdge.CreateImage(w, h);
	BYTE** pEdge = imgEdge.GetPixels2D();

	enum DISTRICT { AREA0 = 0, AREA45, AREA90, AREA135, NOAREA };

	const BYTE STRONG_EDGE = 255;
	const BYTE WEAK_EDGE = 128;

	std::vector<Point> strong_edges;

	float ang;
	int district;
	bool local_max;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			// 그래디언트 크기가 th_low보다 큰 픽셀에 대해서만 국지적 최대 검사.
			// 국지적 최대인 픽셀에 대해서만 강한 엣지 또는 약한 엣지로 설정.
			if (pMag[j][i] > th_low)
			{
				// 그래디언트 방향 계산 (4개 구역)
				if (pGx[j][i] != 0.f)
				{
					ang = atan2(pGy[j][i], pGx[j][i]) * 180 / PI_F;
					if (((ang >= -22.5f) && (ang < 22.5f)) || (ang >= 157.5f) || (ang < -157.5f))
						district = AREA0;
					else if (((ang >= 22.5f) && (ang < 67.5f)) || ((ang >= -157.5f) && (ang < -112.5f)))
						district = AREA45;
					else if (((ang >= 67.5) && (ang < 112.5)) || ((ang >= -112.5) && (ang < -67.5)))
						district = AREA90;
					else
						district = AREA135;
				}
				else
					district = AREA90;

				// 국지적 최대 검사
				local_max = false;
				switch (district)
				{
				case AREA0:
					if ((pMag[j][i] >= pMag[j][i - 1]) && (pMag[j][i] > pMag[j][i + 1]))
						local_max = true;
					break;
				case AREA45:
					if ((pMag[j][i] >= pMag[j - 1][i - 1]) && (pMag[j][i] > pMag[j + 1][i + 1]))
						local_max = true;
					break;
				case AREA90:
					if ((pMag[j][i] >= pMag[j - 1][i]) && (pMag[j][i] > pMag[j + 1][i]))
						local_max = true;
					break;
				case AREA135:
				default:
					if ((pMag[j][i] >= pMag[j - 1][i + 1]) && (pMag[j][i] > pMag[j + 1][i - 1]))
						local_max = true;
					break;
				}

				// 강한 엣지와 약한 엣지 구분.
				if (local_max)
				{
					if (pMag[j][i] > th_high)
					{
						pEdge[j][i] = STRONG_EDGE;
						strong_edges.push_back(Point(i, j));
					}
					else
						pEdge[j][i] = WEAK_EDGE;
				}
			}
		}

	// 4. 히스테리시스 엣지 트래킹

	while (!strong_edges.empty())
	{
		Point p = strong_edges.back();
		strong_edges.pop_back();

		int x = p.x, y = p.y;

		// 강한 엣지 주변의 약한 엣지는 최종 엣지(강한 엣지)로 설정
		CHECK_WEAK_EDGE(x + 1, y)
			CHECK_WEAK_EDGE(x + 1, y + 1)
			CHECK_WEAK_EDGE(x, y + 1)
			CHECK_WEAK_EDGE(x - 1, y + 1)
			CHECK_WEAK_EDGE(x - 1, y)
			CHECK_WEAK_EDGE(x - 1, y - 1)
			CHECK_WEAK_EDGE(x, y - 1)
			CHECK_WEAK_EDGE(x + 1, y - 1)
	}

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			// 끝까지 약한 엣지로 남아있는 픽셀은 모두 엣지가 아닌 것으로 판단.
			if (pEdge[j][i] == WEAK_EDGE) pEdge[j][i] = 0;
		}
}

void HarrisCorner(ByteImage& img, std::vector<Point>& corners, double th)
{
	register int i, j, x, y;

	int w = img.GetWidth();
	int h = img.GetHeight();

	BYTE** ptr = img.GetPixels2D();

	// 1. (fx)*(fx), (fx)*(fy), (fy)*(fy) 계산

	FloatImage imgDx2(w, h);
	FloatImage imgDy2(w, h);
	FloatImage imgDxy(w, h);

	float** dx2 = imgDx2.GetPixels2D();
	float** dy2 = imgDy2.GetPixels2D();
	float** dxy = imgDxy.GetPixels2D();

	float tx, ty;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			tx = (ptr[j - 1][i + 1] + ptr[j][i + 1] + ptr[j + 1][i + 1]
				- ptr[j - 1][i - 1] - ptr[j][i - 1] - ptr[j + 1][i - 1]) / 6.f;
			ty = (ptr[j + 1][i - 1] + ptr[j + 1][i] + ptr[j + 1][i + 1]
				- ptr[j - 1][i - 1] - ptr[j - 1][i] - ptr[j - 1][i + 1]) / 6.f;

			dx2[j][i] = tx * tx;
			dy2[j][i] = ty * ty;
			dxy[j][i] = tx * ty;
		}

	// 2. 가우시안 필터링

	FloatImage imgGdx2(w, h);
	FloatImage imgGdy2(w, h);
	FloatImage imgGdxy(w, h);

	float** gdx2 = imgGdx2.GetPixels2D();
	float** gdy2 = imgGdy2.GetPixels2D();
	float** gdxy = imgGdxy.GetPixels2D();

	float g[5][5] = { { 1, 4, 6, 4, 1 },{ 4, 16, 24, 16, 4 },
		{ 6, 24, 36, 24, 6 },{ 4, 16, 24, 16, 4 },{ 1, 4, 6, 4, 1 } };

	for (y = 0; y < 5; y++)
		for (x = 0; x < 5; x++)
		{
			g[y][x] /= 256.f;
		}

	float tx2, ty2, txy;
	for (j = 2; j < h - 2; j++)
		for (i = 2; i < w - 2; i++)
		{
			tx2 = ty2 = txy = 0;
			for (y = 0; y < 5; y++)
				for (x = 0; x < 5; x++)
				{
					tx2 += (dx2[j + y - 2][i + x - 2] * g[y][x]);
					ty2 += (dy2[j + y - 2][i + x - 2] * g[y][x]);
					txy += (dxy[j + y - 2][i + x - 2] * g[y][x]);
				}

			gdx2[j][i] = tx2;
			gdy2[j][i] = ty2;
			gdxy[j][i] = txy;
		}

	// 3. 코너 응답 함수 생성

	FloatImage imgCrf(w, h);
	float** crf = imgCrf.GetPixels2D();

	float k = 0.04f;
	for (j = 2; j < h - 2; j++)
		for (i = 2; i < w - 2; i++)
		{
			crf[j][i] = (gdx2[j][i] * gdy2[j][i] - gdxy[j][i] * gdxy[j][i])
				- k * (gdx2[j][i] + gdy2[j][i]) * (gdx2[j][i] + gdy2[j][i]);
		}

	// 4. 임계값보다 큰 국지적 최대값을 찾아 코너 포인트로 결정

	corners.clear();
	float cvf_value;
	for (j = 2; j < h - 2; j++)
		for (i = 2; i < w - 2; i++)
		{
			cvf_value = crf[j][i];
			if (cvf_value > th)
			{
				if (cvf_value > crf[j - 1][i] && cvf_value > crf[j - 1][i + 1] &&
					cvf_value > crf[j][i + 1] && cvf_value > crf[j + 1][i + 1] &&
					cvf_value > crf[j + 1][i] && cvf_value > crf[j + 1][i - 1] &&
					cvf_value > crf[j][i - 1] && cvf_value > crf[j - 1][i - 1])
				{
					corners.push_back(Point(i, j));
				}
			}
		}
}
void MorphologyErosion(ByteImage& imgSrc, ByteImage& imgDst)
{
	int i, j;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pDst = imgDst.GetPixels2D();
	BYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			if (pSrc[j][i] != 0)
			{
				if (pSrc[j - 1][i] == 0 || pSrc[j - 1][i + 1] == 0 ||
					pSrc[j][i - 1] == 0 || pSrc[j][i + 1] == 0 ||
					pSrc[j + 1][i - 1] == 0 || pSrc[j + 1][i] == 0 ||
					pSrc[j + 1][i + 1] == 0 || pSrc[j - 1][i - 1] == 0)
				{
					pDst[j][i] = 0;
				}
			}
		}
}

void MorphologyDilation(ByteImage& imgSrc, ByteImage& imgDst)
{
	int i, j;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pDst = imgDst.GetPixels2D();
	BYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			if (pSrc[j][i] == 0)
			{
				if (pSrc[j - 1][i] != 0 || pSrc[j - 1][i + 1] != 0 ||
					pSrc[j][i - 1] != 0 || pSrc[j][i + 1] != 0 ||
					pSrc[j + 1][i - 1] != 0 || pSrc[j + 1][i] != 0 ||
					pSrc[j + 1][i + 1] != 0 || pSrc[j - 1][i - 1] != 0)
				{
					pDst[j][i] = 255;
				}
			}
		}
}

void MorphologyOpening(ByteImage& imgSrc, ByteImage& imgDst)
{
	ByteImage imgTmp;
	MorphologyErosion(imgSrc, imgTmp);
	MorphologyDilation(imgTmp, imgDst);
}

void MorphologyClosing(ByteImage& imgSrc, ByteImage& imgDst)
{
	ByteImage imgTmp;
	MorphologyDilation(imgSrc, imgTmp);
	MorphologyErosion(imgTmp, imgDst);
}

void MorphologyGrayErosion(ByteImage& imgSrc, ByteImage& imgDst)
{
	int i, j, m, n, x, y, pmin;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pDst = imgDst.GetPixels2D();
	BYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			pmin = 255;

			for (n = -1; n <= 1; n++)
				for (m = -1; m <= 1; m++)
				{
					x = i + m;
					y = j + n;

					if (x >= 0 && x < w && y >= 0 && y < h)
					{
						if (pSrc[y][x] < pmin)
							pmin = pSrc[y][x];
					}
				}

			pDst[j][i] = static_cast<BYTE>(pmin);
		}
}

void MorphologyGrayDilation(ByteImage& imgSrc, ByteImage& imgDst)
{
	int i, j, m, n, x, y, pmax;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pDst = imgDst.GetPixels2D();
	BYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			pmax = 0;

			for (n = -1; n <= 1; n++)
				for (m = -1; m <= 1; m++)
				{
					x = i + m;
					y = j + n;

					if (x >= 0 && x < w && y >= 0 && y < h)
					{
						if (pSrc[y][x] > pmax)
							pmax = pSrc[y][x];
					}
				}

			pDst[j][i] = static_cast<BYTE>(pmax);
		}
}

void MorphologyGrayOpening(ByteImage& imgSrc, ByteImage& imgDst)
{
	ByteImage imgTmp;
	MorphologyGrayErosion(imgSrc, imgTmp);
	MorphologyGrayDilation(imgTmp, imgDst);
}

void MorphologyGrayClosing(ByteImage& imgSrc, ByteImage& imgDst)
{
	ByteImage imgTmp;
	MorphologyGrayDilation(imgSrc, imgTmp);
	MorphologyGrayErosion(imgTmp, imgDst);
}

