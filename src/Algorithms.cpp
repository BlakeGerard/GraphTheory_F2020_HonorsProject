#include <iostream>
#include "Algorithms.hpp"
#include "Graph.hpp"

unsigned int cayley_deletion_contraction(Graph g) {
    g.print_graph();
    std::cout << "-----" << std::endl;

    unsigned int g_min_degree = g.min_degree();
    if (g_min_degree == 0 && g.vertices.size() > 1) {                // Graph contains K1 as a component
        return 0;
    } else if (g_min_degree == 0 && g.incidence_map.size() == 0) {   // Graph isomorphic to K1
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