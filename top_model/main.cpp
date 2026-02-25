#include <iostream>
#include "top.hpp"
#include <string>
#include <cadmium/lib/iestream.hpp>
#include "cadmium/simulation/root_coordinator.hpp"
#include <cadmium/simulation/logger/csv.hpp>
#include "cadmium/simulation/logger/logger.hpp" 

using namespace cadmium;

int main() {
    std::ifstream f;
    std::string road_name;
    double maxSimulationTime = 20.0;
    double lambda_peak = 0.0;
    double dtvw = 0.0; //Durchschnittlicher Täglicher Verkehr = Average Daily Traffic
    std::string inputFile = "input_data/car-generators.csv";
    // Load data
    f.open(inputFile);
    if (!f.is_open()) {
        return 1;
    }
    std::string line;
    std::getline(f, line); 

    
    while (std::getline(f, line)) {

        size_t comma_pos = line.find(',');
        std::string road_name = line.substr(0, comma_pos);
        double dtvw = std::stod(line.substr(comma_pos + 1));

        double lambda_peak = (dtvw * 0.10) / 3600.0;

        std::string outputFile = "test/rush_hour_" + road_name + ".csv";

        auto model = std::make_shared<TopCoupled>("top", lambda_peak);

        RootCoordinator rootCoordinator(model);
        rootCoordinator.setLogger<CSVLogger>(outputFile, ";");

        rootCoordinator.start();
        rootCoordinator.simulate(maxSimulationTime);
        rootCoordinator.stop();
    }

    f.close();
    return 0;
}