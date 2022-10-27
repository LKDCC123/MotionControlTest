// based on Lee's RtxCThread.hpp
// creat thread in Rtx bases on Rtx class: Thread
// make a new thread into a new class
// 20221027 Dcc <3120195094@bit.edu.cn>

#pragma once
#ifndef DRTXCTHREAD_HPP
#define DRTXCTHREAD_HPP
#include <RtxHeaders.h>
#include <bitset>

_D_WIN_RTX_TOOLS_BEGIN

DWORD WINAPI fnulCallBack(LPVOID lpt);

class RtxCThread {
    typedef void(*t_fptvCallBack)(double *);
private:
    t_fptvCallBack m_fptvCallBack;  // function pointer of the target funtion
    double * m_dptDataIn;           // input data of the target function
    HANDLE m_hThread;               // handle of the thread
    int m_nRunFlag;                 // if the thread is running
    inline bool fnbInitIOPointer(t_fptvCallBack fptvCallBack = NULL, double * dptDataIn = NULL) { // point the target function pointer and the input data to the members
        m_fptvCallBack = fptvCallBack, m_dptDataIn = dptDataIn;
        return TRUE;
    }
public:
    RtxCThread(t_fptvCallBack fptvCallBack, double * dptDataIn); 
    ~RtxCThread();
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

RtxCThread::RtxCThread(t_fptvCallBack fptvCallBack = NULL, double * dptDataIn = NULL) {
    this->fnbInitIOPointer(fptvCallBack, dptDataIn); // init the pointers in the members
    this->m_nRunFlag = FALSE;
    this->m_hThread = NULL;
}

RtxCThread::~RtxCThread() {
    this->fnbCloseThread(); // close the thread
    Sleep(100);
    if(this->m_hThread != NULL) CloseHandle(this->m_hThread); // close the handle
}

bool RtxCThread::fnbCreateThread() {
    return (this->fnbCreateThread(TRUE));
}

bool RtxCThread::fnbCreateThread(int nStartFlag) {
    m_hThread = CreateThread( // create the thread
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)fnulCallBack,       // the callback function
        LPVOID(this),       // input is the pointer of the class RtxCThread, but in the type of LPVOID
        CREATE_SUSPENDED,   // does not start the thread the first time
        NULL                // thread id is negleted
    );
    _STD cout << "DThread: Created! Handle = " << this->m_hThread << _STD endl;
    if(nStartFlag == TRUE) this->fnbStartThread();
    return TRUE;
}

bool RtxCThread::fnbSetProcessPriority() {
    return(this->fnbSetProcessPriority(REALTIME_PRIORITY_CLASS));
}

bool RtxCThread::fnbSetProcessPriority(DWORD dwPriorityClass) {
    HANDLE hCurrentProcess = GetCurrentProcess(); // get the handle of the current process
    SetPriorityClass(hCurrentProcess, dwPriorityClass); 
    SleepEx(10, FALSE); // not sleep when suspended
    SetProcessPriorityBoost(hCurrentProcess, TRUE);
    SleepEx(10, FALSE);
    return TRUE;
}

bool RtxCThread::fnbGetAvailableProcessor() {
    _SYSTEM_INFO stInfo;
    GetSystemInfo(&stInfo);
    HANDLE hCurrentProcess = GetCurrentProcess(); // get the handle of the current process
    long long dwProcessMask, dwSystemMask;
    GetProcessAffinityMask(hCurrentProcess, (PDWORD_PTR)&dwProcessMask, (PDWORD_PTR)&dwSystemMask);
    _STD cout << "DThread: Processor number = " << stInfo.dwNumberOfProcessors << _STD endl;
    _STD cout << "\tProcess affinity mask = " << _STD bitset<sizeof(int)*8>(dwProcessMask) << _STD endl << "\tSystem affinity mask = " << _STD bitset<sizeof(int)*8>(dwSystemMask) << _STD endl;
    return TRUE;
}

bool RtxCThread::fnbSetThreadProcessor(DWORD dwIdealProcessor) {
    if(SetThreadIdealProcessor(this->m_hThread, dwIdealProcessor) == -1) return FALSE;
    else return TRUE;
}

bool RtxCThread::fnbStartThread() {
    this->m_nRunFlag = TRUE;
    ResumeThread(this->m_hThread);
    return TRUE;
}

bool RtxCThread::fnbPauseThread() {
    this->m_nRunFlag = FALSE;
    SuspendThread(this->m_hThread);
    return TRUE;
}

bool RtxCThread::fnbCloseThread() {
    this->m_nRunFlag = FALSE;
    CloseHandle(this->m_hThread);
    return TRUE;
}

// callback function
DWORD WINAPI fnulCallBack(LPVOID lpt) { // input is a pointer to class RtxCThread
    if(lpt == NULL) {
        _STD cout << "DThread: Wrong callback function!" << _STD endl;
        return -1;
    }
    auto cptCThread = (RtxCThread *)lpt; // translate the type of lpt to the class RtxCThread
    cptCThread->fnbRun(); // run the target function in the callback function
    _STD cout << "DThread: Quit!" << _STD endl;
    return 0;
}

_D_WIN_RTX_TOOLS_END

#endif