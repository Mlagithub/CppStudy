
#pragma once

#include <iostream>

template<size_t N, size_t Low=1, size_t Up = N>
struct Root{
    static const size_t mean = (Low + Up)/2;
    static const bool down = (mean*mean>=N);
    static const size_t value = Root<N, (down ? Low : mean+1), (down ? mean : Up)>::value;
};

template<size_t N, size_t Mid>
struct Root<N, Mid, Mid>{
    static const size_t value = Mid;
};
