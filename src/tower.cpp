#include "tower.hpp"

#include "airport.hpp"
#include "terminal.hpp"

#include <cassert>
#include <algorithm>

WaypointQueue Tower::get_circle() const
{
    return { { Point3D { -1.5f, -1.5f, .5f }, wp_air },
             { Point3D { 1.5f, -1.5f, .5f }, wp_air },
             { Point3D { 1.5f, 1.5f, .5f }, wp_air },
             { Point3D { -1.5f, 1.5f, .5f }, wp_air } };
}

WaypointQueue Tower::get_instructions(Aircraft& aircraft)
{
    if (!aircraft.is_at_terminal)
    {
        // if the aircraft is far, then just guide it to the airport vicinity
        if (aircraft.distance_to(airport.pos) < 5)
        {
            // try and reserve a terminal for the craft to land
            const auto vp = airport.reserve_terminal(aircraft);
            if (!vp.first.empty())
            {
                reserved_terminals.insert_or_assign(&aircraft, vp.second);
//                reserved_terminals.emplace_back(&aircraft, vp.second);
                return vp.first;
            }
            else
            {
                return get_circle();
            }
        }
        else
        {
            std::cout << "So far, have to be removed\n";
            aircraft.toRemove();
            return {};
        }
    }
    else
    {
        // get a path for the craft to start
        const auto it = find_craft_and_terminal(aircraft);
        assert(it != reserved_terminals.end());
        const auto terminal_num = it->second;
        Terminal& terminal      = airport.get_terminal(terminal_num);
        if (!terminal.is_servicing())
        {
            terminal.finish_service();
            reserved_terminals.erase(it);
            aircraft.is_at_terminal = false;
            aircraft.served = true;
            return airport.start_path(terminal_num);
        }
        else
        {
            return {};
        }
    }
}

WaypointQueue Tower::reserve_terminal(Aircraft& aircraft) {
    const auto vp = airport.reserve_terminal(aircraft);
    if (!vp.first.empty())
    {
        reserved_terminals.insert_or_assign(&aircraft, vp.second);
    }
    return vp.first;
}

void Tower::arrived_at_terminal(const Aircraft& aircraft)
{
    const auto it = find_craft_and_terminal(aircraft);
    assert(it != reserved_terminals.end());
    airport.get_terminal(it->second).start_service(aircraft);
}

void Tower::remove(Aircraft& aircraft)
{
    assert(&aircraft);

    const auto it = reserved_terminals.find(&aircraft);
    if (it != reserved_terminals.end()) {
        airport.get_terminal(it->second).free();
        reserved_terminals.erase(it);
    }
}
