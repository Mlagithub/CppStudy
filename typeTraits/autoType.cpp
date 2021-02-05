
#include <iostream>
#include <type_traits>

// For recursive functions, a return value must be returned before the recursive
// call in order to let the compiler to know what will be the type of the value
// to return, as in this example
auto accumulator(int n) ->decltype(n) {
    if (n == 0)
        return 0;

    return n + accumulator(n - 1);
}

int main(void) {
    int n = 10;
    std::cout << "Input a int number: ";
    std::cin >> n;
    std::cout << "accumulate of [1-" << n << "]: " << accumulator(n) << "\n";
    return 0;
}