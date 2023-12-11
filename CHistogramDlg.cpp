// CHistogramDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CHistogramDlg.h"
#include "afxdialogex.h"

#include "AccessPixel.h"
#include "CFourMatDIB.h"
#include "CConvertDataType.h"
#include "CImprovement.h"


// CHistogramDlg 대화 상자

IMPLEMENT_DYNAMIC(CHistogramDlg, CDialogEx)

CHistogramDlg::CHistogramDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HISTOGRAM, pParent)
{
	memset(m_Histogram, 0, sizeof(int) * 256);
}

CHistogramDlg::~CHistogramDlg()
{
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CHistogramDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CHistogramDlg 메시지 처리기
void CHistogramDlg::SetImage(CFourMatDIB& dib)
{
	if (dib.GetBitCount() == 24)
	{
		ByteImage img;
		FourMatDIBToByteImage(dib, img);
		// 정규화된 히스토그램을 구한다.
		float histo[256] = { 0.f, };
		Histogram(img, histo);
		// 정규화된 히스토그램에서 최댓값을 구한다.
		float max_histo = histo[0];
		for (int i = 1; i < 256; i++)
			if (histo[i] > max_histo) max_histo = histo[i];
		// m_Histogram 배열의 최댓값이 100이 되도록 전체 배열의 값을 조절한다.
		for (int i = 0; i < 256; i++)
		{
			m_Histogram[i] = static_cast<int>(histo[i] * 2000 / max_histo);
		}
	}
	else
	{
		memset(m_Histogram, 0, sizeof(int) * 256);
	}
}

void CHistogramDlg::OnPaint()
{

	CPaintDC dc(this); // device context for painting
	CGdiObject* pOldPen = dc.SelectStockObject(DC_PEN);
	// 히스토그램 박스
	dc.SetDCPenColor(RGB(128, 128, 128));
	dc.MoveTo(20, 20);
	dc.LineTo(20, 350);
	dc.LineTo(900, 350);
	dc.LineTo(900, 20);
	// 각 그레이스케일에 해당하는 히스토그램 출력
	dc.SetDCPenColor(RGB(0, 0, 0));
	for (int i = 0; i < 256; i++)
	{
		dc.MoveTo(20 + 2.5*i, 350);
		dc.LineTo(20 + 2.5*i, 350 - m_Histogram[i]);
	}
	// 그레이스케일 레벨 출력
	for (int i = 0; i < 256; i++)
	{
		dc.SetDCPenColor(RGB(i, i, i));
		dc.MoveTo(330 + i, 430);
		dc.LineTo(330 + i, 450);
	}
	dc.SelectObject(pOldPen);
}

