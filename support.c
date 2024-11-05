#include "support.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type.h"

extern char *yytext;
A_TYPE *int_type, *char_type, *void_type, *float_type, *string_type;
A_ID *current_id = NIL;
int syntax_err = 0;
int line_no = 1;
int current_level = 0;

// create symbol table
A_ID *makeIdentifier(char *s) {
  A_ID *id;
  id = malloc(sizeof(A_ID));
  id->name = s;
  id->kind = 0;
  id->specifier = 0;
  id->level = current_level;
  id->address = 0;
  id->init = NIL;
  id->type = NIL;
  id->link = NIL;
  id->line = line_no;
  id->value = 0;
  id->prev = current_id;
  current_id = id;
  return id;
}

// check if references configured well when end of scope
void checkForwardReference() {
  A_ID *id;
  A_TYPE *t;
  id = current_id;
  while (id) {
    if (id->level < current_level) break;

    t = id->type;
    if (id->kind == ID_NULL) syntax_error(31, id->name);
    if ((id->kind == ID_STRUCT) && (t->field == NIL))
      syntax_error(32, id->name);
    id = id->prev;
  }
}

void syntax_error(int i, char *s) {
  syntax_err++;
  printf("line %d: syntax error: ", line_no);
  switch (i) {
    case 11:
      printf("illegal referencing struct or union identifier %s", s);
      break;
    case 12:
      printf("redeclaration of identifier %s", s);
      break;
    case 13:
      printf("undefined identifier %s", s);
      break;
    case 14:
      printf("illegal type specifier in formal parameter");
      break;
    case 20:
      printf("illegal storage class in type specifiers");
      break;
    case 21:
      printf("illegal function declaration");
      break;
    case 22:
      printf("conflicting parameter type in prototype function %s", s);
      break;
    case 23:
      printf("empty parameter name");
      break;
    case 24:
      printf("illegal declaration specifiers");
      break;
    case 25:
      printf("illegal function specifiers");
      break;
    case 26:
      printf("illegal or conflicting return type in function %s", s);
      break;
    case 31:
      printf("undefined type for identifier %s", s);
      break;
    case 32:
      printf("incomplete forward reference for identifier %s", s);
      break;
    default:
      printf("unknown");
      break;
  }

  if (strlen(yytext) == 0)
    printf(" at end\n");
  else
    printf(" near %s\n", yytext);
}
