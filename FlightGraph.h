#ifndef PROJ2_FLIGHTGRAPH_H
#define PROJ2_FLIGHTGRAPH_H


#include <map>
#include <string>
#include "Airport.h"
#include "Flight.h"
#include <list>
#include <unordered_set>
#include <set>
#include <unordered_map>



using namespace std;



class FlightGraph {
    std::unordered_map<std::string, std::string> airportCodeToCity;
    struct Edge {
        int dest;
        Flight* eFlight;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
        int dist;
        Airport* nAirport;
        string lastAirport;
        std::vector<std::list<Edge>> adjList;
    };


    int numNodes;  // Número de nós no grafo
    bool isDirected;
    std::vector<Node> nodes;

public:
    FlightGraph(int numNodes, bool isDirected = false);
    void addNode(Airport* airport);
    void addEdge(int sourceIndex, int targetIndex, Flight* flight);
    void vectorToGraph(vector<Airport*> &airportsVec, vector<Flight*> &flightsVec);
    std::vector<std::pair<std::pair<std::string, std::string>, int>> findMaxStopRoutes();
    //dfs
    void dfs(int nodeIndex);
    pair<int, vector<string>> CountDistinctDestinationCountries(std::string codeAirport, int k);
    pair<int, vector<string>> countAirlines(string code, int v);
    pair<int, unordered_set<string>> countDirectFlightsAndAirlines(const string& airportCode, int airportIndex) const;
    std::tuple<int, std::unordered_set<std::string>, std::unordered_set<std::string>, std::unordered_set<std::string>>
    countCountriesCitiesAirportsTarget(std::string code, int v);
    std::tuple<int, std::unordered_set<std::string>, std::unordered_set<std::string>, std::unordered_set<std::string>>
    countTargetsByMaxStops(std::string code, int v, int k);
    std::pair<int, std::vector<std::pair<std::string, std::string>>> calculateGraphDiameterAndNodes();
    int countAirports(const std::string& sourceCode, int sourceIndex, int maxStops);
    int countCitiesWithinStops(const std::string& sourceCode, int sourceIndex, int maxStops);
    int countCountriesWithinStops(const std::string& sourceCode, int sourceIndex, int maxStops);
    int countAirportsWithinStops(const std::string& sourceCode, int sourceIndex, int maxStops);
    void DFSUtil(int v, std::vector<bool>& visited, std::vector<int>& disc, std::vector<int>& low, std::vector<int>& parent, std::unordered_set<int>& articulationPoints);
    std::unordered_set<int> findArticulationPoints();
    std::unordered_set<std::string> findArticulationAirports();
    std::vector<std::pair<std::string, int>> findTopKAirports(int k);
    bool isConnected(int a, int b);
    list<Flight *> bfsGetList(int v, string sourceCode, string destCode);
    bool checkFlightList(Flight* f, list<Flight*> l);


private:
    std::map<std::string, int> airportIndexMap; // Mapeia códigos de aeroportos para índices de nós
    int findNodeIndex(const std::string &airportCode) const;



};

#endif //PROJ2_FLIGHTGRAPH_H



