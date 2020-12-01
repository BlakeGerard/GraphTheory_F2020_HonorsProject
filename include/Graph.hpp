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
#include <set>
#include <algorithm>
#include <random>
#include "Edge.hpp"

#ifndef GRAPH_H
#define GRAPH_H

typedef std::map<Edge, std::pair<const Vertex*, const Vertex*>> edge_list;

class Graph {
    friend class Edge;
    friend class Vertex;

    enum graph_type_t {
        undirected = 0,
        directed
    };

    private:
        graph_type_t graph_type;
        std::set<Vertex> vertices; 
        edge_list incidence_map;
        edge_list::iterator find_edge_by_label(unsigned int label);

    public:
        // Constructors
        Graph();
        ~Graph();

        // Get Methods
        graph_type_t type();
        const Vertex* get_vertex_ptr_by_id(std::string id);

        // Set Methods
        const Vertex* add_vertex(Vertex v);
        bool add_edge(Edge e, std::pair<const Vertex*, const Vertex*> pair);

        // Printing Methods
        void print_edge_list();

        // Removal Methods
        void delete_edge_by_label(unsigned int label);
        void contract_edge_by_label(unsigned int label);
};

#endif