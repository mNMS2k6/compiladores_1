#include <stdio.h>
#include "parser.h"
typedef int bool;
enum { false, true };

void eval(Expr expr) {
  int result = 0;

  
  if (expr->kind == E_INTEGER)
  {
    printf("%d", expr->attr.value);
  } 
  else if (expr->kind == E_VARIABLE)
  {
    printf("%s", expr->attr.var);
  } 
  else if (expr->kind == E_OPERATION)
  {
    eval(expr->attr.op.left);

    switch (expr->attr.op.operator) 
    {
      case PLUS: 
      printf(" + ");
      break;

      case SUB:
      printf(" - ");      
      break;

      case MUL:
      printf(" * ");
      break;

      case DIV:
      printf(" / ");
      break;

      case MOD:
      printf(" %% ");
      break;
      // TODO Other cases here ...
      default: yyerror("Unknown operator!");
    }
    eval(expr->attr.op.right);

  }
  
  else if (expr->kind == E_OPBOOLEAN)
  {
    eval(expr->attr.op_bl.left);

    switch (expr->attr.op_bl.operator)
    {
      case LESS_THAN: 
      printf(" < ");
      break;

      case LESS_THAN_EQUALS:
      printf(" <= ");      
      break;

      case GREATER_THAN:
      printf(" > ");
      break;

      case GREATER_THAN_EQUALS:
      printf(" >= ");
      break;

      case EQUALS:
      printf(" == ");
      break;

      case DIFF:
      printf(" != ");
      break;
      // TODO Other cases here ...
      default: yyerror("Unknown operator!");
    }
    eval(expr->attr.op_bl.right);

  }

}

void cmd_list(cmd cmd) 
{
  if (cmd->kind == E_ATRIB) 
  {
    printf("%s = ", cmd->attr.atrib.var); 
    eval(cmd->attr.atrib.exp);
    printf("\n");
  } 
  else if (cmd->kind == E_IF) 
  {
    if (cmd->attr.iff.elsee == NULL)
    {
      printf("IF "); 
      eval(cmd->attr.iff.cond);
      printf("\n{\n");
      while(cmd->attr.iff.body != NULL)
      {
        cmd_list(cmd->attr.iff.body->head);
        cmd->attr.iff.body = cmd->attr.iff.body->tail;
      }
      printf("}\n");
    }
    else
    {
      printf("IF "); 
      eval(cmd->attr.iff.cond);
      printf("\n{\n");
      while(cmd->attr.iff.body != NULL)
      {
        cmd_list(cmd->attr.iff.body->head);
        cmd->attr.iff.body = cmd->attr.iff.body->tail;
      }
      printf("}\n");
      printf("ELSE ");
      printf("\n{\n");
      while(cmd->attr.iff.elsee != NULL)
      {
        cmd_list(cmd->attr.iff.elsee->head);
        cmd->attr.iff.elsee = cmd->attr.iff.elsee->tail;
      }
      printf("}\n");
    }
  } 
}

int main(int argc, char** argv) 
{
  --argc; ++argv;
  if (argc != 0)
  {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } 
  if (yyparse() == 0) {

    while(root != NULL)
    {
      cmd_list(root->head);
      root = root->tail;
    }
  }
  return 0;
}
