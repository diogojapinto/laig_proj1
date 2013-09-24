#ifndef OS_H_
#define OS_H_

#ifndef __unix__ 
#include <windows.h>
#define GL_CLAMP_TO_EDGE 0x812F
#define SLASH "\\"
#else
#define SLASH "/"
#endif

#endif
