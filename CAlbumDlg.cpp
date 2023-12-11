// CAlbumDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CHistoryView.h"
#include "drawdoc.h"
#include "CAlbumDlg.h"
#include "afxdialogex.h"
#include "mainfrm.h"
#include "splitfrm.h"

// CAlbumDlg 대화 상자

IMPLEMENT_DYNAMIC(CAlbumDlg, CDialogEx)

CAlbumDlg::CAlbumDlg(CDrawDoc* pDrawDoc, std::vector <CAccessObjectPtr>& listRefDrawObj
	, std::vector<CString> listFileName
	, int nDrwCount, CString fileName, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HISTORY_ALBUM, pParent)
	, m_pDrawDoc(pDrawDoc)
	, m_listRefDrawObj(listRefDrawObj)
	, m_listFileName(listFileName)
	, m_nDrwTotalNo(nDrwCount)
	, m_nCurrentNo(0)
	, m_strFileName(fileName)
{
}

CAlbumDlg::~CAlbumDlg()
{
}

void CAlbumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAlbumDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CAlbumDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CAlbumDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDOK, &CAlbumDlg::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CAlbumDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_BUTTON_LEFT)->ShowWindow(SW_HIDE);
	if (m_nCurrentNo >= m_nDrwTotalNo - 1) GetDlgItem(IDC_BUTTON_RIGHT)->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAlbumDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CFourMatDIB& m_nCurrentDIB = m_listRefDrawObj[m_nCurrentNo]->m_listDIB[0];
	
	CRect rect;
	GetClientRect(rect);

	m_nCurrentDIB.Draw(dc.m_hDC, rect.Width() / 2 - 200, 405, 400, -400, SRCCOPY);

	SetTextColor(dc.m_hDC, RGB(0, 0, 0)); // 글씨 검정
	SetBkMode(dc.m_hDC, TRANSPARENT); // 배경 투명
	SetTextAlign(dc.m_hDC, TA_CENTER);

	CString strPageInfo;
	strPageInfo.Format(_T("%d / %d"), m_nCurrentNo + 1, m_nDrwTotalNo);
	TextOut(dc.m_hDC, rect.Width() / 2, rect.Height() - 60, m_strFileName, m_strFileName.GetLength());
	TextOut(dc.m_hDC, rect.Width() / 2, rect.Height() - 40, m_listFileName[m_nCurrentNo], m_listFileName[m_nCurrentNo].GetLength());
	TextOut(dc.m_hDC, rect.Width() / 2, rect.Height() - 20 , strPageInfo, strPageInfo.GetLength());
	
}


void CAlbumDlg::OnBnClickedButtonLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nCurrentNo--;

	if(m_nCurrentNo == 0) GetDlgItem(IDC_BUTTON_LEFT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_RIGHT)->ShowWindow(SW_SHOW);
	Invalidate();
}


void CAlbumDlg::OnBnClickedButtonRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nCurrentNo++;

	if(m_nCurrentNo == m_nDrwTotalNo - 1) GetDlgItem(IDC_BUTTON_RIGHT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_LEFT)->ShowWindow(SW_SHOW);
	Invalidate();
}

void CAlbumDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CSplitFrame* pSplitFrame = (CSplitFrame*)pMainFrame->GetActiveFrame();
	CHistoryView* pView = (CHistoryView*)pSplitFrame->GetActiveView();

	const int nCount = pView->m_lstHistory.GetItemCount();
	for (int i = nCount - 1; i >= 0; --i) {
		if (pView->m_lstHistory.GetItemText(i, 0) == m_listFileName[m_nCurrentNo]) {
			pView->m_lstHistory.SetCheck(i);
			break;
		}
	}
	
	pView->OnClickedButtonSingle();


	CDialogEx::OnOK();
}

BOOL CAlbumDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_LEFT:
			if (m_nCurrentNo != 0) OnBnClickedButtonLeft();
			GotoDlgCtrl(GetDlgItem(IDOK));
			GetDlgItem(IDOK)->SetFocus();
			return false;
		case VK_RIGHT:
			if (m_nCurrentNo < m_nDrwTotalNo - 1) OnBnClickedButtonRight();
			GotoDlgCtrl(GetDlgItem(IDOK));
			GetDlgItem(IDOK)->SetFocus();
			return false;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}