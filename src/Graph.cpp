/*
    File: Graph.cpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to encode a Graph.
*/

#include <iostream>
#include <algorithm>
#include "Graph.hpp"

Graph::Graph() {
    incidence_map = std::map<unsigned int, std::pair<unsigned int, unsigned int>>();
};

Graph::~Graph() {};

bool Graph::add_edge(unsigned int edge, std::pair<unsigned int, unsigned int> pair) {
    auto ret = incidence_map.insert({edge, pair});
    return ret.second;
};

Graph::graph_type_t Graph::type() {
    return graph_type;
};

/*
    Remove the edge denoted by the given label from the graph
*/
void Graph::delete_edge_by_label(unsigned int edge_label) {
    incidence_map.erase(edge_label);
};

/*
    Contract the edge denoted by the given label from the graph
*/
void Graph::contract_edge_by_label(unsigned int edge_label) {
    std::pair<unsigned int, unsigned int> vertices = incidence_map.at(edge_label);

    // First we get the vertices at the ends of the edge
    unsigned int merger_label = vertices.first;
    unsigned int mergee_label = vertices.second;

    // We iterate through the map and replace any instance of mergee_label with merger_label
    for (auto element : incidence_map) {
        if (element.second.first == mergee_label) {
            element.second.first = merger_label;
        } else if (element.second.second == mergee_label) {
            element.second.second = merger_label;
        }
    }

    // Finally, delete the edge from the map
    incidence_map.erase(edge_label);
};

// Printing Methods

void Graph::print_edge_list() {
    std::ostringstream output;
    unsigned int count = 0;
    std::string v1_id;
    std::string v2_id;

    output << "{ ";
    for(auto it = incidence_map.begin(); it != incidence_map.end(); ++it) {

        output << "{" << it->second.first << ", " << it->second.second << "}";
        if (count < incidence_map.size() - 1) { output << ", "; }
        count += 1;
    }
    output << " }";
    std::cout << output.str() << std::endl;
}
