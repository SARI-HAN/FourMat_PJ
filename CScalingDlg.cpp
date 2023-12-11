// CScalingDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CScalingDlg.h"
#include "afxdialogex.h"
#include "drawdoc.h"
#include "mainfrm.h"
#include "CFourMatDIB.h"
#include "CConvertDataType.h"
#include "CAffineTransform.h"
#include "drawvw.h"


// CScalingDlg 대화 상자

IMPLEMENT_DYNAMIC(CScalingDlg, CDialogEx)

CScalingDlg::CScalingDlg(CDrawDoc* pDrawDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AFFINETRANSFORM_SCALING, pParent)
	, m_nOldWidth(0)
	, m_nOldHeight(0)
	, m_nNewWidth(0)
	, m_nNewHeight(0)
	, m_bAspectRatio(FALSE)
	, m_nInterpolation(0)
	, m_pDrawDoc(pDrawDoc)
	, m_dibRef(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
	, m_dib(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
{

}

CScalingDlg::~CScalingDlg()
{
}

void CScalingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OLD_WIDTH, m_nOldWidth);
	DDX_Text(pDX, IDC_OLD_HEIGHT, m_nOldHeight);
	DDX_Text(pDX, IDC_NEW_WIDTH, m_nNewWidth);
	DDV_MinMaxInt(pDX, m_nNewWidth, 1, 4096);
	DDX_Text(pDX, IDC_NEW_HEIGHT, m_nNewHeight);
	DDV_MinMaxInt(pDX, m_nNewHeight, 1, 4096);
	DDX_Check(pDX, IDC_ASPECT_RATIO, m_bAspectRatio);
	DDX_CBIndex(pDX, IDC_INTERPOLATION, m_nInterpolation);
}


BEGIN_MESSAGE_MAP(CScalingDlg, CDialogEx)
	ON_EN_CHANGE(IDC_NEW_WIDTH, &CScalingDlg::OnEnChangeNewWidth)
	ON_EN_CHANGE(IDC_NEW_HEIGHT, &CScalingDlg::OnEnChangeNewHeight)
	ON_BN_CLICKED(IDC_ASPECT_RATIO, &CScalingDlg::OnBnClickedAspectRatio)
END_MESSAGE_MAP()


// CScalingDlg 메시지 처리기


BOOL CScalingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_WIDTH))->SetRange(1, 4096);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_HEIGHT))->SetRange(1, 4096);
	m_nNewWidth = m_nOldWidth;
	m_nNewHeight = m_nOldHeight;
	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CScalingDlg::OnEnChangeNewWidth()
{
	if (GetDlgItem(IDC_INTERPOLATION) == NULL)
		return;
	if (m_bAspectRatio)
	{
		UpdateData(TRUE);
		m_nNewHeight = m_nNewWidth * m_nOldHeight / m_nOldWidth;
		UpdateData(FALSE);
	}
}


void CScalingDlg::OnEnChangeNewHeight()
{
	if (GetDlgItem(IDC_INTERPOLATION) == NULL)
		return;
	if (m_bAspectRatio)
	{
		UpdateData(TRUE);
		m_nNewWidth = m_nNewHeight * m_nOldWidth / m_nOldHeight;
		UpdateData(FALSE);
	}

}


void CScalingDlg::OnBnClickedAspectRatio()
{
	UpdateData(TRUE);
	if (m_bAspectRatio)
	{
		m_nNewHeight = m_nNewWidth * m_nOldHeight / m_nOldWidth;
		UpdateData(FALSE);
	}
}

