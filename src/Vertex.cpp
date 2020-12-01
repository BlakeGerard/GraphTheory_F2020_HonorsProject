/*
    File: Vertex.hpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to represent a Vertex in a graph.
*/

#include "Edge.hpp"

// Constructors
Vertex::Vertex() {};

Vertex::Vertex(std::string id, unsigned int label) {
    this->_id = id;
    this->_label = label;
};

Vertex::~Vertex() {};

// Get Methods
std::string Vertex::id() const {
    return _id;
};

unsigned int Vertex::label() const {
    return this->_label;
};
        
std::size_t Vertex::degree() {
    return incident_edges.size();
};

// Set Methods
void Vertex::new_adjacent_vertex(const Vertex* v) const {
    adjacent_vertices.insert(v);
}

// Operators
bool Vertex::operator<(const Vertex& rhs) const {
    return _id < rhs._id;
};

