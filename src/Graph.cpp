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

/*
    Default constructor. Initialize incidence_map space.
*/
Graph::Graph() {
    incidence_map = std::map<unsigned int, std::pair<unsigned int, unsigned int>>();
};

Graph::~Graph() {};

/*
    Copy constructor.
*/
Graph::Graph(const Graph &g) {
    this->graph_type = g.graph_type;
    this->incidence_map = g.incidence_map;
    this->vertex_degree_map = g.vertex_degree_map;
}

/*
    Add an edge to the graph.
    Input: 
        edge: label for the edge
        pair: pair of vertex labels to the ends of the edge
    Output:
        boolean value if the edge was inserted
*/
bool Graph::add_edge(unsigned int edge, std::pair<unsigned int, unsigned int> pair) {
    auto ret = incidence_map.insert({edge, pair});
    return ret.second;
};

/*
    Add a vertex_degree_map to the Graph. 
    This is really only accessed after parsing is complete.
    Input: 
        vertex_degree_map: mapping from vertex labels to vertex degrees
*/
void Graph::set_vertex_degree_map(std::map<unsigned int, unsigned int> vertex_degree_map) {
    this->vertex_degree_map = vertex_degree_map;
};

/*
    Return the type of graph {undirected, directed}
*/
Graph::graph_type_t Graph::type() {
    return graph_type;
};

/*
    Return the number of edges in the graph
*/
unsigned int Graph::edge_count() {
    return incidence_map.size();
};

/*
    Return the number of vertices in the graph
*/
unsigned int Graph::vertex_count() {
    return vertex_degree_map.size();
};

/*
    Return the degree of the vertex labeled by the given value
    Input:
        label: label of the vertex 
    Output:
        degree of the vertex
*/
unsigned int Graph::vertex_degree_by_label(unsigned int label) {
    return vertex_degree_map[label];
};

/*
    Compute the minimum degree of the graph. This is done
    by finding the minimum value in the vertex_degree_map.
    Output:
        minimum degree of the graph
*/
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

/*
    Check if the edge labeled by the given value is a loop.
    This function just queries the edge_map to see if both
    values in the pair mapped to by the label are equal.
    Input:
        label: label of the edge
    Output:
        boolean if values in the pair mapped to by the label are equal.
*/
bool Graph::edge_is_loop(unsigned int label) {
    auto pair = incidence_map.at(label);
    return pair.first == pair.second;
}

/*
    Remove the edge denoted by the given label.
    This function also decrements the degree of 
    the vertices at the end of the edge.
    Input:
        label: label of the edge
*/
void Graph::delete_edge_by_label(unsigned int edge_label) {
    assert(incidence_map.size() > 0);
    std::pair<unsigned int, unsigned int> ends = incidence_map.at(edge_label);

    vertex_degree_map[ends.first] -= 1;
    vertex_degree_map[ends.second] -= 1;

    incidence_map.erase(edge_label);
};

/*
    Contract the edge denoted by the given label.
    This function also recomputes the degree of the 
    merger vertex as it traverses the map and updates
    any occurrences of the mergee vertex to merger vertex.
    Input:
        edge_label: label of edge to contract
*/
void Graph::contract_edge_by_label(unsigned int edge_label) {
    assert(incidence_map.size() > 0);
    std::pair<unsigned int, unsigned int> ends = incidence_map.at(edge_label);

    // First we get the vertices at the ends of the edge
    unsigned int merger_label = ends.first;
    unsigned int mergee_label = ends.second;

    // We can go ahead and delete the edge so that it isn't edited unnecessarily
    incidence_map.erase(edge_label);

    // Reset the degree of the merger vertex so it can be recomputed
    vertex_degree_map[merger_label] = 0;

    // We iterate through the map and replace any instance of mergee_label with merger_label
    // We also increment the degree of merger_label any time it is seen in the traversal.
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

    // Finally, delete the mergee vertex from the vertex set
    vertex_degree_map.erase(mergee_label);
};

/*
    Print the graph. The format is:
    vertices: {v1, v2, v3, ..., vn}
    edges: {(v1, v2), (v3, v2), ..., (vi, vj)}

    This function is pretty expensive so use it sparingly.
*/
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
