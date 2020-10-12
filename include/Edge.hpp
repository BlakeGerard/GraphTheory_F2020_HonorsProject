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
        std::pair<Vertex, Vertex> connected_vertices;
        color_t color;

    public:
        Edge();
        ~Edge();
        Edge(std::pair<Vertex, Vertex> connected_vertices);
};

class WeightedEdge : public Edge {
    protected:
        int weight;
    
    public:
        WeightedEdge();
        ~WeightedEdge();
        WeightedEdge(int weight);
        WeightedEdge(std::pair<Vertex, Vertex> connected_vertices);
};

#endif