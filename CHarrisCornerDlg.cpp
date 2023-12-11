// CHarrisCornerDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CHarrisCornerDlg.h"
#include "afxdialogex.h"
#include "drawdoc.h"
#include "mainfrm.h"
#include "CFourMatDIB.h"
#include "CConvertDataType.h"
#include "CMorphology.h"
#include "drawvw.h"

// CHarrisCornerDlg 대화 상자

IMPLEMENT_DYNAMIC(CHarrisCornerDlg, CDialogEx)

CHarrisCornerDlg::CHarrisCornerDlg(CDrawDoc* pDrawDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FEATUREEXTRACTION_HARRIS_CORNER, pParent)
	, m_nHarrisTh(20000)
	, m_pDrawDoc(pDrawDoc)
	, m_dibRef(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
	, m_dib(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))

{

}

CHarrisCornerDlg::~CHarrisCornerDlg()
{
}

void CHarrisCornerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HARRIS_THRESHOLD, m_nHarrisTh);
}


BEGIN_MESSAGE_MAP(CHarrisCornerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PREVIEW, &CHarrisCornerDlg::OnBnClickedPreview)
END_MESSAGE_MAP()


// HarrisCornerDlg 메시지 처리기


void CHarrisCornerDlg::OnPaint()
{
	CPaintDC dc(this);
	m_dibRef.Draw(dc.m_hDC, 100, 300, 200, -200, 0, 0, m_dibRef.GetWidth(), m_dibRef.GetHeight(), SRCCOPY); // 바뀌기 전 
	m_dib.Draw(dc.m_hDC, 450, 300, 200, -200, 0, 0, m_dib.GetWidth(), m_dib.GetHeight(), SRCCOPY); // 바뀐 후 
}


void CHarrisCornerDlg::OnBnClickedPreview()
{
	ByteImage img;
	FourMatDIBToByteImage(m_dib, img);
	std::vector<Point> corners;
	
	if (UpdateData() == FALSE) {
		return;
	}
	
	HarrisCorner(img, corners, m_nHarrisTh);

	BYTE** ptr = img.GetPixels2D();
	int x, y;
	for (Point cp : corners)
	{
		x = cp.x;
		y = cp.y;
		ptr[y - 1][x - 1] = ptr[y - 1][x] = ptr[y - 1][x + 1] = 0;
		ptr[y][x - 1] = ptr[y][x] = ptr[y][x + 1] = 0;
		ptr[y + 1][x - 1] = ptr[y + 1][x] = ptr[y + 1][x + 1] = 0;
	}
	FourMatGrayToDIBImage(img, m_dib);

	Invalidate(true);

}
