
#pragma once

#include <iostream>

template <typename T>
class DotProduct {
public:
    virtual ~DotProduct() {}
    virtual T eval() = 0;
};

template <typename T>
class SimpleDotProduct : public DotProduct<T> {
public:
    SimpleDotProduct(T *a, T *b) : v1(a), v2(b) {}

    virtual T eval() { return (*v1) * (*v2); }

private:
    T *v1;
    T *v2;
};

template <typename T>
class ComDotProduct : public DotProduct<T> {
public:
    ComDotProduct(T *a, T *b, size_t dim)
        : s(new SimpleDotProduct<T>(a, b)),
          c((dim == 1) ? 0 : new ComDotProduct<T>(a + 1, b + 1, dim - 1)) {}

    virtual ~ComDotProduct() {
        delete c;
        delete s;
    }

    virtual T eval() { return (s->eval() + ((c) ? c->eval() : 0)); }

protected:
    SimpleDotProduct<T> *s;
    ComDotProduct<T> *c;
};

template <typename T>
T dot(T *a, T *b, size_t dim) {
    return (dim == 1) ? SimpleDotProduct<T>(a, b).eval()
                      : ComDotProduct<T>(a, b, dim).eval();
};
