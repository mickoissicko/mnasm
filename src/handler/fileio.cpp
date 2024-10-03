#include <iostream>
#include <cstdlib>
#include <fstream>

int HandleFileO(std::ofstream& FileO)
{
    if (!(FileO.is_open()))
    {
        std::cerr << "Could not open file\n";

        return 1;
    }

    return 0;
}

int HandleFileI(std::ifstream& FileI)
{
    if (!(FileI.is_open()))
    {
        std::cerr << "Could not open file\n";

        return 1;
    }

    return 0;
}
