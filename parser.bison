// Tokens
%token 
  INT
  PLUS
  SUB
  MUL
  DIV
  MOD
  EQUALS
  DIFF
  GREATER_THAN
  LESS_THAN
  GREATER_THAN_EQUALS
  LESS_THAN_EQUALS
  ATRIB
  OPEN
  CLOSE
  IF
  ELSE
  END
  FOR
  TRUE
  FALSE
  VAR
  NL
  ABRE
  FECHA



// Operator associativity & precedence
%left PLUS SUB
%left MUL DIV MOD


// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue;
  Exprlist* list; 
}

%type <intValue> INT
%type <exprValue> expr
%type <list> expr_list

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
  Exprlist* rootl;
}

%%
program: cmd_list { rootl = $1; }

cmd_list: 
  exprCmd { $$ = mklist($1, NULL); }
  | exprCmd NL cmd_list { $$ = mklist($1,$2); }

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
  | expr EQUALS expr { $$ = ast_operation(EQUALS, $1, $3); }
  | expr DIFF expr { $$ = ast_operation(DIFF, $1, $3); }
  | expr GREATER_THAN expr { $$ = ast_operation(GREATER_THAN, $1, $3); }
  | expr LESS_THAN expr { $$ = ast_operation(LESS_THAN, $1, $3); }
  | expr GREATER_THAN_EQUALS expr { $$ = ast_operation(GREATER_THAN_EQUALS, $1, $3); }
  | expr LESS_THAN_EQUALS expr { $$ = ast_operation(LESS_THAN_EQUALS, $1, $3); }

exprCmd:
  VAR ATRIB expr
  | IF OPEN exprB CLOSE ABRE CmdList FECHA 
  | IF OPEN exprB CLOSE ABRE CmdList ELSE ABRE CmdList FECHA FECHA

%%


void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}