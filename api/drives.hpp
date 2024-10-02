#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

std::vector<std::string> GetAvailableDrives(const std::string& MNT_PT)
{
    std::vector<std::string> Drives;

    try
    {
        for (const auto& Entry : std::filesystem::directory_iterator(MNT_PT))
            Drives.push_back(Entry.path().string());
    } catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "There was an unexpected error\n";
        exit(1);
    }

    return Drives;
}
