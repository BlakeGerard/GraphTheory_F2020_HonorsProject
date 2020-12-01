/*
    File: Vertex.hpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to represent a Vertex in a graph.
*/

#include <algorithm>
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

std::list<const Vertex*>::iterator Vertex::get_adjacent_vertex_position(const Vertex* v)  const {
    auto it = std::find(adjacent_vertices.begin(), adjacent_vertices.end(), v);
    return it;
};

// Set Methods
void Vertex::new_adjacent_vertex(const Vertex* v) const {
    adjacent_vertices.push_back(v);
}

// Operators
bool Vertex::operator<(const Vertex& rhs) const {
    return _id < rhs._id;
};

/*
    This function is used in edge contraction. The Vertex in which this 
    function is being called is expected to be the named vertex
    into which the connected neighbor is merged. Thus, it serves two purposes:

    1. Remove from this->adjacent_vertices the pointer corresponding to 
       the given vertex v (since that vertex is being removed)

    2. Move all of vertex v's adjacent vertices into that of the current vertex
*/
void Vertex::consume_neighbors_of_contracted_vertex(const Vertex* v) const {

    // Step 1.
    auto v_it = std::find(adjacent_vertices.begin(), adjacent_vertices.end(), v);
    adjacent_vertices.erase(v_it);

    // Step 2.
    this->adjacent_vertices.splice(this->adjacent_vertices.end(), v->adjacent_vertices);
};
        
/*
    This function is used in edge contraction. The Vertex in which this function
    is called is expected to be the vertex being deleted in the contract, which is v2. 
    This function visits each neighbor of the current vector and replaces
    any pointer to itself to the provided pointer v.
*/
void Vertex::direct_neighbors_to_contracted_vertex(const Vertex* v1, const Vertex* v2) const {

    // For each neighbor of this vertex
    for (auto vertex_ptr : this->adjacent_vertices) {

        // Search for v2 in the neighbor's neighbor list
        auto target = vertex_ptr->get_adjacent_vertex_position(v2);

        auto after_erased = target;
        if (target != vertex_ptr->adjacent_vertices.end()) {
            
            // Erasre from list returns iterator to very next element
            after_erased = vertex_ptr->adjacent_vertices.erase(target);

            // Insert into the list just before after_erased
            vertex_ptr->adjacent_vertices.insert(after_erased, v1);
        }
    }
};
