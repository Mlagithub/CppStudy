
#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "color.h"
#include <iostream>
#include <sstream>

namespace Msg
{

class Debug
{
public:
    static std::string render(const std::string &val, size_t begin,
                              size_t end)
    {
        size_t b_ = begin > end ? end : begin;
        size_t e_ = begin > end ? begin : end;

        e_ = e_ > val.length() ? val.length() : e_;

        std::ostringstream rst;

        for (size_t it = 0; it < b_; ++it)
        {
            rst << val[it];
        }

        rst << std::string(GREEN_COLOR);
        for (size_t it = b_; it < e_; ++it)
        {
            rst << val[it];
        }
        rst << std::string(DEFAULT_COLOR);

        for (size_t it = e_; it < val.length(); ++it)
        {
            rst << val[it];
        }

        return rst.str();
    }
    static std::string Header() { return std::string{"[DEBUG] "}; };
    static std::ostream &Flusher(void) { return std::cout; }
};

} // namespace Msg

#endif
