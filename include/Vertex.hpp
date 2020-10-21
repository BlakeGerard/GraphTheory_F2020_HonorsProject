/*
    File: Vertex.hpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to represent a Vertex in a graph.
*/

#include <vector>
#include <string>
#include "Color.hpp"

#ifndef VERTEX_H
#define VERTEX_H

// Forward declaration
class Edge;

class Vertex {
    private:
        std::string _id;
        unsigned int _degree;
        std::vector<Edge> incident_edges;
        std::vector<Vertex> adjacent_vertices;

    protected:
        color_t color;

    public:
        Vertex();
        Vertex(std::string id);
        ~Vertex();

        std::string id();
        unsigned int degree();
        void increment_degree();
};

#endif