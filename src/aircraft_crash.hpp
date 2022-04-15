#pragma once
#include <iostream>
#include "geometry.hpp"

class AircraftCrash1 : public std::runtime_error {
public:
    AircraftCrash1(const std::string& flight_num_, Point3D pos_, float speed_, const std::string& reason_) :
        runtime_error(build_error_msg(flight_num_, pos_, speed_, reason_)),
        flight_num { flight_num_ },
        pos { pos_ },
        speed { speed_ },
        reason { reason_ }
    {
        COUNT_CRASH++;
    }

     inline static int COUNT_CRASH = 0;

private:
    static std::string build_error_msg(const std::string& flight_num_, Point3D pos_, float speed_, const std::string& reason) {
        return "the flight num " + flight_num_ + " for " + reason + " at " + pos_.toString() + " with speed " + std::to_string(speed_);
    }

    const std::string& flight_num;
    Point3D pos;
    float speed;
    const std::string& reason;
};



