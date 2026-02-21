#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"
#include "../data_structures/constants.hpp"


using namespace cadmium;

struct TrafficLightState {
    LightColor color;
    double sigma;
    explicit TrafficLightState()
    : color(GREEN), sigma(0.0) {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const TrafficLightState& state) {
    std::string colors[] = {"RED", "YELLOW", "GREEN"};
    out << "{color: " << colors[(int)state.color] << "}";
    return out;
}
#endif

// Atomic Model: Traffic Light that gives color information to the road model.
class TrafficLight : public Atomic<TrafficLightState> {
public:
    Port<LightColor> out_color;

    TrafficLight(const std::string& id)
        : Atomic<TrafficLightState>(id, TrafficLightState()) {
        out_color = addOutPort<LightColor>("out_color");
    }

    void internalTransition(TrafficLightState& state) const override {
        if (state.color == GREEN) {
            state.color = YELLOW;
            state.sigma = 2.0; 
        } else if (state.color == YELLOW) {
            state.color = RED;
            state.sigma = 5.0;
        } else{
            state.color = GREEN;
            state.sigma = 7.0;
        }

    }

	void externalTransition(TrafficLightState& state, double e) const override {}
    
    void output(const TrafficLightState& state) const override {
        out_color->addMessage(LightColor(state.color));
    }

    [[nodiscard]] double timeAdvance(const TrafficLightState& state) const override {  
        return state.sigma;
    }
};

#endif 