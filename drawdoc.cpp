// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#include "stdafx.h"

#ifndef SHARED_HANDLERS
#include "FourMat.h"
#include "mainfrm.h"
#endif

#include "drawdoc.h"

#ifndef SHARED_HANDLERS
#include "drawvw.h"
#endif

#include "drawobj.h"
//#include "cntritem.h"

#ifndef SHARED_HANDLERS
#include "summpage.h"
#include "statpage.h"
#endif

#include "propkey.h"
#include "splitfrm.h"
#include "CConvertDataType.h"
#include "CAffineTransform.h"
#include "CFilter.h"
#include "CImprovement.h"
#include "CMorphology.h"
#include "CRotationDlg.h"
#include "CScalingDlg.h"
#include "CTranslationDlg.h"
#include "CAddNoiseDlg.h"
#include "CBlurDlg.h"
#include "CReduceNoiseDlg.h"
#include "CBrightnessDlg.h"
#include "CHistogramDlg.h"
#include "CGammaDlg.h"
#include "CCannyEdgeDlg.h"
#include "CHarrisCornerDlg.h"
#include "CCompareDlg.h"
#include <math.h>

const double PI = 3.14159265358979323846;

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc

IMPLEMENT_DYNCREATE(CDrawDoc, COleDocument)

BEGIN_MESSAGE_MAP(CDrawDoc, COleDocument)
	//{{AFX_MSG_MAP(CDrawDoc)
#ifndef SHARED_HANDLERS
	ON_COMMAND(ID_VIEW_PAPERCOLOR, OnViewPaperColor)
	ON_COMMAND(ID_FILE_SUMMARYINFO, OnFileSummaryInfo)
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleDocument::OnUpdatePasteLinkMenu)
	//	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleDocument::OnUpdateEditLinksMenu)
	//	ON_COMMAND(ID_OLE_EDIT_LINKS, COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, COleDocument::OnUpdateObjectVerbMenu)
	// MAPI support
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
#endif
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_AFFINETRANFORM_MIRROR, &CDrawDoc::OnAffinetranformMirror)
	ON_COMMAND(ID_AFFINETRANFORM_ROTATION, &CDrawDoc::OnAffinetranformRotation)
	ON_COMMAND(ID_AFFINETRANFORM_SCALING, &CDrawDoc::OnAffinetranformScaling)
	ON_COMMAND(ID_AFFINETRANFORM_TRANSLATION, &CDrawDoc::OnAffinetranformTranslation)
	ON_COMMAND(ID_AFFINETRANSFORM_FLIP, &CDrawDoc::OnAffinetransformFlip)
	ON_COMMAND(ID_FEATUREEXTRACTION_ADDNOISE, &CDrawDoc::OnFeatureextractionAddnoise)
	ON_COMMAND(ID_FEATUREEXTRACTION_BLUR, &CDrawDoc::OnFeatureextractionBlur)
	ON_COMMAND(ID_FEATUREEXTRACTION_REDUCENOISE, &CDrawDoc::OnFeatureextractionReducenoise)
	ON_COMMAND(ID_FEATUREEXTRACTION_SHARPENING, &CDrawDoc::OnFeatureextractionSharpening)
	ON_COMMAND(ID_FILTERING_BRIGHTNESS, &CDrawDoc::OnFilteringBrightness)
	ON_COMMAND(ID_FILTERING_INVERSE, &CDrawDoc::OnFilteringInverse)

	ON_COMMAND(ID_FILTERING_HISTOGRAM, &CDrawDoc::OnFilteringHistogram)
	ON_COMMAND(ID_FILTERING_WINDOWLEVEL, &CDrawDoc::OnFilteringWindowlevel)
	ON_COMMAND(ID_FEATUREEXTRACTION_HISTOGRAMEQUALIZATION, &CDrawDoc::OnFeatureextractionHistogramequalization)
	ON_COMMAND(ID_FEATUREEXTRACTION_HISTOGRAMSTRETCHING, &CDrawDoc::OnFeatureextractionHistogramstretching)
	ON_COMMAND(ID_MOLPHOLOGY_CLOSING, &CDrawDoc::OnMolphologyClosing)
	ON_COMMAND(ID_MOLPHOLOGY_DILATION, &CDrawDoc::OnMolphologyDilation)
	ON_COMMAND(ID_MOLPHOLOGY_EROSION, &CDrawDoc::OnMolphologyErosion)
	ON_COMMAND(ID_MOLPHOLOGY_OPENING, &CDrawDoc::OnMolphologyOpening)
	ON_COMMAND(ID_OBJECT_SAVEDRAW, &CDrawDoc::OnObjectSavedraw)
	ON_COMMAND(ID_OBJECT_RESETDRAW, &CDrawDoc::OnObjectResetdraw)
	ON_COMMAND(ID_FILTERING_GAMMA, &CDrawDoc::OnFilteringGamma)
	ON_COMMAND(ID_FEATUREEXTRACTION_CANNYEDGE, &CDrawDoc::OnFeatureextractionCannyedge)
	ON_COMMAND(ID_FEATUREEXTRACTION_HARRISCORNER, &CDrawDoc::OnFeatureextractionHarriscorner)
	ON_COMMAND(ID_COMPARE_COMPARE, &CDrawDoc::OnCompareCompare)

	ON_UPDATE_COMMAND_UI(ID_AFFINETRANFORM_ROTATION, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_AFFINETRANFORM_MIRROR, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_AFFINETRANFORM_SCALING, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_AFFINETRANFORM_TRANSLATION, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_AFFINETRANSFORM_FLIP, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_ADDNOISE, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_BLUR, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_HISTOGRAMEQUALIZATION, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_HISTOGRAMSTRETCHING, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_REDUCENOISE, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_SHARPENING, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FILTERING_BRIGHTNESS, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FILTERING_GAMMA, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FILTERING_HISTOGRAM, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FILTERING_INVERSE, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FILTERING_WINDOWLEVEL, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_MOLPHOLOGY_EROSION, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_MOLPHOLOGY_DILATION, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_MOLPHOLOGY_OPENING, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_MOLPHOLOGY_CLOSING, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_SAVEDRAW, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_RESETDRAW, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_CANNYEDGE, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_HARRISCORNER, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_COMPARE_COMPARE, &CDrawDoc::OnUpdateCompareCompare)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc construction/destruction

CDrawDoc::CDrawDoc() : m_leftDrawObj(), m_rightDrawObj()
{
	EnableCompoundFile();

	//	m_bCanDeactivateInplace = TRUE;
	m_nMapMode = MM_ANISOTROPIC;
	m_paperColorLast = m_paperColor = RGB(255, 255, 255);
	m_pSummInfo = NULL;
	ComputePageSize();

	m_strFolderPath.Empty();
}

CDrawDoc::~CDrawDoc()
{
	OnUnloadHandler();
}

void CDrawDoc::OnUnloadHandler()
{
	delete m_pSummInfo;
	m_pSummInfo = NULL;
}

BOOL CDrawDoc::OnNewDocument() //doc 변수 초기화  
{
	if (!COleDocument::OnNewDocument())
		return FALSE;

	// reinitialization code
	//(SDI documents will reuse this document)
	if (m_pSummInfo != NULL)
		delete m_pSummInfo;
	m_pSummInfo = new CSummInfo;
	// Title, Subject, Author, Keywords default to empty string
	// Comments, Template, SavedBy default to empty string
	// LastSave, LastPrint, EditTime, RevNum default to 0
	m_pSummInfo->StartEditTimeCount();
	m_pSummInfo->RecordCreateDate();
	m_pSummInfo->SetNumPages(1);
	// NumWords, NumChars default to 0
	m_pSummInfo->SetAppname(_T("FourMat")); // 속성 변경해보기
	// Security defaults to 0

	m_bPen = TRUE;
	m_logpen.lopnStyle = PS_INSIDEFRAME;
	m_logpen.lopnWidth.x = 1;
	m_logpen.lopnWidth.y = 1;
	m_logpen.lopnColor = RGB(0, 0, 0);

	m_bBrush = TRUE;
	m_logbrush.lbStyle = BS_SOLID;
	m_logbrush.lbColor = RGB(192, 192, 192);
	m_logbrush.lbHatch = HS_HORIZONTAL;

	m_strFolderPath.Empty();
  
	m_bFirstLoad = true;
	m_bChanged = false;

	m_strPatientName = nullptr;

	return TRUE;
}

BOOL CDrawDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (m_pSummInfo != NULL)
		delete m_pSummInfo;
	m_pSummInfo = new CSummInfo;
	m_pSummInfo->StartEditTimeCount();

	return COleDocument::OnOpenDocument(lpszPathName);
}

BOOL CDrawDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	m_pSummInfo->RecordSaveDate();
	m_pSummInfo->IncrRevNum();
	m_pSummInfo->SetLastAuthor(m_pSummInfo->GetAuthor());
	m_pSummInfo->AddCountToEditTime();
	m_pSummInfo->StartEditTimeCount();
	return COleDocument::OnSaveDocument(lpszPathName);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc serialization

void CDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_paperColor;
		//m_objects.Serialize(ar);
		m_pSummInfo->WriteToStorage(m_lpRootStg);
	}
	else
	{
		ar >> m_paperColor;
		m_paperColorLast = m_paperColor;
		//m_objects.Serialize(ar);
		m_pSummInfo->ReadFromStorage(m_lpRootStg);
	}

	// By calling the base class COleDocument, we enable serialization
	//  of the container document's COleClientItem objects automatically.
	COleDocument::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc implementation

void CDrawDoc::Draw(BOOL bLeftView, CDC* pDC, CDrawView* pView)
{
	CDrawObjList* pObjects = GetObjects(bLeftView);
	if (pObjects == nullptr) return;

	POSITION pos = pObjects->GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = pObjects->GetNext(pos);
		pObj->Draw(pDC);
#ifndef SHARED_HANDLERS
		if (pView != NULL && pView->m_bActive && !pDC->IsPrinting() && pView->IsSelected(pObj))
			pObj->DrawTracker(pDC, CDrawObj::selected);
#endif
	}
}

void CDrawDoc::DIBDraw(BOOL bClickedView, CDC* pDC)
{
	CFourMatDIB& dib = GetFourMatDIB(bClickedView); // 현재이미지로 불러옴
	//dib.Draw(pDC->m_hDC, -m_size.cx / 2, m_size.cy / 2); // dlg -> paint dc
	dib.Draw(pDC->m_hDC, -m_size.cx / 2, m_size.cy / 2 - dib.GetHeight(), dib.GetWidth(), dib.GetHeight(), SRCCOPY);

	if (IsRefFrameNo(bClickedView)) {
		DIBRefDraw(pDC);
	}
	DIBInfoDraw(bClickedView, pDC, dib);
}
void CDrawDoc::DIBDraw(BOOL bClickedView, CDC* pDC, int x, int y, int w, int h)
{
	CFourMatDIB& dib = GetRefFourMatDIB(bClickedView); // 대표이미지로 불러옴
	dib.Draw(pDC->m_hDC, x, y, w, h, 0, 0, dib.GetWidth(), dib.GetHeight(), SRCCOPY); // dlg -> paint dc  
}

void CDrawDoc::DIBRefDraw(CDC* pDC) {
	SetTextColor(pDC->m_hDC, RGB(0, 0, 0)); // 글씨 검정
	SetBkColor(pDC->m_hDC, RGB(255, 255, 0)); // 배경 노랑
	TextOut(pDC->m_hDC, -m_size.cx / 2, m_size.cy / 2, _T("R"), 1);
}
void CDrawDoc::DIBInfoDraw(BOOL bClickedView, CDC* pDC, CFourMatDIB& dib) {
	bClickedView ? m_leftDrawObj.DIBInfoDraw(pDC, m_size, dib) 
		: m_rightDrawObj.DIBInfoDraw(pDC, m_size, dib);
	CString strPatientName = m_strPatientName.c_str();
	TextOut(pDC->m_hDC, -m_size.cx / 2 + 5, m_size.cy / 2 - dib.GetHeight() + 40, strPatientName, strPatientName.GetLength());
}

void CDrawDoc::Add(BOOL bLeftView, CDrawObj* pObj)
{
	CDrawObjList* pObjects = GetObjects(bLeftView);
	if (pObjects == nullptr) return;

	pObjects->AddTail(pObj);
	pObj->m_pDocument = this;
	m_bChanged = true;
}

void CDrawDoc::Remove(BOOL bLeftView, CDrawObj* pObj)
{
	CDrawObjList* pObjects = GetObjects(bLeftView);
	if (pObjects == nullptr) return;

	// Find and remove from document
	POSITION pos = pObjects->Find(pObj);
	if (pos != NULL)
		pObjects->RemoveAt(pos);
	// set document modified flag
	m_bChanged = true;

#ifndef SHARED_HANDLERS
	// call remove for each view so that the view can remove from m_selection
	pos = GetFirstViewPosition();
	while (pos != NULL) {
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CDrawView))) {
			((CDrawView*)pView)->Remove(pObj);
		}
	}
#endif
}

// point is in logical coordinates
CDrawObj* CDrawDoc::ObjectAt(BOOL bLeftView, const CPoint& point)
{
	CDrawObjList* pObjects = GetObjects(bLeftView);
	if (pObjects == nullptr) return nullptr;

	CRect rect(point, CSize(1, 1));
	POSITION pos = pObjects->GetTailPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = pObjects->GetPrev(pos);
		if (pObj->Intersects(rect))
			return pObj;
	}

	return NULL;
}

void CDrawDoc::ComputePageSize()
{
	CSize new_size(850, 1100);  // 8.5" x 11" default

	CPrintDialog dlg(FALSE);
	if (AfxGetApp()->GetPrinterDeviceDefaults(&dlg.m_pd))
	{
		// GetPrinterDC returns a HDC so attach it
		CDC dc;
		HDC hDC = dlg.CreatePrinterDC();
		ASSERT(hDC != NULL);
		dc.Attach(hDC);

		// Get the size of the page in loenglish
		new_size.cx = MulDiv(dc.GetDeviceCaps(HORZSIZE), 1000, 254); //pixel to inch 
//지정된 디스플레이 디바이스의 기능에 대한 지정된 종류의 디바이스 관련 정보를 검색합니다.
		new_size.cy = MulDiv(dc.GetDeviceCaps(VERTSIZE), 1000, 254);
	}

#ifndef SHARED_HANDLERS
	// if size changed then iterate over views and reset
	if (new_size != m_size)
	{
		m_size = new_size;
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL) {
			CView* pView = GetNextView(pos);
			if (pView->IsKindOf(RUNTIME_CLASS(CDrawView))) {
				((CDrawView*)pView)->SetPageSize(m_size);
			}
		}
	}
#endif
}



void CDrawDoc::OnViewPaperColor()
{
#ifndef SHARED_HANDLERS
	COLORREF color = ((CMainFrame*)AfxGetMainWnd())->GetColorFromColorButton(ID_VIEW_PAPERCOLOR);
	m_paperColor = color == (COLORREF)-1 ? RGB(255, 255, 255) : color;
	m_paperColorLast = m_paperColor;

	m_bChanged = true;

	UpdateAllViews(NULL);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc diagnostics

#ifdef _DEBUG
void CDrawDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CDrawDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc commands

void CDrawDoc::OnFileSummaryInfo()
{
#ifndef SHARED_HANDLERS
	ASSERT_VALID(this);

	CPropertySheet sheet(_T("Document Properties"));
	CSummPage summ;
	CStatPage stat;
	sheet.AddPage(&summ);
	sheet.AddPage(&stat);

	summ.m_strAppname = m_pSummInfo->GetAppname();
	summ.m_strTitle = m_pSummInfo->GetTitle();
	summ.m_strSubj = m_pSummInfo->GetSubject();
	summ.m_strAuthor = m_pSummInfo->GetAuthor();
	summ.m_strKeywd = m_pSummInfo->GetKeywords();
	summ.m_strCmt = m_pSummInfo->GetComments();
	summ.m_strTempl = m_pSummInfo->GetTemplate();

	stat.m_strSavedBy = m_pSummInfo->GetLastAuthor();
	stat.m_strRevNum = m_pSummInfo->GetRevNum();
	stat.m_strEditTime = m_pSummInfo->GetEditTime();
	stat.m_strLastPrint = m_pSummInfo->GetLastPrintDate();
	stat.m_strCreateDate = m_pSummInfo->GetCreateDate();
	stat.m_strLastSave = m_pSummInfo->GetLastSaveDate();
	stat.m_strNumPages = m_pSummInfo->GetNumPages();
	stat.m_strNumWords = m_pSummInfo->GetNumWords();
	stat.m_strNumChars = m_pSummInfo->GetNumChars();
	stat.m_strSecurity = m_pSummInfo->GetSecurity();

	if (sheet.DoModal() != IDOK)
		return;

	m_pSummInfo->SetAuthor(summ.m_strAuthor);
	m_pSummInfo->SetKeywords(summ.m_strKeywd);
	m_pSummInfo->SetSubject(summ.m_strSubj);
	m_pSummInfo->SetComments(summ.m_strCmt);
	m_pSummInfo->SetTemplate(summ.m_strTempl);
	m_pSummInfo->SetTitle(summ.m_strTitle);

	m_bChanged = true;
#endif
}

void CDrawDoc::SetPreviewColor(COLORREF clr)
{
	m_paperColor = clr == -1 ? m_paperColorLast : clr;
	UpdateAllViews(NULL);
}

void CDrawDoc::LoadDicom(BOOL bLeftView) {

	HelperLoadDicom(bLeftView);
}

void CDrawDoc::HelperLoadDicom(BOOL bLeftView)
{
	DcmFileFormat fileformat;
	OFFilename filePath;

	if (bLeftView) {
		filePath = (OFFilename)m_leftDrawObj.m_strFilePath;
	}
	else {
		filePath = (OFFilename)m_rightDrawObj.m_strFilePath;
	}

	if (fileformat.loadFile(filePath).good()) {
		DcmDataset* dataset = fileformat.getDataset();
		OFString strTransferSyntaxUID = nullptr;
		DcmMetaInfo* pDcmMetaInfo = fileformat.getMetaInfo();
		double slope, intercept;

		// 환자 이름 가져오기
		dataset->findAndGetOFString(DCM_PatientName, m_strPatientName);

		dataset->findAndGetFloat64(DCM_RescaleSlope, slope);
		dataset->findAndGetFloat64(DCM_RescaleIntercept, intercept);
		
		pDcmMetaInfo->findAndGetOFString(DCM_TransferSyntaxUID, strTransferSyntaxUID);
		// 압축된 파일(여러장은 무조건 압축 되어 있음)
		if (std::string::npos != strTransferSyntaxUID.find("1.2.840.10008.1.2.4.50")) {
			//jpeg 일 경우  1.2.840.10008.1.2.4.50    JPEG Baseline (Process 1): Default Transfer Syntax for Lossy JPEG 8 - bit Image Compression
			//여러장의 이미지가 존재함 프레임 수를 읽는다 
			bLeftView ? dataset->findAndGetLongInt(DCM_NumberOfFrames, m_leftDrawObj.m_nTotalFrameNo)
				: dataset->findAndGetLongInt(DCM_NumberOfFrames, m_rightDrawObj.m_nTotalFrameNo);
		}

		// 압축안된 파일
		else if (std::string::npos != strTransferSyntaxUID.find("1.2.840.10008.1.2")) {
			//dicom 기본 영상으로 1개의 프레임 만 존재함 ("1.2.840.10008.1.2")
			bLeftView ? m_leftDrawObj.m_nTotalFrameNo = 1 : m_rightDrawObj.m_nTotalFrameNo = 1;
		}


		E_TransferSyntax xfer = dataset->getOriginalXfer();
		//데이터 셋으로 이미지를 압축 해제 해서 생성한다 
		DicomImage* ptrDicomImage = bLeftView ? new DicomImage(dataset, xfer, slope, intercept, CIF_DecompressCompletePixelData, 0, m_leftDrawObj.m_nTotalFrameNo)
			: new DicomImage(dataset, xfer, slope, intercept, CIF_DecompressCompletePixelData, 0, m_rightDrawObj.m_nTotalFrameNo);

		if (ptrDicomImage) {

			bLeftView ? m_leftDrawObj.LoadDicomImage(ptrDicomImage, this) : m_rightDrawObj.LoadDicomImage(ptrDicomImage, this);

			UpdateAllViews(NULL, HINT_LAOD_DICOMIMAGE);
		}
		delete ptrDicomImage;
	}

	/*BYTE* CDrawDoc::GetBitmapItsAddr() const
	{
		if (m_bmi == NULL)
			return NULL;

		LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_bmi;
		return ((BYTE*)m_bmi + lpbmi->biSize + (sizeof(RGBQUAD) * GetPaletteNums()));
	}*/
}

#ifdef SHARED_HANDLERS
void CDrawDoc::InitializeSearchContent()
{
	SetAuthor(m_pSummInfo->GetAuthor());
	SetTitle(m_pSummInfo->GetTitle());
	SetComment(m_pSummInfo->GetComments());
	SetKeywords(m_pSummInfo->GetKeywords());
	SetLastAuthor(m_pSummInfo->GetLastAuthor());

	if (m_objects.GetCount() == 0)
	{
		return;
	}

	CString strContent;

	LPCTSTR szTypes[] =
	{
		_T("line"),
		_T("rectangle"),
		_T("rounded rectangle"),
		_T("ellipse"),
		_T("polyline"),
		_T("ole object"),
	};

	struct XColor
	{
		LPCTSTR szName;
		COLORREF clr;
	};

	XColor szColors[] =
	{
		{_T("black")  , RGB(0,   0,   0)},
		{_T("gray")   , RGB(128, 128, 128)},
		{_T("white")  , RGB(255, 255, 255)},
		{_T("maroon") , RGB(128,   0,   0)},
		{_T("green")  , RGB(0, 128,   0)},
		{_T("olive")  , RGB(128, 128,   0)},
		{_T("navy")   , RGB(0,   0, 128)},
		{_T("purple") , RGB(128,   0, 128)},
		{_T("teal")   , RGB(0, 128, 128)},
		{_T("red")    , RGB(255,   0,   0)},
		{_T("lime")   , RGB(0, 255,   0)},
		{_T("yellow") , RGB(255, 255,   0)},
		{_T("blue")   , RGB(0,   0, 255)},
		{_T("fuchsia"), RGB(255,   0, 255)},
		{_T("aqua")   , RGB(0, 255, 255)}
	};
	BYTE nColorIndex[] = { 0, 128, 255 };

	POSITION pos = m_objects.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObject = m_objects.GetNext(pos);
		if (pObject == NULL)
		{
			continue;
		}

		int typeObj = -1;
		//0 - line
		//1 - rectangle
		//2 - rounded rectangle
		//3 - ellipse
		//4 - polyline
		//5 - ole object

		int typeClr = -1;
		//0  - black
		//1  - gray
		//2  - white
		//3  - maroon
		//4  - green
		//5  - olive
		//6  - navy
		//7  - purple
		//8  - teal
		//9  - red
		//10 - lime
		//11 - yellow
		//12 - blue
		//13 - fuchsia
		//14 - aqua

		COLORREF clr = (COLORREF)-1;

		if (DYNAMIC_DOWNCAST(CDrawRect, pObject) != NULL)
		{
			CDrawRect* pDraw = (CDrawRect*)pObject;
			switch (pDraw->GetShape())
			{
			case CDrawRect::line:
				typeObj = 0;
				if (pDraw->IsEnableLine())
				{
					clr = pDraw->GetLineColor();
				}
				break;
			case CDrawRect::rectangle:
				typeObj = 1;
				break;
			case CDrawRect::roundRectangle:
				typeObj = 2;
				break;
			case CDrawRect::ellipse:
				typeObj = 3;
				break;
			}

			if (typeObj != 0)
			{
				if (pDraw->IsEnableFill())
				{
					clr = pDraw->GetFillColor();
				}
			}
		}
		else if (DYNAMIC_DOWNCAST(CDrawPoly, pObject) != NULL)
		{
			typeObj = 4;

			CDrawPoly* pDraw = (CDrawPoly*)pObject;
			if (pDraw->IsEnableFill())
			{
				clr = pDraw->GetFillColor();
			}
		}
		else if (DYNAMIC_DOWNCAST(CDrawOleObj, pObject) != NULL)
		{
			typeObj = 5;
		}

		if (typeObj == -1)
		{
			continue;
		}

		CString strClr;
		if (clr != (COLORREF)-1)
		{
			COLORREF clrOrig = clr;
			clr = RGB
			(
				nColorIndex[GetRValue(clr) / 86],
				nColorIndex[GetGValue(clr) / 86],
				nColorIndex[GetBValue(clr) / 86]
			);
			for (int i = 0; i < sizeof(szColors) / sizeof(XColor); i++)
			{
				if (szColors[i].clr == clr)
				{
					strClr = szColors[i].szName;
					break;
				}
			}

			if (strClr.IsEmpty())
			{
				strClr.Format(_T("#%0X"), clrOrig);
			}
		}
		else
		{
			strClr = _T("empty");
		}

		CString str;
		str = strClr + _T(" ") + szTypes[typeObj];

		if (strContent.IsEmpty())
		{
			strContent = str;
		}
		else if (strContent.Find(str) == -1)
		{
			strContent += _T("; ") + str;
		}
	}

	if (strContent.IsEmpty())
	{
		strContent = _T("empty document");
	}

	SetSearchContents(strContent);
}
void CDrawDoc::SetTitle(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Title.fmtid, PKEY_Title.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Title, value, CHUNK_VALUE, 0, 0, 0, CHUNK_EOP);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetAuthor(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Author.fmtid, PKEY_Author.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Author, value, CHUNK_VALUE, 0, 0, 0, CHUNK_EOP);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetCompany(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Company.fmtid, PKEY_Company.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Company, value, CHUNK_VALUE, 0, 0, 0, CHUNK_EOP);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetComment(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Comment.fmtid, PKEY_Comment.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Comment, value, CHUNK_VALUE, 0, 0, 0, CHUNK_EOP);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetCopyright(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Copyright.fmtid, PKEY_Copyright.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Copyright, value, CHUNK_VALUE, 0, 0, 0, CHUNK_EOP);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetKeywords(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Keywords.fmtid, PKEY_Keywords.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Keywords, value);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetLastAuthor(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Document_LastAuthor.fmtid, PKEY_Document_LastAuthor.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Document_LastAuthor, value, CHUNK_VALUE, 0, 0, 0, CHUNK_EOP);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetSearchContents(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
		SetChunkValue(pChunk);
	}
}

#endif

//리본 버튼 클릭 메세지
CFourMatDIB& CDrawDoc::GetFourMatDIB(BOOL bClickedView)
{
	std::vector <CFourMatDIB>& listDib = bClickedView ? m_leftDrawObj.m_listDIB : m_rightDrawObj.m_listDIB;
	long currentFrameNo = bClickedView ? m_leftDrawObj.m_nCurrentFrameNo : m_rightDrawObj.m_nCurrentFrameNo;

	return listDib[currentFrameNo];
}

CFourMatDIB& CDrawDoc::GetRefFourMatDIB(BOOL bClickedView)
{
	std::vector <CFourMatDIB>& listDib = bClickedView ? m_leftDrawObj.m_listDIB : m_rightDrawObj.m_listDIB;
	long refFrameNo = bClickedView ? m_leftDrawObj.m_nRepFrameNo : m_rightDrawObj.m_nRepFrameNo;

	return listDib[refFrameNo];
}

void CDrawDoc::OnAffinetranformMirror()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage imgSrc;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, imgSrc);
	Mirror(imgSrc, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);

	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
}


void CDrawDoc::OnAffinetranformRotation()
{
	CRotationDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage imgSrc;
		ByteImage imgDst;

		FourMatDIBToByteImage(dib, imgSrc);
		switch (dlg.m_nRotate)
		{
		case 0: Rotate90(imgSrc, imgDst); break;
		case 1: Rotate180(imgSrc, imgDst); break;
		case 2: Rotate270(imgSrc, imgDst); break;
		case 3: Rotate(imgSrc, imgDst, (double)dlg.m_fAngle); break;
		}
		FourMatGrayToDIBImage(imgDst, dib);
	
		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
}


void CDrawDoc::OnAffinetranformScaling()
{
	CScalingDlg dlg(this);
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	dlg.m_nOldWidth = dib.GetWidth();
	dlg.m_nOldHeight = dib.GetHeight();
	if (dlg.DoModal() == IDOK)
	{
		ByteImage imgSrc;
		ByteImage imgDst;

		FourMatDIBToByteImage(dib, imgSrc);
		switch (dlg.m_nInterpolation)
		{
		case 0: ResizeNearest(imgSrc, imgDst, dlg.m_nNewWidth, dlg.m_nNewHeight); break;
		case 1: ResizeBilinear(imgSrc, imgDst, dlg.m_nNewWidth, dlg.m_nNewHeight); break;
		case 2: ResizeCubic(imgSrc, imgDst, dlg.m_nNewWidth, dlg.m_nNewHeight); break;
		}
		CFourMatDIB newDIB;// 새로운 객체 생성 
		newDIB.CreateRgbBitmap(dlg.m_nNewWidth, dlg.m_nNewHeight); // rgb bitmap 에 대한 
		FourMatGrayToDIBImage(imgDst, newDIB); // 새로운 객체 생성  
		dib = std::move(newDIB);  

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}

}


void CDrawDoc::OnAffinetranformTranslation()
{
	CTranslationDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage imgSrc;
		ByteImage imgDst;

		FourMatDIBToByteImage(dib, imgSrc);
		Translate(imgSrc, imgDst, dlg.m_nNewSX, dlg.m_nNewSY);
		FourMatGrayToDIBImage(imgDst, dib);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
}


void CDrawDoc::OnAffinetransformFlip()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage imgSrc;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, imgSrc);
	Flip(imgSrc, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);

	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);

	
}



void CDrawDoc::OnFeatureextractionAddnoise()
{
	CAddNoiseDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage imgSrc;
		ByteImage imgDst;
		FourMatDIBToByteImage(dib, imgSrc);

		if (dlg.m_nNoiseType == 0)
			NoiseGaussian(imgSrc, imgDst, dlg.m_nAmount);
		else
			NoiseSaltNPepper(imgSrc, imgDst, dlg.m_nAmount);

		FourMatGrayToDIBImage(imgDst, dib);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);

		}
}


void CDrawDoc::OnFeatureextractionBlur()
{
	CBlurDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage imgsrc;
		FloatImage imgDst;
		FourMatDIBToByteImage(dib, imgsrc);
		FilterGaussian(imgsrc, imgDst, dlg.m_fSigma);

		FloatImageToFourMatDIB(imgDst, dib);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
}


void CDrawDoc::OnFeatureextractionReducenoise()
{
	CReduceNoiseDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage imgSrc;
		FloatImage imgDst;
		FourMatDIBToByteImage(dib, imgSrc);
		FilterDiffusion(imgSrc, imgDst, dlg.m_fLambda, dlg.m_fK, dlg.m_nIteration);
		FloatImageToFourMatDIB(imgDst, dib);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
		}
}


void CDrawDoc::OnFeatureextractionSharpening()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage imgSrc;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, imgSrc);
	FilterLaplacian(imgSrc, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);

	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);

}


void CDrawDoc::OnFilteringBrightness()
{
	CBrightnessDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage img;

		FourMatDIBToByteImage(dib, img);
		Brightness(img, dlg.m_nBrightness);
		Contrast(img, dlg.m_nContrast);
		FourMatGrayToDIBImage(img, dib);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
	
}





void CDrawDoc::OnFilteringHistogram()
{
	CHistogramDlg dlg;
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);

	dlg.SetImage(dib);
	dlg.DoModal();

		
}


void CDrawDoc::OnFilteringWindowlevel()
{

}


void CDrawDoc::OnFilteringInverse()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;

	FourMatDIBToByteImage(dib, img);
	Inverse(img);
	FourMatGrayToDIBImage(img, dib);

	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}

void CDrawDoc::OnFeatureextractionHistogramequalization()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;

	FourMatDIBToByteImage(dib, img);
	HistogramEqualization(img);
	FourMatGrayToDIBImage(img, dib);

	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);

}


void CDrawDoc::OnFeatureextractionHistogramstretching()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;
	FourMatDIBToByteImage(dib, img);
	HistogramStretching(img);
	FourMatGrayToDIBImage(img, dib);

	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
}


void CDrawDoc::OnMolphologyClosing()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, img);
	MorphologyClosing(img, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);
	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
}


void CDrawDoc::OnMolphologyDilation()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, img);
	MorphologyGrayDilation(img, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);
	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
}

void CDrawDoc::OnMolphologyErosion()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, img);
	MorphologyGrayErosion(img, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);
	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
}


void CDrawDoc::OnMolphologyOpening()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, img);
	MorphologyOpening(img, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);
	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
}

void CDrawDoc::OnObjectSavedraw()
{
	if (!m_bChanged && !IsFrameChanged()) {
		AfxMessageBox(_T("변경된 사항이 없습니다."));
		return;
	}

	ChagedSaveDraw();

	m_bChanged = false;
	UpdateAllViews(NULL, HINT_UPDATE_WINDOW);
	// 대표문구 때문에 화면 다시 그리기
}

void CDrawDoc::ChagedSaveDraw() {
	SaveDraw(m_leftDrawObj);
	if (!m_rightDrawObj.m_strFileName.IsEmpty()) {
		SaveDraw(m_rightDrawObj);
	}
	AfxMessageBox(_T("변경 내용을 저장했습니다."));

}

void CDrawDoc::SaveDraw(CAccessObject& drawObj) {
	CFile file;

	CString strFilePath = m_strFolderPath + _T("\\") + drawObj.m_strFileName;
	if (file.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary)) {
		// modeCreate : 파일을 새로 만들거나 기존의 파일을 초기화
		CArchive ar(&file, CArchive::store);

		ar << drawObj.m_pageObjects.size();

		drawObj.Serialize(ar); // 영상부분을 먼저 저장

		for each (auto pDrawObjList in drawObj.m_pageObjects) {
			pDrawObjList->Serialize(ar);
		}

		ar.Close();
		file.Close();
	}
}

BOOL CDrawDoc::IsFrameChanged() {
	return (m_leftDrawObj.IsFrameChanged() || m_rightDrawObj.IsFrameChanged());
}

BOOL CDrawDoc::IsRefFrameNo(BOOL bClickedView) {
	return (bClickedView ? !m_leftDrawObj.IsFrameChanged() : !m_rightDrawObj.IsFrameChanged());
}

void CDrawDoc::OnFilteringGamma()
{
	CGammaDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{

		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage img;

		FourMatDIBToByteImage(dib, img);
		GammaCorrection(img, dlg.m_fGamma);
		FourMatGrayToDIBImage(img, dib);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}



//뷰에 따른 리본 버튼 활성화 비활성화 구분 - UPDATE_COMMAND_UI, Enable()
void CDrawDoc::EnableDrawView(CCmdUI* pCmdUI)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CSplitFrame* pSplitFrame = (CSplitFrame*)pMainFrame->GetActiveFrame();
	CView* pView = pSplitFrame->GetActiveView();
	pCmdUI->Enable(pView->IsKindOf(RUNTIME_CLASS(CDrawView)));
}

void CDrawDoc::OnUpdateActiveRibbon(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	EnableDrawView(pCmdUI);
}

void CDrawDoc::OnFeatureextractionCannyedge()
{
	CCannyEdgeDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;
	ByteImage imgEdge;
	FourMatDIBToByteImage(dib, img);
	EdgeCanny(img, imgEdge, dlg.m_fSigma, dlg.m_fLowTh, dlg.m_fHighTh);
	FourMatGrayToDIBImage(imgEdge, dib);
	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
}


void CDrawDoc::OnFeatureextractionHarriscorner()
{
	CHarrisCornerDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage img;
		FourMatDIBToByteImage(dib, img);
		std::vector<Point> corners;
		HarrisCorner(img, corners, dlg.m_nHarrisTh);

		BYTE** ptr = img.GetPixels2D();
		int x, y;
		for (Point cp : corners)
		{
			x = cp.x;
			y = cp.y;
			ptr[y - 1][x - 1] = ptr[y - 1][x] = ptr[y - 1][x + 1] = 0;
			ptr[y][x - 1] = ptr[y][x] = ptr[y][x + 1] = 0;
			ptr[y + 1][x - 1] = ptr[y + 1][x] = ptr[y + 1][x + 1] = 0;
		}
		FourMatGrayToDIBImage(img, dib);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
}
void CDrawDoc::OnCompareCompare() // 비교 dlg
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CCompareDlg dlg(this);
	dlg.DoModal();
}


void CDrawDoc::OnUpdateCompareCompare(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(!m_rightDrawObj.m_strFilePath.IsEmpty());
}


void CDrawDoc::OnObjectResetdraw()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bClickedView ? m_leftDrawObj.ResetDraw() : m_rightDrawObj.ResetDraw();

	if (IDYES == AfxMessageBox(_T("현재 페이지의 이미지 처리를 초기화하시겠습니까?"), MB_YESNO)) {
		m_bChanged = true;
		UpdateAllViews(NULL, HINT_DICOM_IMAGE_RESET);
		AfxMessageBox(_T("이미지가 초기화되었습니다."));
	}
}
