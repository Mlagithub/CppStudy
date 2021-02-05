
#pragma once

#include "header.h"


void variant_get(){

    std::variant<int, double, std::string> x, y;

    // assign value
    x = 1;
    y = "1.0";

    // check index
    std::cout << "x - " << x.index() << std::endl;
    std::cout << "y - " << y.index() << std::endl;

    // overwrite value
    x = 2.0;

    // check index
    std::cout << "x - " << x.index() << std::endl;
    std::cout << "y - " << y.index() << std::endl;

    // read value
    // d = 2.0
    // s = "1.0"
    double d = std::get<double>(x);
    std::string s = std::get<2>(y);

    // get error type
    // now x is double, so get<int>
    // throw std::bad_variant_access
    try {
        int i = std::get<int>(x);
    } catch (std::bad_variant_access e) {
        std::cerr << e.what() << std::endl;
    }

    // use get_if
    int *i = std::get_if<int>(&x);
    if (i == nullptr) {
        std::cout << "wrong type" << std::endl;
    } else {
        std::cout << "value is " << *i << std::endl;
    }

    // am
    std::variant<long, float> var{std::in_place_index<1>, 7.8};
}

template <class... Ts>
struct overload : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
overload(Ts...)->overload<Ts...>;

void test(){

std::variant<int, float, std::string> intFloatString{"Hello"};
std::visit(overload{[](int &i) { i *= 2; }, [](float &f) { f *= 2.0f; },
                    [](std::string &s) { s = s + s; }},
           intFloatString);  
}
