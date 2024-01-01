#include "FlightNetworkManager.h"
#include "Airport.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <queue>
#include <map>
#include <unordered_set>
#include <cmath>



using namespace std;

/* Parsing e funções base*/
FlightNetworkManager::FlightNetworkManager() :
        airportMap({}),
        airlineMap({}),
        flightsGraph(3019, false) // Supondo que FlightGraph recebe o número de nós e um bool para direcionado/indirecionado
{
}

void FlightNetworkManager::readFiles() {
    readAirport();
    readAirlines();
    readFlights();
    flightsGraph.vectorToGraph(airportsVec, flightsVec);
}

void FlightNetworkManager::readAirport() {
    std::string location = "../Data/airports.csv";
    string line;
    string code, name, city, country, latitude, longitude;
    ifstream file(location);

    if(file.is_open()){
        getline(file, line);
        int index = 1;
        while (getline(file,line)){
            stringstream ss(line);
            getline(ss, code, ',');
            getline(ss, name, ',');
            getline(ss, city, ',');
            getline(ss, country, ',');
            getline(ss, latitude, ',');
            getline(ss,longitude,',');

            airportMap.insert(pair<string, Airport*>(code, new Airport(code,name,city,country, ::strtof(latitude.c_str(), nullptr),::strtof(longitude.c_str(),nullptr))));
            node_keys.insert(pair<string, int>(code, index));
            index++;
            airportsVec.push_back(new Airport(code,name,city,country, ::strtof(latitude.c_str(), nullptr),::strtof(longitude.c_str(),nullptr)));
        }
        file.close();
    } else {
        std::cerr << "Erro no processamento do arquivo dos aeroportos ('aiports.csv')." << std::endl;
    }
}

void FlightNetworkManager::readAirlines() {
    std::string location = "../Data/airlines.csv";
    string line;
    string code, name, callsign, country;
    ifstream file(location);

    if(file.is_open()){
        getline(file, line);

        while (getline(file,line)){
            stringstream ss(line);
            getline(ss, code, ',');
            getline(ss, name, ',');
            getline(ss, callsign, ',');
            getline(ss, country, ',');

            airlinesVec.push_back(new Airline(code,name,callsign,country));
            airlineMap.insert(pair<string, Airline*>(code, new Airline(code, name, callsign, country)));
        }
        file.close();
    } else {
        std::cerr << "Error processing airline file ('airlines.csv')." << std::endl;
    }
}

void FlightNetworkManager::readFlights() {
    std::string location = "../Data/flights.csv";
    string line;
    string source,target,airline;
    ifstream file(location);

    if(file.is_open()){
        getline(file, line);

        while (getline(file,line)){
            stringstream ss(line);
            getline(ss, source, ',');
            getline(ss, target, ',');
            getline(ss, airline, ',');

            flightsVec.push_back(new Flight(source,target,airline));
        }
        file.close();
    } else {
        std::cerr << "Error processing flights file ('flights.csv')" << std::endl;
    }
}



// Função para contar países para os quais um aeroporto viaja - 3.4
int FlightNetworkManager::countCountriesByAirport(const std::string& airportCode) {
    std::set<std::string> countries;
    for (const Flight* flight : flightsVec) {
        if (flight->getSource() == airportCode) {
            std::string country = airportMap[flight->getTarget()]->getCountry();
            countries.insert(country);
        }
    }
    return countries.size();
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
/////////////////////////////////////////////FUNÇÕES PONTO 3\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/////////////////////////////////////////////3.1\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void FlightNetworkManager::DisplayNumberAirportsAirlinesFlights(){
    cout<< "\e[1mNumber of data present \e[0m "<< endl;
    cout<<"Total number of Airports: "<< airportsVec.size() << endl;
    cout<<"Total number of Airlines: "<< airlinesVec.size()<< endl;
    cout<<"Total number of Flights: "<< flightsVec.size()<< endl;

}

/////////////////////////////////////////////3.2\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// Nº de voos diretos realizados a partir de um aeroporto e o nr de companhias que os realizam
void FlightNetworkManager::DirectFlightsCountFromAirport(std::string& code) {
    auto searchIt = node_keys.find(code);
    if (searchIt != node_keys.end()) {
        int airportIndex = searchIt->second;
        auto [directFlightsCount, uniqueAirlines] = flightsGraph.countDirectFlightsAndAirlines(code, airportIndex);

        cout << "Number of direct flights departing from the airport with code " << code << ": " << directFlightsCount << endl;
        cout << "Number of airlines operating these flights: " << uniqueAirlines.size() << endl;
    } else {
        cout << "Airport code not found: " << code << endl;
    }
}


/////////////////////////////////////////////3.3\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// Número de voos realizados por uma determinada companhia aérea, nº e nome de aeroportos nos quais a companhia atua
void FlightNetworkManager::getFlightsByAirline(const string& airlineCode) const {
    unordered_set<string> uniqueAirports;
    int nVoos = 0;
    bool airlineFound = false;

    if (airlineMap.find(airlineCode) == airlineMap.end()) {
        cout << "Error: Airline with code '" << airlineCode << "' not found." << endl;
        return;
    }

    for (const auto& flight : flightsVec) {
        if (flight->getAirline() == airlineCode) {
            nVoos++;
            uniqueAirports.insert(flight->getSource());
            airlineFound = true;
        }
    }

    if (airlineFound) {
        cout << "Number of Flights: " << nVoos << endl;
        cout << "Number of Airports: " << uniqueAirports.size() << endl;
        cout << "Airports List: " << endl;
        cout << "Airport Name -> City, Country" << endl;

        for (const auto& airportCode : uniqueAirports) {
            auto airportIt = airportMap.find(airportCode);
            if (airportIt != airportMap.end()) {
                auto airport = airportIt->second;
                cout << airport->getName() << " -> " << airport->getCity() << ", " << airport->getCountry() << endl;
            }
        }
        cout << endl;
    } else {
        cout << "No flights found for airline with code '" << airlineCode << "'." << endl;
    }
}


// Número de voos que saem/chegam a uma cidade, aeroportos na cidade
void FlightNetworkManager::getFlightsByCity(const string& cityName) const {
    unordered_set<string> uniqueAirports;
    unordered_set<string> uniqueArrivalAirports;
    int nVoos = 0;
    int nVoosChegada = 0;

    bool cityFound = false;

    for (const auto& flight : flightsVec) {
        auto airportIt = airportMap.find(flight->getSource());
        if (airportIt != airportMap.end() && airportIt->second->getCity() == cityName) {
            nVoos++;
            uniqueAirports.insert(flight->getSource());
            cityFound = true;
        }

        auto arrivalAirportIt = airportMap.find(flight->getTarget());
        if (arrivalAirportIt != airportMap.end() && arrivalAirportIt->second->getCity() == cityName) {
            nVoosChegada++;
            uniqueArrivalAirports.insert(flight->getTarget());
            cityFound = true;
        }
    }

    if (!cityFound) {
        cout << "Error: City '" << cityName << "' not found in the data." << endl;
        return;
    }

    cout << "Number of flights departing from the city " << cityName << ": " << nVoos << endl;
    cout << "Number of flights to the city " << cityName << ": " << nVoosChegada << endl;
    cout << "Number of airports in the city " << cityName << ": " << uniqueAirports.size() << endl;
    cout << "List of airports in the city " << cityName << ": " << endl;

    for (const auto& airportCode : uniqueAirports) {
        auto airport = airportMap.find(airportCode)->second;
        cout << airport->getName() << " -> " << airport->getCity() << ", " << airport->getCountry() << endl;
    }
    cout << endl;
}


/////////////////////////////////////////////3.4\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//3.4-metade 1 (diretos)
//Number of different countries that a given airport flies to
//NOVO
void FlightNetworkManager::DisplayAirportDestinationCountries(string code){
    auto searchIt = node_keys.find(code);
    if (searchIt != node_keys.end()) {
        int search = searchIt->second;
        cout << "Total number of countries the airport travels to directly: " << flightsGraph.CountDistinctDestinationCountries(code, search).first << endl;
        cout << "The airport travels to the following countries directly: ";
        for (auto x:flightsGraph.CountDistinctDestinationCountries(code,search).second){
            if (x == flightsGraph.CountDistinctDestinationCountries(code,search).second.back()){
                cout << x;
            }
            else{
                cout << x << ", ";
            }
        }
        cout << endl;
    } else {
        // Lidar com o caso em que code não é encontrado
        std::cerr << "Airport code not found: " << code << std::endl;
        return; // Ou outra lógica apropriada
    }
}
//3.4 - metade 2
//exibe as companhias aéreas que operam voos a partir de um aeroporto específico (diretos)
void FlightNetworkManager::DisplayAirlinesOperatingFromAirport(string airportCode) {
    auto searchIt = node_keys.find(airportCode);
    if (searchIt != node_keys.end()) {
        auto search = node_keys.find(airportCode)->second;
        cout << "Number of airlines that operate direct flights from the airport: " << flightsGraph.countAirlines(airportCode, search).first << endl;
        cout << "List of airlines that operate direct flights from the airport: ";
        for (auto x : flightsGraph.countAirlines(airportCode, search).second){
            if (x == flightsGraph.countAirlines(airportCode,search).second.back()){
                cout << airlineMap.find(x)->second->getName();
            }
            else{
                cout << airlineMap.find(x)->second->getName() << ", ";
            }
        }
    cout << endl;
    } else {
        // Lidar com o caso em que code não é encontrado
        std::cerr << "Airport code not found: " << airportCode << std::endl;
        return; // Ou outra lógica apropriada
    }
}

void FlightNetworkManager::DisplayCityDestinationCountries(const std::string& cityName) {
    std::vector<std::string> airportsInCity = getAirportsInCity(cityName);
    int numCountries = 0;
    bool cityFound = !airportsInCity.empty(); // Assuming getAirportsInCity returns an empty vector if city not found

    for (const auto& airport : airportsInCity) {
        auto searchIt = node_keys.find(airport);
        if (searchIt != node_keys.end()) {
            int search = searchIt->second;
            for (auto x : flightsGraph.CountDistinctDestinationCountries(airport, search).second) {
                numCountries++;
            }
        }
    }

    if (!cityFound) {
        std::cout << "Error: City '" << cityName << "' not found in the airport data." << std::endl;
        return;
    }

    std::cout << "Total number of different countries the city " << cityName << " travels to directly: " << numCountries << std::endl;
    std::cout << "The city travels to the following countries directly: ";

    for (const auto& airport : airportsInCity) {
        auto searchIt = node_keys.find(airport);
        if (searchIt != node_keys.end()) {
            int search = searchIt->second;
            for (auto x : flightsGraph.CountDistinctDestinationCountries(airport, search).second) {
                if (x == flightsGraph.CountDistinctDestinationCountries(airport, search).second.back()) {
                    std::cout << x;
                } else {
                    std::cout << x << ", ";
                }
            }
        }
        std::cout << std::endl;
    }
}

/////////////////////////////////////////////3.5\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void FlightNetworkManager::ReachableDestinations(string code){
    cout << "\e[1mDestinations accessible from your chosen airport \e[0m" << endl;
    auto searchIt = node_keys.find(code);
    if (searchIt != node_keys.end()) {
        int search = searchIt->second;
        auto [numCountries, countries, cities, airports] = flightsGraph.countCountriesCitiesAirportsTarget(code, search);

        cout << "Number of different countries: " << numCountries << endl;
        cout << "Number of different cities: " << cities.size() << endl;
        cout << "Number of different airports: " << airports.size() << endl;
        cout << "List of different countries: ";
        for (const auto& country : countries) {
            cout << country << ", ";
        }
        cout << "\nList of different cities: ";
        for (const auto& city : cities) {
            cout << city << ", ";
        }
        cout << "\nList of different airports: ";
        for (const auto& airport : airports) {
            cout << airport << ", ";
        }
        cout << endl;
    } else {
        cout << "Airport code not found: " << code << endl;
    }
}


/////////////////////////////////////////////3.6\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//conta voos
void FlightNetworkManager::CountFlightsWithStopsFromAirport(std::string code, int stops) {
    auto searchIt = node_keys.find(code);
    if (searchIt != node_keys.end()) {
        int airportIndex = searchIt->second;
        int flightsCount = flightsGraph.countAirports(code, airportIndex, stops + 1);

        if (stops == 1) {
            cout << "Number of flights with 1 stopover from " << code << ": " << flightsCount << endl;
        } else {
            cout << "Number of flights with " << stops << " stopovers from " << code << ": " << flightsCount << endl;
        }
    } else {
        cout << "Airport code not found: " << code << endl;
    }
}

//conta cidade
void FlightNetworkManager::CountReachableCitiesFromAirport(const std::string& airportCode, int maxStops) {
    auto searchIt = node_keys.find(airportCode);
    if (searchIt != node_keys.end()) {
        int airportIndex = searchIt->second;
        int cityCount = flightsGraph.countCitiesWithinStops(airportCode, airportIndex, maxStops);
        std::cout << "Number of reachable cities from " << airportCode << " within " << maxStops << " stops: " << cityCount << std::endl;
    } else {
        std::cout << "Airport code not found: " << airportCode << std::endl;
    }
}

//conta aeroportos
void FlightNetworkManager::CountReachableAirportsFromAirport(const std::string& airportCode, int maxStops) {
    auto searchIt = node_keys.find(airportCode);
    if (searchIt != node_keys.end()) {
        int airportIndex = searchIt->second;
        int airportCount = flightsGraph.countAirportsWithinStops(airportCode, airportIndex, maxStops);
        std::cout << "Number of reachable airports from " << airportCode << " within " << maxStops << " stops: " << airportCount << std::endl;
    } else {
        std::cout << "Airport code not found: " << airportCode << std::endl;
    }
}

//conta paises
void FlightNetworkManager::CountReachableCountriesFromAirport(const std::string& airportCode, int maxStops) {
    auto searchIt = node_keys.find(airportCode);
    if (searchIt != node_keys.end()) {
        int airportIndex = searchIt->second;
        int countryCount = flightsGraph.countCountriesWithinStops(airportCode, airportIndex, maxStops);
        std::cout << "Number of reachable countries from " << airportCode << " within " << maxStops << " stops: " << countryCount << std::endl;
    } else {
        std::cout << "Airport code not found: " << airportCode << std::endl;
    }
}

/////////////////////////////////////////////3.7\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//Determina o número de escalas - diâmetro
/*int FlightNetworkManager::getGraphDiameter() {
    return flightsGraph.calculateGraphDiameter();
}
 */

void FlightNetworkManager::findDiameterAndCorrespondingNodes() {
    auto [diameter, airportPairs] = flightsGraph.calculateGraphDiameterAndNodes();

    cout << "Graph diameter: " << diameter << endl;
    cout << "Airport pairs with this maximum distance:" << endl;
    for (const auto& [startAirport, endAirport] : airportPairs) {
        cout << "From " << startAirport << " to " << endAirport << endl;
    }
}


/////////////////////////////////////////////3.8\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void FlightNetworkManager::DisplayTopKAirports(int k) {
    auto topKAirports = flightsGraph.findTopKAirports(k);
    std::cout << "Top " << k << " Airports with Highest Air Traffic:" << std::endl;
    for (const auto& [airportCode, flightCount] : topKAirports) {
        std::cout << "Airport: " << airportCode << ", Flights: " << flightCount << std::endl;
    }
}

/////////////////////////////////////////////3.9\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//diz número de aeroportos que são articulation points
void FlightNetworkManager::DisplayNumberOfArticulationPoints() {
    int numOfArticulationPoints = flightsGraph.findArticulationPoints().size();
    std::cout << "Number of articulation points in the flight network: " << numOfArticulationPoints << std::endl;
}

//Lista aeroportos que são articulation points
void FlightNetworkManager::DisplayArticulationAirports() {
    auto articulationAirports = flightsGraph.findArticulationAirports();
    std::cout << "Articulation Airports: " << std::endl;
    for (const auto& airportCode : articulationAirports) {
        std::cout << "Airport Code: " << airportCode << std::endl;
    }
}

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
/////////////////////////////////////////////FUNÇÕES PONTO 4\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/////////////////////////////////////////////4.1.1- recebe codigo dos aeroportos e retorna melhores voos\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//sabendo código dos aeroportos retorna os voos diretos (melhores voos)
std::vector<Flight*> FlightNetworkManager::findDirectFlights(const std::string& sourceCode, const std::string& targetCode) {
    std::vector<Flight*> directFlights;
    bool sourceFound = false, targetFound = false;

    for (const auto& flight : flightsVec) {
        if (flight->getSource() == sourceCode && flight->getTarget() == targetCode) {
            directFlights.push_back(flight);
            sourceFound = true;
            targetFound = true;
        } else if (flight->getSource() == sourceCode) {
            sourceFound = true;
        } else if (flight->getTarget() == targetCode) {
            targetFound = true;
        }
    }

    if (!sourceFound) {
        std::cerr << "Error: Source airport code '" << sourceCode << "' not found in the available flights." << std::endl;
    }

    if (!targetFound) {
        std::cerr << "Error: Target airport code '" << targetCode << "' not found in the available flights." << std::endl;
    }

    return directFlights;
}


//sabendo código dos aeroportos retorna os voos com menos paragens  (melhores voos)
std::vector<std::vector<Flight*>> FlightNetworkManager::findFlightsWithMinStops(const std::string& sourceCode, const std::string& targetCode) {
    std::unordered_map<std::string, std::vector<std::vector<Flight*>>> paths;
    std::queue<std::pair<std::string, std::vector<Flight*>>> q;
    std::unordered_map<std::string, int> minStops;

    bool sourceFound = false, targetFound = false;

    for (const auto& flight : flightsVec) {
        if (flight->getSource() == sourceCode) {
            sourceFound = true;
        }
        if (flight->getTarget() == targetCode) {
            targetFound = true;
        }
    }

    if (!sourceFound) {
        std::cerr << "Error: Source airport code '" << sourceCode << "' not found in the available flights." << std::endl;
        return {};
    }

    if (!targetFound) {
        std::cerr << "Error: Target airport code '" << targetCode << "' not found in the available flights." << std::endl;
        return {};
    }

    q.push({sourceCode, {}});

    while (!q.empty()) {
        auto [currentAirport, currentPath] = q.front();
        q.pop();

        if (currentAirport == targetCode) {
            if (currentPath.size() <= minStops[targetCode]) {
                paths[targetCode].push_back(currentPath);
            }
            continue;
        }

        for (const auto& flight : flightsVec) {
            if (flight->getSource() == currentAirport) {
                std::string nextAirport = flight->getTarget();
                std::vector<Flight*> newPath = currentPath;
                newPath.push_back(flight);

                if (minStops.find(nextAirport) == minStops.end() || newPath.size() < minStops[nextAirport]) {
                    q.push({nextAirport, newPath});
                    minStops[nextAirport] = newPath.size();
                }
            }
        }
    }

    return paths[targetCode];
}


//função "final" para o 4.1
void FlightNetworkManager::findBestFlightsAirCode(const std::string& sourceCode, const std::string& targetCode) {
    int counter = 1;
    auto directFlights = findDirectFlights(sourceCode, targetCode);
    if (!directFlights.empty()) {
        for (const auto& flight : directFlights) {
            std::cout << "Origem: " << flight->getSource() << " --> Destino: " << flight->getTarget() << " || Airline: " << flight->getAirline() << " || Direct flight" << std::endl;
        }
    } else {
        auto flightsWithMinStops = findFlightsWithMinStops(sourceCode, targetCode);
        for (const auto& flightPath : flightsWithMinStops) {
            cout << "Opção " << counter << endl;
            for (const auto& flight : flightPath) {
                std::cout << "Origem: " << flight->getSource() << " --> Destino: " << flight->getTarget() << " || Airline: " << flight->getAirline() << std::endl;
            }
            std::cout << "Total Stops: " << flightPath.size() - 1 << std::endl;
        }
    }
}


/////////////////////////////////////////////4.1.2- recebe nome dos aeroportos e retorna melhores voos\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// diz nome do aeroporto sabendo o codigo
std::string FlightNetworkManager::getAirportCodeByName(const std::string& airportName) {
    for (const auto& pair : airportMap) {
        if (pair.second->getName() == airportName) {
            return pair.first; // return the airport code
        }
    }
    return "Airport name not found";
}
/// //função "final" para o 4.2
void FlightNetworkManager::findBestFlightsAirportName(const std::string& sourceName, const std::string& targetName) {
    int counter = 1;
    auto directFlights = findDirectFlights(getAirportCodeByName(sourceName), getAirportCodeByName(targetName));
    if (!directFlights.empty()) {
        for (const auto& flight : directFlights) {
            std::cout << "Origem: " << flight->getSource() << " --> Destino: " << flight->getTarget() << " || Airline: " << flight->getAirline() << " || Direct flight" << std::endl;
        }
    } else {
        auto flightsWithMinStops = findFlightsWithMinStops(getAirportCodeByName(sourceName), getAirportCodeByName(targetName));
        for (const auto& flightPath : flightsWithMinStops) {
            cout << "Opção " << counter << endl;
            for (const auto& flight : flightPath) {
                std::cout << "Origem: " << flight->getSource() << " --> Destino: " << flight->getTarget() << " || Airline: " << flight->getAirline() << std::endl;
            }
            std::cout << "Total Stops: " << flightPath.size() - 1 << std::endl;
        }
    }
}


/////////////////////////////////////////////4.2- recebe nome das cidades e retorna melhores voos\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

std::vector<std::vector<Flight*>> FlightNetworkManager::findBestFlightsBetweenCities(const std::string& sourceCity, const std::string& targetCity) {
    // Encontrar todos os aeroportos nas cidades de origem e destino
    std::vector<std::string> sourceAirports = getAirportsInCity(sourceCity);
    std::vector<std::string> targetAirports = getAirportsInCity(targetCity);

    // Tentar encontrar voos diretos primeiro
    for (const auto& sourceAirport : sourceAirports) {
        for (const auto& targetAirport : targetAirports) {
            std::vector<Flight*> directFlights = findDirectFlights(sourceAirport, targetAirport);
            if (!directFlights.empty()) {
                return {directFlights}; // Retorna voos diretos se encontrados
            }
        }
    }

    // Se não houver voos diretos, procurar por voos com o menor número de escalas
    std::vector<std::vector<Flight*>> bestFlights;
    int minStops = INT_MAX;

    for (const auto& sourceAirport : sourceAirports) {
        for (const auto& targetAirport : targetAirports) {
            std::vector<std::vector<Flight*>> flightsWithMinStops = findFlightsWithMinStops(sourceAirport, targetAirport);
            if (!flightsWithMinStops.empty() && flightsWithMinStops[0].size() < minStops) {
                bestFlights = flightsWithMinStops;
                minStops = flightsWithMinStops[0].size();
            }
        }
    }

    return bestFlights; // Retorna os voos com o menor número de escalas
}

// Função auxiliar para obter os códigos dos aeroportos numa cidade
std::vector<std::string> FlightNetworkManager::getAirportsInCity(const std::string& cityName) {
    std::vector<std::string> airports;
    for (const auto& pair : airportMap) {
        if (pair.second->getCity() == cityName) {
            airports.push_back(pair.first);
        }
    }
    return airports;
}

//NOTA: para escrever no menu/main usar algo como isto:
/*
 * std::string sourceCity, targetCity;

    std::cout << "Digite o nome da cidade de origem: ";
    std::getline(std::cin, sourceCity);

    std::cout << "Digite o nome da cidade de destino: ";
    std::getline(std::cin, targetCity);

    auto bestFlights = manager.findBestFlightsBetweenCities(sourceCity, targetCity);
    int counter = 1;
    if (bestFlights.empty()) {
        std::cout << "Nenhum voo encontrado." << std::endl;
    } else {
        for (const auto& flightPath : bestFlights) {
            cout << "Opção " << counter << ":" << endl;
            for (const auto& flight : flightPath) {
                std::cout << "Voo de " << flight->getSource() << " para " << flight->getTarget() << " pela companhia " << flight->getAirline() << std::endl;
            }
            std::cout << "Total de escalas: " << flightPath.size() - 1 << std::endl;
        }
    }

    return 0;
 */

/////////////////////////////////////////////4.2- recebe coordenadas e retorna melhores voos\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//Auxiliares para cálculo de distâncias
const double EARTH_RADIUS = 6371.0;

double FlightNetworkManager::degreeToRadian(double degree) {
    return degree * M_PI / 180.0;
}

double FlightNetworkManager::calculateDistance(double lat1, double long1, double lat2, double long2) {
    const double EARTH_RADIUS_KM = 6371.0;
    lat1 = degreeToRadian(lat1);
    lat2 = degreeToRadian(lat2);
    double dLat = degreeToRadian(lat2 - lat1);
    double dLong = degreeToRadian(long2 - long1);

    double a = sin(dLat / 2) * sin(dLat / 2) +
               sin(dLong / 2) * sin(dLong / 2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_RADIUS_KM * c;
}

//Encontra o aeroporto mais perto

std::vector<Airport> FlightNetworkManager::findNearestAirports(double lat, double longi, int maxResults) {
    std::vector<std::pair<Airport, double>> airportDistances;
    for (const auto& airport : airportsVec) {
        double distance = calculateDistance(lat, longi, airport->getLat(), airport->getLong());
        airportDistances.emplace_back(*airport, distance);
    }

    std::sort(airportDistances.begin(), airportDistances.end(),
              [](const std::pair<Airport, double>& a, const std::pair<Airport, double>& b) {
                  return a.second < b.second;
              });

    std::vector<Airport> nearestAirports;
    for (int i = 0; i < maxResults && i < airportDistances.size(); ++i) {
        nearestAirports.push_back(airportDistances[i].first);
    }
    return nearestAirports;
}

vector<vector<vector<Flight *>>>
FlightNetworkManager::findBestFlightOptions(double srcLat, double srcLong, double destLat, double destLong) {
    auto sourceAirports = findNearestAirports(srcLat, srcLong, 5);
    auto destinationAirports = findNearestAirports(destLat, destLong, 5);

    std::vector<std::vector<vector<Flight *>>> bestOptions;
    int minStops = INT_MAX;

    // Loop through each combination of source and destination airports
    for (const auto& srcAirport : sourceAirports) {
        for (const auto& destAirport : destinationAirports) {
            // Get the flight path with minimum stops
            vector<vector<Flight *>> flightPath = findFlightsWithMinStops(srcAirport.getCode(), destAirport.getCode());

            // Check if the path is valid and has minimum stops
            if (!flightPath.empty() && flightPath.size() - 1 <= minStops) {
                // Update the best options if a shorter path is found
                if (flightPath.size() - 1 < minStops) {
                    bestOptions.clear();
                    minStops = flightPath.size() - 1;
                }
                bestOptions.push_back(flightPath);
            }
        }
    }

    return bestOptions;
}



/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
/////////////////////////////////////////////FUNÇÕES PONTO 4/5\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

//substituto -- usar este para codigo do aeroporto
void FlightNetworkManager::findFlightRoutesAirportToAirport(const std::string& sourceAirportCode, const std::string& targetAirportCode, const std::vector<std::string>& airlines) {
    auto search = node_keys.find(sourceAirportCode);
    if (search == node_keys.end()) {
        std::cerr << "Error: Source airport code '" << sourceAirportCode << "' not found." << std::endl;
        return;
    }
    auto search2 = node_keys.find(targetAirportCode);
    if (search2 == node_keys.end()) {
        std::cerr << "Error: Target airport code '" << targetAirportCode << "' not found." << std::endl;
        return;
    }
    int con1 = (*search).second;
    int con2 = (*search2).second;
    if (!isConnected(con1, con2)) {
        cout << "It is not possible to make this flight\n";
        return;
    }
    list<Flight*> found = flightsGraph.bfsGetList((*search).second, sourceAirportCode, targetAirportCode);
    list<Flight*> copy = found;
    auto it = found.begin();
    while (it != found.end()) {
        if ((*it)->getTarget() != targetAirportCode || (*it)->getSource() != sourceAirportCode) {
            it = found.erase(it);
        } else it++;
    }

    if (found.empty()) {
        list<vector<Flight*>> scales;
        cout << "\nFlight with stopovers:\n";
        auto found2 = copy;
        for (Flight* f : copy) {
            auto it2 = found2.begin();
            while (it2!=found2.end()) {
                if ((*it2)->getTarget() != targetAirportCode) it2 = found2.erase(it2);
                else it2++;
            }

            for (Flight* f2 : found2) {
                vector<Flight*> v;
                if (f->getTarget()!=f2->getSource() || f->getAirline()!=f2->getAirline()) continue;
                v.push_back(f);
                v.push_back(f2);
                scales.push_back(v);
            }
        }
        if (!airlines.empty()) {
            for (const auto& v : scales) {
                int count = 0;
                for (auto f : v) {
                    for (const auto& a : airlines) {
                        if (a == f->getAirline()) {
                            count++;
                        }
                    }
                    if (count == v.size()) {
                        vector<Flight*> copy = v;
                        for (auto f : copy) {
                            cout << f->getSource() << " -> " << f->getTarget() << " || " << "Airline: " << f->getAirline() << "\n";
                        }
                        cout << " Total distance = " << ScaleDistance(v) << " km\n\n";
                    }
                }
            }
            return;
        }
        for (const auto& v : scales) {
            for (auto f : v) {
                cout << f->getSource() << " -> " << f->getTarget() << " || " << "Airline: " << f->getAirline() << "\n";
            }
            cout << "Total distance = " << ScaleDistance(v) << " km\n\n";
        }
    } else {
        cout << "\nDirect flights:\n";
        if (!airlines.empty()) {
            for (Flight* f : found) {
                if (f->getSource() == sourceAirportCode){
                    for (const auto& a : airlines) {
                        if (a == f->getAirline() ) {
                            cout << f->getSource() << " -> " << f->getTarget() << " || " << "Airline: " << f->getAirline() << endl;
                            cout << "Distance = " << distanciaAeroportos(f->getSource(), f->getTarget()) << " km\n";
                        }
                    }
                }
            }
        } else {
            for (Flight* f : found) {
                if (f->getSource() == sourceAirportCode) {
                    cout << f->getSource() << " -> " << f->getTarget() << " || " << "Airline: " << f->getAirline() << endl;
                    cout <<  "Distance = " << distanciaAeroportos(f->getSource(), f->getTarget()) << " km\n";
                }
            }
        }
    }
}


void FlightNetworkManager::findFlightRoutesAirportToAirportnoprint(const std::string& sourceAirportCode, const std::string& targetAirportCode, const std::vector<std::string>& airlines) {
    auto search = node_keys.find(sourceAirportCode);
    auto search2 = node_keys.find(targetAirportCode);
    if (search == node_keys.end()) {
        std::cerr << "Error: Source airport code '" << sourceAirportCode << "' not found." << std::endl;
        return;
    }
    if (search2 == node_keys.end()) {
        std::cerr << "Error: Target airport code '" << targetAirportCode << "' not found." << std::endl;
        return;
    }
    int con1 = (*search).second;
    int con2 = (*search2).second;
    if (!isConnected(con1, con2)) {
        cout << "It is not possible to make this flight\n";
        return;
    }
    list<Flight*> found = flightsGraph.bfsGetList((*search).second, sourceAirportCode, targetAirportCode);
    list<Flight*> copy = found;
    auto it = found.begin();
    while (it != found.end()) {
        if ((*it)->getTarget() != targetAirportCode || (*it)->getSource() != sourceAirportCode) {
            it = found.erase(it);
        } else it++;
    }

    if (found.empty()) {
        list<vector<Flight*>> scales;
        auto found2 = copy;
        for (Flight* f : copy) {
            auto it2 = found2.begin();
            while (it2!=found2.end()) {
                if ((*it2)->getTarget() != targetAirportCode) it2 = found2.erase(it2);
                else it2++;
            }

            for (Flight* f2 : found2) {
                vector<Flight*> v;
                if (f->getTarget()!=f2->getSource() || f->getAirline()!=f2->getAirline()) continue;
                v.push_back(f);
                v.push_back(f2);
                scales.push_back(v);
            }
        }
        if (!airlines.empty()) {
            for (const auto& v : scales) {
                int count = 0;
                for (auto f : v) {
                    for (const auto& a : airlines) {
                        if (a == f->getAirline()) {
                            count++;
                        }
                    }
                    if (count == v.size()) {
                        vector<Flight*> copy = v;
                        for (auto f : copy) {
                            cout << f->getSource() << " -> " << f->getTarget() << " || " << "Airline: " << f->getAirline() << "\n";
                        }
                        cout << " Total distance = " << ScaleDistance(v) << " km\n\n";
                    }
                }
            }
            return;
        }
        for (const auto& v : scales) {
            for (auto f : v) {
                cout << f->getSource() << " -> " << f->getTarget() << " || " << "Airline: " << f->getAirline() << "\n";
            }
            cout << "Total distance = " << ScaleDistance(v) << " km\n\n";
        }
    } else {
        cout << "\nDirect flights:\n";
        if (!airlines.empty()) {
            for (Flight* f : found) {
                if (f->getSource() == sourceAirportCode){
                    for (const auto& a : airlines) {
                        if (a == f->getAirline() ) {
                            cout << f->getSource() << " -> " << f->getTarget() << " || " << "Airline: " << f->getAirline() << endl;
                            cout << "Distance = " << distanciaAeroportos(f->getSource(), f->getTarget()) << " km\n";
                        }
                    }
                }
            }
        } else {
            for (Flight* f : found) {
                if (f->getSource() == sourceAirportCode) {
                    cout << f->getSource() << " -> " << f->getTarget() << " || " << "Airline: " << f->getAirline() << endl;
                    cout <<  "Distance = " << distanciaAeroportos(f->getSource(), f->getTarget()) << " km\n";
                }
            }
        }
    }
}

//substituto para pesquisa cidade -- Usar este
void FlightNetworkManager::findFlightRoutesCityToCity(std::string sourceCountry, std::string sourceCity, std::string targetCountry, std::string targetCity, vector<std::string> airlinesAllowed) {
    vector<Airport*> airportsInSourceCity;
    vector<Airport*> airportsInTargetCity;

    bool sourceCityFound = false;
    bool targetCityFound = false;

    for (auto x : airportsVec) {
        if (x->getCountry() == sourceCountry && x->getCity() == sourceCity) {
            airportsInSourceCity.push_back(x);
            sourceCityFound = true;
        }
    }

    for (auto x : airportsVec) {
        if (x->getCountry() == targetCountry && x->getCity() == targetCity) {
            airportsInTargetCity.push_back(x);
            targetCityFound = true;
        }
    }

    if (sourceCountry.empty() || sourceCity.empty() || targetCountry.empty() || targetCity.empty()) {
        std::cerr << "Error: Invalid input. All fields must be provided." << std::endl;
        return;
    }

    if (!sourceCityFound) {
        std::cerr << "Error: Airports in the source city '" << sourceCity << "' not found." << std::endl;
        return;
    }

    if (!targetCityFound) {
        std::cerr << "Error: Airports in the target city '" << targetCity << "' not found." << std::endl;
        return;
    }

    if (airportsInSourceCity.empty() || airportsInTargetCity.empty()) {
        std::cerr << "Error: No airports found in one or both of the specified countries/cities." << std::endl;
        return;
    }

    for (auto x : airportsInSourceCity) {
        for (auto z : airportsInTargetCity) {
            findFlightRoutesAirportToAirportnoprint(x->getCode(), z->getCode(), airlinesAllowed);
        }
    }
}




double FlightNetworkManager::distanciaAeroportos(const string& src, const string& dest) {

    double lat1, lat2, lon1, lon2;
    lat1 = airportMap.find(src)->second->getLat();
    lat2 = airportMap.find(dest)->second->getLat();
    lon1 = airportMap.find(src)->second->getLong();
    lon2 = airportMap.find(dest)->second->getLong();

    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formula
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}



double FlightNetworkManager::ScaleDistance(const vector<Flight*> &v) {
    double ans = 0;
    for (auto i : v) {
        ans += distanciaAeroportos(i->getSource(), i->getTarget());
    }
    return ans;
}

bool FlightNetworkManager::isConnected(int a, int b) {
    return flightsGraph.isConnected(a, b);
}

//usar este para coordenadas
void FlightNetworkManager::findFlightRoutesCoordinates(double sourceLongitude, double sourceLatitude, double targetLongitude, double targetLatitude, double radius, vector<std::string> airlinesAllowed) {
    vector<Airport*> airportsInSource;
    vector<Airport*> airportsInTarget;

    bool sourceCoordsFound = false;
    bool targetCoordsFound = false;

    for (auto x : airportsVec) {
        if (distanciaAeroportoCoordinates(x, sourceLongitude, sourceLatitude, radius)) {
            airportsInSource.push_back(x);
            sourceCoordsFound = true;
        }
        if (distanciaAeroportoCoordinates(x, targetLongitude, targetLatitude, radius)) {
            airportsInTarget.push_back(x);
            targetCoordsFound = true;
        }
    }

    if (!sourceCoordsFound) {
        std::cerr << "Error: No airports found near the specified source coordinates." << std::endl;
        return;
    }

    if (!targetCoordsFound) {
        std::cerr << "Error: No airports found near the specified target coordinates." << std::endl;
        return;
    }

    for (auto y : airportsInSource) {
        for (auto z : airportsInTarget) {
            findFlightRoutesAirportToAirportnoprint(y->getCode(), z->getCode(), airlinesAllowed);
        }
    }
}


bool FlightNetworkManager::distanciaAeroportoCoordinates(Airport *airport, const double &longitude, const double &latitude, double x) {
    double lat1 = airport->getLat();
    double lon1 = airport->getLong();

    double dLat = (latitude - lat1) * M_PI / 180.0;
    double dLon = (longitude - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    double lat2 = (latitude) * M_PI /180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    double ans = rad * c;
    if (ans <= x) return true;
    return false;
}