#pragma once

#include "AccessObject.h"

// CHistoryView 폼 보기

class CHistoryView : public CFormView
{
	DECLARE_DYNCREATE(CHistoryView)

public:
	CHistoryView(CString strTmp = NULL);           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CHistoryView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTORY_FORM };
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
	CListCtrl m_lstHistory;
	CImageList m_imgHistory;
	CString m_strPath;

	// album 변수
	std::vector <CAccessObjectPtr> m_listRefDrawObj;
	std::vector<CString> m_listFileName;

	virtual void OnInitialUpdate();
	afx_msg void OnClickedButtonSingle();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	void FolderSearch();
	afx_msg void OnClickedButtonMulti();

	std::pair<bool, int> IsFileExtDCMName(CString strFindDCM);
	BOOL IsFileExtDraw(CString strFileName, CString& strFilePath);
	BOOL IsFileExists(LPCTSTR szPath);

	afx_msg void OnBnClickedButtonAlbum();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


