#ifndef FN_HPP
#define FN_HPP

#include <string>

const std::string& FromConfig_str(const int OPT);
const int FromConfig_num(const int OPT);

int HandleSys(const char SYSTEM_COMMAND[]);
int HandleFileI(std::ifstream& FileI);
int HandleFileO(std::ofstream& FileO);
int HandleChdir(const char Path[]);

void HandleMntPts(char MountPointName[]);
void InitServer(const int PORT);
void GetConf();

#endif
