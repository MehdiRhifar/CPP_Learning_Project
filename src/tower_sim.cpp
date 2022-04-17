#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"
#include "aircraft_crash.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) },
    contextInitializer(argc, argv)
{

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_aircraft(const AircraftType& type)
{
    assert(airport); // make sure the airport is initialized before creating aircraft

    aircraftFactory.create_aircraft(type, *airport, aircraftManager);

//    const std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
//    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
//    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
//    const Point3D direction = (-start).normalize();
//
////    Aircraft* aircraft = new Aircraft { type, flight_number, start, direction, airport->get_tower() };
//
//
////    std::unique_ptr aircraft_unique = std::make_unique<Aircraft>(type, flight_number, start, direction, airport->get_tower());
////    aircraftManager.putAircraft(std::move(aircraft_unique));
//
////    GL::display_queue.emplace_back(aircraft); FAIT AUTOMATIQUEMENT MAINTENANT
//    aircraftManager.putAircraft(std::make_unique<Aircraft>(type, flight_number, start, direction, airport->get_tower()));
//    GL::move_queue.emplace(aircraft);
}

void TowerSimulation::create_random_aircraft()
{
    aircraftFactory.create_random_aircraft(*airport, aircraftManager);
//    create_aircraft(*(aircraft_types[rand() % 3]));
}

void TowerSimulation::create_keystrokes()
{
    // J'ai commenté car sur mon pc, le programme se ferme automatiquement si ces touches sont disponible...
//    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
//    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { create_random_aircraft(); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    // added
    GL::keystrokes.emplace('w', []() { GL::decrease_framerate(); });
    GL::keystrokes.emplace('x', []() { GL::increase_framerate(); });
    GL::keystrokes.emplace(' ', []() { GL::switch_pause(); });


    GL::keystrokes.emplace('0', [this]() { aircraftFactory.print_number_airline(0); });
    GL::keystrokes.emplace('1', [this]() { aircraftFactory.print_number_airline(1); });
    GL::keystrokes.emplace('2', [this]() { aircraftFactory.print_number_airline(2); });
    GL::keystrokes.emplace('3', [this]() { aircraftFactory.print_number_airline(3); });
    GL::keystrokes.emplace('4', [this]() { aircraftFactory.print_number_airline(4); });
    GL::keystrokes.emplace('5', [this]() { aircraftFactory.print_number_airline(5); });
    GL::keystrokes.emplace('6', [this]() { aircraftFactory.print_number_airline(6); });
    GL::keystrokes.emplace('7', [this]() { aircraftFactory.print_number_airline(7); });


    GL::keystrokes.emplace('m', []() { std::cout << "number of crash  : " << AircraftCrash::COUNT_CRASH << std::endl; });
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key, function] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() }, aircraftManager };

    GL::move_queue.emplace(airport);
//    GL::display_queue.emplace_back(airport); already in
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();
    GL::loop();
}
