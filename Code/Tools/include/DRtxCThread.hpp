// DRtxCThread.hpp
// make a new thread into a new class
// based on Rtx class: Thread
// based on Lee's RtxCThread.hpp
// 20221027 bit, Dcc <3120195094@bit.edu.cn>

#pragma once
#ifndef DRTXCTHREAD_HPP
#define DRTXCTHREAD_HPP
#include <bitset>
#include "RtxHeaders.h"

_D_WIN_RTX_TOOLS_BEGIN

template<typename tm_DataIO>
DWORD WINAPI ftmulCallBack(LPVOID lpt);

template<typename tm_DataIO> // define typename: tm_DataIO
class ctm_RtxCThread {
    typedef void(*t_fptvCallBack)(tm_DataIO *);
private:
    t_fptvCallBack m_fptvCallBack;  // function pointer of the target funtion
    tm_DataIO * m_tmptDataIO;           // input data of the target function
    HANDLE m_hThread;               // handle of the thread
    int m_nRunFlag;                 // if the thread is running
    inline bool fnbInitIOPointer(tm_DataIO * tmptDataIO = NULL) { // point the input data to the members
        this->m_tmptDataIO = tmptDataIO;
        return TRUE;
    }
    inline bool fnbInitFunPointer(t_fptvCallBack fptvCallBack = NULL) { // point the target function pointer to the members
        this->m_fptvCallBack = fptvCallBack;
        return TRUE;
    }
public:
    ctm_RtxCThread(tm_DataIO * tmptDataIO); 
    ~ctm_RtxCThread();
    bool fnbCreate(t_fptvCallBack fptvCallBack); // create the thread and start it 
    bool fnbCreate(t_fptvCallBack fptvCallBack, int nStartFlag); // create the thread and set the target function of the process which is going to run in the thread
    bool fnbSetProcessPriority(); // set as the highest priority
    bool fnbSetProcessPriority(DWORD dwPriorityClass); // set as the highest priority
    bool fnbGetAvailableProcessor(); // get the total processor number of the computer and the mask of the available processor
    bool fnbSetThreadProcessor(DWORD dwIdealProcessor); // set the ideal processor of the thread
    bool fnbStart(); // start the thread
    bool fnbPause(); // pause the thread
    bool fnbClose(); // close the thread
    inline bool fnbRun() { // run the target function in the callback
        this->m_fptvCallBack(this->m_tmptDataIO);
        return TRUE;
    }
};

template<typename tm_DataIO>
ctm_RtxCThread<tm_DataIO>::ctm_RtxCThread(tm_DataIO * tmptDataIO) {
    this->fnbInitIOPointer(tmptDataIO); // init the pointers in the members
    this->m_nRunFlag = FALSE;
    this->m_hThread = NULL;
}

template<typename tm_DataIO>
ctm_RtxCThread<tm_DataIO>::~ctm_RtxCThread() {
    this->fnbClose(); // close the thread
    Sleep(100);
    if(this->m_hThread != NULL) RtCloseHandle(this->m_hThread); // close the handle
}

template<typename tm_DataIO>
bool ctm_RtxCThread<tm_DataIO>::fnbCreate(t_fptvCallBack fptvCallBack) {
    return (this->fnbCreate(fptvCallBack, TRUE));
}

template<typename tm_DataIO>
bool ctm_RtxCThread<tm_DataIO>::fnbCreate(t_fptvCallBack fptvCallBack, int nStartFlag) {
    fnbInitFunPointer(fptvCallBack);
    m_hThread = RtCreateThread( // create the thread
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)ftmulCallBack<tm_DataIO>,       // the callback function
        LPVOID(this),       // input is the pointer of the class ctm_RtxCThread, but in the type of LPVOID
        CREATE_SUSPENDED,   // does not start the thread the first time
        NULL                // thread id is negleted
    );
    _STD cout << "DThread: Created! Handle = " << this->m_hThread << _STD endl;
    if(nStartFlag == TRUE) this->fnbStart();
    return TRUE;
}

template<typename tm_DataIO>
bool ctm_RtxCThread<tm_DataIO>::fnbSetProcessPriority() {
    return(this->fnbSetProcessPriority(REALTIME_PRIORITY_CLASS));
}

template<typename tm_DataIO>
bool ctm_RtxCThread<tm_DataIO>::fnbSetProcessPriority(DWORD dwPriorityClass) {
    HANDLE hCurrentProcess = RtGetCurrentProcess(); // get the handle of the current process
    RtSetPriorityClass(hCurrentProcess, dwPriorityClass); 
    SleepEx(10, FALSE); // not sleep when suspended
    RtSetProcessPriorityBoost(hCurrentProcess, TRUE);
    SleepEx(10, FALSE);
    return TRUE;
}

template<typename tm_DataIO>
bool ctm_RtxCThread<tm_DataIO>::fnbGetAvailableProcessor() {
    _SYSTEM_INFO stInfo;
    GetSystemInfo(&stInfo);
    HANDLE hCurrentProcess = GetCurrentProcess(); // get the handle of the current process
    long long dwProcessMask, dwSystemMask;
    RtGetProcessAffinityMask(hCurrentProcess, (PDWORD_PTR)&dwProcessMask, (PDWORD_PTR)&dwSystemMask);
    _STD cout << "DThread: Processor number = " << stInfo.dwNumberOfProcessors << _STD endl;
    _STD cout << "\tProcess affinity mask = " << _STD bitset<sizeof(int)*8>(dwProcessMask) << _STD endl << "\tSystem affinity mask = " << _STD bitset<sizeof(int)*8>(dwSystemMask) << _STD endl;
    return TRUE;
}

template<typename tm_DataIO>
bool ctm_RtxCThread<tm_DataIO>::fnbSetThreadProcessor(DWORD dwIdealProcessor) {
    if(RtSetThreadIdealProcessor(this->m_hThread, dwIdealProcessor) == -1) return FALSE;
    else return TRUE;
}

template<typename tm_DataIO>
bool ctm_RtxCThread<tm_DataIO>::fnbStart() {
    this->m_nRunFlag = TRUE;
    RtResumeThread(this->m_hThread);
    return TRUE;
}

template<typename tm_DataIO>
bool ctm_RtxCThread<tm_DataIO>::fnbPause() {
    this->m_nRunFlag = FALSE;
    RtSuspendThread(this->m_hThread);
    return TRUE;
}

template<typename tm_DataIO>
bool ctm_RtxCThread<tm_DataIO>::fnbClose() {
    this->m_nRunFlag = FALSE;
    if(this->m_hThread != NULL) RtCloseHandle(this->m_hThread);
    return TRUE;
}

// callback function
template<typename tm_DataIO>
DWORD WINAPI ftmulCallBack(LPVOID lpt) { // input is a pointer to class ctm_RtxCThread
    if(lpt == NULL) {
        _STD cout << "DThread: Wrong callback function!" << _STD endl;
        return -1;
    }
    auto cptCThread = (ctm_RtxCThread<tm_DataIO> *)lpt; // translate the type of lpt to the class ctm_RtxCThread
    cptCThread->fnbRun(); // run the target function in the callback function
    _STD cout << "DThread: Quit!" << _STD endl;
    return 0;
}

_D_WIN_RTX_TOOLS_END

#endif