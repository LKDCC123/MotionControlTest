///////////////////////////////////////////////////////////////////////////////
//
//
//			Copyright (c) 2011 IntervalZero, Inc.  All rights reserved.
//
//
//File: RtssApi.h
//
//Abstract:
//
//		This file defines the functions which only RTSS applications can use.
//	RTSS applications can use a superset of the RtApi functionality.  The total
//  RTSS API is declared in RtApi.h and RtssApi.h.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _RTSSAPI_H_
#define _RTSSAPI_H_

#ifndef RTAPI
# define RTAPI
#endif

#ifndef RTFCNDCL
# define RTFCNDCL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "Licensing.h"

///////////////////////////////////////////////////////////////////////////////
//
//Interrupt functions.
//
///////////////////////////////////////////////////////////////////////////////

typedef enum _MSI_CAPABILITY {
    NotMsiMsixCapable,
    MsiCapable,
    MsixCapable,
    MsiMsixCapable
} MSI_CAPABILITY, *PMSI_CAPABILITY;

MSI_CAPABILITY RTAPI RtQueryPciMsiCapability(ULONG BusNumber, PCI_SLOT_NUMBER SlotNumber);


// This enumeration defines control operations to be passed to function RtMonitorControl.
typedef enum _RTX64_MONITOR_CONTROL_OP
{
    // Reserved.  Do not use.
    MONITOR_CONTROL_RESERVED = 0,

    // This operation deterministically starts RTX64 monitoring.  This will succeed only when
    // monitoring is enabled and stopped, otherwise function RtMonitorControl will fail.
    // Parameters "data" and "size" are ignored for this operation.
    MONITOR_CONTROL_START,

    // This operation deterministically stops RTX64 monitoring.  This will succeed only when
    // monitoring is enabled and started, otherwise function RtMonitorControl will fail.
    // Parameters "data" and "size" are ignored for this operation.
    MONITOR_CONTROL_STOP,

    // This operation deterministically enables monitoring events and returns the resulting set of
    // enabled and disabled events.  This can be used to query which events are enabled by
    // specifying no events to be enabled.  Parameter "data" should point to an array of BOOLEANs
    // that has MF_EVENT_KIND_MAX elements, each of which specifies whether or not to enable the
    // event that corresponds to an enumerator in enumeration MF_EVENT_KIND.  If an array element is
    // TRUE, the corresponding event is enabled, otherwise its state remains unchanged.  The indices
    // of the array should be the enumerators in enumeration MF_EVENT_KIND.
    //
    // Parameter "size" is ignored for this operation.
    //
    // If monitoring is not enabled, this operation fails with error ERROR_NOT_READY.
    //
    // When this function returns, the contents of the array pointed to by parameter "data"
    // represents which events are enabled and disabled (TRUE means enabled, FALSE means disabled).
    // NOTE: Any array element passed in as FALSE (meaning "do not enable"), might come back as TRUE
    // (meaning "it was already enabled").
    MONITOR_CONTROL_ENABLE_EVENTS,

    // This operation deterministically disables zero or more monitoring events and returns the
    // resulting set of enabled and disabled events.  This can be used to query which events are
    // enabled by specifying no events to be disabled.  Parameter "data" should point to an array of
    // BOOLEANs that has MF_EVENT_KIND_MAX elements, each of which specifies whether or not to
    // disable the event that corresponds to an enumerator in enumeration MF_EVENT_KIND.  If an array
    // element is TRUE, the corresponding event is disabled, otherwise its state remains unchanged.
    // The indices of the array should be the enumerators in enumeration MF_EVENT_KIND.
    //
    // Parameter "size" is ignored for this operation.
    //
    // If monitoring is not enabled, this operation fails with error ERROR_NOT_READY.
    //
    // When this function returns, the contents of the array pointed to by parameter "data"
    // represents which events are enabled and disabled (TRUE means enabled, FALSE means disabled).
    // NOTE: Any array element passed in as FALSE (meaning "do not disable"), might come back as
    // TRUE (meaning "it was already enabled").
    MONITOR_CONTROL_DISABLE_EVENTS,

    // This operation deterministically sets triggers for monitoring events.  A trigger causes one
    // of a set of pre-defined effects when monitoring is enabled and a given event can be
    // generated, even if that event is disabled.  For instance, if the trigger
    // MF_TRIGGER_START_MONITORING is set for event MF_EVENT_KIND_THREAD_SLEEP, then when that event
    // can be generated (even if that event is disabled), the trigger will cause monitoring to
    // start.
    //
    // Parameter "data" should point to an array of MF_TRIGGERS that contains exactly
    // MF_EVENT_KIND_MAX elements, each of which specifies the triggers to set for the corresponding
    // enumerator in enumeration MF_EVENT_KIND.  NOTE: Each bit that is set in this array represents
    // triggers to be set.  Bits in this array that are zero do not set or reset any triggers.
    //
    // Parameter "size" is ignored for this operation.
    //
    // The following kinds of monitoring events cannot have triggers set on them.  Attempting
    // to do so will cause RtMonitorControl to fail with ERROR_INVALID_PARAMETER.
    //
    //   -- MF_EVENT_KIND_RESERVED (Reserved)
    //   -- MF_EVENT_KIND_BUGCHECK_RTSS_RESERVED (Bugcheck RTSS)
    //   -- MF_EVENT_KIND_MARKER (Marker)
    //   -- MF_EVENT_KIND_SUBSYSTEM_STOP (Subsystem Stop)
    //   -- MF_EVENT_KIND_FAST_SEMAPHORE_ACQUIRE (Fast Semaphore Acquire)
    //   -- MF_EVENT_KIND_FAST_SEMAPHORE_RELEASE (Fast Semaphore Release)
    //   -- MF_EVENT_KIND_FAST_SEMAPHORE_RELEASE_ALL (Fast Semaphore Release All)
    //   -- MF_EVENT_KIND_WFSOEX_WAIT (WaitForSingleObjectEx Wait)
    //   -- MF_EVENT_KIND_WFMOEX_WAIT (WaitForMultipleObjectEx Wait)
    //   -- MF_EVENT_KIND_THREAD_SLEEP (Thread Sleep)
    //
    // This operation can be performed at any time, and its effects remain until the RTX64 subsystem
    // stops, but triggers do nothing unless monitoring is enabled.  Monitoring does not need to be
    // started for triggers to work.
    //
    // When this function returns, the contents of the array pointed to by parameter "data"
    // represents the triggers that are set for each event kind.  NOTE: This operation can only
    // increase the number of triggers that are set.  Use operation
    // MONITOR_CONTROL_RESET_EVENT_TRIGGERS to reset (i.e., turn off) triggers for certain events.
    MONITOR_CONTROL_SET_EVENT_TRIGGERS,

    // This operation deterministically resets (i.e., turns off) triggers for monitoring events.  A
    // trigger causes one of a set of pre-defined effects when monitoring is enabled and a given
    // event can be generated, even if that event is disabled.  For instance, if the trigger
    // MF_TRIGGER_START_MONITORING is set for event MF_EVENT_KIND_THREAD_SLEEP, then when that event
    // can be generated (even if that event is disabled), the trigger will cause monitoring to
    // start.
    //
    // Parameter "data" should point to an array of MF_TRIGGERS that contains exactly
    // MF_EVENT_KIND_MAX elements, each of which specifies the triggers to reset for the
    // corresponding enumerator in enumeration MF_EVENT_KIND.  NOTE: Each bit that is set in this
    // array represents triggers to be _reset_.  Bits in this array that are zero do not set or
    // reset any triggers.
    //
    // Parameter "size" is ignored for this operation.
    //
    // This operation can be performed at any time, and its effects remain until the RTX64 subsystem
    // stops, but triggers do nothing unless monitoring is enabled.  Monitoring does not need to be
    // started for triggers to work.
    //
    // When this function returns, the contents of the array pointed to by parameter "data"
    // represents the triggers that are set for each event kind.  NOTE: This operation can only
    // decrease the number of triggers that are set.  Use operation
    // MONITOR_CONTROL_SET_EVENT_TRIGGERS to set triggers for certain events.
    MONITOR_CONTROL_RESET_EVENT_TRIGGERS,

    // This operation deterministically sets triggers for custom monitoring events.  A trigger
    // causes one of a set of pre-defined effects when monitoring is enabled and a given event can
    // be generated, even if that event is disabled.  For instance, if the trigger
    // MF_TRIGGER_START_MONITORING is set for custom event kind 42, then when that custom event kind
    // can be generated (even if custom events are disabled), the trigger will cause monitoring to
    // start.
    //
    // Parameter "data" should point to an array of MF_TRIGGERS that contains exactly
    // MF_TRIGGERS_FOR_CUSTOM_EVENT_IDS_MAX elements, each of which specifies the triggers to set
    // for the corresponding custom event kind.  NOTE: Each bit that is set in this array represents
    // triggers to be set.  Bits in this array that are zero do not set or reset any triggers.
    //
    // Parameter "size" is ignored for this operation.
    //
    // This operation can be performed at any time, and its effects remain until the RTX64 subsystem
    // stops, but triggers do nothing unless monitoring is enabled.  Monitoring does not need to be
    // started for triggers to work.
    //
    // When this function returns, the contents of the array pointed to by parameter "data"
    // represents the triggers that are set for each custom event kind in the range 0 to
    // MF_TRIGGERS_FOR_CUSTOM_EVENT_IDS_MAX - 1.  NOTE: This operation can only increase the number
    // of triggers that are set.  Use operation MONITOR_CONTROL_RESET_CUSTOM_EVENT_TRIGGERS to
    // reset (i.e., turn off) triggers for certain custom event kinds.
    MONITOR_CONTROL_SET_CUSTOM_EVENT_TRIGGERS,

    // This operation deterministically resets (i.e., turns off) triggers for custom monitoring
    // events.  A trigger causes one of a set of pre-defined effects when monitoring is enabled and
    // a given event can be generated, even if that event is disabled.  For instance, if the trigger
    // MF_TRIGGER_START_MONITORING is set for custom event kind 42, then when that custom event kind
    // can be generated (even if custom events are disabled), the trigger will cause monitoring to
    // start.
    //
    // Parameter "data" should point to an array of MF_TRIGGERS that contains exactly
    // MF_TRIGGERS_FOR_CUSTOM_EVENT_IDS_MAX elements, each of which specifies the triggers to reset
    // for the corresponding custom event kind.  NOTE: Each bit that is set in this array represents
    // triggers to be _reset_.  Bits in this array that are zero do not set or reset any triggers.
    //
    // Parameter "size" is ignored for this operation.
    //
    // This operation can be performed at any time, and its effects remain until the RTX64 subsystem
    // stops, but triggers do nothing unless monitoring is enabled.  Monitoring does not need to be
    // started for triggers to work.
    //
    // When this function returns, the contents of the array pointed to by parameter "data"
    // represents the triggers that are set for each custom event kind in the range 0 to
    // MF_TRIGGERS_FOR_CUSTOM_EVENT_IDS_MAX - 1.  NOTE: This operation can only decrease the number
    // of triggers that are set.  Use operation MONITOR_CONTROL_SET_CUSTOM_EVENT_TRIGGERS to
    // set triggers for certain custom event kinds.
    MONITOR_CONTROL_RESET_CUSTOM_EVENT_TRIGGERS,
} RTX64_MONITOR_CONTROL_OP, * PRTX64_MONITOR_CONTROL_OP;

// This function performs monitoring control operations.  Parameter "operation" specifies which
// control operation to perform.  Parameter "data" points to (optional) operand data. If parameter
// "data" is not needed for a given operation, it is ignored.  Parameter "size" specifies the size
// (in bytes) of the operand data pointed to by parameter "data".  If parameter "size" is not needed
// for a given operation, it is ignored.
//
// This function is not thread-safe.  Client code should implement any needed serialization.
//
// This function returns TRUE if successful.  Otherwise, it returns FALSE, and the caller should
// call GetLastError to obtain the error code.
BOOL RtMonitorControl(RTX64_MONITOR_CONTROL_OP operation, void * data, size_t size);


///////////////////////////////////////////////////////////////////////////////
//
// License query functions.
//
///////////////////////////////////////////////////////////////////////////////

// This enumeration provides status values returned by RtGetLicenseFeatureStatus
// and RtGetLicenseFeatureStatusEx.
typedef enum _RtxFeatureLicenseStatus
{
    STATUS_LICENSE_ERROR = -1,              // Error retrieving license info.

    STATUS_LICENSE_VALID = 0,               // The license is a valid retail license.

    STATUS_LICENSE_VALID_EVALUATION = 1,    // The license is a valid evaluation license.

    STATUS_LICENSE_INVALID = 2,             // The license is invalid for some reason
                                            // (i.e., node-lock violation, bad
                                            // digital signature, etc.).

    STATUS_LICENSE_EXPIRED = 3,             // The license has expired.
} RtxFeatureLicenseStatus;

// This function obtains the status of the license for the product feature specified by parameter featureName.
// The status is written to the location pointed to by parameter status.  Returns TRUE if
// successful, otherwise FALSE.  If this function fails, the contents of the memory pointed to by
// parameter status is undefined.
BOOL RTAPI RtGetLicenseFeatureStatusA(LPSTR featureName, RtxFeatureLicenseStatus * status);
// This function obtains the status of the license for the product feature specified by parameter featureName.
// The status is written to the location pointed to by parameter status.  Returns TRUE if
// successful, otherwise FALSE.  If this function fails, the contents of the memory pointed to by
// parameter status is undefined.
BOOL RTAPI RtGetLicenseFeatureStatusW(LPWSTR featureName, RtxFeatureLicenseStatus * status);

// These functions obtain the status of the license for the product feature specified by parameter
// "featureName".  The status is written to the location pointed to by parameter status.  If the
// license contains an options string, it is copied to the buffer pointed to by parameter options,
// which must be at least 65 characters (not bytes) long.  If the license does not contain an
// options string, the string pointed to by parameter options is set to the empty string.
//
// The syntax of the RTX64 runtime feature options string is a comma-separated list of name/value
// pairs, where the name and value are separated by an '=' character with no surrounding whitespace.
// The value is guaranteed never to contain a comma.  The following names may be present in the
// options string:
//
//   Name        Value
//   ---------   --------------------------------------------------------------------
//   CID         The customer ID, which is an arbitrary string of characters uniquely
//               identifying the customer who purchased the RTX64 runtime license.
//
//   PID         The OEM product ID, which is an arbitrary string of characters
//               uniquely identifying the OEM product of which RTX64 is a component.
//
// Returns TRUE if successful or FALSE if a failure occurs.  If this function fails, the contents of
// the memory pointed to by parameters status and options is undefined.

// This function obtains the status of the license for the product feature specified by parameter
// "featureName". 
BOOL RTAPI RtGetLicenseFeatureStatusExA(LPSTR featureName, RtxFeatureLicenseStatus * status, LPSTR options);
// This function obtains the status of the license for the product feature specified by parameter
// "featureName".  
BOOL RTAPI RtGetLicenseFeatureStatusExW(LPWSTR featureName, RtxFeatureLicenseStatus * status, LPWSTR options);

#ifdef UNICODE
# define RtGetLicenseFeatureStatus RtGetLicenseFeatureStatusW
# define RtGetLicenseFeatureStatusEx RtGetLicenseFeatureStatusExW
#else
# define RtGetLicenseFeatureStatus RtGetLicenseFeatureStatusA
# define RtGetLicenseFeatureStatusEx RtGetLicenseFeatureStatusExA
#endif

///////////////////////////////////////////////////////////////////////////////
//
//Local memory functions.
//
///////////////////////////////////////////////////////////////////////////////

//Supported allocation option for Flags parameter in RtAllocateLocalMemoryEx
#define RTALLOC_NOT_ZERO_MEMORY             0x00000001  
// This function allocates memory from a pre-allocated RTSS local memory pool to avoid SRI activity if allocating 
// memory from the Windows memory pool.
PVOID	RTAPI RtAllocateLocalMemoryEx(ULONG Size, ULONG Flags);
// This function expands the RTSS local memory pool upon request by the  size specified.
BOOL	RTAPI RtExpandLocalMemory(ULONG Size);
// This function shrinks the RTSS local memory pool to the size specified. 
ULONG   RTAPI RtShrinkLocalMemory(ULONG Size);


///////////////////////////////////////////////////////////////////////////////
//
//Physical memory mapping functions.
//
///////////////////////////////////////////////////////////////////////////////

PVOID	RTAPI RtAllocateLockedMemory(ULONG Size);
BOOL	RTAPI RtFreeLockedMemory(PVOID pVirtualAddress);


///////////////////////////////////////////////////////////////////////////////
//
//Thread functions.
//
///////////////////////////////////////////////////////////////////////////////
// This function retrieves timing information for the specified RTSS thread. This function 
// can only be called in RTSS processes.
BOOL	RTAPI RtGetThreadTimes(HANDLE hThread,	LPFILETIME lpCreationTime, LPFILETIME lpExitTime, LPFILETIME lpExecuteTime);

// Return value if function RtGetThreadTimeQuantumEx fails.
#define INVALID_QUANTUM 0x0

// This function gets the current time quantum, in microseconds, for the specified realtime thread. This function
// can only be called in RTSS processes.
ULONG64	RTAPI RtGetThreadTimeQuantumEx(HANDLE hThread);

// This function sets the time quantum, in microseconds, for the specified realtime thread. This function
// can only be called in RTSS processes.
BOOL	RTAPI RtSetThreadTimeQuantumEx(HANDLE hThread, ULONG64 ulQuantumInUS);

///////////////////////////////////////////////////////////////////////////////
//
//Time functions.
//
///////////////////////////////////////////////////////////////////////////////

// This function gets the current value for RTSS time.
VOID	RTAPI RtGetRtssTimeAsFileTime(LPFILETIME pTime);
// This function sets the new value for RTSS time.
VOID	RTAPI RtSetRtssTimeAsFileTime(LPFILETIME pTime);

///////////////////////////////////////////////////////////////////////////////
//
//Waitable Timer functions.
//
///////////////////////////////////////////////////////////////////////////////

#if !defined(_WINDEF_)
typedef VOID (RTFCNDCL *PTIMERAPCROUTINE)(LPVOID lpArgToCompletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue);
#endif


HANDLE	RTAPI RtCreateWaitableTimerA(LPSECURITY_ATTRIBUTES lpTimerAttributes, BOOL bManualReset, LPCSTR lpTimerName);
HANDLE	RTAPI RtCreateWaitableTimerW(LPSECURITY_ATTRIBUTES lpTimerAttributes, BOOL bManualReset, LPCWSTR lpTimerName);


#ifdef UNICODE
#define RtCreateWaitableTimer  RtCreateWaitableTimerW
#else
#define RtCreateWaitableTimer  RtCreateWaitableTimerA
#endif // !UNICODE


HANDLE	RTAPI RtOpenWaitableTimerA(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpTimerName);
HANDLE	RTAPI RtOpenWaitableTimerW(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCWSTR lpTimerName);


#ifdef UNICODE
#define RtOpenWaitableTimer  RtOpenWaitableTimerW
#else
#define RtOpenWaitableTimer  RtOpenWaitableTimerA
#endif // !UNICODE


BOOL	RTAPI RtSetWaitableTimer(HANDLE hWaitableTimer, const LARGE_INTEGER *lpDueTime, LONG lPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, LPVOID lpArgToCompletionRoutine, BOOL fResume);
BOOL	RTAPI RtCancelWaitableTimer(HANDLE hWaitableTimer);
BOOL	RTAPI RtSetWaitableTimerFt(HANDLE hWaitableTimer, const LARGE_INTEGER *lpDueTime, const LARGE_INTEGER *lpPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, LPVOID lpArgToCompletionRoutine, BOOL fResume);


///////////////////////////////////////////////////////////////////////////////
//
//Processor number
//
///////////////////////////////////////////////////////////////////////////////

// This function returns the system-assigned number of the current processor on which the caller is running.
ULONG RTAPI RtGetCurrentProcessorNumber(VOID);


///////////////////////////////////////////////////////////////////////////////
//
//Rt Trace functions.
//
///////////////////////////////////////////////////////////////////////////////

#define PERF_MEASURE_HALISR_ENTEREXIT     0x00000001
#define PERF_MEASURE_HAL_CLOCKTICK        0x00000002
#define PERF_MEASURE_HAL_INTERNAL         0x00000004
#define PERF_MEASURE_RTSS_TIMERTICK       0x00000008
#define PLATFORM_CONFIG_UP_PIC            0x00000001
#define PLATFORM_CONFIG_UP_APIC           0x00000002
#define PLATFORM_CONFIG_MP_DEDICATED      0x00000004
#define PLATFORM_CONFIG_MP_SHARED         0x00000008

BOOL	RTAPI RtTraceEvent(ULONG TraceEventID, PVOID arg1,	PVOID arg2);

ULONG	RTAPI RtStartPerfMeasure(ULONG perfMeasureType,				//control code of operation to perform (input)
								 ULONG_PTR *ioBuffer,				//buffer to pass data (output)
								 ULONG ioBufferSize,				//buffer size (input)
								 ULONG_PTR *ioBufferWrite,			//pointer to write index (output)
								 LONGLONG *lPerfCyclesPerSecond,	//pointer to pass PerfCyclesPerSecond (output)
								 ULONG *platformConfig,				//pointer to pass platform configuration (output)
								 ULONG *rtssProcessorNumber			//pointer to pass RTSS processor number (output)
								);


ULONG	RTAPI RtStopPerfMeasure(ULONG perfMeasureType,	//control code of operation to perform (input)
								ULONG *ioBuffer			//buffer to pass data (output)
							   );


///////////////////////////////////////////////////////////////////////////////
//
//WFSO/WFMO Ex functions.
//
///////////////////////////////////////////////////////////////////////////////

// This function allows a thread to wait on an object to be signaled with high granularity of time-out interval.
DWORD RTAPI RtWaitForSingleObjectEx(
    			HANDLE hHandle,
	            PULARGE_INTEGER  lpWaitTimedOut);

// This function allows a thread to wait on one of multiple objects to be signaled with high granularity of 
// time-out interval.
DWORD RTAPI RtWaitForMultipleObjectsEx(
	DWORD			 dwCount,
    CONST HANDLE	 *lpHandles,
	BOOL			 bWaitAll,
    PULARGE_INTEGER  lpWaitTimedOut);


///////////////////////////////////////////////////////////////////////////////
//
//Get process freeze status.
//
///////////////////////////////////////////////////////////////////////////////

BOOL
RTAPI
RtGetProcessFreeze(
	DWORD		dwProcessId,
    BOOL        *bFreeze
	);


///////////////////////////////////////////////////////////////////////////////
//
//Get enabled XState features on x64 processors
//
///////////////////////////////////////////////////////////////////////////////

//
// Enum type for RtGetEnabledXStateFeature parameter - XSateBit
// Note: following the same bit order as XSAVE Header field - XSave_BV
//
#if ( !defined(_XSTATE_BIT_) )
#define _XSTATE_BIT_
typedef enum _XSTATE_BIT {
	XStateUndefined = -1,    // -1
    XStateFPU,               // 0 - x87 FPU
    XStateSSE,               // 1 - SSE
    XStateAVX,               // 2 - AVX
    XStateMaximum            // Invalid
} XSTATE_BIT, *PXSTATE_BIT;
#endif

#if ( !defined(_ENABLED_HIGHEST_FEATURE_) )
#define _ENABLED_HIGHEST_FEATURE_
typedef enum _ENABLED_HIGHEST_FEATURE {
    NotSupported = -1,
    x87FPU,
	SSE,
	SSE2,
	SSE3,
    SSSE3,
	SSE4_1,
	SSE4_2,
	AVX,
	AVX2
} ENABLED_HIGHEST_FEATURE, *PENABLED_HIGHEST_FEATURE;
#endif

BOOL 
RTAPI 
// This function returns the highest feature for a specified XState feature set supported on the running 
// processor and enabled by RTX64.
RtGetEnabledXStateFeature(
	XSTATE_BIT XSateBit, 
	PENABLED_HIGHEST_FEATURE HighestFeature
	);

LONG
RTAPI
__RtGetAllObjects(
	PUCHAR	Buffer,
	LONG	Length
	);

BOOL RTAPI RtGetFlushTLBTickMod(ULONG  *pTickMod);
BOOL RTAPI RtSetFlushTLBTickMod(ULONG  TickMod);


///////////////////////////////////////////////////////////////////////////////
//
// Process Local Storage (PLS) functions.
//
///////////////////////////////////////////////////////////////////////////////

//
// Maximum number of PLS values per process. Must be in 32 bit multiples.
//
#define	PLS_NINDEX		160

DWORD
RTAPI
RtPlsAlloc(
    VOID
    );

BOOL
RTAPI
RtPlsFree(
    DWORD  dwPlsIndex
    );

LPVOID
RTAPI
RtPlsGetValue(
    DWORD  dwPlsIndex
    );

BOOL
RTAPI
RtPlsSetValue(
    DWORD   dwPlsIndex,
    LPVOID  lpPlsValue
    );


/////////////////////////////////////////////////////////////////
//
// Low-level RTSS lock (e.g. mutex), not through object layer
//
/////////////////////////////////////////////////////////////////

//
// Low-level synchronization events.
//
typedef struct _RTLOCKEVENT
{
    LONG		State;			// non-0 if signaled
    LIST_ENTRY	WaitList;		// FIFO list of waiting threads
} RTLOCKEVENT, *PRTLOCKEVENT;

//
// Low-level locks (e.g. mutexes).
//
typedef struct _RTLOCK {
    RTLOCKEVENT	Event;			// Event to wait for if lock is locked
    PVOID	    OwnerThread;	// Thread holding the lock or NULL
    LONG		Count;			// Nested acquisition count
} RTLOCK, *PRTLOCK;

VOID
RTAPI
RtInitLock(
    PRTLOCK	Lock
    );

BOOL
RTAPI
RtLockLock(
    PRTLOCK	Lock
    );

VOID
RTAPI
RtUnlockLock(
    PRTLOCK	Lock
    );


#ifdef __cplusplus
}
#endif

#endif
