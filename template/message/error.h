
#ifndef ERROR_HPP
#define ERROR_HPP

#include "color.h"

#include <sstream>

namespace Msg
{

class Error
{
public:
    static std::string render(const std::string &val, size_t begin, size_t end)
    {
        size_t b_ = begin > end ? end : begin;
        size_t e_ = begin > end ? begin : end;

        e_ = e_ > val.length() ? val.length() : e_;

        std::ostringstream rst;

        for (size_t it = 0; it < b_; ++it)
        {
            rst << val[it];
        }

        rst << std::string(RED_COLOR);
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
    static std::ostream &Flusher(void) { return std::cerr; }
    static std::string Header() { return std::string{"[ERROR] "}; };
};

} // namespace Msg

#endif
