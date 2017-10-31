
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
typedef struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION,
    E_VARIABLE,
    E_OPBOOLEAN
  } kind;
  
  union 
  {
    int value; // INTEGER
    
    char *var; // VAR

    struct // OPERATION
    { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op;

    struct // OPBOOLEAN 
    { 
      int operator; // MORE, LESS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op_bl;
  } attr;
}* Expr;



typedef struct _cmd
{
  enum
  {
    E_ATRIB,
    E_IF,
    E_WHILE,
    E_FOR, 
    E_OUTPUT,
    E_INPUT

  } kind;
  
  union
  {
    struct // ATRIB
    {
      char *var;
      Expr exp;
    } atrib;

    struct // IF
    {
      Expr cond;
      struct _cmdList* body;   

      struct _cmdList* elsee;
    } iff;

    struct // FOR
    {
      Expr cond;
      struct _cmdList* body;
    } for1;

    struct // FOR
    {
      struct _cmd* decl;
      Expr cond;
      struct _cmdList* body;
    } for1;

    Expr output; // OUTPUT

    char *input; // INPUT
  } attr;
}* cmd;


typedef struct _cmdList
{
  cmd head;
  struct _cmdList *tail;
}* cmdList;

typedef struct _elseif
{
  Expr cond;
  cmdList body;
}* elseif;

typedef struct _elseifList
{
  elseif head;
  struct _elseifList *tail;
}* elseifList;


Expr ast_integer(int v);
Expr ast_var(char *v);
Expr ast_operation(int operator, Expr left, Expr right);
Expr ast_boolean(int operator, Expr left, Expr right);
cmdList mklist(cmd head, cmdList tail);
cmd mkAtrib(char *var, Expr e);
cmd astIf(Expr ifCond, cmdList ifBody, elseifList ElseIFlist, cmdList elsee);
cmd astFor(Expr cond, cmdList body);
cmd astFor(cmd decl, Expr cond, cmdList body);
cmd mkOutput(Expr e);
cmd mkInput(char *var);

#endif
