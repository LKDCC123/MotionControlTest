// DRtxCMutex.hpp
// create a mutex in Rtx 
// based on Rtx class: Mutex
// refering to Lee's rtxMutex.hpp
// 20221028 bit, Dcc <3120195094@bit.edu.cn>

#pragma once
#ifndef DRTXMULTIPROCCOMPUT_HPP
#define DRTXMULTIPROCCOMPUT_HPP
#include "RtxHeaders.h"

_D_WIN_RTX_TOOLS_BEGIN

class c_RtxCMutex {
private: 
    _STD wstring m_wstrName;
    HANDLE m_hMutex;
public:
    inline c_RtxCMutex(const WCHAR * wcptName) { // get the name of the handle
        this->m_wstrName = wcptName;
        this->m_hMutex = NULL;
    }
    inline ~c_RtxCMutex() { // close the mutex
        if(this->m_hMutex != NULL) RtCloseHandle(this->m_hMutex);
    }
    inline bool fnbCreate() { // create a mutex which not belongs to the process with directed name 
        this->m_hMutex = RtCreateMutex(NULL, FALSE, this->m_wstrName.c_str());
        if(this->m_hMutex == NULL) {
            _STD cout << "DMutex: Error! Can't create mutex named <" << this->m_wstrName.c_str() << ">" << _STD endl;
            return FALSE; 
        }
        else _STD cout << "DMutex: Created! Mutex named <" << this->m_wstrName.c_str() << ">" << _STD endl;
        return TRUE;
    }
    inline bool fnbOpen() {
        this->m_hMutex = RtOpenMutex(SYNCHRONIZE, FALSE, this->m_wstrName.c_str());
        if(this->m_hMutex == NULL) {
            _STD cout << "DMutex: Error! Can't get mutex named <" << this->m_wstrName.c_str() << ">" << _STD endl;
            return FALSE; 
        }
        else _STD cout << "DMutex: Get! Mutex named <" << this->m_wstrName.c_str() << ">" << _STD endl;
        return TRUE;
    }
    inline bool fnbLock() {
        RtWaitForSingleObject(this->m_hMutex, INFINITE);
        return TRUE;
    }
    inline bool fnbUnlock() {
        RtReleaseMutex(this->m_hMutex);
        return TRUE;
    }
    inline bool fnbClose() {
        if(this->m_hMutex != NULL) RtCloseHandle(this->m_hMutex);
    }
};

_D_WIN_RTX_TOOLS_END

#endif