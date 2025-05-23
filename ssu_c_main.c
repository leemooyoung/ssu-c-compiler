#include <stdio.h>
#include <string.h>

#include "gen.h"
#include "print.h"
#include "print_sem.h"
#include "semantic.h"
#include "support.h"

extern int yyparse();
extern FILE *yyin;
FILE *fout;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("source file not given\n");
    return 1;
  }
  if (strcmp(argv[1], "-o") == 0)
    if (argc > 3)
      if ((fout = fopen(argv[2], "w")) == NULL) {
        printf("can not open output file: %s\n", argv[3]);
        return 1;
      } else
        ;
    else {
      printf("out file not given\n");
      return 1;
    }
  else if (argc == 2)
    if ((fout = fopen("a.asm", "w")) == NULL) {
      printf("can not open output file: a.asm\n");
      return 1;
    }
  if ((yyin = fopen(argv[argc - 1], "r")) == NULL) {
    printf("can not open input file: %s\n", argv[argc - 1]);
    return 1;
  }
  printf("\nstart syntax analysis\n");
  initialize();
  yyparse();
  if (syntax_err) return 1;
  // print_ast(root);

  printf("\nstart semantic analysis\n");
  semantic_analysis(root);
  if (semantic_err) return 1;
  // print_sem_ast(root);

  printf("start code generation\n");
  code_generation(root);

  return 0;
}
