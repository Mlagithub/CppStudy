
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>


using namespace std;


int main(void)
{

    std::random_device rd;
    std::mt19937 gen(rd());

    cout << gen.min() << endl;
    cout << gen.max() << endl;

    std::uniform_int_distribution<> dist(-10, 10);
    std::vector<int> v;
    generate_n(back_inserter(v), 20, bind(dist, gen));

    std::cout << "Before sort: ";
    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

    sort(v.begin(), v.end());

    std::cout << "\nAfter sort: ";
    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;

    return 0;
}
