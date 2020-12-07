#include <iostream>
#include "Algorithms.hpp"
#include "Graph.hpp"

/*
    Compute the number of spanning trees in the given graph by 
    the Cayley's recursive deletion-contraction algorithm.
    Input:
        g: Graph 
    Output:
        number of spanning trees on Graph g
*/
unsigned int cayley_deletion_contraction(Graph g) {

    // Compute the minimum degree of the graph to evaluate the base cases
    unsigned int g_min_degree = g.min_degree();

    // Graph contains K1 as a component. Thus, it is disconnected and has zero spanning trees.
    if (g_min_degree == 0 && g.vertex_degree_map.size() > 1) {         
        return 0;

    // Graph isomorphic to K1. Thus, it has exactly one spanning tree.
    } else if (g_min_degree == 0 && g.incidence_map.size() == 0) {   
        return 1;
    }

    // Choose the first edge in the map
    unsigned int chosen_edge = g.incidence_map.begin()->first;

    // If the chosen edge is a loop, we do not develop a contraction branch
    if (g.edge_is_loop(chosen_edge)) {
        g.delete_edge_by_label(chosen_edge);
        return cayley_deletion_contraction(g);
    }

    // Create a new graph with chose_edge removed
    Graph g_del = Graph(g);
    g_del.delete_edge_by_label(chosen_edge);

    // Create a new graph with chosen_edge contracted
    Graph g_con = Graph(g);
    g_con.contract_edge_by_label(chosen_edge);
        
    // Return t(G - e) + t(G * e)
    return cayley_deletion_contraction(g_del) + cayley_deletion_contraction(g_con);
};
