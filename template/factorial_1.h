
#pragma once

#include <iostream>

using namespace std;


template<size_t N>
size_t factorial(void){
    return N * factorial<N-1>();
}

template<>
size_t factorial<0>(void){
    return 1;
}

