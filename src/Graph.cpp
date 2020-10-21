/*
    File: Graph.cpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to encode a Graph.
*/

#include <iostream>
#include "Graph.hpp"

Graph::Graph() {};
Graph::~Graph() {};

void Graph::input_incidence_map(std::map<Edge, std::pair<Vertex*, Vertex*>> parsed_map) {
    this->incidence_map = parsed_map;
};

int Graph::compute_adjacency_matrix() {
    int status = 1;
    return status;
};

Graph::graph_type_t Graph::type() {
    return graph_type;
};

void Graph::print() {
    std::ostringstream output;
    unsigned int count = 0;

    output << "{ ";
    for(auto it = incidence_map.begin(); it != incidence_map.end(); ++it) {
        output << "{" << it->second.first->id() << ", " << it->second.second->id() << "}";
        if (count < incidence_map.size() - 1) { output << ", "; }
        count += 1;
    }
    output << " }";
    std::cout << output.str() << std::endl;
}
