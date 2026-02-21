#include <iostream>
#include "top.hpp"

#include <cadmium/lib/iestream.hpp>
#include "cadmium/simulation/root_coordinator.hpp"
#include <cadmium/simulation/logger/csv.hpp>
#include "cadmium/simulation/logger/logger.hpp" 

using namespace cadmium;

int main() {
    double maxSimulationTime = 20.0;
    double lambda = 0.5;

    // Model Creation
    auto model = std::make_shared<TopCoupled>("top", lambda);
    RootCoordinator rootCoordinator(model);

    rootCoordinator.setLogger<CSVLogger>("car_generate.csv", ";");


    // Run Simulation
    rootCoordinator.start();
    rootCoordinator.simulate(maxSimulationTime);
    rootCoordinator.stop(); 

    return 0;
}