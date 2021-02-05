

#include <iostream>

template <typename T>
inline T help(void){
    return 3;
};

template<>
inline int help<int>(void){
    return 1;
}

template <>
inline float help<float>(void) {
    return 2.2;
}

template <typename T>
class A {
public:
    inline T v1(void) { return T{2.0}; }

    template <typename U>
    static inline U v2(void) {
        return help<U>();
    }
};

template <typename T, typename Equ>
class B {
    Equ equ;

public:
    void show(void) {
        std::cout << "v1: " << equ.v1() << '\n';
        std::cout << "v2: " << equ.template v2<float>() << '\n';
        std::cout << "v2: " << equ.template v2<int>() << '\n';
        std::cout << "v2: " << equ.template v2<double>() << '\n';
    }
};

void test_nesting(void) {
    B<float, A<float>> b;
    b.show();
}
