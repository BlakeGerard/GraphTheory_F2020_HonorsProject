/*
    File: Graph.hpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to encode a Graph.
*/

#include <string>
#include <vector>
#include <map>
#include "Edge.hpp"

#ifndef GRAPH_H
#define GRAPH_H

class Graph {
    friend class Edge;
    friend class Vertex;

    enum graph_type_t {
        undirected = 0,
        directed
    };

    private:
        graph_type_t graph_type;
        std::map<Edge, std::pair<Vertex, Vertex>> incidence_map;
        std::map<Edge, std::pair<Vertex, Vertex>> build_incidence_map(std::string incidence_map_str);

    public:
        // Constructors
        Graph();
        ~Graph();
        Graph(std::string incidence_map_str);

        void input_incidence_map_str(std::string incidence_map_str);
        graph_type_t type();
        int compute_adjacency_matrix();
};

#endif