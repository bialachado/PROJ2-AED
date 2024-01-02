#include <iostream>
#include <queue>
#include "FlightGraph.h"
#include "Airport.h"
#include "Flight.h"
#include <unordered_set>
#include <set>
#include <unordered_map>



int FlightGraph::findNodeIndex(const std::string& airportCode) const {
    auto it = airportIndexMap.find(airportCode);
    if (it != airportIndexMap.end()) {
        return it->second; // Return the index of the airport
    } else {
        return -1; // Return -1 if the airport is not found
    }
}


// Adiciona uma aresta (voo) ao grafo
void FlightGraph::addEdge(int src, int dest, Flight* eFlight) {
    if (src<1 || src>numNodes || dest<1 || dest>numNodes) return;
    nodes[src].adj.push_back({dest, eFlight});
    if (!isDirected) nodes[dest].adj.push_back({src, eFlight});
}

// Criação do grafo com base em vetores de aeroportos e voos
void FlightGraph::vectorToGraph(vector<Airport*> &airportsVec, vector<Flight*> &flightsVec) {
    // Primeiro, mapeia os códigos dos aeroportos para os índices
    map<string, int> airportCodeToIndex;
    for (int i = 0; i < airportsVec.size(); i++) {
        nodes[i+1].nAirport = airportsVec[i];
        airportCodeToIndex[airportsVec[i]->getCode()] = i + 1;
    }

    // Em seguida, itera sobre os voos e adiciona as arestas ao grafo
    for (auto &flight : flightsVec) {
        string sourceCode = flight->getSource();
        string targetCode = flight->getTarget();

        auto sourceIndexIt = airportCodeToIndex.find(sourceCode);
        auto targetIndexIt = airportCodeToIndex.find(targetCode);

        if (sourceIndexIt != airportCodeToIndex.end() && targetIndexIt != airportCodeToIndex.end()) {
            int noOrigem = sourceIndexIt->second;
            int noDestino = targetIndexIt->second;
            addEdge(noOrigem, noDestino, flight);
        }
    }
}

// Construtor do FlightGraph
FlightGraph::FlightGraph(int numNodes, bool isDirected) : numNodes(numNodes), isDirected(isDirected), nodes(numNodes+1) {
}

// conta o número de países distintos para os quais há voos a partir de um determinado aeroporto, limitando-se a uma companhia aérea específica
//Auxiliar para o ponto 3.4
//Number of different countries that a given airport flies to
pair<int, vector<string>> FlightGraph::CountDistinctDestinationCountries(std::string codeAirport, int k) {
    for (int i = 1; i <= numNodes; i++) {
        nodes[i].visited = false;
    }
    queue<int> q; // queue para armazenar os nodes não visitados
    q.push(k);
    nodes[k].visited = true;
    vector<string> listaPaises;
    int c = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto e: nodes[x].adj) {
            int w = e.dest;
            if (e.eFlight->getSource() != codeAirport) continue;
            if (!nodes[w].visited) { // new node!
                if (std::find(listaPaises.begin(), listaPaises.end(), nodes[w].nAirport->getCountry()) != listaPaises.end()) continue;
                c++;
                listaPaises.push_back(nodes[w].nAirport->getCountry());
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
    return pair<int, vector<string>>(c,listaPaises);
}


//Auxiliar para o ponto 3.4
pair<int, vector<string>> FlightGraph::countAirlines(string code, int v) {
    if (v < 1 || v > numNodes) {
        return {0, vector<string>()};
    }

    std::unordered_set<string> airlineSet;
    queue<int> q;
    q.push(v);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto& e : nodes[u].adj) {
            string airlineCode = e.eFlight->getAirline();

            if (e.eFlight->getSource() == code && airlineSet.insert(airlineCode).second) {
                // Adiciona a companhia aérea ao conjunto e incrementa o contador somente se o voo tiver origem no aeroporto especificado
                // e a companhia aérea ainda não tiver sido adicionada (usando o resultado do insert)
            }
        }

        // Interrompe a busca, pois só considera voos diretos
        break;
    }

    // Converte set para vector para retornar
    vector<string> airlineList(airlineSet.begin(), airlineSet.end());
    return {airlineList.size(), airlineList};
}





//auxiliar para 3.2
pair<int, unordered_set<string>> FlightGraph::countDirectFlightsAndAirlines(const string& airportCode, int airportIndex) const {
    int directFlightsCount = 0;
    unordered_set<string> uniqueAirlines;

    if (airportIndex >= 1 && airportIndex <= numNodes) {
        for (const auto& flight : nodes[airportIndex].adj) {
            if (flight.eFlight->getSource() == airportCode) {
                directFlightsCount++;
                uniqueAirlines.insert(flight.eFlight->getAirline());
            }
        }
    }

    return {directFlightsCount, uniqueAirlines};
}

//auxiliar da 3.5
std::tuple<int, std::unordered_set<std::string>, std::unordered_set<std::string>, std::unordered_set<std::string>>
FlightGraph::countCountriesCitiesAirportsTarget(std::string code, int v) {
    if (v < 1 || v > numNodes) {
        return {0, {}, {}, {}}; // Retorna tuplo vazio se 'v' for inválido
    }

    std::unordered_set<std::string> countries, cities, airports;
    std::queue<int> q;
    q.push(v);
    nodes[v].visited = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const auto &edge: nodes[u].adj) {
            if (edge.eFlight->getSource() == code) {
                int w = edge.dest;
                if (!nodes[w].visited) {
                    q.push(w);
                    nodes[w].visited = true;

                    std::string country = nodes[w].nAirport->getCountry();
                    std::string city = nodes[w].nAirport->getCity();
                    std::string airportCode = nodes[w].nAirport->getCode();

                    countries.insert(country);
                    cities.insert(city);
                    airports.insert(airportCode);
                }
            }
        }
    }

    for (int i = 1; i <= numNodes; i++) {
        nodes[i].visited = false;
    }

    int numCountries = countries.size();
    return {numCountries, countries, cities, airports};
}


//Auxiliar para 3.6
//não funciona direito
std::tuple<int, std::unordered_set<std::string>, std::unordered_set<std::string>, std::unordered_set<std::string>>
FlightGraph::countTargetsByMaxStops(std::string code, int v, int k) {
    if (v < 1 || v > numNodes) {
        return {0, {}, {}, {}}; // Retorna tuplo vazia se 'v' for inválido
    }

    struct NodeInfo {
        int nodeIndex;
        int stops;
    };

    std::unordered_set<std::string> countries, cities, airports;
    std::queue<NodeInfo> q;
    q.push({v, 0});
    nodes[v].visited = true;

    while (!q.empty()) {
        NodeInfo current = q.front();
        q.pop();

        if (current.stops > k) continue;  // Ignora caminhos com mais de k escalas

        for (const auto& edge : nodes[current.nodeIndex].adj) {
            if (edge.eFlight->getSource() == code) {
                int w = edge.dest;
                if (!nodes[w].visited) {
                    q.push({w, current.stops + 1});
                    nodes[w].visited = true;

                    // Adiciona informações do aeroporto de destino
                    std::string country = nodes[w].nAirport->getCountry();
                    std::string city = nodes[w].nAirport->getCity();
                    std::string airportCode = nodes[w].nAirport->getCode();

                    countries.insert(country);
                    cities.insert(city);
                    airports.insert(airportCode);
                }
            }
        }
    }

    // Resetar o estado 'visited' dos nós
    for (int i = 1; i <= numNodes; i++) {
        nodes[i].visited = false;
    }

    int numCountries = countries.size();
    return {numCountries, countries, cities, airports};
}


//auxiliar do 3.7
std::pair<int, std::vector<std::pair<std::string, std::string>>> FlightGraph::calculateGraphDiameterAndNodes() {
    int diameter = 0;
    std::vector<std::pair<std::string, std::string>> airportPairs;

    for (int i = 1; i <= numNodes; i++) {
        std::vector<int> distance(numNodes + 1, -1);
        std::queue<int> q;
        q.push(i);
        distance[i] = 0;

        while (!q.empty()) {
            int currentNode = q.front();
            q.pop();

            for (const auto& edge : nodes[currentNode].adj) {
                int nextNode = edge.dest;
                if (distance[nextNode] == -1) {
                    q.push(nextNode);
                    distance[nextNode] = distance[currentNode] + 1;

                    if (distance[nextNode] > diameter) {
                        diameter = distance[nextNode];
                        airportPairs.clear();
                    }
                    if (distance[nextNode] == diameter) {
                        airportPairs.emplace_back(nodes[i].nAirport->getCode(), nodes[nextNode].nAirport->getCode());
                    }
                }
            }
        }
    }

    return {diameter, airportPairs};
}

//auxiliar para 3.6
int FlightGraph::countAirports(const std::string& sourceCode, int sourceIndex, int maxStops) {
    int count = 0;
    std::unordered_map<int, int> visited; // Node index and number of stops
    std::queue<std::pair<int, int>> q; // Pair of node index and stops

    q.push({sourceIndex, 0});
    visited[sourceIndex] = 0;

    while (!q.empty()) {
        auto [currentNode, stops] = q.front();
        q.pop();

        if (stops > maxStops) continue;

        for (const auto& edge : nodes[currentNode].adj) {
            int nextNode = edge.dest;
            if (visited.find(nextNode) == visited.end() || visited[nextNode] > stops) {
                visited[nextNode] = stops;
                q.push({nextNode, stops + 1});
                if (stops < maxStops) {
                    count++; // Increment count if less than max stops
                }
            }
        }
    }

    return count;
}

//auxiliar para 3.6
int FlightGraph::countCitiesWithinStops(const std::string& sourceCode, int sourceIndex, int maxStops) {
    std::unordered_set<std::string> visitedCities;
    std::queue<std::pair<int, int>> q;
    q.push({sourceIndex, 0});
    visitedCities.insert(nodes[sourceIndex].nAirport->getCity());

    while (!q.empty()) {
        auto [currentNode, stops] = q.front();
        q.pop();

        if (stops > maxStops) continue;

        for (const auto &edge: nodes[currentNode].adj) {
            int nextNode = edge.dest;
            std::string nextCity = nodes[nextNode].nAirport->getCity();
            if (stops + 1 <= maxStops && visitedCities.insert(nextCity).second) {
                q.push({nextNode, stops + 1});
            }
        }
    }

    return visitedCities.size();
}

//auxiliar para 3.6
int FlightGraph::countCountriesWithinStops(const std::string& sourceCode, int sourceIndex, int maxStops) {
    std::unordered_set<std::string> visitedCountries;
    std::queue<std::pair<int, int>> q;
    q.push({sourceIndex, 0});
    visitedCountries.insert(nodes[sourceIndex].nAirport->getCountry());

    while (!q.empty()) {
        auto [currentNode, stops] = q.front();
        q.pop();

        if (stops > maxStops) continue;

        for (const auto& edge : nodes[currentNode].adj) {
            int nextNode = edge.dest;
            std::string nextCountry = nodes[nextNode].nAirport->getCountry();
            if (stops + 1 <= maxStops && visitedCountries.insert(nextCountry).second) {
                q.push({nextNode, stops + 1});
            }
        }
    }

    return visitedCountries.size();
}

//auxiliar para 3.6
//countAirportsWithinStops
int FlightGraph::countAirportsWithinStops(const std::string& sourceCode, int sourceIndex, int maxStops) {
    std::unordered_set<std::string> visitedAirports;
    std::queue<std::pair<int, int>> q;
    q.push({sourceIndex, 0});
    visitedAirports.insert(nodes[sourceIndex].nAirport->getCode());

    while (!q.empty()) {
        auto [currentNode, stops] = q.front();
        q.pop();

        if (stops > maxStops) continue;

        for (const auto& edge : nodes[currentNode].adj) {
            int nextNode = edge.dest;
            std::string nextAirportCode = nodes[nextNode].nAirport->getCode();
            if (stops + 1 <= maxStops && visitedAirports.insert(nextAirportCode).second) {
                q.push({nextNode, stops + 1});
            }
        }
    }

    return visitedAirports.size();
}

//auxiliar para 3.9
void FlightGraph::DFSUtil(int v, std::vector<bool>& visited, std::vector<int>& disc, std::vector<int>& low, std::vector<int>& parent, std::unordered_set<int>& articulationPoints) {
    static int time = 0;
    int children = 0;
    visited[v] = true;
    disc[v] = low[v] = ++time;

    for (auto i = nodes[v].adj.begin(); i != nodes[v].adj.end(); ++i) {
        int u = (*i).dest;  // v is current node, u is adjacent to v

        if (!visited[u]) {
            children++;
            parent[u] = v;
            DFSUtil(u, visited, disc, low, parent, articulationPoints);

            low[v] = std::min(low[v], low[u]);

            if (parent[v] == -1 && children > 1)
                articulationPoints.insert(v);
            if (parent[v] != -1 && low[u] >= disc[v])
                articulationPoints.insert(v);
        }
        else if (u != parent[v])
            low[v] = std::min(low[v], disc[u]);
    }
}

//auxiliar para 3.9
std::unordered_set<int> FlightGraph::findArticulationPoints() {
    std::vector<bool> visited(numNodes, false);
    std::vector<int> disc(numNodes, -1), low(numNodes, -1), parent(numNodes, -1);
    std::unordered_set<int> articulationPoints;

    for (int i = 0; i < numNodes; i++)
        if (!visited[i])
            DFSUtil(i, visited, disc, low, parent, articulationPoints);

    return articulationPoints;
}

//auxiliar para 3.9
std::unordered_set<std::string> FlightGraph::findArticulationAirports() {
    std::unordered_set<int> articulationPointIndices = findArticulationPoints(); // Existing function to find indices
    std::unordered_set<std::string> articulationAirportCodes;

    for (int index : articulationPointIndices) {
        articulationAirportCodes.insert(nodes[index].nAirport->getCode());
    }

    return articulationAirportCodes;
}

//auxiliar para 3.8
std::vector<std::pair<std::string, int>> FlightGraph::findTopKAirports(int k) {
    std::unordered_map<std::string, int> flightCounts;
    for (const auto& node : nodes) {
        if (node.nAirport != nullptr) {  // Safety check for null pointer
            std::string airportCode = node.nAirport->getCode();
            flightCounts[airportCode] += node.adj.size();  // Counting flights for each airport
        }
    }

    // Create a min-heap to store the top-k airports
    auto cmp = [](const std::pair<std::string, int>& left, const std::pair<std::string, int>& right) {
        return left.second > right.second;
    };
    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(cmp)> minHeap(cmp);

    // Populate the heap
    for (const auto& entry : flightCounts) {
        minHeap.push(entry);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }

    // Extract the top-k airports from the heap
    std::vector<std::pair<std::string, int>> topKAirports;
    while (!minHeap.empty()) {
        topKAirports.push_back(minHeap.top());
        minHeap.pop();
    }
    std::reverse(topKAirports.begin(), topKAirports.end());  // The airports are in ascending order, reverse it

    return topKAirports;
}


bool FlightGraph::isConnected(int a, int b) {
    for (int i = 1; i <= numNodes; i++) {
        nodes[i].visited = false;
    }
    dfs(a);

    return nodes[b].visited;
}



void FlightGraph::dfs(int nodeIndex) {
    nodes[nodeIndex].visited = true; // Mark current node as visited

    for (const auto& edge : nodes[nodeIndex].adj) {
        int adjacentNode = edge.dest;
        if (!nodes[adjacentNode].visited) {
            dfs(adjacentNode); // Recursively visit unvisited adjacent nodes
        }
    }
}

list<Flight *> FlightGraph::bfsGetList(int v, string sourceCode, string destCode) {
// initialize all nodes as unvisited
    for (int i = 1; i <= numNodes; i++) {
        nodes[i].visited = false;
        nodes[i].dist = -1;
    }
    list<Flight *> list1;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].dist = 0;
    nodes[v].visited = true;
    int i = 1;
    while (!q.empty()) { // while there are still unprocessed nodes
        int u = q.front();
        q.pop(); // remove first element of q
        if (i == 1) {
            pair<string, int> p;
            p.first = nodes[u].nAirport->getCode();
            p.second = u;
        }
        for (auto e: nodes[u].adj) {
            if (e.eFlight->getSource() != sourceCode && e.eFlight->getTarget() != destCode) continue;
            if(!checkFlightList(e.eFlight,list1)) list1.push_back(e.eFlight);
            int w = e.dest;
            if (!nodes[w].visited) { // new node!
                q.push(w);
                nodes[w].dist = nodes[u].dist + 1;
                nodes[w].visited = true;
            }
        }
        i++;
    }
    return list1;
}

bool FlightGraph::checkFlightList(Flight* f, list<Flight*> l){
    auto it = l.begin();
    while(it!=l.end()){
        if ((*it)->getSource()==f->getSource() && (*it)->getTarget()==f->getTarget() && (*it)->getAirline()==f->getAirline()) return true;
        it++;
    }
    return false;
}