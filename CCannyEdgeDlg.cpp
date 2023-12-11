// CCannyEdgeDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CCannyEdgeDlg.h"
#include "afxdialogex.h"
#include "drawdoc.h"
#include "mainfrm.h"
#include "CFourMatDIB.h"
#include "CConvertDataType.h"
#include "CMorphology.h"
#include "drawvw.h"


// CCannyEdgeDlg 대화 상자

IMPLEMENT_DYNAMIC(CCannyEdgeDlg, CDialogEx)

CCannyEdgeDlg::CCannyEdgeDlg(CDrawDoc* pDrawDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FEATUREEXTRACTION_CANNY_EDGE, pParent)
	, m_fSigma(1.4f)
	, m_fLowTh(30.f)
	, m_fHighTh(60.f)
	, m_pDrawDoc(pDrawDoc)
	, m_dibRef(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
	, m_dib(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
{

}

CCannyEdgeDlg::~CCannyEdgeDlg()
{
}

void CCannyEdgeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CANNY_SIGMA, m_fSigma);
	DDX_Text(pDX, IDC_LOW_THRESHOLD, m_fLowTh);
	DDX_Text(pDX, IDC_HIGH_THRESHOLD, m_fHighTh);
}


BEGIN_MESSAGE_MAP(CCannyEdgeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PREVIEW, &CCannyEdgeDlg::OnBnClickedPreview)
END_MESSAGE_MAP()


// CCannyEdgeDlg 메시지 처리기


void CCannyEdgeDlg::OnPaint()
{
	CPaintDC dc(this); 

	m_dibRef.Draw(dc.m_hDC, 100, 300, 200, -200, 0, 0, m_dibRef.GetWidth(), m_dibRef.GetHeight(), SRCCOPY); // 바뀌기 전 
	m_dib.Draw(dc.m_hDC, 450, 300, 200, -200, 0, 0, m_dib.GetWidth(), m_dib.GetHeight(), SRCCOPY); // 바뀐 후 


}


void CCannyEdgeDlg::OnBnClickedPreview()
{
	ByteImage img;
	ByteImage imgEdge;

	if (UpdateData() == FALSE) {
		return;
	}

	FourMatDIBToByteImage(m_dib, img);
	EdgeCanny(img, imgEdge, m_fSigma, m_fLowTh, m_fHighTh);
	FourMatGrayToDIBImage(imgEdge, m_dib);

	Invalidate(true);
}
