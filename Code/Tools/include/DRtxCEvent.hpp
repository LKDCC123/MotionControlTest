// DRtxCEvent.hpp
// create event in Rtx
// based on Rtx class: Event
// refering to Lee's RtxCNRTComputingEngine.hpp
// 20221103 Dcc <3120195094@bit.edu.cn>

#pragma once 
#ifndef DTRXCEVENT_HPP
#define DTRXCEVENT_HPP
#include "RtxHeaders.h"

_D_WIN_RTX_TOOLS_BEGIN

class c_RtxCEvent {
private:
    _STD wstring m_wstrName;
    HANDLE m_hEvent;
    int m_nCountNum;
    int m_nMaxNum;
public:
    inline c_RtxCEvent(const WCHAR * wcptName) {
        WCHAR wcNameTemp[_MaxStrLen];
        wcscpy_s(wcNameTemp, wcptName);
        wcscat_s(wcNameTemp, L"_Event");
        this->m_wstrName = wcNameTemp;
        this->m_hEvent = NULL;
        this->m_nCountNum = 0;
    }
    inline ~c_RtxCEvent() {
        this->fnbClose();
    }
    inline bool fnbCreate(int nMaxNum) {
        this->m_hEvent = RtCreateEvent(NULL, NULL, NULL, this->m_wstrName.c_str());
        if(this->m_hEvent == NULL) {
            _D_Msg(_D_CantCreate, "DEvent", "Event", this->m_wstrName.c_str());       
        return FALSE;
        }
        else _D_Msg(_D_Create, "DEvent", "Event", this->m_wstrName.c_str());
        this->m_nMaxNum = nMaxNum;
        return TRUE;
    }
    inline bool fnbCreate() {
        return (fnbCreate(1));
    }
    inline bool fnbOpen() {
        this->m_hEvent = RtOpenEvent(EVENT_ALL_ACCESS, FALSE, this->m_wstrName.c_str());
        if(this->m_hEvent == NULL) {
            _D_Msg(_D_CantOpen, "DEvent", "Event", this->m_wstrName.c_str());       
        return FALSE;
        }
        else _D_Msg(_D_Open, "DEvent", "Event", this->m_wstrName.c_str());
        return TRUE;
    }
    inline bool fnbOpen(int nOpenTryTimes) {
        for(int i = 0; i < nOpenTryTimes; i++) {
            if(this->fnbOpen()) return TRUE;
        }
        return FALSE;
    }
    inline bool fnbSet() {
        if(++this->m_nCountNum >= this->m_nMaxNum) {
            this->m_nCountNum = 0;
            RtSetEvent(this->m_hEvent);
            return TRUE;
        }
        return FALSE;
    }
    inline bool fnbReset() { // reset the event along with the counting
        this->m_nCountNum = 0;
        return (RtResetEvent(this->m_hEvent));
    }
    inline bool fnbWait() {
        return(fnbWait(INFINITE));
    }
    inline bool fnbWait(DWORD dwWaitTimeMs ) {
        RtWaitForSingleObject(this->m_hEvent, dwWaitTimeMs);
        this->fnbReset();
        return TRUE;
    }
    inline bool fnbClose() {
        if(this->m_hEvent != NULL) RtCloseHandle(this->m_hEvent);
        return TRUE;
    }
};

_D_WIN_RTX_TOOLS_END

#endif