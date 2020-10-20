%language "c++"
%skeleton "lalr1.cc" /* -*- C++ -*- */
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

    // Declare Flex/Bison variables and functions
    extern yy::qrane_parser::symbol_type yylex();
    extern char *yytext;
    extern yy::location loc;

    unsigned int edge_count = -1;
    std::vector<std::string> ids_seen;
    std::vector<Vertex*> vertices_seen;
}

%token T_LCUR         "{"
%token T_RCUR         "}"
%token T_COMMA        ","
%token T_EOF 0        "end of file"     
%token <std::string>  T_ID

%type <Graph*> graph;
%type <std::map<Edge, std::pair<Vertex*, Vertex*>>> pair_map;
%type <std::pair<Vertex*, Vertex*>> vertex_pair;

%%

graph : T_LCUR pair_map T_RCUR
     {
        graph->input_incidence_map($2);
     }

pair_map : vertex_pair
           {
               $$ = std::map<Edge, std::pair<Vertex*, Vertex*>>();

               std::string edge_id = "e" + edge_count;
               edge_count += 1;

               Edge edge = Edge(edge_id);
               $$.insert(std::make_pair(edge, $1));
           }
           | pair_map T_COMMA vertex_pair 
           {
               $$ = $1;

               std::string edge_id = "e" + edge_count;
               edge_count += 1;
               
               Edge edge = Edge(edge_id);
               $$.insert(std::make_pair(edge, $1));
           }

vertex_pair : T_LCUR T_ID T_COMMA T_ID T_RCUR
            {
                Vertex* v1;
                Vertex* v2;

                if (auto it = std::find(ids_seen.begin(), ids_seen.end(), $2) != ids_seen.end()) {
                    v1 = vertices_seen.at(it);
                } else {
                    v1 = new Vertex($2);
                    ids_seen.push_back($2);
                    vertices_seen.push_back(v1);
                }
                if (auto it = std::find(ids_seen.begin(), ids_seen.end(), $4) != ids_seen.end()) {
                    v2 = vertices_seen.at(it);
                } else {
                    v2 = new Vertex($4);
                    ids_seen.push_back($4);
                    vertices_seen.push_back(v2);
                }
                
                std::pair<Vertex*, Vertex*> pair;
                pair.first = v1;
                pair.second = v2;
                $$ = pair;
            }

%%

void yy::graph_parser::error (const yy::location & l, const std::string & s) {
	std::cerr << "Parsing error at " << l << " : " << s << std::endl;
}