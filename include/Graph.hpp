/*
    File: Graph.hpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to encode a Graph.
*/

#include <string>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

#ifndef GRAPH_H
#define GRAPH_H

class Graph {
    
    enum graph_type_t {
        undirected = 0,
        directed
    };

    public:
        graph_type_t graph_type;
        std::map<unsigned int, unsigned int> vertex_degree_map;
        std::map<unsigned int, std::pair<unsigned int, unsigned int>> incidence_map;

        // Constructors and graph population
        Graph();
        ~Graph(); 
        Graph(const Graph &g);
        bool add_edge(unsigned int edge, std::pair<unsigned int, unsigned int> vertices);
        void set_vertices(std::set<unsigned int> vertices);
        void set_vertex_degree_map(std::map<unsigned int, unsigned int> vertex_degree_map);

        // Get methods
        graph_type_t type();
        unsigned int edge_count();
        unsigned int vertex_count();
        unsigned int vertex_degree_by_label(unsigned int label);
        unsigned int min_degree();
        bool edge_is_loop(unsigned int label);

        // Printing Methods
        void print_graph();

        // Removal Methods
        void delete_edge_by_label(unsigned int label);
        void contract_edge_by_label(unsigned int label);
};

#endif