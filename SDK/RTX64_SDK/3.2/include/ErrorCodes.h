// Copyright (c) 2015 IntervalZero, Inc.  All rights reserved.
//
// This file defines macros that represent custom Win32 error codes that RTX64 real-time APIs can
// return.  Custom error codes all have bit 29 set.  See:
//
//    https://msdn.microsoft.com/en-us/library/ms680627.aspx
//
// which says:
//
//    Bit 29 is reserved for application-defined error codes; no system error code has this bit set.
//    If you are defining an error code for your application, set this bit to indicate that the
//    error code has been defined by your application and to ensure that your error code does not
//    conflict with any system-defined error codes.
//
// RTX64 real-time APIs can still return normal Win32 error codes, such as ERROR_FILE_NOT_FOUND (2).
// These error codes extend the range of possible error codes to include codes specific to RTX64.

#pragma once

// Custom error codes must have bit 29 set.  Microsoft guarantees that no regular Win32 error code
// will ever have bin 29 set.  IMPORTANT: Do not change the name of this macro!
#define RT_CUSTOM_ERROR(VALUE)  ((VALUE) | (1 << 29))

// This macro has been deprecated.
// Custom error codes must have bit 29 set.  Microsoft guarantees that no regular Win32 error code
// will ever have bin 29 set.  IMPORTANT: Do not change the name of this macro!
#define RTX64_CUSTOM_ERROR(VALUE)  ((VALUE) | (1 << 29))

// Description: No RTX64 runtime license is available. Error Deprecated. 
// This error code has been deprecated.
#define RTX64_NO_RUNTIME_LICENSE						RTX64_CUSTOM_ERROR(1)

// Description: The RTX64 runtime license has expired. 
// This error code has been deprecated.
#define RTX64_EXPIRED_RUNTIME_LICENSE					RTX64_CUSTOM_ERROR(2)

// Description: No RTX64 SDK license was available when this application (or an RTDLL on which it
// depends) was built. 
// This error code has been deprecated.
#define RTX64_MODULE_NO_SDK_LICENSE						RTX64_CUSTOM_ERROR(3)

// Description: This application (or an RTDLL on which it depends) was built with an evaluation
// RTX64 SDK license. It cannot be executed when the RTX64 runtime license is a retail license. 
// This error code has been deprecated.
#define RTX64_MODULE_EVAL_SDK_LICENSE					RTX64_CUSTOM_ERROR(4)

// Description: This application (or an RTDLL on which it depends) is missing important RTX64
// license information.
// This error code has been deprecated.
#define RTX64_MODULE_LICENSE_INFO_MISSING				RTX64_CUSTOM_ERROR(5)

// Description: This application (or an RTDLL on which it depends) contains corrupted license
// information.
// This error code has been deprecated. 
#define RTX64_MODULE_LICENSE_INFO_CORRUPT				RTX64_CUSTOM_ERROR(6)

// Description: One or more object files in this application (or an RTDLL on which it depends) were
// built using an RTX64 SDK version that is incompatible with the current RTX64 runtime.
// This error code has been deprecated.
#define RTX64_MODULE_UNSUPPORTED_SDK					RTX64_CUSTOM_ERROR(7)

// Description: The system clock appears to have been set to a time in the past. This prevents RTX64
// from properly validating licenses.  Please set the system time to the correct time.
// This error code has been deprecated.
#define RTX64_CLOCK_REWIND								RTX64_CUSTOM_ERROR(8)

// Description: Length parameter is invalid
// This error code has been deprecated.
#define RTX64_GETLICENSES_INVALID_LENGTH_PARAMETER		RTX64_CUSTOM_ERROR(9)

// Description: Results buffer passed length is too small
// This error code has been deprecated.
#define RTX64_GETLICENSES_RESULTS_BUFFER_TOO_SMALL		RTX64_CUSTOM_ERROR(10)

// Description: Unable to access system registry
// This error code has been deprecated.
#define RTX64_GETLICENSES_REGISTRY_ACCESS_FAILURE		RTX64_CUSTOM_ERROR(11)

// Description: Expected registry value does not exist
// This error code has been deprecated.
#define RTX64_GETLICENSES_REGISTRY_VALUE_ACCESS_FAILURE	RTX64_CUSTOM_ERROR(12)

// Description: License info data in registry does not match to its hash value stored at last update
// This error code has been deprecated.
#define RTX64_GETLICENSES_HASHSUM_DOES_NOT_MATCH		RTX64_CUSTOM_ERROR(13)

// Description: Version of license info value in registry does not match to the one of the currently
// installed system.
// This error code has been deprecated.
#define RTX64_GETLICENSES_VERSION_DOES_NOT_MATCH		RTX64_CUSTOM_ERROR(14)

// Description: Hashnum cannot be computed 
// This error code has been deprecated.
#define RTX64_GETLICENSES_HASHSUM_COMPUTE_FAILED		RTX64_CUSTOM_ERROR(15)

// Description: Clock rewind detected
// This error code has been deprecated.
#define RTX64_GETLICENSES_CLOCK_REWIND_DETECTED			RTX64_CUSTOM_ERROR(16)

// Description: License not found
// This error code has been deprecated.
#define RTX64_GETLICENSES_NOT_FOUND						RTX64_CUSTOM_ERROR(17)

// Description: Internal Error
// This error code has been deprecated.
#define RTX64_GETLICENSES_INTERNAL_ERROR				RTX64_CUSTOM_ERROR(18)

// Description: Unknown Error
// This error code has been deprecated.
#define RTX64_GETLICENSES_UNKNOWN_ERROR					RTX64_CUSTOM_ERROR(19)

// Description: Call success
// This error code has been deprecated.
#define RTX64_GETLICENSES_SUCCESS						RTX64_CUSTOM_ERROR(20)

// Description: Could not access registry key to read data
// This error code has been deprecated.
#define RTX64_GETDONGLES_REG_KEY_ACCESS_ERROR			RTX64_CUSTOM_ERROR(21)

// Description: Could not access registry key to read data.
// This error code has been deprecated.
#define RTX64_GETDONGLES_REG_VALUE_READ_ERROR			RTX64_CUSTOM_ERROR(22)

// Description: Invalid paraemters were provided.
// This error code has been deprecated.
#define RTX64_GETDONGLES_INVALID_PARAMETERS				RTX64_CUSTOM_ERROR(23)

// Description: Invalid parameters were provided.
// This error code has been deprecated.
#define RTX64_GETDONGLES_BUFFER_TOO_SMALL				RTX64_CUSTOM_ERROR(24)

// Description: Failed to allocate memory.
// This error code has been deprecated.
#define RTX64_GETDONGLES_MEM_ALLOC_FAILED				RTX64_CUSTOM_ERROR(25)

// Description: The number of configured RTSS cores is greater than number of licensed cores.
// This error code has been deprecated.
#define RTX64_TOO_MANY_RTSS_CORES_CONFIGURED			RTX64_CUSTOM_ERROR(26)

// IMPORTANT: Do not change or move the comment on the next line.
// ERROR-CODES-START-HERE

// Description: No RTX64 runtime license is available. 
#define RT_ERROR_NO_RUNTIME_LICENSE                     RT_CUSTOM_ERROR(1)

// Description: The RTX64 runtime license has expired.
#define RT_ERROR_EXPIRED_RUNTIME_LICENSE                RT_CUSTOM_ERROR(2)

// Description: No valid license was found for the given product feature code.
#define RT_ERROR_NO_LICENSE                             RT_CUSTOM_ERROR(3)

// Description: No RTX64 SDK license was available when this application (or an RTDLL on which it
// depends) was built. You may be able to resolve this error by rebuilding the application.
#define RT_ERROR_MODULE_NO_SDK_LICENSE                  RT_CUSTOM_ERROR(4)

// Description: This application (or an RTDLL on which it depends) was built with an evaluation
// RTX64 SDK license. It cannot be executed when the RTX64 runtime license is a retail license. 
// You may be able to resolve this error by rebuilding the application.
#define RT_ERROR_MODULE_EVAL_SDK_LICENSE                RT_CUSTOM_ERROR(5)

// Description: This application (or an RTDLL on which it depends) is missing important RTX64
// license information. You may be able to resolve this error by rebuilding the application.
#define RT_ERROR_MODULE_LICENSE_INFO_MISSING            RT_CUSTOM_ERROR(6)

// Description: This application (or an RTDLL on which it depends) contains corrupted license
// information. You may be able to resolve this error by rebuilding the application.
#define RT_ERROR_MODULE_LICENSE_INFO_CORRUPT            RT_CUSTOM_ERROR(7)

// Description: One or more object files in this application (or an RTDLL on which it depends) were
// built using an RTX64 SDK version that is incompatible with the current RTX64 runtime.
// You may be able to resolve this error by rebuilding the application.
#define RT_ERROR_MODULE_UNSUPPORTED_SDK                 RT_CUSTOM_ERROR(8)

// Description: License data is corrupt.
#define RT_ERROR_CORRUPT_LICENSE_DATA                   RT_CUSTOM_ERROR(9)

// Description: RTX64 Subsystem was unable to communicate with required services.
#define RT_ERROR_SERVICE_ACCESS_FAILURE                 RT_CUSTOM_ERROR(10)

// Description: Internal error 1.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_1                             RT_CUSTOM_ERROR(11)

// Description: Internal error 2.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_2                             RT_CUSTOM_ERROR(12)

// Description: Internal error 3.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_3                             RT_CUSTOM_ERROR(13)

// Description: Internal error 4.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_4                             RT_CUSTOM_ERROR(14)

// Description: Internal error 5.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_5                             RT_CUSTOM_ERROR(15)

// Description: Internal error 6.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_6                             RT_CUSTOM_ERROR(16)

// Description: Internal error 7.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_7                             RT_CUSTOM_ERROR(17)

// Description: Internal error 8.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_8                             RT_CUSTOM_ERROR(18)

// Description: Internal error 9.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_9                             RT_CUSTOM_ERROR(19)

// Description: Internal error 10.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_10                            RT_CUSTOM_ERROR(20)

// Description: Internal error 11.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_11                            RT_CUSTOM_ERROR(21)

// Description: Internal error 12.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_12                            RT_CUSTOM_ERROR(22)

// Description: Internal error 13.  Please contact IntervalZero support for more information. 
#define RT_ERROR_INTERNAL_13                            RT_CUSTOM_ERROR(23)

// Description: Attempt to load a library that is not an RTDLL. RTSS applications and RTDLL libraries cannot link implicitly or explicitly to Windows dynamic link libraries (DLLs). Please make sure your project's linker inputs do not contain references to kernel32.lib, user32.lib, or any other Windows DLL import library.
#define RT_ERROR_INVALID_BINARY_FORMAT					RT_CUSTOM_ERROR(24)
