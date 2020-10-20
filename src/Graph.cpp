/*
    File: Graph.cpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to encode a Graph.
*/

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
