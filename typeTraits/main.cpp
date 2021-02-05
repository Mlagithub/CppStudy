
#include <iostream>
#include <type_traits>
#include <map>

using namespace std;



template<auto n>
auto f() -> pair<decltype(n), decltype(n)>{
    return {n, n};
}


int main(void){

    auto i = f<3>();

    cout << typeid(i).name() << '\n';

    cout << i.first << '\n';

    return 0;
}
