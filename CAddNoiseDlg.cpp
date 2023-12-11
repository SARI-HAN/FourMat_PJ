// CAddNoiseDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CAddNoiseDlg.h"
#include "afxdialogex.h"
#include "drawdoc.h"
#include "mainfrm.h"
#include "CFourMatDIB.h"
#include "CConvertDataType.h"
#include "CFilter.h"
#include "drawvw.h"

// CAddNoiseDlg 대화 상자

IMPLEMENT_DYNAMIC(CAddNoiseDlg, CDialogEx)

CAddNoiseDlg::CAddNoiseDlg(CDrawDoc* pDrawDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FEATUREEXTRACTION_ADDNOISE, pParent)
	, m_nNoiseType(0)
	, m_nAmount(0)
	,m_pDrawDoc(pDrawDoc)
	, m_dibRef(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
	, m_dib(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
{
	
}

CAddNoiseDlg::~CAddNoiseDlg()
{
}

void CAddNoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_NOISE_RADIO1, m_nNoiseType);
	DDX_Text(pDX, IDC_NOISE_AMOUNT, m_nAmount);
	DDV_MinMaxInt(pDX, m_nAmount, 0, 100);
}


BEGIN_MESSAGE_MAP(CAddNoiseDlg, CDialogEx)
	ON_WM_PAINT()
//	ON_EN_VSCROLL(IDC_NOISE_AMOUNT, &CAddNoiseDlg::OnEnVscrollNoiseAmount)
//ON_EN_VSCROLL(IDC_NOISE_AMOUNT, &CAddNoiseDlg::OnEnVscrollNoiseAmount)
//ON_EN_CHANGE(IDC_NOISE_AMOUNT, &CAddNoiseDlg::OnEnChangeNoiseAmount)
ON_BN_CLICKED(IDC_PREVIEW, &CAddNoiseDlg::OnBnClickedPreview)
END_MESSAGE_MAP()


// CAddNoiseDlg 메시지 처리기


BOOL CAddNoiseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_AMOUNT))->SetRange(0, 100);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAddNoiseDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	m_dibRef.Draw(dc.m_hDC, 100, 300, 200, -200, 0, 0, m_dibRef.GetWidth(), m_dibRef.GetHeight(), SRCCOPY); // 바뀌기 전 
	m_dib.Draw(dc.m_hDC, 450, 300, 200, -200, 0, 0, m_dib.GetWidth(), m_dib.GetHeight(), SRCCOPY); // 바뀐 후 

}


void CAddNoiseDlg::OnBnClickedPreview()
{
	ByteImage imgSrc;
	ByteImage imgDst;
	FourMatDIBToByteImage(m_dib, imgSrc);
	
	if (UpdateData() == FALSE) {
		return;
	}
	
	if (m_nNoiseType == 0)
		NoiseGaussian(imgSrc, imgDst, m_nAmount);
	else
		NoiseSaltNPepper(imgSrc, imgDst, m_nAmount);
	
	FourMatGrayToDIBImage(imgDst, m_dib);
	
	Invalidate(true);
}
