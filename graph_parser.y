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

    #include "include/Graph.hpp"
}

%code {
    #include <string>
    #include <map>
    #include <vector>
    #include <algorithm>

    // Declare Flex/Bison variables and functions
    extern yy::graph_parser::symbol_type yylex();
    extern char *yytext;
    extern yy::location loc;

    unsigned int vertex_count = -1;
    unsigned int edge_count = -1;
    std::vector<std::string> ids_seen;
}

%token T_LCUR         "{"
%token T_RCUR         "}"
%token T_COMMA        ","
%token T_EOF 0        "end of file"     
%token <std::string>  T_ID

%type <Graph*> graph;
%type <std::map<Edge, std::pair<const Vertex*, const Vertex*>>> pair_map;
%type <std::pair<const Vertex*, const Vertex*>> vertex_pair;

%%

graph : T_LCUR pair_map T_RCUR
    {
    }

pair_map : vertex_pair
           {
                // Increment the edge_count and make a new edge with label=edge_count
                // and store the vertex pair with it.
                edge_count += 1;
                Edge edge = Edge(edge_count, $1);

                // Insert the new edge into the Graph incidence map
                graph->add_edge(edge, $1);
           }
           | pair_map T_COMMA vertex_pair 
           {
                $$ = $1;

                // Increment the edge_count and make a new edge with label=edge_count
                // and store the vertex pair with it.
                edge_count += 1;
                Edge edge = Edge(edge_count, $3);

                // Insert the new edge into the Graph incidence map
                graph->add_edge(edge, $3);
           }

vertex_pair : T_LCUR T_ID T_COMMA T_ID T_RCUR
            {
                Vertex v1;                                  // Vertex corresponding to the first id
                Vertex v2;                                  // Vertex corresponding to the second id
                const Vertex* v1_ptr;                       // Ptr to v1 after it has been inserted into the graph
                const Vertex* v2_ptr;                       // Ptr to v2 after it has been inserted into the graph
                bool v1_found = false;                      // Bool if v1's id has already been seen
                bool v2_found = false;                      // Bool if v2's id has already been seen
                std::vector<std::string>::iterator it;      // Iterator for finding ids in ids_seen vector

                // Search for the v1 label in the list of seen ids
                it = std::find(ids_seen.begin(), ids_seen.end(), $2);

                // If the vertex ID was NOT found
                if (it == ids_seen.end()) {

                    // Increment the vertex_count and create a new vertex with id=$2 and label=vertex_count
                    vertex_count += 1;
                    v1 = Vertex($2, vertex_count);

                    // Add the vertex to the graph and recieve a ptr to that element in the vertex set
                    v1_ptr = graph->add_vertex(v1);
                    v1_found = true;

                } else {

                    // Otherwise, get the vertex_ptr from the graph to work with
                    v1_ptr = graph->get_vertex_ptr_by_id(*it);
                    v1_found = true;
                }

                // Search for the v2 ID in the list of seen ids
                it = std::find(ids_seen.begin(), ids_seen.end(), $4);

                if (it == ids_seen.end()) {

                    // Increment the vertex_count and create a new vertex with id=$2
                    // and label=vertex_count
                    vertex_count += 1;
                    v2 = Vertex($4, vertex_count);

                    // Add the vertex to the graph and recieve a ptr to that element in the vertex set
                    v2_ptr = graph->add_vertex(v2);
                    v2_found = true;

                } else {

                    // Otherwise, get the vertex_ptr from the graph to work with
                    v2_ptr = graph->get_vertex_ptr_by_id(*it);
                    v2_found = true;
                }

                // At the end of that search, v1_ptr and v2_ptr will point to 
                // the addresses of v1 and v2, respectively, in the graph's vertex set.

                // Add new vertex ids to the list
                if (!v1_found) { ids_seen.push_back($2); }
                if (!v2_found) { ids_seen.push_back($4); }

                // v1 and v2 should track each other in their respective adjacent_vertices sets
                v1_ptr->new_adjacent_vertex(v2_ptr);
                v2_ptr->new_adjacent_vertex(v1_ptr);

                // Return (v1_ptr, v2_ptr) pair
                std::pair<const Vertex*, const Vertex*> pair;
                pair.first = v1_ptr;
                pair.second = v2_ptr;
                $$ = pair;
            }
%%

void yy::graph_parser::error (const yy::location & l, const std::string & s) {
	std::cerr << "Parsing error at " << l << " : " << s << std::endl;
}