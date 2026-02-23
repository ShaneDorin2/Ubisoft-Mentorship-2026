#pragma once


#if defined(_DEBUG)
#define assert(test) \
if (!(test)) \
DebugBreak();

#define softAssert(test, message) \
if (!(test)) \
std::printf(message)
#else
#define assert(test)
#define softAssert(test, message)
#endif