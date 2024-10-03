#include "../../include/var.hpp"
#include <filesystem>
#include <iostream>
#include <cstdio>

namespace Fs = std::filesystem;

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
