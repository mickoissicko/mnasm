#include "../common.h"

static char* gethome()
{
    unsigned long LEN = MAX_STR_LEN;

    char* HomeDirectory = getenv("USERPROFILE");

    return HomeDirectory;
}

