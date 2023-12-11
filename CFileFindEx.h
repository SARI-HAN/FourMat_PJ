#pragma once
#include <afx.h>
class CFileFindEx :
    public CFileFind
{
public:
    CFileFindEx(void);
    ~CFileFindEx(void);
    CString GetCreationTimeString(CString strTmp = "-"); // 파일 생성 시간
};

