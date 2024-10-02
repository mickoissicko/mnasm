#ifndef GETHOME_H
    #define GETHOME_H
#endif

#ifndef _WIN32
    #include "linux/linux.h"
    static char* gethome();

/**
* #elif __APPLE__
*     #include "macos/macos.h"
*     static char* gethome();
**/

#else
    #include "windows/win32.h"
    static char* gethome();
#endif

