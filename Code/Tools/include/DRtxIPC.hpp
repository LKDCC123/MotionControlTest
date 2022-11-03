// DRtxIPC.hpp
// inter-process communication in Rtx
// based on Dcc class: SharedMemory, Mutex
// refering to Lee's RtxCIPC.hpp
// 20221103 bit, Dcc <3120195094@bit.edu.cn>

#pragma once
#ifndef DRTXIPC_HPP
#define DRTXIPC_HPP
#include "RtxHeaders.h"

_D_WIN_RTX_TOOLS_BEGIN

#define _Shm    ctm_RtxCShm<tm_DataIO>::
#define _Mutex  c_RtxCMutex::

template<typename tm_DataIO>
class ctm_RtxIPC:   protected ctm_RtxCShm<tm_DataIO>, 
                    protected c_RtxCMutex{
private:
    _STD wstring m_wstrName;
public:
    inline ctm_RtxIPC(const WCHAR * wcptName):ctm_RtxCShm<tm_DataIO>(wcptName), c_RtxCMutex(wcptName) {
        this->m_wstrName = wcptName;
    }
    inline ~ctm_RtxIPC() {
        this->fnbClose();
    }
    // used in Rtx
    inline bool fnbCreate() {
        return(this->_Shm fnbCreate() && this->_Mutex fnbCreate()); // create sharedmemory and the mutex
    }
    // used in Win
    inline bool fnbOpen() {
        return(this->_Shm fnbOpen(5) && this->_Mutex fnbOpen(5)); // open sharememory and the mutex
    }
    // both required
    inline bool fnbSendData(tm_DataIO * tmptDataIO) { // send data
        if(this->_Mutex fnbLock()) *this->_Shm fntmptGetDataIOPointer() = *tmptDataIO; // lock and send data to sharedmemory
        this->_Mutex fnbUnlock(); // unlock
        return TRUE;
    }
    inline bool fnbGetData(tm_DataIO * tmptDataIO) { // receive data
        if(this->_Mutex fnbLock()) *tmptDataIO = *this->_Shm fntmptGetDataIOPointer(); // lock and receive data from sharedmemory
        this->_Mutex fnbUnlock(); // unlock
        return TRUE;
    }
    inline bool fnbClose() {
        this->_Shm fnbClose();
        this->_Mutex fnbClose();
        return TRUE;
    }
};

_D_WIN_RTX_TOOLS_END

#endif