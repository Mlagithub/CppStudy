
#pragma once

#include <string>

namespace Msg
{

struct DelimitComma
{
    static std::string delimit(void) { return (", "); }
};

struct DelimitSpace
{
    static std::string delimit(void) { return (" "); }
};

struct DelimitStar
{
    static std::string delimit(void) { return ("*"); }
};

struct DelimitLine
{
    static std::string delimit(void) { return ("-"); }
};

} // namespace Msg
