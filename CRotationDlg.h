#pragma once
#include "CFourMatDIB.h"

class CDrawDoc; //전방위 선언 

// CRotationDlg 대화 상자

class CRotationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRotationDlg)

public:
	CRotationDlg(CDrawDoc* pDrawDoc, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRotationDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AFFINETRANSFORM_ROTATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nRotate;
	float m_fAngle;
	CFourMatDIB& m_dibRef;
	CFourMatDIB  m_dib;
	CDrawDoc* m_pDrawDoc;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnSetfocusAngle();
	afx_msg void OnBnClickedRotateUser();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedPreview();
};
