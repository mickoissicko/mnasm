#include "../lib/gethome/gethome.h"
#include "../include/var.hpp"

#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#define MAX_PATH_LEN 8192

namespace Fs = std::filesystem;

enum ErrorCodeTable
{
    SUCCESS           = 0,
    USER_CANCELLED    = 1,
    HOME_DIR_ERROR    = 2,
    CONFIG_DIR_ERROR  = 3,
    CONFIG_FILE_ERROR = 4,
    FILE_WRITE_ERROR  = 5,
};

int CreateConfFile()
{
    std::cout << "Make config file? [y/n]\n> ";
    char Inpt = getchar();
    getchar();

    if (Inpt == 'y')
    {
        std::ofstream ConfigFile(DEFAULT_CONFIG_FILE);

        if (!ConfigFile.is_open()) return FILE_WRITE_ERROR;

        std::cout << "Ready to configure...\n";

        std::string MountLocation;
        int Port = 8080;

        std::cout << "Enter mount location (e.g. /run/media, /media, /mnt): ";
        std::cin >> MountLocation;

        std::cout << "Enter port number (e.g. 8080): ";

        while (!(std::cin >> Port) || Port <= 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid input. Please enter a valid port number: ";
        }

        ConfigFile << "DEFAULT_MOUNT_LOCATION: " << MountLocation << "\n";
        ConfigFile << "DEFAULT_PORT: " << Port << "\n";
        ConfigFile.close();
    }

    else
    {
        std::cout << "User cancelled operation.\n";
        return USER_CANCELLED;
    }

    return SUCCESS;
}

void GetConf()
{
    char* HomeDir = gethome();

    if (!HomeDir || !Fs::exists(HomeDir))
    {
        std::cerr << "Could not obtain home directory\n";
        exit(HOME_DIR_ERROR);
    }

    if (chdir(HomeDir) != 0)
    {
        std::cerr << "Could not change to home directory\n";
        exit(HOME_DIR_ERROR);
    }

    if (Fs::exists(CONFIG_DIR))
    {
        if (chdir(CONFIG_DIR) != 0)
        {
            std::cerr << "Could not change to .config directory\n";
            exit(CONFIG_DIR_ERROR);
        }
    }

    else
    {
        if (!Fs::create_directory(CONFIG_DIR))
        {
            std::cerr << "Could not create configuration directory\n";
            exit(CONFIG_DIR_ERROR);
        }
    }

    std::ifstream ConfigFile(DEFAULT_CONFIG_FILE);

    if (!ConfigFile.is_open())
    {
        std::cerr << "No config file present or other error\n";

        int Err = CreateConfFile();

        if (Err != SUCCESS) exit(Err);
    }

    ConfigFile.close();
}
