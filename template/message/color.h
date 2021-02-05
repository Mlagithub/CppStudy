
#ifndef COLOR_H
#define COLOR_H

#ifdef _WIN32

#include <Windows.h>
#include <WinBase.h>

#define DEFAULT_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                              FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

#define BLACK_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                            FOREGROUND_INTENSITY);

#define RED_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                          FOREGROUND_INTENSITY | FOREGROUND_RED);

#define GREEN_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                            FOREGROUND_INTENSITY | FOREGROUND_GREEN);

#define YELLOW_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                             FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);

#define BLUE_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                           FOREGROUND_INTENSITY | FOREGROUND_BLUE);

#define MAGENTA_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                              FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);

#define CYAN_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                           FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);

#define WHITE_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                                            FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

#endif

#if defined(__linux__) || defined(__linux)

#define DEFAULT_COLOR "\033[0m"
#define BLACK_COLOR "\033[00;30m"
#define RED_COLOR "\033[00;31m"
#define GREEN_COLOR "\033[00;32m"
#define YELLOW_COLOR "\033[00;33m"
#define BLUE_COLOR "\033[00;34m"
#define MAGENTA_COLOR "\033[00;35m"
#define CYAN_COLOR "\033[00;36m"
#define WHITE_COLOR "\033[00;37m"

#endif // WIN32

#endif
