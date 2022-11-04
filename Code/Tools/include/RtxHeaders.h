#pragma once
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

#ifdef _USE_RTX
#include <rtapi.h>
#else
#define RtCreateEvent               CreateEvent
#define RtOpenEvent                 OpenEvent
#define RtResetEvent                ResetEvent  
#define RtSetEvent                  SetEvent      
#define RtCreateThread              CreateThread
#define RtResumeThread              ResumeThread
#define RtSetThreadPriority         SetThreadPriority 
#define RtGetProcessAffinityMask    GetProcessAffinityMask
#define RtCreateMutex               CreateMutex
#define RtOpenMutex                 OpenMutex
#define RtReleaseMutex              ReleaseMutex      
#define RtWaitForSingleObject       WaitForSingleObject 
#define RtCreateSemaphore           CreateSemaphore
#define RtOpenSemaphore             OpenSemaphore 
#define RtCloseHandle               CloseHandle   
#endif

#define _MaxStrLen                  60

#define _D_Create                   433001
#define _D_CantCreate               433002
#define _D_Open                     433003
#define _D_CantOpen                 433004
#define _D_Exist                    433005

inline void fnvSendMsg(int nIssueIndex, const CHAR * wcptBelongs, const CHAR * wcptObject, const WCHAR * wcptName) {
    printf_s("%s", wcptBelongs);
    switch(nIssueIndex) {
        case _D_Create:     _STD cout << ": Created! "              ; break;
        case _D_CantCreate: _STD cout << ": Error! Can't created "  ; break;
        case _D_Open:       _STD cout << ": opened! "               ; break;
        case _D_CantOpen:   _STD cout << ": Error! Can't open "     ; break;
        case _D_Exist:      _STD cout << ": Already exist! "        ; break; 
    }
    printf_s("%s ", wcptObject);
    _STD cout << "Named <";
    wprintf_s(L"%s", wcptName);
    _STD cout << ">" << _STD endl;
}

#define _D_Msg(IssusIndex, Belongs, Object, Name) fnvSendMsg(IssusIndex, Belongs, Object, Name)
#define _D_WIN_RTX_TOOLS_BEGIN namespace Dcc { namespace WIN_RTX_TOOLS {
#define _D_WIN_RTX_TOOLS_END }}
#define _D_WRT ::Dcc::WIN_RTX_TOOLS::

#endif
