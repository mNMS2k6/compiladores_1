%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }

#.*\n { yyline++; }

\n { yyline++; }

\-?[0-9]+ { 
yylval.intValue = atoi(yytext);
return INT;
}
"+" { return PLUS; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"%" { return MOD; }
"==" { return EQUALS; }
"!=" { return DIFF; }
">"  { return GREATER_THAN; }
"<" { return LESS_THAN; }
">=" { return GREATER_THAN_EQUALS; }
"<=" { return LESS_THAN_EQUALS; }
":=" { return ATRIB; }
"(" { return OPEN; }
")" { return CLOSE; }
"{" { return ABRE; }
"}" { return FECHA; }
"if" { return IF1; }
"else" { return ELSE1; }
"for" { return FOR1; }
"true" { return TRUE; }
"false" { return FALSE; }


";" { return F; }

\-?[a-z,A-Z]+ {
yylval.varval = strdup(yytext);
return VAR; }

. { yyerror("unexpected character"); }
%%