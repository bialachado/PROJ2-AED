#ifndef PROJ2_FLIGHTNETWORKMANAGER_H
#define PROJ2_FLIGHTNETWORKMANAGER_H
#include "Airport.h"

#include <string>
#include <vector>
#include <set>
#include "Airport.h"
#include "Flight.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "Airline.h"
#include "FlightGraph.h"
#include <unordered_map>


class FlightNetworkManager {
private:
    std::vector<Airport> airports;
    std::vector<Flight> flights;

    //adições 28/12
    std::map<std::string, Airport*> airportMap;
    std::map<std::string, Airline*> airlineMap;
    std::vector<Airport*> airportsVec;
    std::vector<Airline*> airlinesVec;
    std::vector<Flight*> flightsVec;
    FlightGraph flightsGraph;

public:
    //adições 28/12
    FlightNetworkManager();
    int countCountriesByAirport(const std::string& airportCode); //3.4
    int countCountriesByCity(const std::string& cityName); //3.4
    std::map<std::string, int> countFlightsByAirline(); //3.3
    std::map<std::string, int> countFlightsByCity(); //3.3
    std::vector<std::pair<std::string, std::string> > findMaxStopRoutes();
    std::vector<std::pair<std::string, int> > topKAirports(int k); //3.8
    int countStopsForFlight(const Flight* flight); //auxiliar para 3.7
    std::string getLastDestination(const Flight* initialFlight); //auxiliar para 3.7
    unordered_map<string, int> node_keys; //novo
    void CountReachableCountriesFromAirport(const std::string& airportCode, int maxStops);
    void CountReachableAirportsFromAirport(const std::string& airportCode, int maxStops);
    void DisplayCityDestinationCountries(const std::string& city);
    void DisplayNumberOfArticulationPoints();
    void DisplayArticulationAirports();
    void DisplayTopKAirports(int k);
    void findBestFlightsAirCode(const std::string& sourceCode, const std::string& targetCode);
    std::vector<Flight*> findDirectFlights(const std::string& sourceCode, const std::string& targetCode);
    std::vector<std::vector<Flight*>> findFlightsWithMinStops(const std::string& sourceCode, const std::string& targetCode);
    void findBestFlightsAirportName(const std::string& sourceName, const std::string& targetName);
    std::string getAirportCodeByName(const std::string& airportName);
    std::vector<std::vector<Flight*>> findBestFlightsBetweenCities(const std::string& sourceCity, const std::string& targetCity);
    std::vector<std::string> getAirportsInCity(const std::string& cityName);
    void bestFlightAirportToAirportnoprint(const std::string& sourceAirportCode, const std::string& targetAirportCode, const std::vector<std::string>& airlines);









        void readFiles();
    void readAirport();
    void readAirlines();
    void readFlights();

    void numAeroportosnumVoos();
    void voosAeroporto(const string& airportCode);
    void destinosVoos(const string& airportCode);
    std::__1::set<string> destinosMAX(const string& airportCode, int max);
    void DisplayAirportDestinationCountries(string code); //3.4
    void DisplayAirlinesOperatingFromAirport(string airportCode); //3.4
    void DisplayNumberAirportsAirlinesFlights(); //3.1
    void ReachableDestinations(string code); //3.5
    void getFlightsByAirline(const string& airlineCode) const; //3.3
    void getFlightsByCity(const string& cityName) const; //3.3
    void DirectFlightsCountFromAirport(std::string& code); //3.2
    void TargetsCountFromSourceWithMaxStops(const string& code, int maxStops);
    void findMaximumStopFlight();
    int getGraphDiameter();
    void findDiameterAndCorrespondingNodes();
    void CountFlightsWithStopsFromAirport(std::string code, int stops);
    void CountReachableCitiesFromAirport(const std::string& airportCode, int maxStops);

    vector<vector<Flight *>>
    findBestFlightsByCoordinates(double sourceLat, double sourceLong, double targetLat, double targetLong);

    double degreeToRadian(double degree);

    double calculateDistance(double lat1, double long1, double lat2, double long2);

    std::vector<Airport> findNearestAirports(double lat, double longi, int maxResults);
    vector<vector<vector<Flight *>>> findBestFlightOptions(double srcLat, double srcLong, double destLat, double destLong);
    void bestFlightsCityToCity(std::string sourceCountry, std::string sourceCity, std::string targetCountry,
                                                          std::string targetCity, vector<std::string> airlinesAllowed);
    void bestFlightAirportToAirport(const std::string& sourceAirportCode, const std::string& targetAirportCode, const std::vector<std::string>& airlines);

    double computeDistance(const vector<Flight*> &v);
    double airportregDistance(const string& src, const string& dest);
    bool isConnected(int i, int k);
    void bestFlightCoord(double sourceLongitude, double sourceLatitude, double targetLongitude,
                                                           double targetLatitude, double radius, vector<std::string> airlinesAllowed);
    bool airportCordDistance(Airport *airport, const double &longi, const double &lat, double x);
    void bestFlightAirportToAirportname(const std::string& sourceAirportName, const std::string& targetAirportName, const std::vector<std::string>& airlines);
    void bestFlightAirportToAirportNameCode(const std::string& sourceAirportName, const std::string& targetAirportCode, const std::vector<std::string>& airlines);
    void bestFlightAirportToAirportCodeName(const std::string& sourceAirportCode, const std::string& targetAirportName, const std::vector<std::string>& airlines);
    void bestFlightsCityToCitycodecity(string sourceAirportCode,std::string targetCountry, std::string targetCity, vector<std::string> airlinesAllowed);
    void bestFlightsCityToCitycitycode(std::string sourceCountry, std::string sourceCity,std::string targetAirportCode, vector<std::string> airlinesAllowed);

};

#endif //PROJ2_FLIGHTNETWORKMANAGER_H
