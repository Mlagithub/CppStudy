
#pragma once

#include "header.h"


void variant_size(){
    // define 3 variant contains different number of class.
    // here Base, Derived1, Derived2, Derived3 are classes.
    // check the size of var1 var2 and var3
    // result is : var1 = var2 = var3 = 2
    std::variant<Base, Derived1> var1;
    std::variant<Base, Derived1, Derived2> var2;
    std::variant<Base, Derived1, Derived2, Derived3> var3;
    std::cout << "size of variant<Base, Derived1> is " << sizeof(var1) << '\n';
    std::cout << "size of variant<Base, Derived1, Derived2> is " << sizeof(var2) << '\n';
    std::cout << "size of variant<Base, Derived1, Derived2, Derived3> is " << sizeof(var3) << '\n';
}