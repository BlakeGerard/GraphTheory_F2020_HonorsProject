/*
    File: Edge.hpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to represent an Edge in a graph.
*/

#include <vector>
#include "Vertex.hpp"

#ifndef EDGE_H
#define EDGE_H

class Edge {
    protected:
        unsigned int _label;
        std::pair<const Vertex*, const Vertex*> connected_vertices;

    public:
        // Constructors
        Edge();
        ~Edge();
        Edge(unsigned int label, std::pair<const Vertex*, const Vertex*> connected_vertices);

        // Get Methods
        unsigned int label();

        // Operators
        bool operator<(const Edge& rhs) const;
};

#endif