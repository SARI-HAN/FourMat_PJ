// CCompareDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CFourMatDIB.h"
#include "CConvertDataType.h"
#include "CImprovement.h"
#include "drawdoc.h"
#include "CCompareDlg.h"
#include "afxdialogex.h"


// CCompareDlg 대화 상자

IMPLEMENT_DYNAMIC(CCompareDlg, CDialogEx)

CCompareDlg::CCompareDlg(CDrawDoc* pDrawDoc, CWnd* pParent)
	: CDialogEx(IDD_HISTORY_COMPARE, pParent)
	, m_pDrawDoc(pDrawDoc)
	, m_dibLeftRef(pDrawDoc->GetFourMatDIB(TRUE))
	, m_dibRightRef(pDrawDoc->GetFourMatDIB(FALSE))
	, m_dib(pDrawDoc->GetFourMatDIB(TRUE))
{
	FourMatDIBToByteImage(m_dibLeftRef, m_imgLeftSrc);
	FourMatDIBToByteImage(m_dibRightRef, m_imgRightSrc);
	FourMatDIBToByteImage(m_dib, m_imgDst);
}

CCompareDlg::~CCompareDlg()
{
}

void CCompareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPARE_SLIDER, m_sliderCompare);
	//DDX_Text(pDX, IDC_COMPARE_EDIT, m_nCompare);
}


BEGIN_MESSAGE_MAP(CCompareDlg, CDialogEx)
	ON_WM_PAINT()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_COMPARE_SLIDER, &CCompareDlg::OnNMReleasedcaptureCompareSlider)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CCompareDlg 메시지 처리기


void CCompareDlg::OnPaint() // 출력부분
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	m_pDrawDoc->DIBDraw(TRUE, &dc, 7, 10, 100, 100); //imgLeftSrc
	m_pDrawDoc->DIBDraw(FALSE, &dc, 700, 10, 100, 100); //imgRightSrc

	m_dib.Draw(dc.m_hDC, 200, 10, 400, 400); //imgDst
}


BOOL CCompareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CompareImage();

	m_sliderCompare.SetRange(0, 100);
	m_sliderCompare.SetRangeMin(0);
	m_sliderCompare.SetRangeMax(100);
	m_sliderCompare.SetPos(0); // 슬라이더 초기 위치
	m_sliderCompare.SetTicFreq(5); // 슬라이더 이동 간격
	m_sliderCompare.SetLineSize(1); // 키보드 커서 이동 간격
	m_sliderCompare.SetPageSize(10); // PgUp, PgDn 이동 간격

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCompareDlg::OnNMReleasedcaptureCompareSlider(NMHDR* pNMHDR, LRESULT* pResult) // 슬라이더 이동
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nPos = m_sliderCompare.GetPos(); // 슬라이더 위치 얻기
	
	*pResult = 0;
}

void CCompareDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) // 슬라이더 값 얻기
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_sliderCompare.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		CompareImage(); // 이미지 평균 연산 출력
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CCompareDlg::CompareImage() // 이미지 연산 부분을 함수로 추출
{		
	int w = m_imgLeftSrc.GetWidth();
	int h = m_imgLeftSrc.GetHeight();
	int size = m_imgDst.GetSize();
	BYTE* p1 = m_imgLeftSrc.GetPixels();
	BYTE* p2 = m_imgRightSrc.GetPixels();
	BYTE* p3 = m_imgDst.GetPixels();

	int nCompare = m_sliderCompare.GetPos(); 

	for (int i = 0; i < size; i++) // 평균 연산
	{
		p3[i] = ((p1[i]* (100- nCompare)/100) + (p2[i]* nCompare /100))/2;
	}
	
	ByteImageToFourMatDIB(m_imgDst, m_dib);

	CRect rect(200, 10, 600, 410);
	InvalidateRect(&rect);
}