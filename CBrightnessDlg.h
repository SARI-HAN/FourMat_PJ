#pragma once
#include "CFourMatDIB.h"


// CBrightnessDlg 대화 상자
class CDrawDoc;


class CBrightnessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBrightnessDlg)

public:
	CBrightnessDlg(CDrawDoc* DrawDoc, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBrightnessDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTERING_BRIGHTNESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int m_nBrightness;
	CSliderCtrl m_sliderBrightness;
	int m_nContrast;
	CSliderCtrl m_sliderContrast;
	CFourMatDIB& m_dibRef;
	CFourMatDIB  m_dib;
	CDrawDoc* m_pDrawDoc;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedPreview();
};
