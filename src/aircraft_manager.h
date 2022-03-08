////#pragma once
//
//#include <vector>
//#include <iostream>
//#include <memory>
//#include "aircraft.hpp"
//#include "GL/dynamic_object.hpp"
//
//class AircraftManager : public GL::DynamicObject {
//
//private:
//    std::vector<std::unique_ptr<Aircraft>> aircrafts;
//
//public:
//    void move() override {
//        for (auto it = aircrafts.begin(); it != aircrafts.end();) {
//            (*it)->move();
//            if ((*it)->haveToRemove()) {
//                it = aircrafts.erase(it);
//            }
//            else {
//                it++;
//            }
//        }
//    }
//
//    void putAircraft(std::unique_ptr<Aircraft> aircraft) {
//        aircrafts.emplace_back(std::move(aircraft));
//    }
//};