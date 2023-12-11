#pragma once
#include "CFourMatDIB.h"
// CGammaDlg 대화 상자

class CDrawDoc;

class CGammaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGammaDlg)

public:
	CGammaDlg(CDrawDoc* DrawDoc, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CGammaDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTERING_GAMMA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderGamma;
	float m_fGamma;
	
	CFourMatDIB& m_dibRef;
	CFourMatDIB  m_dib;
	CDrawDoc* m_pDrawDoc;
	
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeGammaEdit();
	afx_msg void OnNMCustomdrawGammaSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedPreview();
};
