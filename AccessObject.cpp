#include "stdafx.h"
#include "DrawDoc.h"
#include "AccessObject.h"


CAccessObject::CAccessObject()
	: m_strFilePath(_T("")), m_strFileName(_T(""))
	, m_nCurrentFrameNo(0), m_nTotalFrameNo(0), m_nRepFrameNo(0), m_pObjects(NULL)
{
	m_pageObjects.reserve(16); // 복제일어나지 않도록 초기설정
	m_listDIB.reserve(16);
	m_listDIBOrigin.reserve(16);
}

CAccessObject::~CAccessObject() {
	for (auto& pObjects : m_pageObjects) {
		POSITION pos = pObjects->GetHeadPosition();
		while (pos != NULL)
			delete pObjects->GetNext(pos);
		pObjects->RemoveAll();
		delete pObjects;
	}
	m_pageObjects.clear();

	m_pObjects = NULL;

	m_listDIB.clear();
	m_listDIBOrigin.clear();
}

void CAccessObject::Serialize(CArchive& ar) {
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		if (m_nCurrentFrameNo != m_nRepFrameNo) {
			m_nRepFrameNo = m_nCurrentFrameNo;
		}
		ar << m_nRepFrameNo;
	}
	else
	{
		ar >> m_nRepFrameNo;
	}

	m_listDIB[m_nRepFrameNo].Serialize(ar); // 영상처리 변화된 부분 저장
}


BOOL CAccessObject::LoadDicomImage(DicomImage* ptrDicomImage, CDrawDoc* pDoc)
{
	//이미지의 폭과 높이를 얻는다 
	int width = (int)ptrDicomImage->getWidth();
	int height = (int)ptrDicomImage->getHeight();
	void* data = nullptr;

	for (int i = 0; i < m_nTotalFrameNo; i++) {
		//프레임의 위치에 있는 영상 정보를 윈도우 이미지 24bit로 생성하여 얻는다 
		ptrDicomImage->createWindowsDIB(data, width * height, i, 24);
		//이미지의 주소를 출력한다

		CFourMatDIB fourMatDIB;
		fourMatDIB.CreateRgbBitmap(width, height, (BYTE*)data);

		m_listDIBOrigin.push_back(fourMatDIB);
		m_listDIB.emplace_back(std::move(fourMatDIB));

		m_pageObjects.push_back(new CDrawObjList());

		//이미지의 주소를 메모리 해제 한다
		delete[] data;
		data = nullptr;
	}

	LoadDraw(pDoc);
	SetCurrentFrameNo(-m_nRepFrameNo);

	return true;
}


void CAccessObject::LoadDraw(CDrawDoc* pDoc) {
	CFile file;

	CString strFilePath = pDoc->getFolderPath() + _T("\\") + m_strFileName;
	if (!m_strFileName.IsEmpty()) {
		if (file.Open(strFilePath, CFile::modeRead | CFile::typeBinary)) {
			CArchive ar(&file, CArchive::load);
			ar.m_pDocument = pDoc;
			size_t size;
			ar >> size;
			if (size == m_pageObjects.size()) { // .drw 받아드림
				Serialize(ar);

				for each (auto pDrawObjList in m_pageObjects) {
					pDrawObjList->Serialize(ar);
				}
			}
			else {// 사이즈가 다르면 .drw 새로 생성
				pDoc->SaveDraw(*this);
			}
			ar.Close();
			file.Close();
		}
		else { // .drw 파일이 없다면 새로 생성
			pDoc->SaveDraw(*this);
		}
	}
}
void CAccessObject::LoadRefDraw(CString filePath, CDrawDoc* pDoc) {
	CFile file;
	CString strFilePath = filePath;

	if (file.Open(strFilePath, CFile::modeRead | CFile::typeBinary)) {
		CArchive ar(&file, CArchive::load);
		ar.m_pDocument = pDoc;

		size_t size;
		ar >> size;
		ar >> m_nRepFrameNo;

		CFourMatDIB fourMatDIB;
		m_listDIB.push_back(fourMatDIB);
		m_listDIB[0].Serialize(ar); // ref 페이지와 대표이미지만 사용

		ar.Close();
		file.Close();
	}
}

void CAccessObject::SetCurrentFrameNo(int nDelta) 
{
	m_nCurrentFrameNo -= nDelta;
	m_nCurrentFrameNo = long((m_listDIB.size() + m_nCurrentFrameNo) % m_listDIB.size());
	m_pObjects = m_pageObjects[m_nCurrentFrameNo];
}

CString CAccessObject::GetFileDCMName() {
	int nIndex = m_strFileName.ReverseFind(TCHAR('.'));
	return m_strFileName.Left(nIndex);
}

void CAccessObject::DIBInfoDraw(CDC* pDC, CSize& size, CFourMatDIB& dib) {
	CString strFileName = GetFileDCMName();
	CString strPageInfo;
	strPageInfo.Format(_T("%d / %d"), m_nCurrentFrameNo + 1, m_nTotalFrameNo);
	SetTextColor(pDC->m_hDC, RGB(220, 220, 0)); // 글씨 하양
	SetBkMode(pDC->m_hDC, TRANSPARENT); // 배경 투명
	TextOut(pDC->m_hDC, -size.cx / 2 + 5, size.cy / 2 - dib.GetHeight() + 60, strFileName, strFileName.GetLength());
	TextOut(pDC->m_hDC, -size.cx / 2 + 5, size.cy / 2 - dib.GetHeight() + 20, strPageInfo, strPageInfo.GetLength());
}

void CAccessObject::ResetDraw() {
	// 본 코드
	/*BYTE* newDIBits = m_listDIBOrigin[m_nCurrentFrameNo].GetDIBitsAddr();
	m_listDIB[m_nCurrentFrameNo].SetDIBits(newDIBits);*/

	// new deep copy
	std::async([this] {
		// 복제해야할 코드를 작성
		BYTE* newDIBits = this->m_listDIBOrigin[this->m_nCurrentFrameNo].GetDIBitsAddr();
		this->m_listDIB[this->m_nCurrentFrameNo].SetDIBits(newDIBits);
		});
	/*
	영상처리 초기화 부분 -> CFOURMATDIB 쓰레드 사용해서
	프로그램이 동작하는 동안에 내부적으로 origin버전을 복재함
	- future, promise 이것 두개 모두 async안에 숨어있음 -> 쓰레드 만들 필요없이 async를 사용하면 됨
	- async(STL)

	*/
}