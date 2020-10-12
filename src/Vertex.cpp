/*
    File: Vertex.hpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to represent a Vertex in a graph.
*/

#include "Edge.hpp"

Vertex::Vertex() {
    
};

Vertex::Vertex(std::vector<Edge> incident_edges, std::vector<Vertex> adjacent_vertices) {
    this->incident_edges = incident_edges;
    this->adjacent_vertices = adjacent_vertices;
};

Vertex::~Vertex() {};
        
unsigned int Vertex::degree() {
    return _degree;
}