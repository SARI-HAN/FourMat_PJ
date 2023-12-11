#pragma once
#include "CFourMatDIB.h"

// CAddNoiseDlg 대화 상자

class CDrawDoc;

class CAddNoiseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddNoiseDlg)

public:
	CAddNoiseDlg(CDrawDoc* DrawDoc,CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAddNoiseDlg();
	int m_Histogram[256];

	
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FEATUREEXTRACTION_ADDNOISE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nNoiseType;
	int m_nAmount;
	CFourMatDIB& m_dibRef;
	CFourMatDIB  m_dib;
	CDrawDoc* m_pDrawDoc;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedPreview();
};
