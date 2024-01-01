#include "Flight.h"


Flight::Flight(std::string source, std::string target, std::string airline):
    source(source), target(target), airline(airline)
{}

std::string Flight::getSource() const {
    return source;
}

std::string Flight::getTarget() const {
    return target;
}

std::string Flight::getAirline() const {
    return airline;
}




/*
std::vector<Flight> Flight::loadFromCSV(const std::string& filename){
    std::vector<Flight> flights;
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string source, target, airline;

        std::getline(ss, source, ',');
        std::getline(ss, target, ',');
        std::getline(ss, airline, ',');


        flights.emplace_back(source, target, airline);
    }

    return flights;
}
*/


