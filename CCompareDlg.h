#pragma once


// CCompareDlg 대화 상자

class CDrawDoc;

class CCompareDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCompareDlg)

public:
	//CCompareDlg(CWnd* pParent /*=nullptr*/);   // 표준 생성자입니다.
	CCompareDlg(CDrawDoc* pDrawDoc, CWnd* pParent =nullptr);

	void SetImage(CFourMatDIB& dib);

	virtual ~CCompareDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTORY_COMPARE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CDrawDoc* m_pDrawDoc;

	CFourMatDIB& m_dibLeftRef;
	CFourMatDIB& m_dibRightRef;
	CFourMatDIB  m_dib;
	CSliderCtrl m_sliderCompare;
	ByteImage m_imgLeftSrc;
	ByteImage m_imgRightSrc;
	ByteImage m_imgDst;

	void CompareImage();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMReleasedcaptureCompareSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
