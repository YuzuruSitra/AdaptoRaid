#pragma once
//
// MREAL Platform API
//
#if !defined( _WIN64 )	// for 32bit
#include "MrhApi.h"
#else					// for 64bit
#include "MrhApi_x64.h"
#endif
#include "MrhApiDef.h"

// Retrieving error information
// [in] unknown  An interface which output error
// [in] hr  Error code
// [in,out] buf  A buffer for storing the error infomation
// [in] bytes  Number of bytes of the error information buffer
void MrhGetLastErrorDescription(IUnknown * unknown, HRESULT hr, LPTSTR buf, size_t bytes);
extern "C"
void MrhGetLastErrorDescriptionW(IUnknown * unknown, HRESULT hr, LPWSTR buf, size_t bytes);
extern "C"
void MrhGetLastErrorDescriptionA(IUnknown * unknown, HRESULT hr, LPSTR buf, size_t bytes);
#if defined( UNICODE )
#define MrhGetLastErrorDescription MrhGetLastErrorDescriptionW
#else
#define MrhGetLastErrorDescription MrhGetLastErrorDescriptionA
#endif
