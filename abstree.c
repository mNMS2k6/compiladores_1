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


// imcompleto alterar para comand list
Exprlist* mklist(Expr* e, Exprlist* list)
{
  Exprlist* node= (Exprlist *)malloc(sizeof(Exprlist));
  node->exp=e;
  node->next=list;
  return node;
}