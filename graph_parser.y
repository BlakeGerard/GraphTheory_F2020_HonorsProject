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
               auto map_start = std::map<Edge, std::pair<Vertex*, Vertex*>>();

               // Name the edge and increase the edge count
               edge_count += 1;
               std::string edge_id = std::string("e");
               edge_id.append(std::to_string(edge_count));
               Edge edge = Edge(edge_id);

               // Map edge to vertex_pair
               map_start.insert(std::make_pair(edge, $1));
               $$ = map_start;
           }
           | pair_map T_COMMA vertex_pair 
           {
               $$ = $1;

               // Name the edge and increase the edge count
               edge_count += 1;
               std::string edge_id = std::string("e");
               edge_id.append(std::to_string(edge_count));
               
               // Create a new Edge and map it to the vertex_pair
               Edge edge = Edge(edge_id);
               $$.insert(std::make_pair(edge, $3));
           }

vertex_pair : T_LCUR T_ID T_COMMA T_ID T_RCUR
            {
                Vertex* v1;
                Vertex* v2;

                // Search for the v1 ID in the list of seen ids
                auto it = std::find(ids_seen.begin(), ids_seen.end(), $2);
                if (it != ids_seen.end()) {

                    // If found, set v1 to the vertex corresponding to the id and increment its degree
                    v1 = vertices_seen[std::distance(ids_seen.begin(), it)];
                    v1->increment_degree();

                } else {

                    // If not found, create a new vertex with ID $2. Update ids_seen and vertices_seen accordingly
                    v1 = new Vertex($2);
                    ids_seen.push_back($2);
                    vertices_seen.push_back(v1);
                    v1->increment_degree();
                }

                // Search for the v2 ID in the list of seen ids
                it = std::find(ids_seen.begin(), ids_seen.end(), $4);
                if (it != ids_seen.end()) {

                    // If found, set v2 to the vertex corresponding to the id and increment its degree
                    v2 = vertices_seen[std::distance(ids_seen.begin(), it)];
                    v2->increment_degree();

                } else {

                    // If not found, create a new vertex with ID $4. Update ids_seen and vertices_seen accordingly
                    v2 = new Vertex($4);
                    ids_seen.push_back($4);
                    vertices_seen.push_back(v2);
                    v2->increment_degree();
                }
                
                // Return (v1, v2) pair
                std::pair<Vertex*, Vertex*> pair;
                pair.first = v1;
                pair.second = v2;
                $$ = pair;
            }

%%

void yy::graph_parser::error (const yy::location & l, const std::string & s) {
	std::cerr << "Parsing error at " << l << " : " << s << std::endl;
}