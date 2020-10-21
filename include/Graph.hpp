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
#include <sstream>
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
        std::map<Edge, std::pair<Vertex*, Vertex*>> incidence_map;

    public:
        // Constructors
        Graph();
        ~Graph();

        void input_incidence_map(std::map<Edge, std::pair<Vertex*, Vertex*>> parsed_map);
        graph_type_t type();
        int compute_adjacency_matrix();

        // Printing functions for debugging
        void print();
};

#endif