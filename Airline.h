//
// Created by Francisca Fernandes on 17/12/2023.
//

#ifndef PROJ2_AIRLINE_H
#define PROJ2_AIRLINE_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
class Airline {
public:
    Airline(std::string code, std::string name, std::string callsign, std::string country);
    //static std::vector<Airline> loadFromCSV(const std::string& filename);

    std::string getCode() const;
    std::string getName() const;
    std::string getCallsign() const;
    std::string getCountry() const;


private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;


    };


#endif //PROJ2_AIRLINE_H
