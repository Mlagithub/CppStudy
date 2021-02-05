
#pragma once

#include <iostream>

using namespace std;

class Vehicle {
protected:
    int fuelCapacity;

public:
    Vehicle() {}
    Vehicle(int fuelCapacity) : fuelCapacity(fuelCapacity) {}
    virtual ~Vehicle() {}
    virtual Vehicle *clone() const = 0;

    virtual void describe() const = 0;
};

template <typename Base, typename Derived>
class VehicleCloneable : public Base {
public:
    using Base::Base;
    virtual Base *clone() const {
        return new Derived(static_cast<Derived const &>(*this));
    }
};

class Car : public VehicleCloneable<Vehicle, Car> {
private:
    typedef VehicleCloneable<Vehicle, Car> BaseClass;

public:
    Car() {}
    Car(int fuelCapacity) : BaseClass(fuelCapacity) {}

    virtual void describe() const { std::cout << "I am a car" << std::endl; }
};

class Plane : public VehicleCloneable<Vehicle, Plane> {
private:
    typedef VehicleCloneable<Vehicle, Plane> BaseClass;

protected:
    int wingSpan;

public:
    Plane() {}
    Plane(int fuelCapacity, int wingSpan)
        : BaseClass(fuelCapacity), wingSpan(wingSpan) {}

    virtual void describe() const { std::cout << "I am a plane" << std::endl; }
};

class FighterPlane : public VehicleCloneable<Plane, FighterPlane> {
private:
    typedef VehicleCloneable<Plane, FighterPlane> BaseClass;

protected:
    int numberOfBombs;

public:
    FighterPlane() {}
    FighterPlane(int fuelCapacity, int wingSpan, int numberOfBombs)
        : BaseClass(fuelCapacity, wingSpan), numberOfBombs(numberOfBombs) {}

    virtual void describe() const {
        std::cout << "I am a fighter plane" << std::endl;
    }
};