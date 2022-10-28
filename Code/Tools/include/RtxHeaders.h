#pragma once
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

#ifdef _USE_RTX
#include <rtapi.h>
#define CreateEvent             RtCreateEvent
#define OpenEvent               RtOpenEvent
#define ResetEvent              RtResetEvent  
#define SetEvent                RtSetEvent      
#define SetThreadPriority       RtSetThreadPriority 
#define CreateMutex             RtCreateMutex
#define OpenMutex               RtOpenMutex
#define ReleaseMutex            RtReleaseMutex      
#define WaitForSingleObject     RtWaitForSingleObject 
#define CreateSemaphore         RtCreateSemaphore
#define OpenSemaphore           RtOpenSemaphore 
#define CloseHandle             RtCloseHandle   
#endif

#define _D_WIN_RTX_TOOLS_BEGIN namespace Dcc { namespace WIN_RTX_TOOLS {
#define _D_WIN_RTX_TOOLS_END }}
#define _D_WRT ::Dcc::WIN_RTX_TOOLS::

#endif
