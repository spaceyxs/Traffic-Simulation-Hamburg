#ifndef TOP_HPP
#define TOP_HPP

#include <string>
#include <memory>
#include "cadmium/modeling/devs/coupled.hpp"
#include "../atomics/car_generator.hpp"
#include "intersection_coupled.hpp"
using namespace cadmium;

struct TopCoupled : public Coupled {
    Port <Cars> topOut;
    TopCoupled(const std::string& id, double lambda) : Coupled(id) {
        
        auto carGen = addComponent<CarGenerator>("car_gen", lambda);
        auto layer1 = addComponent<IntersectionCoupled>("inter_coupled");
        topOut = addOutPort<Cars>("top_out");
        addCoupling(carGen->carExit, layer1->nodeIn);
        addCoupling(layer1->nodeOut, topOut);
    }
};

#endif