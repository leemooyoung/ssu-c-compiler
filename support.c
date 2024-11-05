#include "support.h"

#include <stdlib.h>

#include "type.h"

A_TYPE *int_type, *char_type, *void_type, *float_type, *string_type;
A_ID *current_id = NIL;
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
