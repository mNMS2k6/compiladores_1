// AST constructor functions

#include <stdlib.h> // for malloc
#include "abstree.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_operation
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Expr ast_boolean (int operator, Expr* left, Expr* right) 
{
  Expr node = (Expr) malloc(sizeof(struct _Expr));
  node->kind = E_OPBOOLEAN;
  node->attr.op_bl.operator = operator;
  node->attr.op_bl.left = left;
  node->attr.op_bl.right = right;
  return node;
}

cmd mkAtrib(char *var, Expr e)
{
	cmd node = (cmd) malloc(sizeof(struct _cmd));
  node->kind = E_ATRIB;
  node->attr.atrib.var = var;
  node->attr.atrib.exp = e;
  return node;		
}

cmd astIf(Expr ifCond, cmdList ifBody, cmdList elsee)
{
  cmd node = (cmd) malloc(sizeof(struct _cmd));
  node->kind = E_IF;
  node->attr.iff.cond = ifCond;
  node->attr.iff.body = ifBody;
  node->attr.iff.elsee = elsee;
  return node;     
}


// imcompleto alterar para comand list
Exprlist* mklist(Expr* e, Exprlist* list)
{
  Exprlist* node= (Exprlist *)malloc(sizeof(Exprlist));
  node->exp=e;
  node->next=list;
  return node;
}
