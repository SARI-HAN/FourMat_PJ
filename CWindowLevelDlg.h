#pragma once


// CWindowLevelDlg 대화 상자

class CWindowLevelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWindowLevelDlg)

public:
	CWindowLevelDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CWindowLevelDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTERING_WINDOW_LEVEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderWindow;
	CSliderCtrl m_sliderLevel;
	int m_nWindow;
	int m_nLevel;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
