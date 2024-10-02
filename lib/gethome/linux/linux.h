#include "../common.h"

static char* gethome()
{
    struct passwd *Home;

    char* Path = NULL;

    if ((Home = getpwuid(getuid())) != NULL)
    {
        Path = (char*)malloc(MAX_STR_LEN);

        if (Path != NULL)
            strcpy(Path, Home->pw_dir);
    }

    return Path;
}

