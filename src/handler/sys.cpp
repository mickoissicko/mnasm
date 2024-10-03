#include <iostream>
#include <cstdlib>

int HandleSys(const char SYSTEM_COMMAND[])
{
    if (int Ret = std::system(SYSTEM_COMMAND) != 0)
    {
        std::cerr << "Could not execute command!\n";
        std::cout << "Attempted: " << SYSTEM_COMMAND;

        return (Ret);
    }

    return 0;
}
