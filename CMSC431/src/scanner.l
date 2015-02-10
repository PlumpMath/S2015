%{
#include <cstdlib>
#include "parser.tab.hh"
%}

%%

[[:digit:]]+ {
    /* Integers */
    yylval.longval = atof(yytext);
    return INTEGER;
}

[ \t]+ {
    /* Eat whitespace */
}

.|\n {
    /* Return any unmatched character as is */
    return (int)(*yytext);
}

%%
