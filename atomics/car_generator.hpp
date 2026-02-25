#ifndef CAR_GENERATOR_HPP
#define CAR_GENERATOR_HPP

#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include "cadmium/modeling/devs/atomic.hpp"
#include "../data_structures/cars.hpp"

using namespace cadmium;
struct GeneratorState {
    int count;
    
    std::default_random_engine generator;
    std::exponential_distribution<double> distribution;
    double sigma;
    
    explicit GeneratorState(double lambda)
    : count(0), distribution(lambda), sigma(0.0) {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const GeneratorState& state) {
    out << "{car_count: " << state.count << "}";
    return out;
}
#endif

// Atomic Model: Car Generator that creates car with exponential distribution.
class CarGenerator : public Atomic<GeneratorState> {
public:
    Port<Cars> carExit;

    CarGenerator(const std::string& id, double lambda)
        : Atomic<GeneratorState>(id, GeneratorState(lambda)) {
        carExit = addOutPort<Cars>("carExit");
    }

    void internalTransition(GeneratorState& state) const override {
        state.count++;
        //Set sigma with expo dist
        state.sigma = state.distribution(state.generator);
    }

	void externalTransition(GeneratorState& state, double e) const override {}
    
    void output(const GeneratorState& state) const override {
        carExit->addMessage(Cars(state.count));
    }

    [[nodiscard]] double timeAdvance(const GeneratorState& state) const override {     
        return state.sigma;
    }
};

#endif 