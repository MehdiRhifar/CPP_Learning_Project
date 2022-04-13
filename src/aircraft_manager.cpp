#include "aircraft_manager.hpp"
#include "aircraft.hpp"
#include "GL/dynamic_object.hpp"
#include <iostream>

AircraftManager::AircraftManager()
{
    GL::move_queue.emplace(this);
}

void AircraftManager::move()
{
    for (auto it = aircrafts.begin(); it != aircrafts.end();) {
        (*it)->move();
        if ((*it)->haveToRemove()) {
            it = aircrafts.erase(it);
        }
        else {
            it++;
        }
    }
}

void AircraftManager::putAircraft(std::unique_ptr<Aircraft> aircraft) {
    std::cout << "put aircraft in aircraft manager" << std::endl;
    aircrafts.emplace_back(std::move(aircraft));
}
