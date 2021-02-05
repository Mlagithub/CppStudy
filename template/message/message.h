

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "delimiter.h"
#include "debug.h"
#include "error.h"
#include "info.h"
#include "timer.h"
#include "warning.h"

#include <fstream>
#include <sstream>

namespace Msg
{

template <class Plcy = Info, class Delimiter = DelimitComma,
          bool HasDate = true, bool HasHeader = true, bool HasNewline = true>

class Message : public std::ostream
{
public:
    Message() {}
    ~Message()
    {
        if (fileStream_.is_open())
            fileStream_.close();
    }

public:
    template <typename T>
    Message &operator<<(T &&val)
    {
        if (fileStream_.is_open())
        {
            fileStream_ << std::forward<T>(val);
        }
        if (showOnScreen_)
        {
            Plcy::Flusher() << std::forward<T>(val);
        }
        return *this;
    }

public:
    template <typename F, typename... Args>
    void operator()(F &&first, Args &&... args)
    {
        strStream_.str("");

        size_t renderB_ = 0, renderE_ = 0;

        // Date
        if (HasDate)
        {
            strStream_ << currentTime();
            renderB_ += 0;
            renderE_ += currentTime().length();
        }

        // header
        if (HasHeader)
        {
            strStream_ << Plcy::Header();
            renderB_ += 0;
            renderE_ += Plcy::Header().length();
        }

        // Args
        strStream_ << first;
        int dummy[] = {
            (strStream_ << Delimiter::delimit(), strStream_ << std::forward<Args>(args), 0)...};

        // std::endl
        if (HasNewline)
            strStream_ << std::endl;

        // flush buffer
        if (fileStream_.is_open())
            fileStream_ << strStream_.str();
        if (showOnScreen_)
            Plcy::Flusher() << Plcy::render(strStream_.str(), renderB_, renderE_);
    }

public:
    void writeToFile(const std::string &fname, const std::ios_base::openmode mode,
                     bool showOnScreen = false)
    {
        if (fileStream_.is_open())
        {
            fileStream_.close();
            fileStream_.open(fname, mode);
        }
        else
        {
            fileStream_.open(fname, mode);
        }
        showOnScreen_ = showOnScreen;
    }

public:
    void showOnScreen(bool ifShow) { showOnScreen_ = ifShow; }

private:
    static std::ostringstream strStream_;
    static std::ofstream fileStream_;
    static bool showOnScreen_;
};

template <class Plcy, class Delimiter, bool HasDate, bool HasHeader,
          bool HasNewline>
std::ostringstream
    Message<Plcy, Delimiter, HasDate, HasHeader, HasNewline>::strStream_;

template <class Plcy, class Delimiter, bool HasDate, bool HasHeader,
          bool HasNewline>
std::ofstream
    Message<Plcy, Delimiter, HasDate, HasHeader, HasNewline>::fileStream_;

template <class Plcy, class Delimiter, bool HasDate, bool HasHeader,
          bool HasNewline>
bool Message<Plcy, Delimiter, HasDate, HasHeader, HasNewline>::showOnScreen_ =
    true;

} // namespace Msg

#endif
