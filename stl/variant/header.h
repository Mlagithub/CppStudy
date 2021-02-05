
#pragma once

#include <iostream>
#include <variant>
#include <string>
#include <iomanip>
#include <type_traits>

template <typename T>
struct always_false : std::false_type {};

// different type use comman operation
struct Func {
    template <typename T>
    void operator()(T &&i) {
        std::cout << "call from Func, value is " << i << std::endl;
    }
};

// different type use different operation
struct Func1 {
    void operator()(const int &i) {
        std::cout << "call from Func, int * 2 " << i * 2 << std::endl;
    }

    void operator()(const double &i) {
        std::cout << "call from Func, double - 2 " << i - 2 << std::endl;
    }

    void operator()(const std::string &i) {
        std::cout << "call from Func, string.size() " << i.size() << std::endl;
    }
};

// another polymoprhism method with variant and visit
class Base {
public:
    void PrintName() const { std::cout << "calling Base!\n"; }
};

class Derived1 {
public:
    void PrintName() const { std::cout << "calling Derived1!\n"; }
};

class Derived2 {
public:
    void PrintName() const { std::cout << "calling Derived2!\n"; }
};
class Derived3 {
public:
    void PrintName() const { std::cout << "calling Derived3!\n"; }
};


struct CallPrintName{
    void operator()(const Base &b) { b.PrintName(); }
    void operator()(const Derived1 &d1) { d1.PrintName(); }
    void operator()(const Derived2 &d2) { d2.PrintName(); }
    void operator()(const Derived3 &d3) { d3.PrintName(); }
};