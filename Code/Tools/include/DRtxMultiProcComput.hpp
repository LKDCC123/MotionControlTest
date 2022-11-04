// DRtxMultiProcComput.hpp
// create a computing thread synchronously or asynchronously
// based on Dcc Win Rtx64 Tool class: ctm_RtxCThread, ctm_RtxIPC, c_RtxCEvent
// refering to Lee's RtxCNRTComputingEngine.hpp
// 20221104 bit, Dcc <3120195094@bit.edu.cn>

#pragma once
#ifndef DRTXMULTIPROCCOMPUT_HPP
#define DRTXMULTIPROCCOMPUT_HPP
#include "RtxHeaders.h"
#include <DRtxCEvent.hpp>

_D_WIN_RTX_TOOLS_BEGIN

template<typename tm_DataIO>
class ctm_RtxMultiPC:   protected ctm_RtxCThread<tm_DataIO>,
                        protected ctm_RtxIPC<tm_DataIO> {
    typedef tm_DataIO * tmpt_DataIO;
private:
    _STD wstring m_wstrName;
    HANDLE m_hEvent;
    tmpt_DataIO m_tmptDataIO;
    int m_nAsynCyc;
public:
    inline ctm_RtxMultiPC(const WCHAR * wcptName): { 
        this->m_wstrName = wcptName;
        this->m_nCountNum = 0;
    }
    inline ~ctm_RtxMultiPC() {
        
    }
    inline bool fnbCreate() { // used in Rtx to creating a synchronous computation thread on Win

    }
    inline bool fnbCreate(int nAsynCyc) { // used in Win to creating a synchronous or an asynchronous computation thread, nAsynCyc is the asynchronous cycle
        this->m_nAsynCyc = nAsynCyc;
        this->c_RtxCEvent
    }

};

_D_WIN_RTX_TOOLS_END

#endif
