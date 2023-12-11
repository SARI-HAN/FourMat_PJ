// Transformation.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CTranslationDlg.h"
#include "afxdialogex.h"
#include "drawdoc.h"
#include "mainfrm.h"
#include "CFourMatDIB.h"
#include "CConvertDataType.h"
#include "CAffineTransform.h"
#include "drawvw.h"

// Translation 대화 상자

IMPLEMENT_DYNAMIC(CTranslationDlg, CDialogEx)

CTranslationDlg::CTranslationDlg(CDrawDoc* pDrawDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AFFINETRANSFORM_TRANSLATION, pParent)
	, m_nNewSX(0)
	, m_nNewSY(0)
	, m_pDrawDoc(pDrawDoc)
	, m_dibRef(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
	, m_dib(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))

{

}

CTranslationDlg::~CTranslationDlg()
{
}

void CTranslationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NEW_SX, m_nNewSX);
	DDX_Text(pDX, IDC_NEW_SY, m_nNewSY);
}


BEGIN_MESSAGE_MAP(CTranslationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PREVIEW, &CTranslationDlg::OnBnClickedPreview)
END_MESSAGE_MAP()


// Transformation 메시지 처리기





void CTranslationDlg::OnPaint()
{
	CPaintDC dc(this); 

	m_dibRef.Draw(dc.m_hDC, 100, 300, 200, -200, 0, 0, m_dibRef.GetWidth(), m_dibRef.GetHeight(), SRCCOPY); // 바뀌기 전 
	m_dib.Draw(dc.m_hDC, 450, 300, 200, -200, 0, 0, m_dib.GetWidth(), m_dib.GetHeight(), SRCCOPY); // 바뀐 후 
}


void CTranslationDlg::OnBnClickedPreview()
{
	ByteImage imgSrc;
	ByteImage imgDst;
	FourMatDIBToByteImage(m_dib, imgSrc);
	
	if (UpdateData() == FALSE) {
		return;
	}
	
	Translate(imgSrc, imgDst, m_nNewSX, m_nNewSY);

	FourMatGrayToDIBImage(imgDst, m_dib);

	Invalidate(true);
}
