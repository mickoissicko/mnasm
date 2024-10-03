#include "../lib/gethome/gethome.h"
#include "../include/var.hpp"
#include "../include/fn.hpp"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

std::string& GetMntLoc(std::ifstream& File)
{
    static std::string MntPt;
    std::string Line;

    while (std::getline(File, Line))
    {
        // ...
    }

    return MntPt;
}

int GetPrtNum(std::ifstream& File)
{
    int PrtNum = 8080;
    std::string Line;

    while (std::getline(File, Line))
    {
        // ...
    }

    return PrtNum;
}

const std::string& FromConfig_str(const int OPT)
{
    char* Home = gethome();

    if (HandleChdir(Home)) std::exit(HandleChdir(Home));

    GetConf();

    if (HandleChdir(CONFIG_DIR)) std::exit(HandleChdir(CONFIG_DIR));

    std::ifstream ConfigFile(DEFAULT_CONFIG_FILE);

    if (HandleFileI(ConfigFile)) std::exit(HandleFileI(ConfigFile));

    if (OPT == 1) return GetMntLoc(ConfigFile);

    else
    {
        std::cout << "Invalid OPT\n";

        ConfigFile.close();

        std::exit(1);
    }
}

const int FromConfig_num(const int OPT)
{
    
}
