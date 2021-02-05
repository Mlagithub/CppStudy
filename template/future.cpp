
#include <iostream>
#include <string>
#include <set>
#include <random>
#include <algorithm>
#include <future>

using namespace std;


std::set<int> make_sorted_random(const size_t num_ele)
{
    std::set<int> retVal;
    random_device rd;

    mt19937 gen(rd());

    std::uniform_int_distribution<> dis(0, num_ele -1);

    std::generate_n(std::inserter(retVal, retVal.end()), num_ele, [&](){return dis(gen);});

    return retVal;
}

int main()
{
    auto f1 = std::async(std::launch::async, make_sorted_random, 1000000);
    auto f2 = std::async(std::launch::async, make_sorted_random, 1000000);

    cout << f1.get().size() << "  " << f2.get().size() << '\n';
    return 0;

}
