%{ 
#include <string>
#include <iostream>
#include "graph_parser.h"

// Flex incompatibility protection
# undef yywrap
# define yywrap() 1

// yylex() declaration
#undef YY_DECL
#define YY_DECL yy::graph_parser::symbol_type yylex()
YY_DECL;

// Location declaration
yy::location loc;

// Code run each time a pattern is matched.
#define YY_USER_ACTION  loc.columns(yyleng);
%}

%option yylineno
%option noyywrap nounput

ID [A-Za-z0-9_'-]*

%%

\/\/.*$

[ \t]+		{ 
				loc.step(); 
			}
		
[\n]+		{ 
				loc.lines(yyleng); loc.step(); 
			}

"{"			{  
				return yy::graph_parser::make_T_LCUR(loc); 
			}

"}"			{  
				return yy::graph_parser::make_T_RCUR(loc); 
			}

","			{  
				return yy::graph_parser::make_T_COMMA(loc); 
			}

{ID}		{ 
    			return yy::graph_parser::make_T_ID(std::string(yytext), loc);
			}

<<EOF>>		{ 
				return yy::graph_parser::make_T_EOF(loc);
			}

.			{ 
				std::cout << "Unexpected character: " << yytext << std::endl;
				exit(1);
			}

%%