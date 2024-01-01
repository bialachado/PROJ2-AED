#include "Airline.h"

Airline::Airline(std::string code, std::string name, std::string callsign, std::string country) :
        code(code), name(name), callsign(callsign), country(country) {}

std::string Airline::getCode() const {
    return code;
}

std::string Airline::getName() const {
    return name;
}

std::string Airline::getCallsign() const {
    return callsign;
}

std::string Airline::getCountry() const {
    return country;
}


/*
std::vector<Airline> Airline::loadFromCSV(const std::string& filename) {
    std::vector<Airline> airlines;
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string code, name, callsign, country;

        std::getline(ss, code, ',');
        std::getline(ss, name, ',');
        std::getline(ss, callsign, ',');
        std::getline(ss, country, ',');


        airlines.emplace_back(code, name, callsign, country);
    }

    return airlines;
}
*/
