#ifndef PROJ2_FLIGHT_H
#define PROJ2_FLIGHT_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

class Flight {
public:
    Flight(std::string source, std::string target, std::string airline);
    //static std::vector<Flight> loadFromCSV(const std::string& filename);
    std::string getSource() const;
    std::string getTarget() const;
    std::string getAirline() const;


private:
    std::string source;
    std::string target;
    std::string airline;
};


#endif //PROJ2_FLIGHT_H
