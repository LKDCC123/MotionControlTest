// DRtxCSemaphore.hpp
// create semaphore in Rtx
// base on Rtx class: Semaphore
// refering to Lee's RtxCIPC.hpp
// 20221101 bit, Dcc <3120195094@bit.edu.cn>

#pragma once
#ifndef DRTXCSEMAPHORE_HPP
#define DRTXCSEMAPHORE_HPP
#include "RtxHeaders.h"

_D_WIN_RTX_TOOLS_BEGIN

class c_RtxSem {
private:
    _STD wstring m_wstrName;
    HANDLE m_hSem;
public:
    inline c_RtxSem(const WCHAR * wcptName) {
        this->m_wstrName = wcptName;
        this->m_hSem = NULL;
    }
    inline ~c_RtxSem() {
        if(this->m_hSem != NULL) RtCloseHandle(this->m_hSem);
    }
    inline bool fnbCreate(int nMaxCounts) { // create a semaphore which not belongs to the process with directed name, and set the maximum count number
        this->m_hSem = RtCreateSemaphore(NULL, 0, nMaxCounts, this->m_wstrName.c_str());
        if(this->m_hSem == NULL) {
            _STD cout << "DSema: Error! Can't create semaphore named <" << this->m_wstrName.c_str() << ">" << _STD endl;
            return FALSE; 
        }
        else _STD cout << "DSema: Created! semaphore named <" << this->m_wstrName.c_str() << ">" << _STD endl;
        return TRUE;
    }
    inline bool fnbOpen() {
        this->m_hSem = RtOpenSemaphore(SYNCHRONIZE, FALSE, this->m_wstrName.c_str());
        if(this->m_hSem == NULL) {
            _STD cout << "DSema: Error! Can't get semaphore named <" << this->m_wstrName.c_str() << ">" << _STD endl;
            return FALSE; 
        }
        else _STD cout << "DSema: Get! semaphore named <" << this->m_wstrName.c_str() << ">" << _STD endl;
        return TRUE;
    }
    inline bool fnbWait() { // wait for the semaphore and discount the counting number to ?
        RtWaitForSingleObject(this->m_hSem, INFINITE);
        return TRUE;
    }
    inline bool fnbRelease() { // rise the counting number of semaphore for 1
        ReleaseSemaphore(this->m_hSem, 1, NULL);
        return TRUE;
    }
    inline bool fnbClose() {
        if(this->m_hSem != NULL) RtCloseHandle(this->m_hSem);
    }
};

_D_WIN_RTX_TOOLS_END

#endif