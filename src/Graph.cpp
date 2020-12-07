/*
    File: Graph.cpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to encode a Graph.
*/

#include <assert.h>
#include <iostream>
#include <algorithm>
#include <limits>
#include "Graph.hpp"

Graph::Graph() {
    incidence_map = std::map<unsigned int, std::pair<unsigned int, unsigned int>>();
};

Graph::~Graph() {};

Graph::Graph(const Graph &g) {
    this->graph_type = g.graph_type;
    this->incidence_map = g.incidence_map;
    this->vertex_degree_map = g.vertex_degree_map;
}

bool Graph::add_edge(unsigned int edge, std::pair<unsigned int, unsigned int> pair) {
    auto ret = incidence_map.insert({edge, pair});
    return ret.second;
};

void Graph::set_vertex_degree_map(std::map<unsigned int, unsigned int> vertex_degree_map) {
    this->vertex_degree_map = vertex_degree_map;
};

Graph::graph_type_t Graph::type() {
    return graph_type;
};

unsigned int Graph::size() {
    return incidence_map.size();
};

unsigned int Graph::vertex_degree_by_label(unsigned int label) {
    return vertex_degree_map[label];
};

unsigned int Graph::min_degree() {
    unsigned int min_degree = UINT8_MAX;
    unsigned int contender;

    for (const auto element : vertex_degree_map) {
        contender = element.second;
        if (contender < min_degree) {
            min_degree = contender;
        }
    };
    return min_degree;
};

bool Graph::edge_is_loop(unsigned int label) {
    auto pair = incidence_map.at(label);
    return pair.first == pair.second;
}

/*
    Remove the edge denoted by the given label from the graph
*/
void Graph::delete_edge_by_label(unsigned int edge_label) {
    assert(incidence_map.size() > 0);
    std::pair<unsigned int, unsigned int> ends = incidence_map.at(edge_label);

    vertex_degree_map[ends.first] -= 1;
    vertex_degree_map[ends.second] -= 1;

    incidence_map.erase(edge_label);
};

/*
    Contract the edge denoted by the given label from the graph
*/
void Graph::contract_edge_by_label(unsigned int edge_label) {
    assert(incidence_map.size() > 0);
    std::pair<unsigned int, unsigned int> ends = incidence_map.at(edge_label);

    // First we get the vertices at the ends of the edge
    unsigned int merger_label = ends.first;
    unsigned int mergee_label = ends.second;
    incidence_map.erase(edge_label);

    vertex_degree_map[merger_label] = 0;

    // We iterate through the map and replace any instance of mergee_label with merger_label
    for (auto &element : incidence_map) {
        if (element.second.first == merger_label) {
            vertex_degree_map[merger_label] += 1;
        } 
        if (element.second.second == merger_label) {
            vertex_degree_map[merger_label] += 1;
        }
        if (element.second.first == mergee_label) {
            element.second.first = merger_label;
            vertex_degree_map[merger_label] += 1;
        } 
        if (element.second.second == mergee_label) {
            element.second.second = merger_label;
            vertex_degree_map[merger_label] += 1;
        }
    }

    // Finally, delete the mergee vertex from the vertex set and edge from the map
    vertex_degree_map.erase(mergee_label);
};

// Printing Methods

void Graph::print_graph() {
    std::ostringstream output;
    unsigned int count = 0;

    // Vertices
    output << "vertices: {";
    for (auto it = vertex_degree_map.begin(); it != vertex_degree_map.end(); ++it) {
        output << it->first;
        if (count < vertex_degree_map.size() - 1) { output << ", "; }
        count += 1;
    }
    output << "}" << std::endl;

    // Edge list
    count = 0;
    output << "edges: { ";
    for(auto it = incidence_map.begin(); it != incidence_map.end(); ++it) {

        output << "{" << it->second.first << ", " << it->second.second << "}";
        if (count < incidence_map.size() - 1) { output << ", "; }
        count += 1;
    }
    output << " }" << std::endl;
    std::cout << output.str();
}
