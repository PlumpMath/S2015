%{
#include <cstdlib>
#include <cstring>
#include "parser.tab.hh"
%}

NUMBER [0-9]+

%option noyywrap

%%
{NUMBER}(\.{NUMBER}|(\.{NUMBER})?[eE][+-]?{NUMBER}) {
    /* Floats */
    yylval.sVal = yytext;
    return FLOAT;
}

{NUMBER}+ {
    /* Integers */
    yylval.sVal = yytext;
    return INTEGER;
}

"def" {
    return DEF;
}

"print" {
    return PRINT;
}

"println" {
    return PRINTLN;
}

[A-Za-z_]+ {
    char* token = strdup(yytext);
    yylval.sVal = strtok(token, " ");
    return ID;
}

[ \t]+ {
    /* Eat whitespace */
}

.|\n {
    /* Return any unmatched character as is */
    return (int)(*yytext);
}

%%
