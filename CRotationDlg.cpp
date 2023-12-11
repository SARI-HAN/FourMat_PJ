// CRotation.cpp: 구현 파일

#include "stdafx.h"
#include "FourMat.h"
#include "CRotationDlg.h"
#include "afxdialogex.h"
#include "drawdoc.h"
#include "mainfrm.h"
#include "CFourMatDIB.h"
#include "CConvertDataType.h"
#include "CAffineTransform.h"
#include "drawvw.h"


// CRotation 대화 상자

IMPLEMENT_DYNAMIC(CRotationDlg, CDialogEx)

CRotationDlg::CRotationDlg(CDrawDoc* pDrawDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AFFINETRANSFORM_ROTATION, pParent)
	, m_nRotate(0)
	, m_fAngle(0)
	, m_pDrawDoc(pDrawDoc)
	, m_dibRef(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
	, m_dib(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
{

}

CRotationDlg::~CRotationDlg()
{
}

void CRotationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_ROTATE90, m_nRotate);
	DDX_Text(pDX, IDC_ANGLE, m_fAngle);
	DDV_MinMaxFloat(pDX, m_fAngle, 0, 360);
}


BEGIN_MESSAGE_MAP(CRotationDlg, CDialogEx)
	ON_EN_SETFOCUS(IDC_ANGLE, &CRotationDlg::OnEnSetfocusAngle)
	ON_BN_CLICKED(IDC_ROTATE_USER, &CRotationDlg::OnBnClickedRotateUser)
	ON_WM_PAINT()
ON_BN_CLICKED(IDC_PREVIEW, &CRotationDlg::OnBnClickedPreview)
END_MESSAGE_MAP()


// CRotation 메시지 처리기


BOOL CRotationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
//세 개의 함수는 모두 ByteImage 타입의 입력 영상 imgSrc를 각각 정해진 각도만큼 회전하여 결과 영상을 imgDst에 저장한다.



void CRotationDlg::OnEnSetfocusAngle()
{
	m_nRotate = 3;
	UpdateData(FALSE);
}



void CRotationDlg::OnBnClickedRotateUser()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_ANGLE);
	pEdit->SetSel(0, -1);
	pEdit->SetFocus();
}


void CRotationDlg::OnPaint()
{
	CPaintDC dc(this); 
	m_dibRef.Draw(dc.m_hDC, 100, 300, 200, -200, 0, 0, m_dibRef.GetWidth(), m_dibRef.GetHeight(), SRCCOPY); // 바뀌기 전 
	m_dib.Draw(dc.m_hDC, 450, 300, 200, -200, 0, 0, m_dib.GetWidth(), m_dib.GetHeight(), SRCCOPY); // 바뀐 후 

}

void CRotationDlg::OnBnClickedPreview()
{
	ByteImage imgSrc;
	ByteImage imgDst;

	FourMatDIBToByteImage(m_dib, imgSrc);

	if (UpdateData() == FALSE) {
		return;
	}

	switch (m_nRotate)
	{
	case 0: Rotate90(imgSrc, imgDst); break;
	case 1: Rotate180(imgSrc, imgDst); break;
	case 2: Rotate270(imgSrc, imgDst); break;
	case 3: Rotate(imgSrc, imgDst, (double)m_fAngle); break;
	}
	FourMatGrayToDIBImage(imgDst, m_dib);

	Invalidate(true);
}
