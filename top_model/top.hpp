#ifndef TOP_HPP
#define TOP_HPP

#include <string>
#include <memory>
#include "cadmium/modeling/devs/coupled.hpp"
#include "../atomics/car_generator.hpp"

using namespace cadmium;

struct TopCoupled : public Coupled {
    Port <Cars> top_out;
    TopCoupled(const std::string& id, double lambda) : Coupled(id) {
        
        auto carGen = addComponent<CarGenerator>("car_gen", lambda);
        top_out = addOutPort<Cars>("top_out");
        addCoupling(carGen->car_exit, top_out);
    }
};

#endif