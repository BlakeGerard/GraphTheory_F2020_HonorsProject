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
#include "unistd.h"
#include "Graph.hpp"
#include "graph_parser.h"

extern yy::graph_parser::symbol_type yylex();
extern FILE *yyin;

int main(int argc, char **argv) {

    FILE *input_graph;
    input_graph = fopen(argv[2], "r");
    if (input_graph) {
        yyin = input_graph;
    } else {
        std::cout << "Failed to open file" << std::endl;
        exit(1);
    }

    Graph* g;
    yy::graph_parser parser(g);
    int result = parser.parse();

    if (result) {
        std::cout << "Parsing complete" << std::endl;
    } else {
        std::cout << "Parsing failed" << std::endl;
        exit(2);
    }
    
    return 0;
};