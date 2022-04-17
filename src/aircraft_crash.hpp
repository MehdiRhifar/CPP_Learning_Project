#pragma once
#include <iostream>
#include "geometry.hpp"


class CrashAnimation : public GL::Displayable {
public:
    CrashAnimation(Point3D pos_) :
        GL::Displayable { pos_.x() + pos_.y() },
        pos {pos_},
        textureExplose { new img::Image { MediaPath { "explosion3.png" }.get_full_path() }, 15 }
    {}

    void display() const override {
        textureExplose.draw(project_2D(pos), { PLANE_TEXTURE_DIM, PLANE_TEXTURE_DIM }, 1);
        delete this;
    }
private:
    const Point3D pos;
    const GL::Texture2D textureExplose;
    int i = 0;
};

class AircraftCrash : public std::runtime_error {
public:
    AircraftCrash(const std::string& flight_num_, Point3D pos_, float speed_, const std::string& reason_) :
        runtime_error(build_error_msg(flight_num_, pos_, speed_, reason_)),
        flight_num { flight_num_ },
        pos { pos_ },
        speed { speed_ },
        reason { reason_ }
    {
        new CrashAnimation(pos);
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
