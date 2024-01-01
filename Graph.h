//
// Created by Francisca Fernandes on 17/12/2023.
//

#ifndef PROJ2_GRAPH_H
#define PROJ2_GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Airport.h"

class Graph {
public:
    void addAirport(const Airport& airport);
    void addConnection(const std::string& fromCode, const std::string& toCode);


private:
    std::unordered_map<std::string, std::vector<std::string> > adjList;
};


#endif //PROJ2_GRAPH_H
