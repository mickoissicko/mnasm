#include "../../include/fn.hpp"
#include <iostream>

void Server()
{
    const std::string MOUNT_POINT = FromConfig_str(1);
    const int PORT = FromConfig_num(0);

    InitServer(PORT);
}
