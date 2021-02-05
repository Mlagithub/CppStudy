#include <iostream>
#include <type_traits>
#include <functional>


template<class F1, class... Fs>
struct overload : F1, overload<Fs...>
{
    using F1::operator();
    using overload<Fs...>::operator();
    overload(F1 f1, Fs... fs) : F1(f1), overload<Fs...>(fs...) {}
};

template<class F1>
struct overload<F1> : F1
{
    using F1::operator();
    overload(F1 f1) : F1(f1) {}
};


template <class... F>
auto make_overload(F... f) {
    return overload<F...>(f...);
}


int main() {

    std::function <int(int,int)> f = [](int x,int y) {
        return x+y;
    };
    std::function <double(double,double)> g = [](double x,double y) {
        return x+y;
    };
    std::function <std::string(std::string,std::string)> h = [](std::string x,std::string y) {
        return x+y;
    };

    auto fgh = make_overload(f,g,h);
    std::cout << fgh(1,2) << std::endl;
    std::cout << fgh(1.5,2.5) << std::endl;
    std::cout << fgh("bob","larry") << std::endl;
}