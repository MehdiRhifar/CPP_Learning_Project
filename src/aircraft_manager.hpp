#pragma once

#include "GL/dynamic_object.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <set>

class Aircraft;

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    AircraftManager();
    void move() override;
    void putAircraft(std::unique_ptr<Aircraft> aircraft);
    int get_required_fuel () const;
};
