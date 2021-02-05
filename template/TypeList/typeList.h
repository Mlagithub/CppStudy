
#pragma once

#include <iostream>
#include <map>
#include <list>

namespace TypeList {
template <typename First, typename... Rest>
struct TpList;

struct EmptyType {
    ~EmptyType() = delete;
};
struct NullType {
    ~NullType() = delete;
};
}


namespace TypeList {
namespace {
template <typename T, typename... Rest>
struct makeList_ {
    using type = TpList<T, Rest...>;
};

template <>
struct makeList_<NullType> {
    using type = NullType;
};
}
}

namespace TypeList {
template <typename First, typename... Rest>
struct TpList {
    using Head = First;
    using Tail = typename makeList_<Rest...>::type;
};

template <typename T>
struct TpList<T> {
    using Head = T;
    using Tail = NullType;
};
}

namespace TypeList {
namespace Algo {
// length
template <class TL>
struct length;
// index
template <class TL, typename T>
struct index;
// at
template <class TL, size_t N>
struct at;
// insert
template <class TL, typename F, size_t N>
struct insert;
// join
template <class TL1, class TL2>
struct join;
}
}

// length
namespace TypeList {
namespace Algo {
template <typename F, typename... L>
struct length<TpList<F, L...>> {
    enum { value = 1 + length<typename TpList<F, L...>::Tail>::value };
};

template <>
struct length<NullType> {
    enum { value = 0 };
};
};
}

// index
namespace TypeList {
namespace Algo {
template <typename T, typename F, typename... L>
struct index<TpList<F, L...>, T> {
private:
    using tail = typename TpList<F, L...>::Tail;

public:
    enum { value = index<tail, T>::value < 0 ? -1 : 1 + index<tail, T>::value };
};

template <typename T>
struct index<NullType, T> {
    enum { value = -1 };
};

template <typename F, typename... L>
struct index<TpList<F, L...>, F> {
    enum { value = 0 };
};

template <typename... L>
struct index<TpList<EmptyType, L...>, EmptyType> {
    enum { value = 0 };
};

template <typename T>
struct index<TpList<T, EmptyType>, EmptyType> {
    enum { value = 1 };
};
};
}

// at
namespace TypeList {
namespace Algo {
template <size_t N, typename F, typename... L>
struct at<TpList<F, L...>, N> {
    using type = typename at<typename TpList<F, L...>::Tail, N - 1>::type;
};

template <typename F, typename... L>
struct at<TpList<F, L...>, 0> {
    using type = typename TpList<F, L...>::Head;
};

template <typename F, typename... L>
struct at<TpList<F, L...>, -1> {
    using type = NullType;
};

};
}

// insert
namespace TypeList {
namespace Algo {
template <typename F, typename... L, typename U, size_t N>
struct insert<TpList<F, L...>, U, N>{
    using Head = typename TpList<F, L...>::Head;
    using Tail = typename insert<typename TpList<F, L...>::Tail, U, N - 1>::type;
    using type = typename join<Head, Tail>::type;
};

template <typename F, typename... L, typename U>
struct insert<TpList<F, L...>, U, 0> {
    using type = TpList<U, F, L...>;
};

}; // namespace Algo
} // namespace TypeList



// join
namespace TypeList {
namespace Algo {
template <typename F1, typename F2, typename... L1, typename... L2>
struct join<TpList<F1, L1...>, TpList<F2, L2...>> {
    using type = TpList<F1, L1..., F2, L2...>;
};

// single + TL
template<typename F1, typename ...L1, typename U>
struct join<TpList<F1, L1...>, U>{
    using type = TpList<F1, L1..., U>;
};
template <typename F1, typename... L1, typename U>
struct join<U, TpList<F1, L1...>> {
    using type = TpList<U, F1, L1...>;
};

// two single type
template <typename F1, typename F2>
struct join {
    using type = TpList<F1, F2>;
};

}; // namespace Algo
} // namespace TypeList