#pragma once

#include "CFourMatDIB.h"
// CReduceNoiseDlg 대화 상자

class CDrawDoc;

class CReduceNoiseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReduceNoiseDlg)

public:
	CReduceNoiseDlg(CDrawDoc* DrawDoc, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CReduceNoiseDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FEATUREEXTRACTION_REDUCENOISE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_fLambda;
	float m_fK;
	int m_nIteration;
	CFourMatDIB& m_dibRef;
	CFourMatDIB  m_dib;
	CDrawDoc* m_pDrawDoc;

	afx_msg void OnPaint();
	afx_msg void OnBnClickedPreview();
};
