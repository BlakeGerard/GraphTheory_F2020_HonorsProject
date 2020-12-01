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

Graph::Graph() {
    vertices = std::set<Vertex>();
    incidence_map = std::map<Edge, std::pair<const Vertex*, const Vertex*>>();
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
