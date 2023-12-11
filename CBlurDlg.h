#pragma once
#include "CFourMatDIB.h"

// CBlurDlg 대화 상자
class CDrawDoc;

class CBlurDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBlurDlg)

public:
	CBlurDlg(CDrawDoc* DrawDoc, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBlurDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FEATUREEXTRACTION_BLUR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderSigma;
	float m_fSigma;
	CFourMatDIB& m_dibRef;
	CFourMatDIB  m_dib;
	CDrawDoc* m_pDrawDoc;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeSigmaEdit();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedPreview();
};
