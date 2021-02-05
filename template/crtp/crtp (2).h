
#pragma once

#include <memory>
#include <string>

template <class Base, class Drived>
class Cloneable : public Base {
public:
    using Base::Base;
    std::shared_ptr<Base> clone(void) const override {
        return std::make_shared<Drived>(static_cast<const Drived &>(*this));
    }

private:
    friend Drived;
};

template <class Base, class Drived>
struct CloneableInherit : public Base {
public:
    using Base::Base;
    std::shared_ptr<Base> clone(void) const {
        return std::make_shared<Drived>(static_cast<const Drived &>(*this));
    }

private:
    friend Drived;
};

class BA {
public:
    BA()          = default;
    virtual ~BA() = default;
    virtual void show(void) = 0;

public:
    virtual std::shared_ptr<BA> clone(void) const = 0;
};

class A : public CloneableInherit<BA, A> {
public:
    A() = default;
    void show(){}
};

struct Reader {
public:
    Reader()                                    = default;
    virtual ~Reader()                           = default;
    virtual std::shared_ptr<Reader> clone(void) const = 0;
    virtual void read(const std::string &fname) = 0;

};

struct ReaderYAML : public CloneableInherit<Reader, ReaderYAML> {
public:
    void read(const std::string &fname) override {}
};