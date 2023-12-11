// CReduceNoiseDlg.cpp: 구현 파일

#include "stdafx.h"
#include "FourMat.h"
#include "CReduceNoiseDlg.h"
#include "afxdialogex.h"
#include "drawdoc.h"
#include "mainfrm.h"
#include "CFourMatDIB.h"
#include "CConvertDataType.h"
#include "CFilter.h"
#include "drawvw.h"

// CReduceNoiseDlg 대화 상자

IMPLEMENT_DYNAMIC(CReduceNoiseDlg, CDialogEx)

CReduceNoiseDlg::CReduceNoiseDlg(CDrawDoc* pDrawDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FEATUREEXTRACTION_REDUCENOISE, pParent)
	, m_fLambda(0)
	, m_fK(0)
	, m_nIteration(0)
	, m_pDrawDoc(pDrawDoc)
	, m_dibRef(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))
	, m_dib(pDrawDoc->GetFourMatDIB(pDrawDoc->getClickedView()))

{

}

CReduceNoiseDlg::~CReduceNoiseDlg()
{

}

void CReduceNoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DIFFUSION_LAMBDA, m_fLambda);
	DDV_MinMaxFloat(pDX, m_fLambda, 0, 0.25);
	DDX_Text(pDX, IDC_DIFFUSION_K, m_fK);
	DDX_Text(pDX, IDC_DIFFUSION_ITER, m_nIteration);
	DDV_MinMaxInt(pDX, m_nIteration, 0, 100);
}


BEGIN_MESSAGE_MAP(CReduceNoiseDlg, CDialogEx)
ON_WM_PAINT()
ON_BN_CLICKED(IDC_PREVIEW, &CReduceNoiseDlg::OnBnClickedPreview)
END_MESSAGE_MAP()


// CReduceNoiseDlg 메시지 처리기
void CReduceNoiseDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	m_dibRef.Draw(dc.m_hDC, 100, 300, 200, -200, 0, 0, m_dibRef.GetWidth(), m_dibRef.GetHeight(), SRCCOPY); // 바뀌기 전 
	m_dib.Draw(dc.m_hDC, 410, 300, 200, -200, 0, 0, m_dib.GetWidth(), m_dib.GetHeight(), SRCCOPY); // 바뀐 후 

}


void CReduceNoiseDlg::OnBnClickedPreview()
{
	ByteImage imgSrc;
	FloatImage imgDst;
	FourMatDIBToByteImage(m_dib, imgSrc);

	if (UpdateData() == FALSE) {
		return;
	}

	FilterDiffusion(imgSrc, imgDst, m_fLambda, m_fK, m_nIteration);

	FloatImageToFourMatDIB(imgDst, m_dib);

	Invalidate(true);
}
