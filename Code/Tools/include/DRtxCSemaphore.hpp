// DRtxCSemaphore.hpp
// create semaphore in Rtx
// base on Rtx class: Semaphore
// refering to Lee's RtxCIPC.hpp
// 20221101 bit, Dcc <3120195094@bit.edu.cn> // some problem

#pragma once
#ifndef DRTXCSEMAPHORE_HPP
#define DRTXCSEMAPHORE_HPP
#include "RtxHeaders.h"

_D_WIN_RTX_TOOLS_BEGIN

class c_RtxCSem {
private:
    _STD wstring m_wstrName;
    HANDLE m_hSem;
    int m_nNameFlag;
public:
    inline c_RtxCSem(const WCHAR * wcptName) {
        WCHAR wcNameTemp[60];
        wcscpy_s(wcNameTemp, wcptName);
        wcscat_s(wcNameTemp, L"_Sem");
        this->m_wstrName = wcNameTemp;
        this->m_hSem = NULL;
        this->m_nNameFlag = TRUE;
    }
    inline c_RtxCSem() {
        this->m_wstrName = L"Default_Sem";
        this->m_hSem = NULL;
        this->m_nNameFlag = FALSE;
    }
    inline ~c_RtxCSem() {
        this->fnbClose();
    }
    inline bool fnbSetName(const WCHAR * wcptName) {
        WCHAR wcNameTemp[_MaxStrLen];
        wcscpy_s(wcNameTemp, wcptName);
        wcscat_s(wcNameTemp, L"_Sem");
        this->m_wstrName = wcNameTemp;
        this->m_nNameFlag = TRUE;
        return TRUE;
    }
    inline bool fnbCreate(int nMaxCounts) { // create a semaphore which not belongs to the process with directed name, and set the maximum count number
        if(!this->m_nNameFlag) return FALSE;
        this->m_hSem = RtCreateSemaphore(NULL, nMaxCounts, nMaxCounts, this->m_wstrName.c_str());
        if(this->m_hSem == NULL) {
            _D_Msg(_D_CantCreate, "DSema", "Semaphore", this->m_wstrName.c_str());
            return FALSE; 
        }
        else _D_Msg(_D_Create, "DSema", "Semaphore", this->m_wstrName.c_str());
        return TRUE;
    }
    inline bool fnbOpen() {
        this->m_hSem = RtOpenSemaphore(SYNCHRONIZE, FALSE, this->m_wstrName.c_str());
        if(this->m_hSem == NULL) {
            _D_Msg(_D_CantOpen, "DSema", "Semaphore", this->m_wstrName.c_str());
            return FALSE; 
        }
        else _D_Msg(_D_Open, "DSema", "Semaphore", this->m_wstrName.c_str());
        return TRUE;
    }
    inline bool fnbOpen(int nOpenTryTimes) {
        for(int i = 0; i < nOpenTryTimes; i++) {
            if(this->fnbOpen()) return TRUE;
        }
        return FALSE;
    }
    inline bool fnbWait() { // wait for the semaphore and discount the counting number to ?
        switch(RtWaitForSingleObject(this->m_hSem, INFINITE)) {
            case WAIT_OBJECT_0:
                return TRUE;
            case WAIT_TIMEOUT:
                return FALSE;
            case WAIT_ABANDONED:
                return FALSE;
        }
    }
    inline bool fnbRelease() { // rise the counting number of semaphore for 1
        ReleaseSemaphore(this->m_hSem, 1, NULL);
        return TRUE;
    }
    inline bool fnbClose() {
        if(this->m_hSem != NULL) RtCloseHandle(this->m_hSem);
        return TRUE;
    }
};

_D_WIN_RTX_TOOLS_END

#endif