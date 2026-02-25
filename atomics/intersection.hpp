#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <iostream>
#include <vector>
#include <string>
#include "cadmium/modeling/devs/atomic.hpp"
#include "../data_structures/cars.hpp"
#include "../data_structures/constants.hpp"
#include "traffic_light.hpp"

using namespace cadmium;

struct IntersectionState {
    double sigma;
    bool hasCar;
    Cars currentCar;
    LightColor currentColor;

    explicit IntersectionState(): sigma(infinity), hasCar(false) {} 
}; 

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const IntersectionState& state) {
    return out << "HasCar: " << (state.hasCar ? "Yes" : "No") ;
}
#endif

// Atomic DEVS model of a single-entry, single-exit intersection.
class Intersection : public Atomic<IntersectionState> {
public:
    Port<Cars> inCar; 
    Port<Cars> outCar; 
    Port<LightColor> inColor;

    Intersection(const std::string id): 
                 Atomic<IntersectionState>(id, IntersectionState()) {
        inCar = addInPort<Cars>("inCar");
        outCar = addOutPort<Cars>("outCar");
        inColor = addInPort<LightColor>("inColor");
    }

    // After the car is sent, reset to idle state
    void internalTransition(IntersectionState& state) const override {
        state.hasCar = false; 
        state.sigma = infinity; 
    }

    // When a car arrives, prepare to send it immediately
    void externalTransition(IntersectionState& state, double e) const override {
        if (!inColor->getBag().empty()) {
            state.currentColor = inColor->getBag().back();
        }

        if (!inCar->getBag().empty()) {
            state.currentCar = inCar->getBag().back();
            state.hasCar = true;
        }

        if (state.hasCar && state.currentColor == GREEN ||state.currentColor == YELLOW ) {
            state.sigma = 0.0; // Trigger output immediately
        } else {
            state.sigma = infinity; // Wait for light to turn green
        }
    }

    // Send the car through the single output port
    void output(const IntersectionState& state) const override {
        outCar->addMessage(state.currentCar);
    }

    [[nodiscard]] double timeAdvance(const IntersectionState& state) const override {     
        return state.sigma;
    }
};

#endif // INTERSECTION_HPP