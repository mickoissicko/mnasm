#ifndef COMMON_H
    #define COMMON_H
#endif

#define MAX_STR_LEN 8192

#ifndef _WIN32
    #include <sys/types.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdlib.h>
    #include <pwd.h>
#else
    #include <unistd.h>
    #include <string.h>
#endif

