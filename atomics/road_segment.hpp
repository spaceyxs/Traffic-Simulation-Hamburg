#ifndef ROAD_SEGMENT_HPP
#define ROAD_SEGMENT_HPP

#include <iostream>
#include <deque>
#include "cadmium/modeling/devs/atomic.hpp"
#include "../data_structures/cars.hpp"
#include "../data_structures/constants.hpp"


using namespace cadmium;

struct RoadState{
    double sigma;
    double length;
    double speedLimit;
    std::deque<double> carDepartureTimes;

    std::deque<Cars> CarsOnRoad; // Car queue on the road
    explicit RoadState() : sigma(infinity) {}; 

};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const RoadState& state) {
     out << "{queue_size: " << state.CarsOnRoad.size()
        << ", sigma: " << state.sigma << "}";
    return out;
}
#endif

// Atomic model: Road model that use OD data.
class Road : public Atomic<RoadState> {
public:
    Port<Cars> carEntrance, carExit;
    //std::string originId; // intersection car init
    //std::string destId;

    Road(const std::string id, int length, int speedLimit) : 
        Atomic<RoadState>(id, RoadState()) {
        carEntrance = addInPort<Cars>("carEntrance");
        carExit = addOutPort<Cars>("carExit");

        state.length = length; 
        state.speedLimit = speedLimit;
    }

    void internalTransition(RoadState& state) const override {
        // Car exits road.
        // The time at the front of queue is the elapsed time
        double elapsedTime = state.carDepartureTimes.front();
        // Update remaining departure times
        for(int i = 1; i < state.carDepartureTimes.size(); i++){
            state.carDepartureTimes[i] = state.carDepartureTimes[i] - elapsedTime;
        }
        // Romeving departed car's time 
        state.carDepartureTimes.pop_front();

        // Set sigma to next car's departure time.
        if(!state.carDepartureTimes.empty()){
            state.sigma = state.carDepartureTimes.front();
        }else {
            state.sigma = infinity;
        }
        
        if(!state.CarsOnRoad.empty()){
            state.CarsOnRoad.pop_front(); //remove vechile exiting road
        }
    
        // Elapsed time going to change with pop_front for next internal transition event.


    }

	void externalTransition(RoadState& state, double e) const override {
        // Car enters road. 

        // Update all departure times based on elapsed time.

        for (int i = 0; i < state.carDepartureTimes.size(); i++) {
            state.carDepartureTimes[i] = state.carDepartureTimes[i] - e;
            
        }

        // Calculate how long the car that entered takes to travel the road.
        //
        // Assume cars travel the speed limit; ignore accelaration and deceleration.
        double lengthInKm = state.length / 1000;
        double hours = lengthInKm / state.speedLimit;
        double minutes = hours * 60;
        double TravelTime = minutes * 60;


        if (!carEntrance->getBag().empty()) {
            Cars c = carEntrance->getBag().back();
            state.CarsOnRoad.push_back(c);   // add vehicle to road queue
        }

        // Schedule car to exit the road.
        state.carDepartureTimes.push_back(TravelTime);
        state.sigma = state.carDepartureTimes.front();
    
    }
    
    void output(const RoadState& state) const override {
         if (!state.CarsOnRoad.empty()) {
            carExit->addMessage(state.CarsOnRoad.front());
        }
    }

    [[nodiscard]] double timeAdvance(const RoadState& state) const override {     
        return state.sigma;
    }
};

#endif 