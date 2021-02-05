#pragma once

template<int n>
int factorial(void){
    return n*factorial<n-1>();
}

template<>
int factorial<0>(void){
    return 1;
}
