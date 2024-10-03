#include "../include/cmd.hpp"
#include "../include/var.hpp"
#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <cstdio>

namespace Fs = std::filesystem;

// Mount function

void HandleMntPts(char MountPointName[])
{
    char FullMountPath[4096];

    snprintf(FullMountPath, sizeof(FullMountPath), "%s/%s", DEFAULT_MOUNT_POINT, MountPointName);

    if (!(Fs::exists(DEFAULT_MOUNT_POINT)))
    {
        std::cout << "Creating mountpoints...\n";

        Fs::create_directories(DEFAULT_MOUNT_POINT);
        Fs::create_directories(FullMountPath);
    }

    else if (!(Fs::exists(FullMountPath)))
    {
        std::cout << "Creating drive mountpoint...\n";

        Fs::create_directories(FullMountPath);
    }
}

void Umount(char Dev[])
{
    char UmountCommand[2048];
    snprintf(UmountCommand, sizeof(UmountCommand), "%s %s", UMOUNT, Dev);

    HandleMntPts(Dev);

    if (std::system(UmountCommand) != 0)
    {
        std::cerr << "Unable to unmount device. Maybe its being used?\n";
        std::exit(1);
    }
}

void Mount(char Dev[], char DevName[])
{
    char MountCommand[2048];

    std::cout << "Attempting to mount...\n";

    HandleMntPts(DevName);

    snprintf(MountCommand, sizeof(MountCommand), "%s %s %s/%s", MOUNT, Dev, DEFAULT_MOUNT_POINT, DevName);

    if (std::system(MountCommand) != 0)
    {
        std::cerr << "Error encountered whilst mounting\n";
        std::exit(1);
    }
}
