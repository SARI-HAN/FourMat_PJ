// CWindowLevel.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CWindowLevelDlg.h"
#include "afxdialogex.h"


// CWindowLevel 대화 상자

IMPLEMENT_DYNAMIC(CWindowLevelDlg, CDialogEx)

CWindowLevelDlg::CWindowLevelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILTERING_WINDOW_LEVEL, pParent)
	, m_nWindow(0)
	, m_nLevel(0)
{

}

CWindowLevelDlg::~CWindowLevelDlg()
{
}

void CWindowLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_sliderWindow);
	DDX_Control(pDX, IDC_SLIDER2, m_sliderLevel);
	DDX_Text(pDX, IDC_EDIT1, m_nWindow);
	DDV_MinMaxInt(pDX, m_nWindow, -255, 255);
	DDX_Text(pDX, IDC_EDIT3, m_nLevel);
	DDV_MinMaxInt(pDX, m_nLevel, -100, 100);
}


BEGIN_MESSAGE_MAP(CWindowLevelDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CWindowLevel 메시지 처리기


BOOL CWindowLevelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_sliderWindow.SetRange(0, 255);
	m_sliderWindow.SetTicFreq(32);
	m_sliderWindow.SetPageSize(32);
	// 명암비 조절 슬라이더 컨트롤 초기화
	m_sliderLevel.SetRange(0, 255);
	m_sliderLevel.SetTicFreq(20);
	m_sliderLevel.SetPageSize(20);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CWindowLevelDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_sliderWindow.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nWindow = m_sliderWindow.GetPos();
		UpdateData(FALSE);
	}
	// 명암비 조절 슬라이드바에서 발생한 WM_HSCROLL 메시지 처리
	else if (m_sliderLevel.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nLevel = m_sliderLevel.GetPos();
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
