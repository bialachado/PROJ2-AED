//
// Created by Francisca Fernandes on 17/12/2023.
//

#include "Airport.h"
#include <fstream>
#include <sstream>

Airport::Airport(std::string code, std::string name, std::string city,
                 std::string country, double latitude, double longitude)
        : airportCode(code), airportName(name), city(city), country(country),
        latitude(latitude), longitude(longitude){}



std::string Airport::getCode() const {
    return airportCode;
}

std::string Airport::getName() const {
    return airportName;
}

std::string Airport::getCity() const {
    return city;
}

std::string Airport::getCountry() const {
    return country;
}

double Airport::getLat() const {
    return latitude;
}

double Airport::getLong() const {
    return longitude;
}



/*
std::vector<Airport> Airport::loadAirports(const std::string& filename) {
    std::vector<Airport> airports;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string code, name, city, country, latitude, longitude;

        std::getline(ss, code, ',');
        std::getline(ss, name, ',');
        std::getline(ss, city, ',');
        std::getline(ss, country, ',');
        std::getline(ss, latitude, ',');
        std::getline(ss, longitude, ',');

        airports.emplace_back(code, name, city, country, latitude, longitude);
    }

    return airports;
}
 */







void Airport::setCode(string code) {
    airportCode = code;
}
