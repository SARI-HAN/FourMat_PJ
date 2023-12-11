#include "drawobj.h"
#include "summinfo.h"
#include "AccessPixel.h"
#include "RGBBYTE.h"
#include "CFourMatDIB.h"
#include "AccessObject.h"

class CDrawView;

class CDrawDoc : public COleDocument
{
protected: // create from serialization only
	CDrawDoc();
	DECLARE_DYNCREATE(CDrawDoc)

// Attributes
public:
	void SetCurrentFrameNo(BOOL bLeftView, int nDelta) {
		if (bLeftView) {
			m_leftDrawObj.SetCurrentFrameNo(nDelta);
		}
		else {
			m_rightDrawObj.SetCurrentFrameNo(nDelta);
		}
	}

	CDrawObjList* GetObjects(BOOL bLeftView)
	{ 
		return bLeftView ? m_leftDrawObj.m_pObjects : m_rightDrawObj.m_pObjects;
	}

	CFourMatDIB& GetFourMatDIB(BOOL bClickedView);
	CFourMatDIB& GetRefFourMatDIB(BOOL bClickedView);

	const CSize& GetSize() const { return m_size; }
	void ComputePageSize();
	int GetMapMode() const { return m_nMapMode; }
	COLORREF GetPaperColor() const { return m_paperColor; }
	CSummInfo* m_pSummInfo;

	
	BOOL m_bPen;
	LOGPEN m_logpen;
	BOOL m_bBrush;
	LOGBRUSH m_logbrush;

public:
	CDrawObj* ObjectAt(BOOL bLeftView, const CPoint& point);
	void Draw(BOOL bLeftView, CDC* pDC, CDrawView* pView);
	// ------ Draw called for live icon and Win7 taskbar thumbnails
	void DIBDraw(BOOL bLeftView, CDC* pDC);
	void DIBDraw(BOOL bLeftView, CDC* pDC, int x, int y, int w, int h);
	void DIBRefDraw(CDC* pDC);
	void DIBInfoDraw(BOOL bClickedView, CDC* pDC, CFourMatDIB& dib);
	CRect m_rectDocumentBounds;
	// ------

	void Add(BOOL bLeftView, CDrawObj* pObj);
	void Remove(BOOL bLeftView, CDrawObj* pObj);

	void SetPreviewColor(COLORREF clr);

#ifdef SHARED_HANDLERS
	// Search support
	virtual void InitializeSearchContent();

	// Set properties for search
	void SetTitle(const CString& value);
	void SetAuthor(const CString& value);
	void SetCompany(const CString& value);
	void SetComment(const CString& value);
	void SetCopyright(const CString& value);
	void SetKeywords(const CString& value);
	void SetLastAuthor(const CString& value);
	void SetSearchContents(const CString& value);
#endif

// Implementation
public:
	virtual ~CDrawDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnUnloadHandler();

public:
	// 클래스 분할
	CAccessObject m_leftDrawObj;
	CAccessObject m_rightDrawObj;

	CSize m_size;
	int m_nMapMode;
	COLORREF m_paperColor;
	COLORREF m_paperColorLast;
  
	CImage m_bmp;
	LONG    m_nWidth;      // 비트맵 가로 크기 (픽셀 단위)
	LONG    m_nHeight;     // 비트맵 세로 크기 (픽셀 단위)
	WORD    m_nBitCount;   // 픽셀 당 비트 수
	DWORD   m_nDibSize;    // DIB 전체 크기 (BITMAPINFOHEADER + 색상 테이블 + 픽셀 데이터)
	BYTE* m_pDib;        // DIB 시작 주소 (BITMAPINFOHEADER 시작 주소)
	int m_nPitch;
	BYTE* lpvBits;
	BOOL m_bFirstLoad;

	OFString m_strPatientName;
  
protected:
	BOOL m_bClickedView;		//다중 화면에서 클릭된 뷰 확인
	CString m_strFolderPath;	//환자 이름 폴더의 경로

public:
	void setClickedView(BOOL bClickedView)
	{
		m_bClickedView = bClickedView;
	}
	BOOL getClickedView()
	{
		return m_bClickedView;
	}
	void setFolderPath(CString strFolderPath)
	{
		m_strFolderPath = strFolderPath;
	}
	CString getFolderPath()
	{
		return m_strFolderPath;
	}

	void LoadDicom(BOOL bLeftView);
	void ChagedSaveDraw();
	void SaveDraw(CAccessObject& drawObj);

	BOOL m_bChanged; // 변경사항 있있으면 true
	BOOL IsFrameChanged();
	BOOL IsRefFrameNo(BOOL bClickedView);
  
	void HelperLoadDicom(BOOL bLeftView);
	void EnableDrawView(CCmdUI* pCmdUI);



protected:
	//{{AFX_MSG(CDrawDoc)
	afx_msg void OnViewPaperColor();
	afx_msg void OnFileSummaryInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAffinetranformMirror();
	afx_msg void OnAffinetranformRotation();
	afx_msg void OnAffinetranformScaling();
	afx_msg void OnAffinetranformTranslation();
	afx_msg void OnAffinetransformFlip();
	afx_msg void OnFeatureextractionAddnoise();
	afx_msg void OnFeatureextractionBlur();
	afx_msg void OnFeatureextractionReducenoise();
	afx_msg void OnFeatureextractionSharpening();
	afx_msg void OnFilteringBrightness();
	afx_msg void OnFilteringHistogram();
	afx_msg void OnFilteringWindowlevel();
	afx_msg void OnFilteringInverse();
	afx_msg void OnFeatureextractionHistogramequalization();
	afx_msg void OnFeatureextractionHistogramstretching();
	afx_msg void OnMolphologyClosing();
	afx_msg void OnMolphologyDilation();
	afx_msg void OnMolphologyErosion();
	afx_msg void OnMolphologyOpening();
	afx_msg void OnObjectSavedraw();
	afx_msg void OnFilteringGamma();
	afx_msg void OnFeatureextractionCannyedge();
	afx_msg void OnFeatureextractionHarriscorner();
	afx_msg void OnCompareCompare(); // 비교 dlg

	afx_msg void OnUpdateActiveRibbon(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCompareCompare(CCmdUI* pCmdUI);
	afx_msg void OnObjectResetdraw();
};
