// DRtxCSharedMem.hpp
// create shared memory in Rtx
// base on Rtx class: SharedMemory
// refering to Lee's RtxCIPC.hpp
// 20221031 bit, Dcc <3120195094@bit.edu.cn>

#pragma once
#ifndef DRTXCSHAREDMEM_HPP
#define DRTXCSHAREDMEM_HPP
#include "RtxHeaders.h"
// #define _USE_RTX
_D_WIN_RTX_TOOLS_BEGIN

template<typename tm_DataIO>
class ctm_RtxCShm {
    typedef tm_DataIO * tmpt_DataIO;
private:
    _STD wstring m_wstrName;
    HANDLE m_hShm;
    tmpt_DataIO m_tmptDataIO;
public:
    inline ctm_RtxCShm(const WCHAR * wcptName) { // get the name of the handle
        this->m_wstrName = wcptName;
        this->m_hShm = NULL;
    }
    inline ~ctm_RtxCShm() {
        if(this->m_hShm != NULL) RtCloseHandle(this->m_hShm);
    }
    inline tmpt_DataIO fntmptGetDataIOPointer() {
        return this->m_tmptDataIO;
    }
    inline bool fnbCreateShm() {
        #ifdef _USE_RTX
            RtCreateSharedMemory(PAGE_READWRITE, 0, sizeof(tm_DataIO), this->m_hShm, (LPVOID*)&m_tmptDataIO);
        #else
            this->m_hShm = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(tm_DataIO), this->m_wstrName.c_str());
        #endif
        if(GetLastError() == ERROR_ALREADY_EXISTS) _STD cout << "DShm: Shared memory already exist!" << _STD endl;
        if(this->m_hShm == NULL) {
            _D_Msg(_D_CantCreate, "DShm", "SharedMemory", this->m_wstrName.c_str());
            return FALSE;
        }
        #ifndef _USE_RTX
            this->m_tmptDataIO = (tm_DataIO *)MapViewOfFile(this->m_hShm, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(tm_DataIO));
        #endif
        _D_Msg(_D_Create, "DShm", "SharedMemory", this->m_wstrName.c_str());
        return TRUE;
    }
    inline bool fnbOpen() {
        #ifdef _USE_RTX 
            this->m_hShm = RtOpenSharedMemory(PAGE_READWRITE, FALSE, this->m_hShm, (LPVOID*)&m_tmptDataIO);
        #else
            this->m_hShm = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, this->m_hShm);
        #endif
        return TRUE;
    }
    inline bool fnbClose() {
        if(this->m_hShm != NULL) RtCloseHandle(this->m_hShm);
        return TRUE;
    }
};

_D_WIN_RTX_TOOLS_END

#endif