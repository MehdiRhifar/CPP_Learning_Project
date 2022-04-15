#include "aircraft_manager.hpp"
#include "aircraft.hpp"
#include "GL/dynamic_object.hpp"
#include <iostream>
#include <algorithm>

AircraftManager::AircraftManager()
{
    GL::move_queue.emplace(this);
}

void AircraftManager::move()
{
    std::sort(aircrafts.begin(), aircrafts.end(), [](const std::unique_ptr<Aircraft>& air1, const std::unique_ptr<Aircraft>& air2) {
        return air1->has_terminal() || (!air2->has_terminal() && air1->get_fuel() < air2->get_fuel());
    });


    for (auto it = aircrafts.begin(); it != aircrafts.end(); it++) {
        std::cout << ((*it)->has_terminal() ? "true" : "false") << " / with Fuel : " << (*it)->get_fuel() << " | ";
        try
        {
            (*it)->move();
        } catch (AircraftCrash& aircraftCrash)
        {
            (*it)->toRemove();
            std::cerr << aircraftCrash.what() << std::endl;
        }
    }
    std::cout << std::endl;

    auto result = std::remove_if(aircrafts.begin(), aircrafts.end(),
                   [](const std::unique_ptr<Aircraft>& item) { return item->haveToRemove(); });

    aircrafts.erase(result, aircrafts.end());
}

void AircraftManager::putAircraft(std::unique_ptr<Aircraft> aircraft) {
    std::cout << "put aircraft in aircraft manager" << std::endl;
    aircrafts.emplace_back(std::move(aircraft));
}

int AircraftManager::get_required_fuel() const
{
    return std::accumulate(aircrafts.begin(), aircrafts.end(), 0,
                                       [](unsigned int count, const std::unique_ptr<Aircraft>& aircraft)
                           {
                               assert(aircraft != nullptr);
                               if (!aircraft->is_served() && aircraft->is_low_on_fuel())
                               {
                                   return count + (aircraft->get_max_fuel() - aircraft->get_fuel());
                               }
                               return count;
                           });
}