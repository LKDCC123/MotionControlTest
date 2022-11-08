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
    c_RtxCEvent m_cComEngineReady;
    c_RtxCEvent m_cComRequest;
    c_RtxCEvent m_cComFinished;
    DWORD m_wdWaitTimeMs;
    int m_nComRunFlag;
    int m_nAsynCyc;
    int m_nCurrentCyc;
public:
    inline ctm_RtxMultiPC(const WCHAR * wcptName):ctm_RtxIPC<tm_DataIO>(wcptName) {
        this->m_wstrName = wcptName;
        wcscpy_s(this->m_wcComEngineReadyName, wcptName);   wcscat_s(this->m_wcComEngineReadyName, L"_Ready");  m_cComEngineReady.fnbSetName(this->m_wcComEngineReadyName);
        wcscpy_s(this->m_wcComRequestName, wcptName);       wcscat_s(this->m_wcComRequestName, L"_Request");    m_cComRequest.fnbSetName(this->m_wcComRequestName);
        wcscpy_s(this->m_wcComFinishedName, wcptName);      wcscat_s(this->m_wcComFinishedName, L"_Finished");  m_cComFinished.fnbSetName(this->m_wcComFinishedName);
        this->m_hComEngineReady = this->m_hComRequest = this->m_hComFinished = this->m_hThread = NULL;
        this->m_nComRunFlag = FALSE;
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
    inline bool fnbSetRunFlag(bool bSetFlag) {
        return this->m_nComRunFlag = bSetFlag;
    }
    inline bool fnbGetRunFlag() {
        return this->m_nComRunFlag;
    }
    inline bool fnbSendComputeData() {
        return (this->_IPC fnbSendData(this->m_tmptDataIO));
    }
    inline bool fnbGetComputeData() {
        return (this->_IPC fnbGetData(this->m_tmptDataIO));
    }
    // used in request thread
    inline bool fnbInitRequest(tmpt_DataIO tmptDataIO) { // used in Rtx or Win to push a request for a synchronous or an asynchronous computation thread in Win, nAsynCyc is the asynchronous cycle
        this->fnbInitIOPointer(tmptDataIO);
        this->fnbSetWaitTime(1);
        this->fnbSetAsynCyc(1);
        this->m_nCurrentCyc = 0;
        if (this->m_cComEngineReady.fnbCreate()     &&  // create the event of engine ready 
            this->m_cComRequest.fnbCreate()         &&  // create the event of compute request 
            this->m_cComFinished.fnbCreate()        &&  // create the event of compute finished
            this->_IPC fnbCreate()) {                   // create the IPC interface for send & receive data
            _D_Msg(_D_Create, "DMultiPC", "Computing Engine", this->m_wstrName.c_str());
            return TRUE;
        }
        return FALSE;
    }
    inline bool fnbSetAsynCyc(int nAsynCyc) { // default: 1
        this->m_nAsynCyc = nAsynCyc;
        return TRUE;
    }
    inline bool fnbSetWaitTime(DWORD wdWaitTimeMs) { // default: 1000 Ms
        this->m_wdWaitTimeMs = wdWaitTimeMs;
        return TRUE;
    }
    inline bool fnbComputeRequest() {
        if(this->m_cComEngineReady.fnbSwichOn(this->m_wdWaitTimeMs)) { // if the computing engine is ready
            if(this->m_nCurrentCyc == 0) { // the first cycle
                this->fnbSendComputeData(); // send data to the sharedmemory
                this->m_cComRequest.fnbSet(); // set event of computing request
                return TRUE;
            }
        }
        return FALSE;
    }
    inline bool fnbComputeRecieve() {
        if(++this->m_nCurrentCyc >= this->m_nAsynCyc) { // the last cycle that need to recieve computing result
            this->m_nCurrentCyc = 0; // reset the cycle
            if(this->m_cComFinished.fnbWait(this->m_wdWaitTimeMs)) { // if the computation is finished
                this->fnbGetComputeData(); // get data from the sharedmemory
                return TRUE;
            }
            _STD cout << "Fail to recieve result!" << _STD endl; 
        }
        return FALSE;
    }
    inline bool fnbComputeEngine() { // use this when no other computing tasks is needed simutaneously in the request thread
        this->fnbComputeRequest();
        return(this->fnbComputeRecieve());
    }
    // used in engine thread
    inline bool fnbInitEngine(t_fptvCallBack fptvCallBack, tmpt_DataIO tmptDataIO) { // used in Win to initiate the computing engine
        this->fnbInitIOPointer(tmptDataIO);
        this->fnbInitFunPointer(fptvCallBack);
        m_hThread = RtCreateThread( // create the thread
            NULL,
            0,
            (LPTHREAD_START_ROUTINE)ftmulCallBackMultiCom<tm_DataIO>,   // the callback function
            LPVOID(this),                                               // input is the pointer of the class ctm_RtxCThread, but in the type of LPVOID
            CREATE_SUSPENDED,                                           // does not start the thread the first time
            NULL                                                        // thread id is negleted
        );
        fnbSetProcessPriority(REALTIME_PRIORITY_CLASS);
        if (this->m_cComEngineReady.fnbOpen(5)        &&  // open the event of engine ready 
            this->m_cComRequest.fnbOpen(5)            &&  // open the event of compute request 
            this->m_cComFinished.fnbOpen(5)           &&  // open the event of compute finished
            this->_IPC fnbOpen()) {                      // open the IPC interface for send & receive data
            _D_Msg(_D_Open, "DMultiPC", "Computing Engine", this->m_wstrName.c_str());
            return TRUE;
        }
        return FALSE;
    }
    inline bool fnbSetProcessPriority(DWORD dwPriorityClass) { // default: real time priority
        HANDLE hCurrentProcess = GetCurrentProcess(); // get the handle of the current process
        SetPriorityClass(hCurrentProcess, dwPriorityClass); 
        SleepEx(10, FALSE); // not sleep when suspended
        SetProcessPriorityBoost(hCurrentProcess, TRUE);
        SleepEx(10, FALSE);
        return TRUE;
    }
    inline bool fnbRunCompute() {
        this->m_fptvCallBack(this->m_tmptDataIO);
        return TRUE;
    }
    inline bool fnbStartEngine() {
        return (RtResumeThread(this->m_hThread));
    }
    inline bool fnbComputeEngineReady() {
        return (this->m_cComEngineReady.fnbSet());
    }
    inline bool fnbWaitRequest() {
        return (this->m_cComRequest.fnbWait(this->m_wdWaitTimeMs));
    }
    inline bool fnbComputeFinished() {
        return (this->m_cComFinished.fnbSet());
    }
};

// callback function
template<typename tm_DataIO>
DWORD WINAPI ftmulCallBackMultiCom(LPVOID lpt) { // input is a pointer to class ctm_RtxCThread
    if(lpt == NULL) {
        _STD cout << "DMultiPC: Wrong callback function!" << _STD endl;
        return -1;
    }
    auto cptCMultiPC = (ctm_RtxMultiPC<tm_DataIO> *)lpt; // translate the type of lpt to the class ctm_RtxMultiPC
    cptCMultiPC->fnbSetRunFlag(TRUE);
    cptCMultiPC->fnbComputeEngineReady(); // set event of computing engine is ready
    while(cptCMultiPC->fnbGetRunFlag()) { // if keeps running the computation
        if(cptCMultiPC->fnbWaitRequest()) { // if get computing request
            cptCMultiPC->fnbGetComputeData(); // get data from the sharedmemory
            cptCMultiPC->fnbRunCompute(); // run computation
            cptCMultiPC->fnbSendComputeData(); // send data to the sharedmemory
            cptCMultiPC->fnbComputeFinished(); // set event of computing finished
        }
    }
    INFINITE;
    _STD cout << "DMultiPC: Quit!" << _STD endl;
    return 0; 
}

_D_WIN_RTX_TOOLS_END

#endif
