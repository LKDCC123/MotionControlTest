// DRtxCThread.hpp
// make a new thread into a new class
// bases on Rtx class: Thread
// based on Lee's RtxCThread.hpp
// 20221027 bit, Dcc <3120195094@bit.edu.cn>

#pragma once
#ifndef DRTXCTHREAD_HPP
#define DRTXCTHREAD_HPP
#include <bitset>
#include "RtxHeaders.h"

_D_WIN_RTX_TOOLS_BEGIN

template<typename tm_InputData>
DWORD WINAPI ftmulCallBack(LPVOID lpt);

template<typename tm_InputData> // define typename: tm_InputData
class ctm_RtxCThread {
    typedef void(*t_fptvCallBack)(tm_InputData *);
private:
    t_fptvCallBack m_fptvCallBack;  // function pointer of the target funtion
    tm_InputData * m_dptDataIn;           // input data of the target function
    HANDLE m_hThread;               // handle of the thread
    int m_nRunFlag;                 // if the thread is running
    inline bool fnbInitIOPointer(t_fptvCallBack fptvCallBack = NULL, tm_InputData * dptDataIn = NULL) { // point the target function pointer and the input data to the members
        m_fptvCallBack = fptvCallBack, m_dptDataIn = dptDataIn;
        return TRUE;
    }
public:
    ctm_RtxCThread(t_fptvCallBack fptvCallBack, tm_InputData * dptDataIn); 
    ~ctm_RtxCThread();
    bool fnbCreateThread(); // create the thread and start it 
    bool fnbCreateThread(int nStartFlag); // create the thread
    bool fnbSetProcessPriority(); // set as the highest priority
    bool fnbSetProcessPriority(DWORD dwPriorityClass); // set as the highest priority
    bool fnbGetAvailableProcessor(); // get the total processor number of the computer and the mask of the available processor
    bool fnbSetThreadProcessor(DWORD dwIdealProcessor); // set the ideal processor of the thread
    bool fnbStartThread(); // start the thread
    bool fnbPauseThread(); // pause the thread
    bool fnbCloseThread(); // close the thread
    inline bool fnbRun() { // run the target function in the callback
        this->m_fptvCallBack(this->m_dptDataIn);
        return TRUE;
    }
};

template<typename tm_InputData>
ctm_RtxCThread<tm_InputData>::ctm_RtxCThread(t_fptvCallBack fptvCallBack, tm_InputData * dptDataIn) {
    this->fnbInitIOPointer(fptvCallBack, dptDataIn); // init the pointers in the members
    this->m_nRunFlag = FALSE;
    this->m_hThread = NULL;
}

template<typename tm_InputData>
ctm_RtxCThread<tm_InputData>::~ctm_RtxCThread() {
    this->fnbCloseThread(); // close the thread
    Sleep(100);
    if(this->m_hThread != NULL) CloseHandle(this->m_hThread); // close the handle
}

template<typename tm_InputData>
bool ctm_RtxCThread<tm_InputData>::fnbCreateThread() {
    return (this->fnbCreateThread(TRUE));
}

template<typename tm_InputData>
bool ctm_RtxCThread<tm_InputData>::fnbCreateThread(int nStartFlag) {
    m_hThread = CreateThread( // create the thread
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)ftmulCallBack<tm_InputData>,       // the callback function
        LPVOID(this),       // input is the pointer of the class ctm_RtxCThread, but in the type of LPVOID
        CREATE_SUSPENDED,   // does not start the thread the first time
        NULL                // thread id is negleted
    );
    _STD cout << "DThread: Created! Handle = " << this->m_hThread << _STD endl;
    if(nStartFlag == TRUE) this->fnbStartThread();
    return TRUE;
}

template<typename tm_InputData>
bool ctm_RtxCThread<tm_InputData>::fnbSetProcessPriority() {
    return(this->fnbSetProcessPriority(REALTIME_PRIORITY_CLASS));
}

template<typename tm_InputData>
bool ctm_RtxCThread<tm_InputData>::fnbSetProcessPriority(DWORD dwPriorityClass) {
    HANDLE hCurrentProcess = GetCurrentProcess(); // get the handle of the current process
    SetPriorityClass(hCurrentProcess, dwPriorityClass); 
    SleepEx(10, FALSE); // not sleep when suspended
    SetProcessPriorityBoost(hCurrentProcess, TRUE);
    SleepEx(10, FALSE);
    return TRUE;
}

template<typename tm_InputData>
bool ctm_RtxCThread<tm_InputData>::fnbGetAvailableProcessor() {
    _SYSTEM_INFO stInfo;
    GetSystemInfo(&stInfo);
    HANDLE hCurrentProcess = GetCurrentProcess(); // get the handle of the current process
    long long dwProcessMask, dwSystemMask;
    GetProcessAffinityMask(hCurrentProcess, (PDWORD_PTR)&dwProcessMask, (PDWORD_PTR)&dwSystemMask);
    _STD cout << "DThread: Processor number = " << stInfo.dwNumberOfProcessors << _STD endl;
    _STD cout << "\tProcess affinity mask = " << _STD bitset<sizeof(int)*8>(dwProcessMask) << _STD endl << "\tSystem affinity mask = " << _STD bitset<sizeof(int)*8>(dwSystemMask) << _STD endl;
    return TRUE;
}

template<typename tm_InputData>
bool ctm_RtxCThread<tm_InputData>::fnbSetThreadProcessor(DWORD dwIdealProcessor) {
    if(SetThreadIdealProcessor(this->m_hThread, dwIdealProcessor) == -1) return FALSE;
    else return TRUE;
}

template<typename tm_InputData>
bool ctm_RtxCThread<tm_InputData>::fnbStartThread() {
    this->m_nRunFlag = TRUE;
    ResumeThread(this->m_hThread);
    return TRUE;
}

template<typename tm_InputData>
bool ctm_RtxCThread<tm_InputData>::fnbPauseThread() {
    this->m_nRunFlag = FALSE;
    SuspendThread(this->m_hThread);
    return TRUE;
}

template<typename tm_InputData>
bool ctm_RtxCThread<tm_InputData>::fnbCloseThread() {
    this->m_nRunFlag = FALSE;
    CloseHandle(this->m_hThread);
    return TRUE;
}

// callback function
template<typename tm_InputData>
DWORD WINAPI ftmulCallBack(LPVOID lpt) { // input is a pointer to class ctm_RtxCThread
    if(lpt == NULL) {
        _STD cout << "DThread: Wrong callback function!" << _STD endl;
        return -1;
    }
    auto cptCThread = (ctm_RtxCThread<tm_InputData> *)lpt; // translate the type of lpt to the class ctm_RtxCThread
    cptCThread->fnbRun(); // run the target function in the callback function
    _STD cout << "DThread: Quit!" << _STD endl;
    return 0;
}

_D_WIN_RTX_TOOLS_END

#endif