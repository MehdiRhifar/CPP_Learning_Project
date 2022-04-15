#pragma once

#include "aircraft_manager.hpp"
#include "aircraft_factory.hpp"
#include <iostream>
#include <string>

class Airport;
struct AircraftType;

struct ContextInitializer {
public:
    ContextInitializer(int argc, char** argv) {
        MediaPath::initialize(argv[0]);
        GL::init_gl(argc, argv, "Airport Tower Simulation");
    }
};

class TowerSimulation
{
private:
    bool help        = false;
    Airport* airport = nullptr;
    ContextInitializer contextInitializer;
    AircraftManager aircraftManager;
    AircraftFactory aircraftFactory;


    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    void create_aircraft(const AircraftType& type) ;
    void create_random_aircraft() ;

    void create_keystrokes() ;
    void display_help() const;

    void init_airport();

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};
