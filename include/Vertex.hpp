/*
    File: Vertex.hpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to represent a Vertex in a graph.
*/

#include <set>
#include <list>
#include <string>
#include "Color.hpp"

#ifndef VERTEX_H
#define VERTEX_H

// Forward declaration
class Edge;

class Vertex {
    private:
        std::string _id;
        unsigned int _label;
        mutable std::vector<Edge> incident_edges;
        mutable std::list<const Vertex*> adjacent_vertices;

    public:
        // Constructors
        Vertex();
        Vertex(std::string id, unsigned int label);
        ~Vertex();

        // Get Methods
        std::string id() const;
        unsigned int label() const;
        std::size_t degree();
        std::list<const Vertex*>::iterator get_adjacent_vertex_position(const Vertex* v) const;

        // Set Methods
        void new_adjacent_vertex(const Vertex* v) const;

        // Operators
        bool operator<(const Vertex& rhs) const;


        void consume_neighbors_of_contracted_vertex(const Vertex* v) const;
        void direct_neighbors_to_contracted_vertex(const Vertex* v1, const Vertex* v2) const;
};

#endif