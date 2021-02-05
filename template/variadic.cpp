
#include <iostream>
#include <vector>


using  namespace std;


template<typename T>
void print_impl(const T& t)
{
    cout << t << '\n';
}

template<typename ... T>
void print(const T& ... t)
{
    (void)std::initializer_list<int>{ (print_impl(t), 0)... };
}

int f1()
{
    cout << "f1\n";
    return 1;
}

int f2()
{
    cout << "f1\n";
    return 2;
}

int main(void)
{

    print("Hello ", 1, 3, 4.56, "world");
    print(f1(), f2());
    return 0;
}
