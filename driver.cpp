/*
    File: driver.cpp
    Project: MATH-4673 Graph Theory Honors Project
    Author: Blake Gerard
    Date: 12/10/2020
    Description:
        Driver class to act as a user of my graph library
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
#include "Graph.hpp"
#include "graph_parser.h"
#include "include/Algorithms.hpp"

extern yy::graph_parser::symbol_type yylex();
extern FILE *yyin;

int main(int argc, char **argv) {

    FILE *input_graph;
    input_graph = fopen(argv[1], "r");
    if (input_graph) {
        yyin = input_graph;
    } else {
        std::cout << "Failed to open file." << std::endl;
        exit(1);
    }

    Graph* g = new Graph();
    yy::graph_parser parser(g);
    int result = parser.parse();
    fclose(input_graph);

    if (!result) {
        std::cout << "Parsing complete." << std::endl;
    } else {
        std::cout << "Parsing failed." << std::endl;
        exit(2);
    }

    //g->print_graph();
    unsigned int spanning_trees = cayley_deletion_contraction(*g);
    std::cout << "spanning_trees: " << spanning_trees << std::endl;
    
    return 0;
};