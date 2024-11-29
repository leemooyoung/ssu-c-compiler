#include <stdio.h>

#include "print.h"
#include "print_sem.h"
#include "semantic.h"
#include "support.h"

extern int yyparse();

int main() {
  initialize();
  yyparse();
  if (syntax_err) return 1;
  print_ast(root);

  semantic_analysis(root);
  if (semantic_err) return 1;
  print_sem_ast(root);

  return 0;
}
