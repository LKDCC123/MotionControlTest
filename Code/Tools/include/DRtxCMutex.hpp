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
    inline c_RtxCMutex(const WCHAR * wstrName) {
        this->m_wstrName = wstrName;
    }
    inline ~c_RtxCMutex() {
        if(this->m_hMutex != NULL) CloseHandle(this->m_hMutex);
    }
    inline bool fnbCreateMutex(){
        this->m_hMutex = CreateMutex(NULL, FALSE, this->m_wstrName.c_str());
        if(this->m_hMutex == NULL) {
            _STD cout << "DMutex: Error! Can't create mutex named <" << this->m_wstrName.c_str() << ">" << _STD endl;
            return FALSE; 
        }
        else _STD cout << "DMutex: Created! Mutex named <" << this->m_wstrName.c_str() << ">" << _STD endl;
        return TRUE;
    }
    inline bool fnbGetMutex() {
        this->m_hMutex = OpenMutex(SYNCHRONIZE, FALSE, this->m_wstrName.c_str());
        if(this->m_hMutex == NULL) {
            _STD cout << "DMutex: Error! Can't get mutex named <" << this->m_wstrName.c_str() << ">" << _STD endl;
            return FALSE; 
        }
        else _STD cout << "DMutex: Get! Mutex named <" << this->m_wstrName.c_str() << ">" << _STD endl;
        return TRUE;
    }
    inline bool fnbLock() {
        WaitForSingleObject(this->m_hMutex, INFINITE);
        return TRUE;
    }
    inline bool fnbUnlock() {
        ReleaseMutex(this->m_hMutex);
        return TRUE;
    }
};

_D_WIN_RTX_TOOLS_END

#endif
