#ifndef INTERSECTION_COUPLED_HPP
#define INTERSECTION_COUPLED_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "../atomics/intersection.hpp"
#include "../atomics/traffic_light.hpp"
#include "../atomics/road_segment.hpp"

using namespace cadmium;

struct IntersectionCoupled : public Coupled {
    Port<Cars> carIn;
    Port<Cars> carOut;

    IntersectionCoupled(const std::string& id) : Coupled(id) {
        // Ports of the coupled model
        
        carIn = addInPort<Cars>("carIn");
        carOut = addOutPort<Cars>("carOut");

        // Components
        auto road_1 = addComponent<Road>("road_1", 100.0, 40.0);
        auto road_2 = addComponent<Road>("road_2", 70.0, 20.0);
        auto light = addComponent<TrafficLight>("traffic_light");
        auto intersection = addComponent<Intersection>("intersection");

        // EIC (External Input Coupling): From Boundary to Atomic
        addCoupling(carIn, road_1->carEntrance);
       
        // IC: Road finishes travel time -> Car enters Intersection logic
        addCoupling(road_1->carExit, intersection->inCar);

        // IC (Internal Coupling): From Light to Atomic Logic
        addCoupling(light->outColor, intersection->inColor);

        //  EOC (External Output Coupling): From Atomic Logic to Boundary
        addCoupling(intersection->outCar, road_2->carEntrance);

        addCoupling(road_2->carExit, carOut);
    }
};
#endif