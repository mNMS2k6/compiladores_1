// Tokens
%token 
INT			// Inteiros
PLUS 			// +
SUB		   	// -
MUL 			// x
DIV		  	// /
MOD 		  	// %
EQUALS 	  	// ==
DIFF 		  	// !=
GREATER_THAN 		// >
LESS_THAN 		// < 
GREATER_THAN_EQUALS 	// >=
LESS_THAN_EQUALS 	// <=
ATRIB 		// :=
OPEN 			// (
CLOSE 		// )
IF1 			// IF
ELSE1 			// ELSE
FOR1 			// FOR
TRUE 			// TRUE 
FALSE 		// FALSE 
VAR 			// Variaveis 
NL 			// nova linha
ABRE 			// { 
FECHA 		// }
F 		//;



// Operator associativity & precedence
%left PLUS SUB
%left MUL DIV MOD


// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
int intValue;
Expr* exprValue;
//Exprlist* list;
char *varval;
cmdList cmd_l; 
cmd cmd_;
}

%type <intValue> INT
%type <exprValue> expr
//%type <Exprlist> Exprlist
%type <exprValue> exprB // Exp bool

%type <varval> VAR

%type <cmd_> for_atrib
%type <cmd_> exprCmd
%type <cmd_l> cmd_list


// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires
{
#include <stdio.h>
#include <stdlib.h>
#include "abstree.h"  

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
Expr* root;
//Exprlist* rootl;
}

%%
program: cmd_list { rootl = $1; }

cmd_list: 
exprCmd { $$ = mklist($1, NULL); }
| exprCmd F cmd_list { $$ = mklist($1,$3); }

expr: 
INT { $$ = ast_integer($1); }
| expr PLUS expr { $$ = ast_operation(PLUS, $1, $3); }
| expr SUB expr { $$ = ast_operation(SUB, $1, $3); }
| expr MUL expr { $$ = ast_operation(MUL, $1, $3); }
| expr DIV expr { $$ = ast_operation(DIV, $1, $3); }
| expr MOD expr { $$ = ast_operation(MOD, $1, $3); }      

exprB:
TRUE { $$ = ast_integer(1);}
|FALSE { $$ = ast_integer(0);}
| VAR  { $$ = ast_var($1); }
| expr EQUALS expr { $$ = ast_boolean(EQUALS, $1, $3); }
| expr DIFF expr { $$ = ast_boolean(DIFF, $1, $3); }
| expr GREATER_THAN expr { $$ = ast_boolean(GREATER_THAN, $1, $3); }
| expr LESS_THAN expr { $$ = ast_boolean(LESS_THAN, $1, $3); }
| expr GREATER_THAN_EQUALS expr { $$ = ast_boolean(GREATER_THAN_EQUALS, $1, $3); }
| expr LESS_THAN_EQUALS expr { $$ = ast_boolean(LESS_THAN_EQUALS, $1, $3); }

exprCmd:
VAR ATRIB expr  { $$ = mkAtrib($1, $3); }
| IF1 OPEN exprB CLOSE ABRE cmd_list FECHA  { $$ = astif($3, $6, NULL); }
| IF1 OPEN exprB CLOSE ABRE cmd_list ELSE1 ABRE cmd_list FECHA FECHA { $$ = astif($3, $6, $9); }
| FOR1 for_atrib F exprB F exprCmd ABRE cmd_list FECHA { $$ = astfor($2, $4, $8); }
| FOR1 exprB ABRE cmd_list FECHA { $$ = astfor($2, $4); }

for_atrib:
	VAR ATRIB expr     { $$ = mkAtrib($1,$3); }

%%

void yyerror(const char* err) {
printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}