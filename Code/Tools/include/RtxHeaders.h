#pragma once
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

#ifdef _USE_RTX
#include <rtapi.h>
#define ResetEvent              RtResetEvent  
#define SetEvent                RtSetEvent    
#define WaitForSingleObject     RtWaitForSingleObject 
#define CloseHandle             RtCloseHandle   
#define ReleaseMutex            RtReleaseMutex      
#define SetThreadPriority       RtSetThreadPriority 
#endif

#define _D_WIN_RTX_TOOLS_BEGIN namespace Dcc { namespace WIN_RTX_TOOLS {
#define _D_WIN_RTX_TOOLS_END }}
#define _D_WRT ::Dcc::WIN_RTX_TOOLS::

#endif
