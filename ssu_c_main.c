#include <stdio.h>

#include "print.h"
#include "support.h"

extern int yyparse();

int main() {
  initialize();
  yyparse();
  if (syntax_err) return 1;
  printf("parse complete!\n\n");
  print_ast(root);

  return 0;
}
