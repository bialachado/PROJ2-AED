//
// Created by Francisca Fernandes on 17/12/2023.
//
using namespace std;
#include <string>
#include <vector>

#ifndef PROJ2_AIRPORT_H
#define PROJ2_AIRPORT_H


class Airport {
public:
    Airport(std::string code, std::string name, std::string city,
            std::string country, double latitude, double longitude);

    static std::vector<Airport> loadAirports(const std::string& filename);

    std::string getCode() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    double getLat() const;
    double getLong() const;
    void setCode(string basicString);

private:
    std::string airportCode;
    std::string airportName;
    std::string city;
    double longitude;
    string country;
    double latitude;
};



#endif //PROJ2_AIRPORT_H
