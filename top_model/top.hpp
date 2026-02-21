#ifndef TOP_HPP
#define TOP_HPP

#include <string>
#include <memory>
#include "cadmium/modeling/devs/coupled.hpp"
#include "../atomics/car_generator.hpp"
#include "../atomics/road_segment.hpp"
#include "../atomics/traffic_light.hpp"

using namespace cadmium;

struct TopCoupled : public Coupled {
    Port <Cars> top_out;
    TopCoupled(const std::string& id, double lambda) : Coupled(id) {
        
        auto carGen = addComponent<CarGenerator>("car_gen", lambda);
        //auto trafficLight = addComponent<TrafficLight>("out_color");
        auto road_1 = addComponent<Road>("road_1", 100.0, 40.0);
        top_out = addOutPort<Cars>("top_out");
        addCoupling(carGen->car_exit, road_1->car_entrance);
        addCoupling(road_1->car_exit, top_out);
    }
};

#endif