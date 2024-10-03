#include "../include/cmd.hpp"
#include "../include/var.hpp"
#include "../include/fn.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>

void Umount(char Dev[])
{
    char UmountCommand[2048];
    snprintf(UmountCommand, sizeof(UmountCommand), "%s %s", UMOUNT, Dev);

    HandleMntPts(Dev);

    if (HandleSys(UmountCommand) != 0) std::exit(HandleSys(UmountCommand));
}

void Mount(char Dev[], char DevName[])
{
    char MountCommand[2048];

    std::cout << "Attempting to mount...\n";

    HandleMntPts(DevName);

    snprintf(MountCommand, sizeof(MountCommand), "%s %s %s/%s", MOUNT, Dev, DEFAULT_MOUNT_POINT, DevName);

    if (HandleSys(MountCommand) != 0) std::exit(HandleSys(MountCommand));
}
