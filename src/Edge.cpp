/*
    File: Edge.cpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Class to represent an Edge in a graph.
*/

#include "Edge.hpp"

/* Edge */
Edge::Edge() {};
Edge::~Edge() {};

Edge::Edge(std::string id) {
    this->id = id;
};

Edge::Edge(std::pair<Vertex, Vertex> connected_vertices) {
    this->connected_vertices = connected_vertices;
}

/* WeightedEdge */
WeightedEdge::WeightedEdge() {};
WeightedEdge::~WeightedEdge() {};

WeightedEdge::WeightedEdge(int weight) {
    this->weight = weight;
};

WeightedEdge::WeightedEdge(std::pair<Vertex, Vertex> connected_vertices) {
    this->connected_vertices = connected_vertices;
};