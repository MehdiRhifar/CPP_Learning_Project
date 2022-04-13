#pragma once

#include "aircraft_manager.hpp"
#include "airport.hpp"
#include <set>

class AircraftFactory {
public :
    void create_aircraft(const AircraftType& type, Airport& airport, AircraftManager& aircraftManager)
    {
//        assert(airport); // make sure the airport is initialized before creating aircraft

        const std::string flight_number = get_flight_number();
        const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
        const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
        const Point3D direction = (-start).normalize();

        aircraftManager.putAircraft(std::make_unique<Aircraft>(type, flight_number, start, direction, airport.get_tower()));
    }

    void create_random_aircraft(Airport& airport, AircraftManager& aircraftManager)
    {
        create_aircraft(*(aircraft_types[rand() % 3]), airport, aircraftManager);
    }

private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    static const size_t NUM_AIRCRAFT_TYPES = 3;
    const AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {
        new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } },
        new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } },
        new AircraftType { .03f, .08f, .03f, MediaPath { "concorde_af.png" } }
    };

    std::set<std::string> all_flight_number;

    const std::string& get_flight_number() {
        auto res = all_flight_number.insert(airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000)));
        while (!res.second) { //flight number already exist
            res = all_flight_number.insert(airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000)));
        }
        return *res.first;
    }
};