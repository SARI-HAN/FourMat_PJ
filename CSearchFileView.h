#pragma once

#include "CFileFindEx.h"
#include "CListCtrlEx.h"


// CSearchFileView 폼 보기

class CSearchFileView : public CFormView
{
	DECLARE_DYNCREATE(CSearchFileView)

public:
	CSearchFileView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CSearchFileView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH_FORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strToken;
	CImageList m_img;
	CButton m_btnStart;
	CString m_strFileName;
	CString m_strFileLocation;
	BOOL m_bSub;
	CListCtrlEx m_lstResult;
	virtual void OnInitialUpdate();

	void SearFileNotSub();
	void SearFile(CString strStartFolder);
	afx_msg void OnClickedButtonSelect();
	afx_msg void OnNMDblclkListResult(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


