

#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <iostream>
#include <locale>
#include <sstream>

namespace Msg
{

static std::string currentTime(void)
{
    std::locale::global(std::locale());
    std::time_t t = std::time(nullptr);
    char mbstr[100];
    std::strftime(mbstr, sizeof(mbstr), "[%Y-%m-%d %H:%M:%S]",
                  std::localtime(&t));
    std::string rst(mbstr);
    return rst;
}

} // namespace Msg

#endif
