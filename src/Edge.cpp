/*
    File: Edge.cpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to represent an Edge in a graph.
*/

#include <iostream>
#include "Edge.hpp"

// Constructors
Edge::Edge() {};
Edge::~Edge() {};

Edge::Edge(unsigned int label, std::pair<const Vertex*, const Vertex*> connected_vertices) {
    this->_label = label;
    this->connected_vertices = connected_vertices;
}

// Get Methods
unsigned int Edge::label() {
    return this->_label;
};

// Operators
bool Edge::operator<(const Edge& rhs) const {
    return _label < rhs._label;
};