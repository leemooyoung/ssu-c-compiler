#include "support.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type.h"

extern char *yytext;

A_TYPE *int_type, *char_type, *void_type, *float_type, *string_type;
A_NODE *root;
A_ID *current_id = NIL;
int syntax_err = 0;
int line_no = 1;
int current_level = 0;

A_NODE *makeNode(NODE_NAME n, A_NODE *a, A_NODE *b, A_NODE *c) {
  A_NODE *m;
  m = (A_NODE *)malloc(sizeof(A_NODE));
  m->name = n;
  m->llink = a;
  m->clink = b;
  m->rlink = c;
  m->type = NIL;
  m->line = line_no;
  m->value = 0;
  return m;
}

// append b to a
A_NODE *makeNodeList(NODE_NAME n, A_NODE *a, A_NODE *b) {
  A_NODE *m, *k;

  k = a;
  while (k->rlink) k = k->rlink;

  m = makeNode(k->name, NIL, NIL, NIL);
  k->name = n;
  k->llink = b;
  k->rlink = m;

  return a;
}

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

A_ID *makeDummyIdentifier(void) {
  A_ID *id;
  id = (A_ID *)malloc(sizeof(A_ID));
  id->name = "";
  id->kind = 0;
  id->specifier = 0;
  id->level = current_level;
  id->address = 0;
  id->init = NIL;
  id->type = NIL;
  id->link = NIL;
  id->line = line_no;
  id->value = 0;
  id->prev = 0;
  return id;
}

A_TYPE *makeType(T_KIND k) {
  A_TYPE *t;

  t = (A_TYPE *)malloc(sizeof(A_TYPE));
  t->kind = k;
  t->size = 0;
  t->local_var_size = 0;
  t->element_type = NIL;
  t->field = NIL;
  t->expr = NIL;
  t->check = FALSE;
  t->prt = FALSE;
  t->line = line_no;

  return t;
}

A_SPECIFIER *makeSpecifier(A_TYPE *t, S_KIND s) {
  A_SPECIFIER *p;
  p = malloc(sizeof(A_SPECIFIER));
  p->type = t;
  p->stor = s;
  p->line = line_no;
  return p;
}

A_ID *searchIdentifier(char *s, A_ID *id) {
  while (id) {
    if (strcmp(id->name, s) == 0) break;
    id = id->prev;
  }

  return id;
}

A_ID *searchIdentifierAtCurrentLevel(char *s, A_ID *id) {
  while (id) {
    if (id->level < current_level) return NIL;
    if (strcmp(id->name, s) == 0) break;
    id = id->prev;
  }
  return id;
}

// merge and update declaration_specifier
// p must not be NULL
A_SPECIFIER *updateSpecifier(A_SPECIFIER *p, A_TYPE *t, S_KIND s) {
  if (t != NULL)
    if (p->type)
      if (p->type == t)
        ;
      else
        syntax_error(24, NULL);
    else
      p->type = t;

  if (s) {
    if (p->stor)
      if (s == p->stor)
        ;
      else
        syntax_error(24, NULL);
    else
      p->stor = s;
  }
}

// check if references configured well when end of scope
void checkForwardReference(void) {
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

void setDefaultSpecifier(A_SPECIFIER *p) {
  A_TYPE *t;
  if (p->type == NIL) p->type = int_type;
  if (p->stor == S_NULL) p->stor = S_AUTO;
}

// concat declarator list id1 and id2
A_ID *linkDeclaratorList(A_ID *id1, A_ID *id2) {
  A_ID *m;

  if (id1 == NIL) return id2;

  m = id1;
  while (m->link) m = m->link;
  m->link = id2;

  return id1;
}

A_ID *getIdentifierDeclared(char *s) {
  A_ID *id;

  id = searchIdentifier(s, current_id);
  if (id == NIL) syntax_error(13, s);

  return id;
}

A_TYPE *getTypeOfStructOrEnumRefIdentifier(T_KIND k, char *s, ID_KIND kk) {
  A_TYPE *t;
  A_ID *id;

  id = searchIdentifier(s, current_id);
  if (id)
    if (id->kind == kk && id->type->kind == k)
      return id->type;
    else
      syntax_error(11, s);

  t = makeType(k);
  id = makeIdentifier(s);
  id->kind = kk;
  id->type = t;

  return t;
}

A_ID *setDeclaratorInit(A_ID *id, A_NODE *n) {
  id->init = n;
  return id;
}

A_ID *setDeclaratorKind(A_ID *id, ID_KIND k) {
  A_ID *a;

  a = searchIdentifierAtCurrentLevel(id->name, id->prev);
  if (a) syntax_error(12, id->name);

  id->kind = k;
  return id;
}

A_ID *setDeclaratorType(A_ID *id, A_TYPE *t) {
  id->type = t;
  return id;
}

// append element type to symbol table (A_ID)
A_ID *setDeclaratorElementType(A_ID *id, A_TYPE *t) {
  A_TYPE *tt;

  if (id->type == NIL)
    id->type = t;
  else {
    tt = id->type;
    while (tt->element_type) tt = tt->element_type;
    tt->element_type = t;
  }

  return id;
}

A_ID *setDeclaratorTypeAndKind(A_ID *, A_TYPE *, ID_KIND);

A_ID *setDeclaratorListSpecifier(A_ID *id, A_SPECIFIER *p) {
  A_ID *a;
  setDefaultSpecifier(p);

  a = id;
  while (a) {
    // check duplicate declaration
    if (strlen(a->name) && searchIdentifierAtCurrentLevel(a->name, a->prev))
      syntax_error(12, a->name);

    // set type of identifier
    a = setDeclaratorElementType(a, p->type);
    if (p->stor == S_TYPEDEF)
      a->kind = ID_TYPE;
    else if (a->type->kind == T_FUNC)
      a->kind = ID_FUNC;
    else
      a->kind = ID_VAR;

    a->specifier = p->stor;
    // p have default value from setDefaultSpecifier
    // if (a->specifier == S_NULL) a->specifier = S_AUTO;

    a = a->link;
  }

  return id;
}

A_ID *setFunctionDeclaratorSpecifier(A_ID *id, A_SPECIFIER *p) {
  A_ID *a;

  // error if storage class specified?
  if (p->stor) syntax_error(25, NULL);

  setDefaultSpecifier(p);

  // check if declarator type is function
  if (id->type->kind != T_FUNC) {
    syntax_error(21, NULL);
    return id;
  } else {
    id = setDeclaratorElementType(id, p->type);
    id->kind = ID_FUNC;
  }

  a = searchIdentifierAtCurrentLevel(id->name, id->prev);
  if (a && (a->kind != ID_FUNC || a->type->expr))
    // there is same name identifier and that is not prototype
    syntax_error(12, id->name);
  else if (a) {
    // if that identifier is prototype, check return type and parameters
    if (isNotSameFormalParameters(a->type->field, id->type->field))
      syntax_error(22, id->name);
    if (isNotSameType(a->type->element_type, id->type->element_type))
      syntax_error(26, a->name);
  }

  a = id->type->field;
  while (a) {
    if (strlen(a->name))
      current_id = a;
    else if (a->type)
      syntax_error(23, NULL);

    a = a->link;
  }

  return id;
}

A_ID *setFunctionDeclaratorBody(A_ID *id, A_NODE *n) {
  id->type->expr = n;
  return id;
}

A_ID *setParameterDeclaratorSpecifier(A_ID *id, A_SPECIFIER *p) {
  // check duplicate declaration
  if (searchIdentifierAtCurrentLevel(id->name, id->prev))
    syntax_error(12, id->name);

  // function parameter can not have storage class and be void type
  if (p->stor || p->type == void_type) syntax_error(14, NULL);

  setDefaultSpecifier(p);
  id = setDeclaratorElementType(id, p->type);
  id->kind = ID_PARAM;

  return id;
}

A_ID *setStructDeclaratorListSpecifier(A_ID *id, A_TYPE *t) {
  A_ID *a;

  a = id;
  while (a) {
    if (searchIdentifierAtCurrentLevel(a->name, a->prev))
      syntax_error(12, a->name);

    a = setDeclaratorElementType(a, t);
    a->kind = ID_FIELD;
    a = a->link;
  }

  return id;
}

A_TYPE *setTypeNameSpecifier(A_TYPE *t, A_SPECIFIER *p) {
  // can't use storage class specifier in cast operation
  if (p->stor) syntax_error(20, NULL);

  setDefaultSpecifier(p);
  t = setTypeElementType(t, p->type);

  return t;
}

// append s to last element type of t
A_TYPE *setTypeElementType(A_TYPE *t, A_TYPE *s) {
  A_TYPE *q;
  if (t == NIL) return s;

  q = t;
  while (q->element_type) q = q->element_type;
  q->element_type = s;

  return t;
}

A_TYPE *setTypeField(A_TYPE *t, A_ID *n) {
  t->field = n;
  return t;
}

A_TYPE *setTypeExpr(A_TYPE *t, A_NODE *n) {
  t->expr = n;
  return t;
}

A_TYPE *setTypeAndKindOfDeclarator(A_TYPE *, ID_KIND, A_ID *);

// Find previously used same identifier and if there isn't, create a symbol
// table for given identifier. The main difference between getTypeOfStruct~ is
// that it uses searchIdentifierAtCurrentLevel, so identifier declared outside
// can be redeclared
A_TYPE *setTypeStructOrEnumIdentifier(T_KIND k, char *s, ID_KIND kk) {
  A_TYPE *t;
  A_ID *id, *a;

  // check duplicate declaration at current level
  a = searchIdentifierAtCurrentLevel(s, current_id);
  if (a)
    if (a->kind == kk && a->type->kind == k)
      if (a->type->field)
        syntax_error(12, s);
      else
        return a->type;  // is free(s) needed?
    else
      // type of identifier declared before and type of current identifier are
      // different
      syntax_error(12, s);

  id = makeIdentifier(s);
  t = makeType(k);
  id->type = t;
  id->kind = kk;

  return t;
}

// return TRUE when parameter type of prototype and definition conflicts
BOOLEAN isNotSameFormalParameters(A_ID *prototype, A_ID *definition) {
  if (prototype == NIL) return FALSE;
  while (prototype) {
    if (definition == NIL || isNotSameType(prototype->type, definition->type))
      return TRUE;
    prototype = prototype->link;
    definition = definition->link;
  }

  if (definition)
    return TRUE;
  else
    return FALSE;
}

// if t1 or t2 are same, return false
BOOLEAN isNotSameType(A_TYPE *t1, A_TYPE *t2) {
  if (isPointerOrArrayType(t1) && isPointerOrArrayType(t2))
    return t1->expr != t2->expr
           || isNotSameType(t1->element_type, t2->element_type);
  else
    return t1 != t2;
}

BOOLEAN isPointerOrArrayType(A_TYPE *t) {
  if (t && (t->kind == T_POINTER || t->kind == T_ARRAY))
    return TRUE;
  else
    return FALSE;
}

void initialize(void);  // {
//   // set primitive data types
//   int_type = setTypeAndKindOfDeclarator();
// }

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
