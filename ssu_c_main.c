#include <stdio.h>

extern int yyparse();

int main() {
    yyparse();
    printf("parse complete!\n");
}
