// CBrightnessDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CBrightnessDlg.h"
#include "afxdialogex.h"
#include "drawdoc.h"
#include "mainfrm.h"
#include "CFourMatDIB.h"
#include "CConvertDataType.h"
#include "CImprovement.h"
#include "drawvw.h"

// CBrightnessDlg 대화 상자

IMPLEMENT_DYNAMIC(CBrightnessDlg, CDialogEx)

CBrightnessDlg::CBrightnessDlg(CDrawDoc* pDrawDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILTERING_BRIGHTNESS, pParent)
	, m_nBrightness(0)
	, m_nContrast(0)
	, m_pDrawDoc(pDrawDoc)
	, m_dibRef(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
	, m_dib(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))

{

}

CBrightnessDlg::~CBrightnessDlg()
{
}

void CBrightnessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDV_MinMaxInt(pDX, m_nBrightness, -255, 255);
	DDX_Text(pDX, IDC_BRIGHT_EDIT, m_nBrightness);
	DDX_Control(pDX, IDC_SLIDER1, m_sliderBrightness);
	DDX_Text(pDX, IDC_CONTRAST_EDIT, m_nContrast);
	DDV_MinMaxInt(pDX, m_nContrast, -100, 100);
	DDX_Control(pDX, IDC_CONTRAST_SLIDER, m_sliderContrast);
}


BEGIN_MESSAGE_MAP(CBrightnessDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PREVIEW, &CBrightnessDlg::OnBnClickedPreview)
END_MESSAGE_MAP()


// CBrightnessDlg 메시지 처리기


BOOL CBrightnessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 밝기 조절 슬라이더 컨트롤 초기화
	m_sliderBrightness.SetRange(-255, 255);
	m_sliderBrightness.SetTicFreq(32);
	m_sliderBrightness.SetPageSize(32);
	// 명암비 조절 슬라이더 컨트롤 초기화
	m_sliderContrast.SetRange(-100, 100);
	m_sliderContrast.SetTicFreq(20);
	m_sliderContrast.SetPageSize(20);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBrightnessDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_sliderBrightness.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nBrightness = m_sliderBrightness.GetPos();
		UpdateData(FALSE);
	}
	// 명암비 조절 슬라이드바에서 발생한 WM_HSCROLL 메시지 처리
	else if (m_sliderContrast.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nContrast = m_sliderContrast.GetPos();
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBrightnessDlg::OnPaint()
{
	CPaintDC dc(this);

	m_dibRef.Draw(dc.m_hDC, 100, 300, 200, -200, 0, 0, m_dibRef.GetWidth(), m_dibRef.GetHeight(), SRCCOPY); // 바뀌기 전 
	m_dib.Draw(dc.m_hDC, 450, 300, 200, -200, 0, 0, m_dib.GetWidth(), m_dib.GetHeight(), SRCCOPY); // 바뀐 후 
}


void CBrightnessDlg::OnBnClickedPreview()
{
	ByteImage img;

	if (UpdateData() == FALSE) {
		return;
	}

	FourMatDIBToByteImage(m_dib, img);
	Brightness(img, m_nBrightness);
	Contrast(img, m_nContrast);
	FourMatGrayToDIBImage(img, m_dib);

	Invalidate(true);
}
