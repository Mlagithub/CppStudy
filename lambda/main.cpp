


// #include <iostream>
// #include <cstdio>
// #include <type_traits>

// using namespace std;

// template <typename T, typename U>
// struct decay_equive : std::is_same<typename std::decay<T>::type, U>::type {};

// int main(void) {
//     auto l = []() { return 4; };
//     puts(typeid(l).name());

//     auto plus = [value=1](int x){return x + value;};

//     return l();
// }

#include <iostream>
#include <type_traits>
#include <memory>

#include <vector>


// int g = 10;
// auto kitten = [=]() { return g + 1; };
// auto cat = [g = g]() { return g + 1; };

// int main() {
//     g = 20;
//     std::cout << kitten() << '\t' << cat() << std::endl;
// }

// struct MyType {
//     MyType() { std::cout << "MyType()\n"; }
//     MyType(const MyType &) { std::cout << "MyType(const MyType&)\n"; }
//     ~MyType() { std::cout << "~MyType()\n"; }
//     MyType(MyType &&) { std::cout << "MyType(MyType &&)\n"; }
// };
// int main() {
//     MyType o;
//     const auto &v = [&]() { return o; }();
//     return 0;
// }

// #include <iostream>
// #include <type_traits>
// #include <set>

// template<typename Lhs, typename Rhs>
// struct S : Lhs, Rhs{
//     S(Lhs lhs, Rhs rhs) : Lhs(lhs), Rhs(rhs) {}
//     using Lhs::operator();
//     using Rhs::operator();
// };


// template<typename Lhs, typename Rhs>
// auto make_combined(Lhs &&lhs, Rhs &&rhs){
//     return S<std::decay_t<Lhs>, std::decay_t<Rhs>>(std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
// }

// int main(){
//     auto l1 = [](){return 3;};
//     auto l2 = [](int i){return i*10;};
//     auto combined = make_combined(l1, l2);
//     std::cout << combined() << std::endl;
//     std::cout << combined(3) << std::endl;

//     std::vector<int> a;
//     std::set<int> b ;
    
//     return 0;
// }

// #include <iostream>
// #include <functional>

// std::function<void(void)> closureWrapper1() {
//     int x = 10;
//     return [x]() { std::cout << "Value in the closure: " << x << std::endl; };
// }

// std::function<void(void)> closureWrapper2() {
//     int x = 11;
//     return [x]() mutable {
//         x += 1;
//         std::cout << "Value in the closure: " << x << std::endl;
//     };
// }

// int main() {
//     int x = 10;
//     auto func0 = [&x]() {
//         x += 1;
//         std::cout << "Value in the closure: " << x << std::endl;
//     };
//     std::function<void(void)> func1 = closureWrapper1();
//     std::function<void(void)> func2 = closureWrapper2();
//     func0();
//     func0();
//     func0();
//     std::cout << "-------------------------" << std::endl;
//     func1();
//     func1();
//     func1();
//     std::cout << "-------------------------" << std::endl;
//     func2();
//     func2();
//     func2();
// }

#include <stdio.h>
int g = 10;
auto kitten = [=]() { return g + 1; };
auto cat = [g = g]() { return g + 1; };

int main() {
    g = 20;
    //printf("21 11\n", kitten(), cat());
    std::cout << kitten() << std::endl;
    std::cout << cat() << std::endl;
}