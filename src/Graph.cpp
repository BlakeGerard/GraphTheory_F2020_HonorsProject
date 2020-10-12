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

Graph::Graph(std::string incidence_map_str) {
    this->incidence_map = build_incidence_map(incidence_map_str);
};

void Graph::input_incidence_map_str(std::string incidence_map_str) {
    this->incidence_map = build_incidence_map(incidence_map_str);
};

std::map<Edge, std::pair<Vertex, Vertex>> Graph::build_incidence_map(std::string incidence_map_str) {
    std::map<Edge, std::pair<Vertex, Vertex>> im;
    return im;
};

int Graph::compute_adjacency_matrix() {
    int status = 1;
    return status;
};

Graph::graph_type_t Graph::type() {
    return graph_type;
};
