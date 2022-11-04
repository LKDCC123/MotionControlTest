// DRtxMultiProcCompute.hpp
// create a computing thread synchronously or asynchronously
// the code is in two parts: the request (the main thread of Rtx or Win), the engine (the computing tread)
// based on Dcc Win Rtx64 Tool class: ctm_RtxCThread, ctm_RtxIPC, c_RtxCEvent
// refering to Lee's RtxCNRTComputingEngine.hpp
// 20221104 bit, Dcc <3120195094@bit.edu.cn>

#pragma once
#ifndef DRTXMULTIPROCCOMPUTE_HPP
#define DRTXMULTIPROCCOMPUTE_HPP
#include "RtxHeaders.h"
#include "DRtxCEvent.hpp"

_D_WIN_RTX_TOOLS_BEGIN

#define _IPC        ctm_RtxIPC<tm_DataIO>::

template<typename tm_DataIO>
class ctm_RtxMultiPC:protected ctm_RtxIPC<tm_DataIO> {
    typedef tm_DataIO * tmpt_DataIO;
    typedef void(*t_fptvCallBack)(tmpt_DataIO);
private:
    _STD wstring m_wstrName;
    t_fptvCallBack m_fptvCallBack;
    tmpt_DataIO m_tmptDataIO;
    HANDLE m_hThread;
    HANDLE m_hComEngineReady;                   // the event handle of the readily prepared of the computing engine in Win, given from the engine and recieve by the request
    HANDLE m_hComRequest;                       // the event handle of the request of the computing, given from the request and recieved by the engine
    HANDLE m_hComFinished;                      // the event handle of the finish of the computing in the engine, given from the engine and recieved bythe request
    WCHAR m_wcComEngineReadyName[_MaxStrLen];
    WCHAR m_wcComRequestName[_MaxStrLen];
    WCHAR m_wcComFinishedName[_MaxStrLen];
    c_RtxCEvent * m_cptComEngineReady;
    c_RtxCEvent * m_cptComRequest;
    c_RtxCEvent * m_cptComFinished;
    DWORD m_wdWaitTimeMs;
public:
    inline ctm_RtxMultiPC(const WCHAR * wcptName):ctm_RtxIPC<tm_DataIO>(wcptName) {
        this->m_wstrName = wcptName;
        wcscpy_s(this->m_wcComEngineReadyName, wcptName);   wcscat_s(this->m_wcComEngineReadyName, L"_Event.Ready");
        wcscpy_s(this->m_wcComRequestName, wcptName);       wcscat_s(this->m_wcComRequestName, L"_Event.Request");
        wcscpy_s(this->m_wcComFinishedName, wcptName);      wcscat_s(this->m_wcComFinishedName, L"_Event.Finished");
        this->m_hComEngineReady = this->m_hComRequest = this->m_hComFinished = this->m_hThread = NULL;
    }
    inline ~ctm_RtxMultiPC() {
        
    }
    inline bool fnbInitIOPointer(tmpt_DataIO tmptDataIO = NULL) { // point the input data to the members
        this->m_tmptDataIO = tmptDataIO;
        return TRUE;
    }
    inline bool fnbInitFunPointer(t_fptvCallBack fptvCallBack = NULL) { // point the target function pointer to the members
        this->m_fptvCallBack = fptvCallBack;
        return TRUE;
    }
    inline bool fnbInitEvents() {
        c_RtxCEvent cComEngineReady(this->m_wcComEngineReadyName);  this->m_cptComEngineReady = &cComEngineReady;
        c_RtxCEvent cComRequest(this->m_wcComRequestName);          this->m_cptComRequest = &cComRequest;
        c_RtxCEvent cComFinished(this->m_wcComFinishedName);        this->m_cptComFinished = &cComFinished;
        return TRUE;
    }
    // used in request thread
    inline bool fnbSetProcessPriority() {
        HANDLE hCurrentProcess = GetCurrentProcess(); // get the handle of the current process
        SetPriorityClass(hCurrentProcess, REALTIME_PRIORITY_CLASS); 
        SleepEx(10, FALSE); // not sleep when suspended
        SetProcessPriorityBoost(hCurrentProcess, TRUE);
        SleepEx(10, FALSE);
        return TRUE;
    }
    inline bool fnbInitRequest(int nAsynCyc, tmpt_DataIO tmptDataIO) { // used in Rtx or Win to push a request for a synchronous or an asynchronous computation thread in Win, nAsynCyc is the asynchronous cycle
        this->fnbInitIOPointer(tmptDataIO);
        this->fnbInitEvents();
        this->fnbSetWaitTime(1000);
        _STD cout << "DMultiPC: Created! Handle = " << this->m_hThread << _STD endl;
        return (this->m_cptComEngineReady->fnbCreate()      &&  // create the event of engine ready 
                this->m_cptComRequest->fnbCreate(nAsynCyc)  &&  // create the event of compute request 
                this->m_cptComFinished->fnbCreate()         &&  // create the event of compute finished
                this->_IPC fnbCreate());                        // create the IPC interface for send & receive data
    }
    inline bool fnbSetWaitTime(DWORD wdWaitTimeMs) { // default: 1000 Ms
        this->m_wdWaitTimeMs = wdWaitTimeMs;
    }
    inline bool fnbComputeRequest() {
        if(this->m_cptComEngineReady->fnbWait(this->m_wdWaitTimeMs)) { // check the engine thread if be started

        }
    }
    // used in engine thread
    inline bool fnbInitEngine(t_fptvCallBack fptvCallBack, tmpt_DataIO tmptDataIO) { // used in Win to initiate the computing engine
        this->fnbInitIOPointer(tmptDataIO);
        this->fnbInitFunPointer(fptvCallBack);
        this->fnbInitEvents(); 
        m_hThread = RtCreateThread( // create the thread
            NULL,
            0,
            (LPTHREAD_START_ROUTINE)ftmulCallBackMultiCom<tm_DataIO>,   // the callback function
            LPVOID(this),                                               // input is the pointer of the class ctm_RtxCThread, but in the type of LPVOID
            CREATE_SUSPENDED,                                           // does not start the thread the first time
            NULL                                                        // thread id is negleted
        );
        fnbSetProcessPriority();
        return (this->m_cptComEngineReady->fnbOpen()        &&  // open the event of engine ready 
                this->m_cptComRequest->fnbOpen()            &&  // open the event of compute request 
                this->m_cptComFinished->fnbOpen()           &&  // open the event of compute finished
                this->_IPC fnbOpen());                          // open the IPC interface for send & receive data
    }
    inline bool fnbRunCompute() {
        this->fptvCallBack(this->tmptDataIO);
    }
    inline bool fnbStart() {
        RtResumeThread(this->m_hThread);
    }
    
};

// callback function
template<typename tm_DataIO>
DWORD WINAPI ftmulCallBackMultiCom(LPVOID lpt) { // input is a pointer to class ctm_RtxCThread
    if(lpt == NULL) {
        _STD cout << "DThread: Wrong callback function!" << _STD endl;
        return -1;
    }
    auto cptCMultiPC = (ctm_RtxMultiPC<tm_DataIO> *)lpt; // translate the type of lpt to the class ctm_RtxCThread
    cptCMultiPC->m_cptComEngineReady->fnbSet();
    _STD cout << "DThread: Quit!" << _STD endl;
    return 0;
}

_D_WIN_RTX_TOOLS_END

#endif
