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
    this->_degree = 0;
};

Vertex::Vertex(std::string id) {
    this->_id = id;
    this->_degree = 0;
};

Vertex::~Vertex() {};

std::string Vertex::id() {
    return _id;
};
        
unsigned int Vertex::degree() {
    return _degree;
};

void Vertex::increment_degree() {
    _degree += 1;
};