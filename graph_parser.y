%language "c++"
%skeleton "lalr1.cc"
%require "3.2"
%locations
%defines
%verbose

%define parse.assert true
%define parse.trace true
%define parse.error verbose

%define api.token.constructor
%define api.value.type variant
%define api.parser.class {graph_parser}
%parse-param {Graph* graph}

%code requires {
    #ifndef YY_NULLPTR
    #define YY_NULLPTR 0
    #endif

    #include <iostream>
    #include <limits>
    #include "include/Graph.hpp"
}

%code {
    #include <string>
    #include <map>
    #include <set>

    // Declare Flex/Bison variables and functions
    extern yy::graph_parser::symbol_type yylex();
    extern char *yytext;
    extern yy::location loc;

    unsigned int vertex_count = -1;
    unsigned int edge_count = -1;
    std::map<unsigned int, unsigned int> vertex_degrees = std::map<unsigned int, unsigned int>();
    std::map<std::string, unsigned int> vertex_ids = std::map<std::string, unsigned int>();
}

%token T_LCUR         "{"
%token T_RCUR         "}"
%token T_COMMA        ","
%token T_EOF 0        "end of file"     
%token <std::string>  T_ID

%type <Graph*> graph;
%type <std::map<unsigned int, std::pair<unsigned int, unsigned int>>> pair_map;
%type <std::pair<unsigned int, unsigned int>> vertex_pair;

%%

graph : T_LCUR pair_map T_RCUR
    {
        /*
        std::set<unsigned int> vertices;
        for (const auto& element : vertex_ids) {
            vertices.insert(element.second);
        }
        graph->set_vertices(vertices);
        */
        graph->set_vertex_degree_map(vertex_degrees);
    }

pair_map : vertex_pair
           {
                if ($1.first != UINT8_MAX) {
                    edge_count += 1;
                    graph->add_edge(edge_count, $1);
                }
           }
           | pair_map T_COMMA vertex_pair 
           {
                $$ = $1;
                if ($3.first != UINT8_MAX) {
                    edge_count += 1;
                    graph->add_edge(edge_count, $3);
                }
           }

vertex_pair : T_LCUR T_ID T_COMMA T_ID T_RCUR
            {
                unsigned int v1;
                unsigned int v2;
                unsigned int found;

                // Search for the v1 label in the list of seen ids
                found = vertex_ids.count($2);

                // If the vertex ID was NOT found
                if (!found) {

                    vertex_count += 1;
                    v1 = vertex_count;
                    vertex_ids.insert({$2, vertex_count});
                    vertex_degrees.insert({vertex_count, 0});

                } else {

                    // Otherwise, get the vertex_ptr from the graph to work with
                    v1 = vertex_ids[$2];
                }

                // Search for the v2 ID in the list of seen ids
                found = vertex_ids.count($4);

                if (!found) {

                    vertex_count += 1;
                    v2 = vertex_count;
                    vertex_ids.insert({$4, vertex_count});
                    vertex_degrees.insert({vertex_count, 0});

                } else {

                    // Otherwise, get the vertex_ptr from the graph to work with
                    v2 = vertex_ids[$4];
                }

                vertex_degrees[v1] += 1;
                vertex_degrees[v2] += 1;

                $$ = std::pair<unsigned int, unsigned int>(v1, v2);
            }
            | T_LCUR T_ID T_RCUR
            {
                unsigned int found;

                // Search for the v1 label in the list of seen ids
                found = vertex_ids.count($2);

                // If the vertex ID was NOT found
                if (!found) {
                    vertex_count += 1;
                    vertex_ids.insert({$2, vertex_count});
                    vertex_degrees.insert({vertex_count, 0});
                }

                $$ = std::pair<unsigned int, unsigned int>(UINT8_MAX, UINT8_MAX);
            }
            
%%

void yy::graph_parser::error (const yy::location & l, const std::string & s) {
	std::cerr << "Parsing error at " << l << " : " << s << std::endl;
}