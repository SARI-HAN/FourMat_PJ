#pragma once

#include <windows.h>

class CFourMatDIB : public CObject 
{
public:
	// 생성자와 소멸자
	CFourMatDIB();
	CFourMatDIB(const CFourMatDIB& dib);
	CFourMatDIB(CFourMatDIB&& dib);
	~CFourMatDIB();

	// 비트맵 생성과 소멸
	BOOL CreateGrayBitmap(LONG nWidth, LONG nHeight);
	BOOL CreateRgbBitmap(LONG nWidth, LONG nHeight);
	BOOL CreateRgbBitmap(LONG nWidth, LONG nHeight, BYTE* pImageData);
	void DestroyBitmap();

	virtual void Serialize(CArchive& ar);   // overridden for document i/o

	
	// 비트맵 화면 출력
	void Draw(HDC hdc, int dx = 0, int dy = 0);
	void Draw(HDC hdc, int dx, int dy, int dw, int dh, DWORD dwRop = SRCCOPY);
	void Draw(HDC hdc, int dx, int dy, int dw, int dh, int sx, int sy, int sw,
		int sh, DWORD dwRop = SRCCOPY);

	// Windows 환경에서 클립보드로 복사하기 및 붙여넣기
	BOOL CopyToClipboard();
	BOOL PasteFromClipboard();

	// 대입 연산자 재정의
	CFourMatDIB& operator=(const CFourMatDIB& dib);

	// 비트맵 정보 반환
	LONG        GetWidth()    const { return m_nWidth; }
	LONG        GetHeight()	  const { return m_nHeight; }
	WORD        GetBitCount() const { return m_nBitCount; }
	DWORD       GetDibSize()  const { return m_nDibSize; }
	LPBITMAPINFO GetBitmapInfoAddr() const { return (LPBITMAPINFO)m_pDib; }
	BYTE*		GetDIBitsAddr() const;
	int         GetPaletteNums() const;
	BOOL        IsValid() const { return (m_pDib != NULL); }

	// 이미지 재설정
	void SetDIBits(BYTE* m_pDib);
	
private:
	LONG    m_nWidth;      // 비트맵 가로 크기 (픽셀 단위)
	LONG    m_nHeight;     // 비트맵 세로 크기 (픽셀 단위)
	WORD    m_nBitCount;   // 픽셀 당 비트 수
	DWORD   m_nDibSize;    // DIB 전체 크기 (BITMAPINFOHEADER + 색상 테이블 + 픽셀 데이터)
	BYTE* m_pDib;        // DIB 시작 주소 (BITMAPINFOHEADER 시작 주소)
};

