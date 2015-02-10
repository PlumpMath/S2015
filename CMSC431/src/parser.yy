%{
#include <iostream>
#include <cmath>
#include "compiler.cc"

/* Parser error reporting routine */
void yyerror(const char *msg);

/* Scannar routine defined by Flex */
int yylex();

using namespace std;

Compiler comp;
%}

/* yylval union type */
%union {
    long longval;
}

/* Miscellaneous token types */
%token <longval> INTEGER

/* Operators */
%right '+' '-'
%right '*' '/' '%'
%right UMINUS
%right '^'

/* Nonterminal types */
%type <longval> expr
%start input
%%

input:
/* empty */
| input line
;

line:
'\n'
| { comp.startBoilerplate(); } '(' expr ')' '\n' { comp.output(); }
;

expr:
'+' expr expr   { comp.add(); }
| '-' expr expr { comp.sub(); }
| '*' expr expr { comp.mult(); }
| '/' expr expr { comp.div(); }
| '%' expr expr { comp.mod(); }
| '-' expr      { comp.negate(); }
| '^' expr expr { comp.exp(); }
| INTEGER       { comp.push($1); }
| '(' expr ')'    { $$ = $2; }
;

%%

void yyerror(const char *msg)
{
    cerr << "Parser error:\n" << msg << endl;
    exit(1);
}

int main()
{
    return yyparse();
}
