#pragma once
#include "CFourMatDIB.h"

// CTranslationDlg 대화 상자
class CDrawDoc;

class CTranslationDlg : public CDialogEx // dlg이름 변경 
{
	DECLARE_DYNAMIC(CTranslationDlg)

public:
	CTranslationDlg(CDrawDoc* DrawDoc, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTranslationDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AFFINETRANSFORM_TRANSLATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nNewSX;
	int m_nNewSY;

	CFourMatDIB& m_dibRef;
	CFourMatDIB  m_dib;
	CDrawDoc* m_pDrawDoc;

	afx_msg void OnPaint();
	afx_msg void OnBnClickedPreview();
};
