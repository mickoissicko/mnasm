#ifndef FN_HPP
#define FN_HPP

#include <string>

const std::string& FromConfig_str(const int OPT);
const int FromConfig_num(const int OPT);

void InitServer(const int PORT);

#endif
