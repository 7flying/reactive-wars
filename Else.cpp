#include "Else.hpp"
#include <string>


std::string getFileSeparator()
{
#ifdef _WIN32
    return "\\";
#else
    return "/";
#endif
}
