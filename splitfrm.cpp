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
#include "FourMat.h"
#include "drawdoc.h"
#include "drawvw.h"
#include "splitfrm.h"
#include "CSearchFileView.h"
#include "CHistoryView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame

IMPLEMENT_DYNCREATE(CSplitFrame, CMDIChildWndEx)

CSplitFrame::CSplitFrame()
{
	m_pDrawView = new CDrawView();
	m_pWndHistoryView = new CHistoryView();
}

CSplitFrame::~CSplitFrame()
{
}

BEGIN_MESSAGE_MAP(CSplitFrame, CMDIChildWndEx)
	//{{AFX_MSG_MAP(CSplitFrame)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	//}}AFX_MSG_MAP

	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

void CSplitFrame::OnFilePrint ()
{
	//if (m_dockManager.IsPrintPreviewValid ())
	//{
	//	PostMessage (WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	//}
}

void CSplitFrame::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid ())
	{
		PostMessage (WM_COMMAND, AFX_ID_PREVIEW_CLOSE);      // Force Print Preview Close
	}
}

void CSplitFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_dockManager.IsPrintPreviewValid ());
}

void CSplitFrame::SwitchView(int nID)
{
	CView* pOldView = GetActiveFrame()->GetActiveView();
	CView* pNewView = NULL;

	switch (nID)
	{
	case VIEWID_SEARCH:
		pNewView = (CView*)m_pWndSearchFileView;
		break;

	case VIEWID_HISTORY:
		pNewView = (CView*)m_pWndHistoryView;
		break;

	case VIEWID_DRAW:
		pNewView = (CView*)m_pDrawView;
		break;
		
	case VIEWID_MULTIDRAW:
		pNewView = (CView*)m_wndSplitter.GetPane(0,0);
		m_wndSplitter.ShowWindow(SW_SHOW);
		Invalidate(TRUE);
		break;
	}
	if (pNewView)
	{
		if (pOldView == pNewView)			return;

		pOldView->ShowWindow(SW_HIDE);
		pOldView->SetDlgCtrlID(nID);

		pNewView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
		pNewView->ShowWindow(SW_SHOW);	
		GetActiveFrame()->SetActiveView(pNewView);
		GetActiveFrame()->RecalcLayout();
	}
}

BOOL CSplitFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	m_wndSplitter.CreateStatic(this, 1, 2);
	
	CRect rect;
	this->GetClientRect(rect);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CDrawView), CSize(rect.Width() / 2 + 100, rect.Height()), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CDrawView), CSize(rect.Width() / 2, rect.Height()), pContext);
	m_wndSplitter.ShowWindow(SW_HIDE);
	CDrawView* pLeftView = (CDrawView*)m_wndSplitter.GetPane(0, 0);
	CDrawView* pRightView = (CDrawView*)m_wndSplitter.GetPane(0, 1);
	pLeftView->setLeftView(TRUE);
	pRightView->setLeftView(FALSE);

	m_pDrawView->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this, VIEWID_DRAW, pContext);
	m_pWndHistoryView->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this, VIEWID_HISTORY, pContext);

	return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}


int CSplitFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CSplitFrame::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDrawDoc* pDoc = (CDrawDoc*)GetActiveDocument();
	if (pDoc->m_bChanged || pDoc->IsFrameChanged()) {
		if (IDYES == AfxMessageBox(_T("변경 내용을 저장하시겠습니까?"), MB_YESNO)) {
			pDoc->ChagedSaveDraw();
		}
	}

	CMDIChildWndEx::OnClose();
}
