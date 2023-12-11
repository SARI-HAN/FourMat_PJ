#pragma once

#include "CFourMatDIB.h"

// CCannyEdgeDlg 대화 상자
class CDrawDoc;


class CCannyEdgeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCannyEdgeDlg)

public:
	CCannyEdgeDlg(CDrawDoc* DrawDoc, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCannyEdgeDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FEATUREEXTRACTION_CANNY_EDGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_fSigma;
	float m_fLowTh;
	float m_fHighTh;
	
	CFourMatDIB& m_dibRef;
	CFourMatDIB  m_dib;
	CDrawDoc* m_pDrawDoc;

	afx_msg void OnPaint();
	afx_msg void OnBnClickedPreview();
};
