#include <iostream>
#include <unistd.h>

int HandleChdir(const char Path[])
{
    if (chdir(Path) != 0)
    {
        std::cerr << "Error whilst changing directory\n";

        return 1;
    }

    return 0;
}
