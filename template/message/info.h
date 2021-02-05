
#ifndef INFO_HPP
#define INFO_HPP

#include <iostream>

namespace Msg
{

class Info
{
public:
    static std::string render(const std::string &val, size_t begin,
                              size_t end)
    {
        return val;
    }
    static std::string Header() { return std::string{"[INFO] "}; };
    static std::ostream &Flusher(void) { return std::cout; }
};

} // namespace Msg

#endif
