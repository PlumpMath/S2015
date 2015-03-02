%{
#include <iostream>
#include <cmath>
#include "compiler.cc"


/* Parser error reporting routine */
void yyerror(const char *msg);

/* Scanner routine defined by Flex */
int yylex();

using namespace std;

Compiler comp;

enum type {
    INT_TYPE = 0,
    FLOAT_TYPE = 1
};

%}

%define parse.error verbose

/* yylval union type */
%union {
    char* sVal;
    long lVal;
}

/* Miscellaneous token types */
%token <sVal> INTEGER
%token <sVal> FLOAT
%token <sVal> DEF
%token <sVal> ID
%token <sVal> PRINT
%token <sVal> PRINTLN

/* Operators */
%right '+' '-'
%right '*' '/' '%'
%right UMINUS
%right '^'

/* Nonterminal types */
%type <lVal> expr
%start input

%%

input:
/* empty */
| input line
;

line:
'\n'
| '(' expr ')' '\n'
| '(' DEF ID expr ')' '\n' { comp.assign($3, $4); }
| '(' PRINT expr ')' '\n' { comp.print(NULL, $3, false); }
| '(' PRINT ID ')' '\n' { int type = comp.getType($3); if (type == -1) yyerror("Undefined value"); comp.print($3, type, false); }
| '(' PRINTLN expr ')' '\n' { comp.print(NULL, $3, true); }
| '(' PRINTLN ID ')' '\n' { int type = comp.getType($3); if (type == -1) yyerror("Undefined value"); comp.print($3, type, true); }
;

expr:
 '+' expr expr   { $$ = $2; if ($2 == $3) comp.add($2); else yyerror("Type mismatch"); }
| '-' expr expr { $$ = $2; if ($2 == $3) comp.sub($2); else yyerror("Type mismatch"); }
| '*' expr expr { $$ = $2; if ($2 == $3) comp.mult($2); else yyerror("Type mismatch"); }
| '/' expr expr { $$ = $2; if ($2 == $3) comp.div($2); else yyerror("Type mismatch"); }
| '%' expr expr { $$ = $2; if ($2 == $3) comp.mod($2); else yyerror("Type mismatch"); }
| '-' expr      { $$ = $2; comp.negate($2); }
| '^' expr expr { $$ = $2; if ($2 == $3) comp.exp($2); else yyerror("Type mismatch"); }
| INTEGER       { comp.push($1, INT_TYPE, false); $$ = INT_TYPE; }
| FLOAT         { comp.push($1, FLOAT_TYPE, false); $$ = FLOAT_TYPE; }
| ID            { int type = comp.getType($1); comp.push($1, type, true); $$ = type; }
| '(' expr ')'  { $$ = $2; }
;

%%

void yyerror(const char *msg) {

    cerr << "Parser error:\n" << msg << endl;
    exit(1);
}

int main()
{
    yyparse();
    comp.output();
    return EXIT_SUCCESS;
}
