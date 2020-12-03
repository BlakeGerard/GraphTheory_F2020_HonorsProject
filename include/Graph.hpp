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
#include <sstream>
#include <algorithm>

#ifndef GRAPH_H
#define GRAPH_H

class Graph {
    
    enum graph_type_t {
        undirected = 0,
        directed
    };

    private:
        graph_type_t graph_type;
        std::map<std::string, unsigned int>* vertex_ids_ptr;
        std::map<unsigned int, std::pair<unsigned int, unsigned int>> incidence_map;

    public:
        // Constructors and graph population
        Graph();
        ~Graph(); 
        bool add_edge(unsigned int edge, std::pair<unsigned int, unsigned int> vertices);

        // Get methods
        graph_type_t type();

        // Printing Methods
        void print_edge_list();

        // Removal Methods
        void delete_edge_by_label(unsigned int label);
        void contract_edge_by_label(unsigned int label);
};

#endif