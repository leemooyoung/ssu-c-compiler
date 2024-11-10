#include <stdio.h>

#include "print.h"
#include "support.h"

extern int yyparse();

int main() {
  initialize();
  yyparse();
  if (syntax_err) return 1;
  print_ast(root);

  return 0;
}
