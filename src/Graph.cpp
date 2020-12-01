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
    vertices = std::set<Vertex>();
    incidence_map = edge_list();
};

Graph::~Graph() {};

const Vertex* Graph::add_vertex(Vertex v) {
    std::set<Vertex>::iterator it = (vertices.insert(v)).first;
    return &(*it);
};

bool Graph::add_edge(Edge e, std::pair<const Vertex*, const Vertex*> pair) {
    auto ret = incidence_map.insert({e, pair});
    return ret.second;
};

Graph::graph_type_t Graph::type() {
    return graph_type;
};

const Vertex* Graph::get_vertex_ptr_by_id(std::string id) {
    auto it = vertices.find(Vertex(id, 0));
    return &(*it);
};

/*
    Remove the edge denoted by the given label from the graph
*/
void Graph::delete_edge_by_label(unsigned int label) {
    auto edge_it = find_edge_by_label(label);

    if (edge_it != incidence_map.end()) {
        incidence_map.erase(edge_it);
    }
};

/*
    Contract the edge denoted by the given label from the graph
*/
void Graph::contract_edge_by_label(unsigned int label) {
    auto edge_it = find_edge_by_label(label);

    const Vertex* v1 = edge_it->second.first;
    const Vertex* v2 = edge_it->second.second;

    v1->consume_neighbors_of_contracted_vertex(v2);
    v2->direct_neighbors_to_contracted_vertex(v1, v2);
};

std::map<Edge, std::pair<const Vertex*, const Vertex*>>::iterator Graph::find_edge_by_label(unsigned int label) {
    auto it = std::find_if(incidence_map.begin(), incidence_map.end(), 
    [label](const auto &it) -> bool { return it.first.label() == label; } );
    return it;
};

// Printing Methods

void Graph::print_edge_list() {
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
