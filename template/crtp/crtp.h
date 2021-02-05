
#pragma once


#include <iostream>
#include <memory>

using namespace std;


struct AbstractConfig{
    virtual ~AbstractConfig() = default;
    virtual std::unique_ptr<AbstractConfig> clone() const = 0;
};

template<class Drived>
struct ConfigBase : public AbstractConfig{
public:
    std::unique_ptr<AbstractConfig> clone(void) const override{
        return std::make_unique<Drived>(static_cast<const Drived &>(*this));
    }

    void show(void) { static_cast<Drived *>(this)->show(); }

private:
    ConfigBase() = default;
    ConfigBase(const ConfigBase &val) = default;

private:
    friend Drived;
    float version_;
};

struct ConfigYAML : public ConfigBase<ConfigYAML>{
    ConfigYAML(const float val) : version_(val){}
    void show(void) { std::cout << "This is ConfigYAML\n"; }
private:
    float version_;
};

struct ConfigXML : public ConfigBase<ConfigXML> {
    void show(void) { std::cout << "This is ConfigXML\n"; }
};

struct ConfigAct : public ConfigBase<ConfigAct>{
    void show(void) { std::cout << "This is ConfigAct\n"; }
};




