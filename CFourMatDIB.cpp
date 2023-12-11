#include "stdafx.h"
#include "CFourMatDIB.h"

#define DIB_HEADER_MARKER ((WORD) ('M' << 8) | 'B')

CFourMatDIB::CFourMatDIB()
	: m_nWidth(0), m_nHeight(0), m_nBitCount(0), m_nDibSize(0), m_pDib(NULL)
{
}

CFourMatDIB::CFourMatDIB(const CFourMatDIB& dib) // 깊은 복사 생성자 
	: m_nWidth(dib.m_nWidth), m_nHeight(dib.m_nHeight), m_nBitCount(dib.m_nBitCount), m_nDibSize(dib.m_nDibSize), m_pDib(NULL)
{
	if (dib.m_pDib != NULL)
	{
		m_pDib = new BYTE[m_nDibSize];
		memcpy(m_pDib, dib.m_pDib, m_nDibSize);
	}
}

CFourMatDIB::CFourMatDIB(CFourMatDIB&& dib)  //sementic move 
	: m_nWidth(dib.m_nWidth), m_nHeight(dib.m_nHeight), m_nBitCount(dib.m_nBitCount), m_nDibSize(dib.m_nDibSize), m_pDib(dib.m_pDib)
{
	dib.m_pDib = nullptr;
}


CFourMatDIB::~CFourMatDIB()
{
	if (m_pDib)
		delete[] m_pDib;
}

BOOL CFourMatDIB::CreateGrayBitmap(LONG nWidth, LONG nHeight)
{
	if (m_pDib)
		DestroyBitmap();

	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nBitCount = 8;

	DWORD dwWidthStep = (m_nWidth * m_nBitCount / 8 + 3) & ~3;
	DWORD dwSizeImage = (m_nHeight * dwWidthStep);
	m_nDibSize = sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * GetPaletteNums()) + dwSizeImage;

	m_pDib = new BYTE[m_nDibSize];
	if (m_pDib == NULL)
		return FALSE;

	// BITMAPINFOHEADER 구조체 설정
	LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;
	lpbmi->biSize = sizeof(BITMAPINFOHEADER);
	lpbmi->biWidth = m_nWidth;
	lpbmi->biHeight = m_nHeight;
	lpbmi->biPlanes = 1;
	lpbmi->biBitCount = m_nBitCount;
	lpbmi->biCompression = BI_RGB;
	lpbmi->biSizeImage = dwSizeImage;
	lpbmi->biXPelsPerMeter = 0;
	lpbmi->biYPelsPerMeter = 0;
	lpbmi->biClrUsed = 0;
	lpbmi->biClrImportant = 0;

	// 그레이스케일 팔레트 설정
	RGBQUAD* pPal = (RGBQUAD*)((BYTE*)m_pDib + sizeof(BITMAPINFOHEADER));
	for (int i = 0; i < 256; i++)
	{
		pPal->rgbBlue = (BYTE)i;
		pPal->rgbGreen = (BYTE)i;
		pPal->rgbRed = (BYTE)i;
		pPal->rgbReserved = 0;
		pPal++;
	}

	// 픽셀 데이터 초기화
	BYTE* pData = GetDIBitsAddr();
	memset(pData, 0, dwSizeImage);

	return TRUE;
}

BOOL CFourMatDIB::CreateRgbBitmap(LONG nWidth, LONG nHeight)
{
	if (m_pDib)
		DestroyBitmap();

	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nBitCount = 24;

	DWORD dwWidthStep = (m_nWidth * m_nBitCount / 8 + 3) & ~3;
	DWORD dwSizeImage = (m_nHeight * dwWidthStep);
	m_nDibSize = sizeof(BITMAPINFOHEADER) + dwSizeImage;

	m_pDib = new BYTE[m_nDibSize];
	if (m_pDib == NULL)
		return FALSE;

	// BITMAPINFOHEADER 구조체 설정
	LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;
	lpbmi->biSize = sizeof(BITMAPINFOHEADER);
	lpbmi->biWidth = m_nWidth;
	lpbmi->biHeight = m_nHeight;
	lpbmi->biPlanes = 1;
	lpbmi->biBitCount = m_nBitCount;
	lpbmi->biCompression = BI_RGB;
	lpbmi->biSizeImage = dwSizeImage;
	lpbmi->biXPelsPerMeter = 0;
	lpbmi->biYPelsPerMeter = 0;
	lpbmi->biClrUsed = 0;
	lpbmi->biClrImportant = 0;

	// 픽셀 데이터 초기화
	BYTE* pData = GetDIBitsAddr();
	memset(pData, 0, dwSizeImage);

	return TRUE;
}

BOOL CFourMatDIB::CreateRgbBitmap(LONG nWidth, LONG nHeight, BYTE* pImageData)
{
	if (m_pDib)
		DestroyBitmap();

	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nBitCount = 24;

	DWORD dwWidthStep = (m_nWidth * m_nBitCount / 8 + 3) & ~3;
	DWORD dwSizeImage = (m_nHeight * dwWidthStep);
	m_nDibSize = sizeof(BITMAPINFOHEADER) + dwSizeImage;

	m_pDib = new BYTE[m_nDibSize];
	if (m_pDib == NULL)
		return FALSE;

	// BITMAPINFOHEADER 구조체 설정
	LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;
	lpbmi->biSize = sizeof(BITMAPINFOHEADER);
	lpbmi->biWidth = m_nWidth;
	lpbmi->biHeight = m_nHeight;
	lpbmi->biPlanes = 1;
	lpbmi->biBitCount = m_nBitCount;
	lpbmi->biCompression = BI_RGB;
	lpbmi->biSizeImage = dwSizeImage;
	lpbmi->biXPelsPerMeter = 0;
	lpbmi->biYPelsPerMeter = 0;
	lpbmi->biClrUsed = 0;
	lpbmi->biClrImportant = 0;

	// 픽셀 데이터 초기화
	BYTE* pData = GetDIBitsAddr();
	memcpy(pData, pImageData, dwSizeImage);

	return TRUE;
}


void CFourMatDIB::DestroyBitmap()
{
	if (m_pDib)
	{
		delete[] m_pDib;
		m_pDib = NULL;
	}

	m_nWidth = 0;
	m_nHeight = 0;
	m_nBitCount = 0;
	m_nDibSize = 0;
}

void CFourMatDIB::Draw(HDC hdc, int dx, int dy) //출력 위치 
{
	if (m_pDib == NULL)
		return;

	LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
	LPVOID lpBits = (LPVOID)GetDIBitsAddr();

	SetStretchBltMode(hdc, HALFTONE);

	::SetDIBitsToDevice(hdc,	// hdc
		dx,					// DestX
		dy,					// DestY
		m_nWidth,			// nSrcWidth
		m_nHeight,			// nSrcHeight
		0,					// SrcX
		0,					// SrcY
		0,					// nStartScan
		m_nHeight,			// nNumScans
		lpBits,				// lpBits
		lpbi,				// lpBitsInfo
		DIB_RGB_COLORS);	// wUsage
}

void CFourMatDIB::Draw(HDC hdc, int dx, int dy, int dw, int dh, DWORD dwRop) // 출력위치 시작 좌표, 폭 높이  
{
	Draw(hdc, dx, dy, dw, dh, 0, 0, m_nWidth, m_nHeight, dwRop);
}

void CFourMatDIB::Draw(HDC hdc, int dx, int dy, int dw, int dh,
	int sx, int sy, int sw, int sh, DWORD dwRop) // 찐 그려주는 애  
{
	if (m_pDib == NULL)
		return;

	LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
	LPSTR lpDIBBits = (LPSTR)GetDIBitsAddr();

	SetStretchBltMode(hdc, HALFTONE);
	::StretchDIBits(hdc,	// hdc
		dx,					// XDest
		dy,					// YDest
		dw,					// nDestWidth
		dh,					// nDestHeight
		sx,					// XSrc
		sy,					// YSrc
		sw,					// nSrcWidth
		sh,					// nSrcHeight
		lpDIBBits,			// lpBits
		lpbi,				// lpBitsInfo
		DIB_RGB_COLORS,		// wUsage
		SRCCOPY);			// dwROP
}

BOOL CFourMatDIB::CopyToClipboard()
{
	if (!::OpenClipboard(NULL))
		return FALSE;

	// DIB 전체를 전역 메모리 블럭에 복사
	DWORD dwDibSize = GetDibSize();
	HANDLE hDib = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, dwDibSize);
	if (hDib == NULL)
	{
		::CloseClipboard();
		return FALSE;
	}

	LPVOID lpDib = ::GlobalLock((HGLOBAL)hDib);
	memcpy(lpDib, GetBitmapInfoAddr(), dwDibSize);
	::GlobalUnlock(hDib);

	// 클립보드에 데이터 입력
	::EmptyClipboard();
	::SetClipboardData(CF_DIB, hDib);
	::CloseClipboard();

	return TRUE;
}

BOOL CFourMatDIB::PasteFromClipboard()
{
	// CF_DIB 타입이 아니면 종료한다.
	if (!::IsClipboardFormatAvailable(CF_DIB))
		return FALSE;

	// 클립 보드를 연다.
	if (!::OpenClipboard(NULL))
		return FALSE;

	// 클립 보드 내용을 받아온다.
	HANDLE hDib = ::GetClipboardData(CF_DIB);
	if (hDib == NULL)
	{
		::CloseClipboard();
		return FALSE;
	}

	// 메모리 블럭의 크기는 DIB 전체 크기와 동일
	DWORD dwSize = (DWORD)::GlobalSize((HGLOBAL)hDib);
	LPVOID lpDib = ::GlobalLock((HGLOBAL)hDib);

	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)lpDib;
	m_nWidth = lpbi->biWidth;
	m_nHeight = lpbi->biHeight;
	m_nBitCount = lpbi->biBitCount;

	DWORD dwWidthStep = (DWORD)((m_nWidth * m_nBitCount / 8 + 3) & ~3);
	DWORD dwSizeImage = m_nHeight * dwWidthStep;

	if (m_nBitCount == 24)
		m_nDibSize = sizeof(BITMAPINFOHEADER) + dwSizeImage;
	else
		m_nDibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << m_nBitCount) + dwSizeImage;

	// 현재 설정된 CFourMatDIB 객체가 있다면 삭제한다.
	if (m_pDib)
		DestroyBitmap();

	m_pDib = new BYTE[m_nDibSize];
	if (m_pDib == NULL)
	{
		::GlobalUnlock(hDib);
		::CloseClipboard();
		return FALSE;
	}

	memcpy(m_pDib, lpDib, m_nDibSize);

	::GlobalUnlock(hDib);
	::CloseClipboard();

	return TRUE;
}

CFourMatDIB& CFourMatDIB::operator=(const CFourMatDIB& dib)
{
	if (this == &dib)	// 재귀 검사
		return *this;

	if (m_pDib)
		delete[] m_pDib;

	m_nWidth = dib.m_nWidth;
	m_nHeight = dib.m_nHeight;
	m_nBitCount = dib.m_nBitCount;
	m_nDibSize = dib.m_nDibSize;
	m_pDib = NULL;

	if (dib.m_pDib != NULL)
	{
		m_pDib = new BYTE[m_nDibSize];
		memcpy(m_pDib, dib.m_pDib, m_nDibSize);
	}

	return *this;
}

BYTE* CFourMatDIB::GetDIBitsAddr() const
{
	if (m_pDib == NULL)
		return NULL;

	LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;
	return ((BYTE*)m_pDib + lpbmi->biSize + (sizeof(RGBQUAD) * GetPaletteNums()));
}

int CFourMatDIB::GetPaletteNums() const
{
	switch (m_nBitCount)
	{
	case 1:     return 2;
	case 4:     return 16;
	case 8:     return 256;
	default:    return 0;
	}
}
void CFourMatDIB::SetDIBits(BYTE* pDib) {

	DWORD dwWidthStep = (m_nWidth * m_nBitCount / 8 + 3) & ~3;
	DWORD dwSizeImage = (m_nHeight * dwWidthStep);
	BYTE* pData = GetDIBitsAddr();

	memcpy(pData, pDib, dwSizeImage);
}

void CFourMatDIB::Serialize(CArchive& ar)    // overridden for document i/o
{
	if (ar.IsStoring()) {
		ar << m_nWidth;      // 비트맵 가로 크기 (픽셀 단위)
		ar << m_nHeight;     // 비트맵 세로 크기 (픽셀 단위)
		ar << m_nBitCount;   // 픽셀 당 비트 수
		ar << m_nDibSize;    // DIB 전체 크기 (BITMAPINFOHEADER + 색상 테이블 + 픽셀 데이터)
		ar.Write(m_pDib, m_nDibSize);        // DIB 시작 주소 (BITMAPINFOHEADER 시작 주소)
	}
	else {
		ar >> m_nWidth;      // 비트맵 가로 크기 (픽셀 단위)
		ar >> m_nHeight;     // 비트맵 세로 크기 (픽셀 단위)
		ar >> m_nBitCount;   // 픽셀 당 비트 수
		ar >> m_nDibSize;    // DIB 전체 크기 (BITMAPINFOHEADER + 색상 테이블 + 픽셀 데이터)
		m_pDib = new BYTE[m_nDibSize];
		ar.Read(m_pDib, m_nDibSize);        // DIB 시작 주소 (BITMAPINFOHEADER 시작 주소)
	}
}
