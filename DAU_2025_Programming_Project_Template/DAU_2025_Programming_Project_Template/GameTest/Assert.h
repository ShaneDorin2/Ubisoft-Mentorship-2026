#pragma once
#include <windows.h>
//#include <cstdio>
//#include <intrin.h>

/* 
* These functions will be used in debug. 
* Outside of _DEBUG, they have no functionality. 
* 
* assert(test)
* if test is false, forcefully interupt code and create break point. 
* 
* softAssert(test, message)
* if test is false, print debug message into output txt. The code is aloud to resume. 
*/


#if defined(_DEBUG)
#define assert(test) \
if (!(test)) \
DebugBreak();

#define softAssert(test, message) \
if (!(test)) \
OutputDebugStringA("ASSERT FAILED ------------ >      " message "\n") \

#else
#define assert(test)
#define softAssert(test, message)

#endif