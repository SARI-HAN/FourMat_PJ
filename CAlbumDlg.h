#pragma once


// CAlbumDlg 대화 상자

class CAlbumDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAlbumDlg)

public:
	CAlbumDlg(CDrawDoc* pDrawDoc
		, std::vector <CAccessObjectPtr>& listRefDrawObj
		, std::vector<CString> listFileName
		, int nDrwCount, CString fileName
		, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAlbumDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTORY_ALBUM };
#endif
	CDrawDoc* m_pDrawDoc;
	std::vector <CAccessObjectPtr>& m_listRefDrawObj;
	std::vector<CString> m_listFileName;

	CString m_strFileName;
	int m_nDrwTotalNo;
	int m_nCurrentNo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
