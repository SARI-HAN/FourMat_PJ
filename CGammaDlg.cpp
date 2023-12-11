// CGammaDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CGammaDlg.h"
#include "afxdialogex.h"
#include "drawdoc.h"
#include "mainfrm.h"
#include "CFourMatDIB.h"
#include "CConvertDataType.h"
#include "CImprovement.h"
#include "drawvw.h"


// CGammaDlg 대화 상자

IMPLEMENT_DYNAMIC(CGammaDlg, CDialogEx)

CGammaDlg::CGammaDlg(CDrawDoc* pDrawDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILTERING_GAMMA, pParent)
	, m_fGamma(2.20f)
	, m_pDrawDoc(pDrawDoc)
	, m_dibRef(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
	, m_dib(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))

{

}

CGammaDlg::~CGammaDlg()
{
}

void CGammaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAMMA_SLIDER, m_sliderGamma);
	DDX_Text(pDX, IDC_GAMMA_EDIT, m_fGamma);
	DDV_MinMaxFloat(pDX, m_fGamma, 0.20, 5.00);
}


BEGIN_MESSAGE_MAP(CGammaDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_GAMMA_EDIT, &CGammaDlg::OnEnChangeGammaEdit)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_GAMMA_SLIDER, &CGammaDlg::OnNMCustomdrawGammaSlider)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PREVIEW, &CGammaDlg::OnBnClickedPreview)
END_MESSAGE_MAP()


// CGammaDlg 메시지 처리기


BOOL CGammaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 슬라이더 컨트롤 초기화
	m_sliderGamma.SetRange(10, 250);
	m_sliderGamma.SetTicFreq(20);
	m_sliderGamma.SetPageSize(20);
	m_sliderGamma.SetPos(static_cast<int>(m_fGamma * 50));

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CGammaDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_sliderGamma.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int pos = m_sliderGamma.GetPos();
		m_fGamma = (pos / 50.f);
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CGammaDlg::OnEnChangeGammaEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	m_sliderGamma.SetPos(static_cast<int>(m_fGamma * 50));

}


void CGammaDlg::OnNMCustomdrawGammaSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CGammaDlg::OnPaint()
{
	CPaintDC dc(this); 
	m_dibRef.Draw(dc.m_hDC, 100, 300, 200, -200, 0, 0, m_dibRef.GetWidth(), m_dibRef.GetHeight(), SRCCOPY); // 바뀌기 전 
	m_dib.Draw(dc.m_hDC, 450, 300, 200, -200, 0, 0, m_dib.GetWidth(), m_dib.GetHeight(), SRCCOPY); // 바뀐 후 

}


void CGammaDlg::OnBnClickedPreview()
{
	ByteImage img;

	FourMatDIBToByteImage(m_dib, img);
	
	if (UpdateData() == FALSE) {
		return;
	}

	GammaCorrection(img, m_fGamma);

	FourMatGrayToDIBImage(img, m_dib);

	Invalidate(true);
}
