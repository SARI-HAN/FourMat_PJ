// CBlurDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CBlurDlg.h"
#include "afxdialogex.h"
#include "drawdoc.h"
#include "mainfrm.h"
#include "CFourMatDIB.h"
#include "CConvertDataType.h"
#include "CFilter.h"
#include "drawvw.h"

// CBlurDlg 대화 상자

IMPLEMENT_DYNAMIC(CBlurDlg, CDialogEx)

CBlurDlg::CBlurDlg(CDrawDoc* pDrawDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FEATUREEXTRACTION_BLUR, pParent)
	, m_fSigma(0)
	, m_pDrawDoc(pDrawDoc)
	, m_dibRef(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
	, m_dib(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))

{

}

CBlurDlg::~CBlurDlg()
{
}

void CBlurDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SIGMA_SLIDER, m_sliderSigma);
	DDX_Text(pDX, IDC_SIGMA_EDIT, m_fSigma);
	DDV_MinMaxFloat(pDX, m_fSigma, 0.20f, 5.00f);
}


BEGIN_MESSAGE_MAP(CBlurDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_SIGMA_EDIT, &CBlurDlg::OnEnChangeSigmaEdit)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PREVIEW, &CBlurDlg::OnBnClickedPreview)
END_MESSAGE_MAP()


// CBlurDlg 메시지 처리기


BOOL CBlurDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 슬라이더 컨트롤의 초기화
	m_sliderSigma.SetRange(10, 250);
	m_sliderSigma.SetTicFreq(20);
	m_sliderSigma.SetPageSize(20);
	m_sliderSigma.SetPos(static_cast<int>(m_fSigma * 50));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBlurDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// 슬라이드바에서 발생한 WM_HSCROLL 메시지인 경우 처리
	if (m_sliderSigma.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int pos = m_sliderSigma.GetPos();
		m_fSigma = (pos / 50.f);
		UpdateData(FALSE);
	}


	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBlurDlg::OnEnChangeSigmaEdit()
{
	UpdateData(TRUE);
	m_sliderSigma.SetPos(static_cast<int>(m_fSigma * 50));
}


void CBlurDlg::OnPaint()
{
	CPaintDC dc(this); 
	m_dibRef.Draw(dc.m_hDC, 100, 300, 200, -200, 0, 0, m_dibRef.GetWidth(), m_dibRef.GetHeight(), SRCCOPY); // 바뀌기 전 
	m_dib.Draw(dc.m_hDC, 410, 300, 200, -200, 0, 0, m_dib.GetWidth(), m_dib.GetHeight(), SRCCOPY); // 바뀐 후 
}


void CBlurDlg::OnBnClickedPreview()
{
	ByteImage imgsrc;
	FloatImage imgDst;
	FourMatDIBToByteImage(m_dib, imgsrc);
	if (UpdateData() == FALSE) {
		return;
	}
	
	FilterGaussian(imgsrc, imgDst, m_fSigma);

	FloatImageToFourMatDIB(imgDst, m_dib);

	Invalidate(true);
}
