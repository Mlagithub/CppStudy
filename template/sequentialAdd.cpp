
#include <iostream>
#include <vector>

using namespace std;

template <typename In, typename Out, typename Op = std::plus<int>>
Out inclusive_scan(In it, In end, Out to, Op op) {
    return it != end ? inclusive_scan(it + 1, end, to + 1, *to = *it) : to;
}

template <typename In, typename Out, typename Op, typename Value>
Out inclusive_scan(In it, In end, Out to, Op ope, Value value) {
    for (; it != end; ++it, ++to)
        *to = value = op(value, *it);
    return to;
}

int main(void) {

    vector<int> a{1, 2, 3, 4, 5, 6};
    vector<int> b(6, 0);

    cout << "A size : " << a.size() << '\n';
    cout << "B size : " << b.size() << '\n';

    using InIt = vector<int>::iterator;
    using OutIt = vector<int>::iterator;

    std::plus<int> plusop;

    cout << *inclusive_scan<InIt, OutIt>(a.begin(), a.end(), b.begin(), plusop)
         << '\n';

    return 0;
}
