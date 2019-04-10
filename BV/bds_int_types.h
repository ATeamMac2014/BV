//
//  bds_int_types.h
//  CPP_UTIL_TESTER
//
//  Created by lappi on 10/16/15.
//  Copyright © 2015 baidu. All rights reserved.
//

#ifndef bds_int_types_h
#define bds_int_types_h

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
/* UNIX-style OS. ------------------------------------------- */
#include <inttypes.h>
#elif defined(_WIN32)
/* Windows. ------------------------------------------- */
#include <windows.h>
/*
#ifndef uint8_t
#define uint8_t unsigned __int8
#endif
#ifndef int8_t
#define int8_t __int8
#endif
#ifndef uint16_t
#define uint16_t unsigned __int16
#endif
#ifndef int16_t
#define int16_t __int16
#endif
#ifndef uint32_t
#define uint32_t unsigned __int32
#endif
#ifndef int32_t
#define int32_t __int32
#endif
#ifndef uint64_t
#define uint64_t unsigned __int64
#endif
#ifndef int64_t
#define int64_t __int64
#endif
*/
#endif

#endif /* bds_int_types_h */
