#include "semantic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "support.h"
#include "type.h"

#define LIT_MAX 100
#define ROUNDUP(a) ((a) / 4 * 4 + 4)

A_LITERAL literal_table[LIT_MAX];
int literal_no = 0;
int literal_size = 0;
int global_address = 12;
int semantic_err = 0;

void semantic_analysis(A_NODE *node) {
  sem_program(node);
  set_literal_address(node);
}

void set_literal_address(A_NODE *node) {
  int i;
  for (i = 1; i <= literal_no; i++) literal_table[i].addr += node->value;

  node->value += literal_size;
}

int put_literal(A_LITERAL lit, int ll) {
  float ff;
  if (literal_no >= LIT_MAX)
    semantic_error(93, ll, NIL);
  else
    literal_no++;

  literal_table[literal_no] = lit;
  literal_table[literal_no].addr = literal_size;

  if (lit.type->kind == T_ENUM)
    literal_size += 4;
  else if (isStringType(lit.type))
    literal_size += strlen(lit.value.s) + 1;

  if (literal_size % 4) literal_size = ROUNDUP(literal_size);

  return literal_no;
}

void sem_program(A_NODE *node) {
  switch (node->name) {
    case N_PROGRAM:
      sem_declaration_list((A_ID *)node->clink, 12);
      node->value = global_address;
      break;
    default:
      semantic_error(90, node->line, NIL);
      break;
  }
}

int sem_declaration_list(A_ID *id, int addr) {
  int i = addr;
  while (id) {
    addr += sem_declaration(id, addr);
    id = id->link;
  }

  return addr - i;
}

int sem_declaration(A_ID *id, int addr) {
  A_TYPE *t;
  int size = 0, i;
  A_LITERAL lit;
  switch (id->kind) {
    case ID_VAR:
      i = sem_A_TYPE(id->type);
      // check empty array
      if (isArrayType(id->type) && id->type->expr == NIL)
        semantic_error(86, id->line, NIL);
      if (i % 4) ROUNDUP(i);
      if (id->specifier == S_STATIC) id->level = 0;
      if (id->level == 0) {
        id->address = global_address;
        global_address += i;
      } else {
        id->address = addr;
        size = i;
      }
      break;
    case ID_FIELD:
      i = sem_A_TYPE(id->type);
      if (isFunctionType(id->type) || isVoidType(id->type))
        semantic_error(84, id->line, NIL);

      if (1 % 4) i = ROUNDUP(i);
      id->address = addr;
      size = i;
      break;
    case ID_FUNC:
      i = sem_A_TYPE(id->type);
      break;
    case ID_PARAM:
      if (id->type) {
        size = sem_A_TYPE(id->type);
        // usual unary conversion of parm type
        if (id->type == char_type)
          id->type = int_type;
        else if (isArrayType(id->type)) {
          id->type->kind = T_POINTER;
          id->type->size = 4;
        } else if (isFunctionType(id->type)) {
          t = makeType(T_POINTER);
          t->element_type = id->type;
          t->size = 4;
          id->type = t;
        }
        size = id->type->size;
        if (size % 4) size = ROUNDUP(size);
        id->address = addr;
      }
      break;
    case ID_TYPE:
      i = sem_A_TYPE(id->type);
      break;
    default:
      semantic_error(89, id->line, id->name);
      break;
  }

  return size;
}

int sem_A_TYPE(A_TYPE *t) {
  A_ID *id;
  A_TYPE *tt;
  A_LITERAL lit;
  int result = 0, i;

  if (t->check) return (t->size);
  t->check = 1;

  switch (t->kind) {
    case T_NULL:
      semantic_error(80, t->line, NIL);
      break;
    case T_ENUM:
      i = 0;
      id = t->field;
      while (id) {  // enumerators
        if (id->init) {
          lit = getTypeAndValueOfExpression(id->init);
          if (!isIntType(lit.type)) semantic_error(81, id->line, NIL);

          i = lit.value.i;
        }
        id->init = i++;
        id = id->link;
      }
      result = 4;
      break;
    case T_ARRAY:
      if (t->expr) {
        lit = getTypeAndValueOfExpression(t->expr);
        if (!isIntType(lit.type) || lit.value.i <= 0) {
          semantic_error(82, t->line, NIL);
          t->expr = 0;
        } else
          t->expr = lit.value.i;
      }
      i = sem_A_TYPE(t->element_type) * (int)t->expr;
      if (isVoidType(t->element_type) || isFunctionType(t->element_type))
        semantic_error(83, t->line, NIL);
      else
        result = i;
      break;
    case T_STRUCT:
      id = t->field;
      while (id) {
        result += sem_declaration(id, result);
        if (id->type == t) semantic_error(84, id->line, NIL);
        id = id->link;
      }
      break;
    case T_UNION:
      id = t->field;
      while (id) {
        i = sem_declaration(id, 0);
        if (i > result) result = i;
        if (id->type == t) semantic_error(84, id->line, NIL);
        id = id->link;
      }
      break;
    case T_FUNC:
      tt = t->element_type;
      i = sem_A_TYPE(tt);
      if (isArrayType(tt) || isFunctionType(tt))  // check return type
        semantic_error(85, t->line, NIL);
      i = sem_declaration_list(t->field, 12) + 12;  // parameter type and size
      if (t->expr) {  // skip prototype declaration
        i = i + sem_statement(t->expr, i, t->element_type, FALSE, FALSE, FALSE);
      }
      t->local_var_size = i;
      break;
    case T_POINTER:
      i = sem_A_TYPE(t->element_type);
      result = 4;
      break;
    case T_VOID:
      break;
    default:
      semantic_error(90, t->line, NIL);
      break;
  }
  t->size = result;
  return result;
}

int sem_statement(
  A_NODE *node, int addr, A_TYPE *ret, BOOLEAN sw, BOOLEAN brk, BOOLEAN cnt
) {
  int local_size = 0, i;
  A_LITERAL lit;
  A_TYPE *t;
  switch (node->name) {
    case N_STMT_LABEL_CASE:
      if (sw == FALSE) semantic_error(71, node->line, NIL);
      lit = getTypeAndValueOfExpression(node->llink);
      if (isIntegralType(lit.type))
        node->llink = lit.value.i;
      else
        semantic_error(51, node->line, NIL);
      local_size = sem_statement(node->rlink, addr, ret, sw, brk, cnt);
      break;
    case N_STMT_LABEL_DEFAULT:
      if (sw == FALSE) semantic_error(72, node->line, NIL);
      local_size = sem_statement(node->clink, addr, ret, sw, brk, cnt);
      break;
    case N_STMT_COMPOUND:
      if (node->llink)
        local_size = sem_declaration_list((A_ID *)node->llink, addr);
      local_size += sem_statement_list(
        node->rlink, local_size + addr, ret, sw, brk, cnt
      );
      break;
    case N_STMT_EMPTY:
      break;
    case N_STMT_EXPRESSION:
      t = sem_expression(node->clink);
      break;
    case N_STMT_IF:
      t = sem_expression(node->llink);
      if (isScalarType(t))
        node->llink = convertScalarToInteger(node->llink);
      else
        semantic_error(50, node->line, NIL);
      local_size = sem_statement(node->rlink, addr, ret, FALSE, brk, cnt);
      break;
    case N_STMT_IF_ELSE:
      t = sem_expression(node->llink);
      if (isScalarType(t))
        node->llink = convertScalarToInteger(node->llink);
      else
        semantic_error(50, node->line, NIL);
      local_size = sem_statement(node->clink, addr, ret, FALSE, brk, cnt);
      i = sem_statement(node->rlink, addr, ret, FALSE, brk, cnt);
      if (local_size < i) local_size = i;
      break;
    case N_STMT_SWITCH:
      t = sem_expression(node->llink);
      if (!isIntegralType(t)) semantic_error(50, node->line, NIL);
      local_size = sem_statement(node->rlink, addr, ret, TRUE, TRUE, cnt);
      break;
    case N_STMT_WHILE:
      t = sem_expression(node->llink);
      if (isScalarType(t))
        node->llink = convertScalarToInteger(node->llink);
      else
        semantic_error(50, node->line, NIL);
      local_size = sem_statement(node->rlink, addr, ret, FALSE, TRUE, TRUE);
      break;
    case N_STMT_DO:
      local_size = sem_statement(node->llink, addr, ret, FALSE, TRUE, TRUE);
      t = sem_expression(node->rlink);
      if (isScalarType(t))
        node->rlink = convertScalarToInteger(node->rlink);
      else
        semantic_error(50, node->line, NIL);
      break;
    case N_STMT_FOR:
      sem_for_expression(node->llink);
      local_size = sem_statement(node->rlink, addr, ret, FALSE, TRUE, TRUE);
      break;
    case N_STMT_CONTINUE:
      if (cnt == FALSE) semantic_error(74, node->line, NIL);
      break;
    case N_STMT_BREAK:
      if (brk == FALSE) semantic_error(73, node->line, NIL);
      break;
    case N_STMT_RETURN:
      if (node->clink) {
        t = sem_expression(node->clink);
        if (isAllowableCastingConversion(ret, t))
          node->clink = convertCastingConversion(node->clink, ret);
        else
          semantic_error(57, node->line, NIL);
      }
      break;
    default:
      semantic_error(90, node->line, NIL);
      break;
  }
  node->value = local_size;
  return (local_size);
}

void sem_for_expression(A_NODE *node) {
  A_TYPE *t;
  switch (node->name) {
    case N_FOR_EXP:
      if (node->llink) t = sem_expression(node->llink);
      if (node->clink) {
        t = sem_expression(node->clink);
        if (isScalarType(t))
          node->clink = convertScalarToInteger(node->clink);
        else
          semantic_error(49, node->line, NIL);
      }
      if (node->rlink) t = sem_expression(node->rlink);
      break;
    default:
      semantic_error(90, node->line, NIL);
      break;
  }
}

int sem_statement_list(
  A_NODE *node, int addr, A_TYPE *ret, BOOLEAN sw, BOOLEAN brk, BOOLEAN cnt
) {
  int size, i;
  switch (node->name) {
    case N_STMT_LIST:
      size = sem_statement(node->llink, addr, ret, sw, brk, cnt);
      i = sem_statement_list(node->rlink, addr, ret, sw, brk, cnt);
      if (size < i) size = i;
      break;
    case N_STMT_LIST_NIL:
      size = 0;
      break;
    default:
      semantic_error(90, node->line, NIL);
      break;
  }
  node->value = size;
  return size;
}

A_TYPE *sem_expression(A_NODE *node) {
  A_TYPE *result = NIL, *t, *t1, *t2;
  A_ID *id;
  A_LITERAL lit;
  int i;
  BOOLEAN lvalue = FALSE;

  switch (node->name) {
    case N_EXP_IDENT:
      id = (A_ID *)node->clink;
      switch (id->kind) {
        case ID_VAR:
        case ID_PARAM:
          result = id->type;
          if (!isArrayType(result)) lvalue = TRUE;
          break;
        case ID_FUNC:
          result = id->type;
          break;
        case ID_ENUM_LITERAL:
          result = int_type;
          break;
        default:
          semantic_error(38, node->line, id->name);
          break;
      }
      break;
    case N_EXP_INT_CONST:
      result = int_type;
      break;
    case N_EXP_FLOAT_CONST:
      lit.type = float_type;
      lit.value.f = atof((char *)node->clink);
      node->clink = put_literal(lit, node->line);
      result = float_type;
      break;
    case N_EXP_CHAR_CONST:
      result = char_type;
      break;
    case N_EXP_STRING_LITERAL:
      lit.type = string_type;
      lit.value.s = (char *)node->clink;
      node->clink = put_literal(lit, node->line);
      result = string_type;
      break;
    case N_EXP_ARRAY:
      t1 = sem_expression(node->llink);
      t2 = sem_expression(node->rlink);
      t = convertUsualBinaryConversion(node);
      t1 = node->llink->type;
      t2 = node->rlink->type;

      if (isPointerOrArrayType(t1))
        result = t1->element_type;
      else
        semantic_error(32, node->line, NIL);

      if (!isIntegralType(t2)) semantic_error(29, node->line, NIL);

      if (!isArrayType(result)) lvalue = TRUE;

      break;
    case N_EXP_STRUCT:
      t = sem_expression(node->llink);
      id = getStructFieldIdentifier(t, (char *)node->rlink);
      if (id) {
        result = id->type;
        if (node->llink->value && !isArrayType(result)) lvalue = TRUE;
      } else
        semantic_error(37, node->line, NIL);

      node->rlink = (A_NODE *)id;
      break;
    case N_EXP_ARROW:
      t = sem_expression(node->llink);
      id = getPointerFieldIdentifier(t, (char *)node->rlink);
      if (id) {
        result = id->type;
        if (!isArrayType(result)) lvalue = TRUE;
      } else
        semantic_error(37, node->line, NIL);

      node->rlink = (A_NODE *)id;
      break;
    case N_EXP_FUNCTION_CALL:
      t = sem_expression(node->llink);
      node->llink = convertUsualUnaryConversion(node->llink);
      t = node->llink->type;

      if (isPointerType(t) && isFunctionType(t->element_type)) {
        sem_arg_expr_list(node->rlink, t->element_type->field);
        result = t->element_type->element_type;
      } else
        semantic_error(21, node->line, NIL);
      break;
    case N_EXP_POST_INC:
    case N_EXP_POST_DEC:
      result = sem_expression(node->clink);
      if (!isScalarType(result)) semantic_error(27, node->line, NIL);
      if (!isModifiableLvalue(node->clink)) semantic_error(60, node->line, NIL);
      break;
    case N_EXP_CAST:
      result = (A_TYPE *)node->llink;
      i = sem_A_TYPE(result);
      t = sem_expression(node->rlink);
      if (!isAllowableCastingConversion(result, t))
        semantic_error(58, node->line, NIL);
      break;
    case N_EXP_SIZE_TYPE:
      t = (A_TYPE *)node->clink;
      i = sem_A_TYPE(t);
      if (isArrayType(t) && t->size == 0 || isFunctionType(t) || isVoidType(t))
        semantic_error(39, node->line, NIL);
      else
        node->clink = i;
      result = int_type;
      break;
    case N_EXP_SIZE_EXP:
      t = sem_expression(node->clink);
      if ((node->clink->name != N_EXP_IDENT
           || ((A_ID *)node->clink->clink)->kind != ID_PARAM)
          && (isArrayType(t) && t->size == 0 || isFunctionType(t)))
        semantic_error(39, node->line, NIL);
      else
        node->clink = t->size;
      result = int_type;
      break;
    case N_EXP_PLUS:
    case N_EXP_MINUS:
      t = sem_expression(node->clink);
      if (isArithmeticType(t)) {
        node->clink = convertUsualUnaryConversion(node->clink);
        result = node->clink->type;
      } else
        semantic_error(13, node->line, NIL);
      break;
    case N_EXP_NOT:
      t = sem_expression(node->clink);
      if (isScalarType(t)) {
        node->clink = convertUsualUnaryConversion(node->clink);
        result = int_type;
      } else
        semantic_error(27, node->line, NIL);
      break;
    case N_EXP_AMP:
      t = sem_expression(node->clink);
      if (node->clink->value == TRUE || isFunctionType(t)) {
        result = setTypeElementType(makeType(T_POINTER), t);
        result->size = 4;
      } else
        semantic_error(60, node->line, NIL);
      break;
    case N_EXP_STAR:
      t = sem_expression(node->clink);
      node->clink = convertUsualUnaryConversion(node->clink);
      if (isPointerType(t)) {
        result = t->element_type;
        // \alue if points to an object
        if (isStructOrUnionType(result) || isScalarType(result)) lvalue = TRUE;
      } else
        semantic_error(31, node->line, NIL);
      break;
    case N_EXP_PRE_INC:
    case N_EXP_PRE_DEC:
      result = sem_expression(node->clink);
      // usual binary conversion between the expression and 1
      if (!isScalarType(result)) semantic_error(27, node->line, NIL);
      // check if modifiable Ivalue
      if (!isModifiableLvalue(node->clink)) semantic_error(60, node->line, NIL);
      break;
    case N_EXP_MUL:
    case N_EXP_DIV:
      t1 = sem_expression(node->llink);
      t2 = sem_expression(node->rlink);
      if (isArithmeticType(t1) && isArithmeticType(t2))
        result = convertUsualBinaryConversion(node);
      else
        semantic_error(28, node->line, NIL);
      break;
    case N_EXP_MOD:
      t1 = sem_expression(node->llink);
      t2 = sem_expression(node->rlink);
      if (isIntegralType(t1) && isIntegralType(t2))
        result = convertUsualBinaryConversion(node);
      else
        semantic_error(29, node->line, NIL);
      result = int_type;
      break;
    case N_EXP_ADD:
      t1 = sem_expression(node->llink);
      t2 = sem_expression(node->rlink);
      if (isArithmeticType(t1) && isArithmeticType(t2))
        result = convertUsualBinaryConversion(node);
      else if (isPointerType(t1) && isIntegralType(t2))

        result = t1;
      else if (isIntegralType(t1) && isPointerType(t2))
        result = t2;
      else
        semantic_error(24, node->line, NIL);
      break;

    case N_EXP_SUB:
      t1 = sem_expression(node->llink);
      t2 = sem_expression(node->rlink);
      if (isArithmeticType(t1) && isArithmeticType(t2))
        result = convertUsualBinaryConversion(node);
      else if (isPointerType(t1) && isIntegralType(t2))

        result = t1;
      else if (isCompatiblePointerType(t1, t2))
        result = t1;
      else
        semantic_error(24, node->line, NIL);
      break;

    case N_EXP_LSS:
    case N_EXP_GTR:
    case N_EXP_LEQ:
    case N_EXP_GEQ:
      t1 = sem_expression(node->llink);
      t2 = sem_expression(node->rlink);
      if (isArithmeticType(t1) && isArithmeticType(t2))
        t = convertUsualBinaryConversion(node);
      else if (!isCompatiblePointerType(t1, t2))
        semantic_error(40, node->line, NIL);
      result = int_type;
      break;
    case N_EXP_NEQ:
    case N_EXP_EQL:
      t1 = sem_expression(node->llink);
      t2 = sem_expression(node->rlink);
      if (isArithmeticType(t1) && isArithmeticType(t2))
        t = convertUsualBinaryConversion(node);
      else if (!isCompatiblePointerType(t1, t2)
               && (!isPointerType(t1) || !isConstantZeroExp(node->rlink))
               && (!isPointerType(t2) || !isConstantZeroExp(node->llink)))
        semantic_error(40, node->line, NIL);
      result = int_type;
      break;
    case N_EXP_AND:
    case N_EXP_OR:
      t = sem_expression(node->llink);
      if (isScalarType(t))
        node->llink = convertUsualUnaryConversion(node->llink);
      else
        semantic_error(27, node->line, NIL);
      t = sem_expression(node->rlink);
      if (isScalarType(t))
        node->rlink = convertUsualUnaryConversion(node->rlink);
      else
        semantic_error(27, node->line, NIL);
      result = int_type;
      break;
    case N_EXP_ASSIGN:
      result = sem_expression(node->llink);
      // check if modifiable Ivalue
      if (!isModifiableLvalue(node->llink)) semantic_error(60, node->line, NIL);
      t = sem_expression(node->rlink);
      if (isAllowableAssignmentConversion(result, t, node->rlink)) {
        if (isPointerType(result) && isPointerType(t)
            && !isCompatiblePointerType(result, t))
          semantic_warning(11, node->line);
        if (isArithmeticType(result) && isArithmeticType(t))
          node->rlink = convertUsualAssignmentConversion(result, node->rlink);
      } else
        semantic_error(58, node->line, NIL);
      break;
    default:
      semantic_error(90, node->line, NIL);
      break;
  }
  node->type = result;
  node->value = lvalue;
  return result;
}

void sem_arg_expr_list(A_NODE *node, A_ID *id) {
  A_TYPE *t;
  A_ID *a;
  int arg_size = 0;
  switch (node->name) {
    case N_ARG_LIST:
      if (id == 0)
        semantic_error(34, node->line, NIL);
      else {
        if (id->type) {
          t = sem_expression(node->llink);
          node->llink = convertUsualUnaryConversion(node->llink);
          if (isAllowableCastingConversion(id->type, node->llink->type))
            node->llink = convertCastingConversion(node->llink, id->type);
          else
            semantic_error(59, node->line, NIL);
          sem_arg_expr_list(node->rlink, id->link);
        } else {  // DOTDOT parameter : no conversion
          t = sem_expression(node->llink);
          sem_arg_expr_list(node->rlink, id);
        }
        arg_size = node->llink->type->size + node->rlink->value;
      }
      break;
    case N_ARG_LIST_NIL:
      if (id && id->type)  // check if’... argument
        semantic_error(35, node->line, NIL);

      break;
    default:
      semantic_error(90, node->line, NIL);
      break;
  }
  if (arg_size % 4) arg_size = ROUNDUP(arg_size);
  node->value = arg_size;
}

BOOLEAN isModifiableLvalue(A_NODE *node) {
  if (node->value == FALSE || isVoidType(node->type)
      || isFunctionType(node->type))
    return FALSE;
  else
    return TRUE;
}

A_ID *getStructFieldIdentifier(A_TYPE *t, char *s) {
  A_ID *id = NIL;
  if (isStructOrUnionType(t)) {
    id = t->field;
    while (id) {
      if (strcmp(id->name, s) == 0) break;
      id = id->link;
    }
  }
  return id;
}

A_ID *getPointerFieldIdentifier(A_TYPE *t, char *s) {
  A_ID *id = NIL;
  if (t && t->kind == T_POINTER) {
    t = t->element_type;

    if (isStructOrUnionType(t)) {
      id = t->field;
      while (id) {
        if (strcmp(id->name, s) == 0) break;
        id = id->link;
      }
    }
  }
  return id;
}

BOOLEAN isSameParameterType(A_ID *a, A_ID *b) {
  while (a) {
    if (b == NIL || isNotSameType(a->type, b->type)) return FALSE;

    a = a->link;
    b = b->link;
  }
  if (b)
    return FALSE;
  else
    return TRUE;
}

BOOLEAN isCompatibleType(A_TYPE *t1, A_TYPE *t2) {
  if (isArrayType(t1) && isArrayType(t2))
    if (t1->size == 0 || t2->size || t1->size == t2->size)
      return isCompatibleType(t1->element_type, t2->element_type);
    else
      return FALSE;
  else if (isFunctionType(t1) && isFunctionType(t2))
    if (isSameParameterType(t1->field, t2->field))
      return isCompatibleType(t1->element_type, t2->element_type);
    else
      return FALSE;
  else if (isPointerType(t1) && isPointerType(t2))
    return isCompatibleType(t1->element_type, t2->element_type);
  else
    return t1 == t2;
}

BOOLEAN isConstantZeroExp(A_NODE *node) {
  if (node->name == N_EXP_INT_CONST && node->clink == 0)
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isCompatiblePointerType(A_TYPE *t1, A_TYPE *t2) {
  if (isPointerType(t1) && isPointerType(t2))
    return isCompatibleType(t1->element_type, t2->element_type);
  else
    return FALSE;
}

A_NODE *convertScalarToInteger(A_NODE *node) {
  if (isFloatType(node->type)) {
    semantic_warning(16, node->line);
    node = makeNode(N_EXP_CAST, (A_NODE *)int_type, NIL, node);
  }
  node->type = int_type;
  return node;
}

A_NODE *convertUsualAssignmentConversion(A_TYPE *t1, A_NODE *node) {
  A_TYPE *t2;
  t2 = node->type;
  if (!isCompatibleType(t1, t2)) {
    semantic_warning(11, node->line);
    node = makeNode(N_EXP_CAST, (A_NODE *)t1, NIL, node);
    node->type = t1;
  }
  return node;
}

A_NODE *convertUsualUnaryConversion(A_NODE *node) {
  A_TYPE *t;
  t = node->type;
  if (t == char_type) {
    t = int_type;
    node = makeNode(N_EXP_CAST, (A_NODE *)t, NIL, node);
    node->type = t;
  } else if (isArrayType(t)) {
    t = setTypeElementType(makeType(T_POINTER), t->element_type);
    t->size = 4;
    node = makeNode(N_EXP_CAST, (A_NODE *)t, NIL, node);
    node->type = t;
  } else if (isFunctionType(t)) {
    t = setTypeElementType(makeType(T_POINTER), t);
    t->size = 4;
    node = makeNode(N_EXP_AMP, NIL, node, NIL);
    node->type = t;
  }
  return node;
}

A_TYPE *convertUsualBinaryConversion(A_NODE *node) {
  A_TYPE *t1, *t2, *result = NIL;
  t1 = node->llink->type;
  t2 = node->rlink->type;
  if (isFloatType(t1) && !isFloatType(t2)) {
    semantic_warning(14, node->line);
    node->rlink = makeNode(N_EXP_CAST, (A_NODE *)t1, NIL, node->rlink);
    node->rlink->type = t1;
    result = t1;
  } else if (!isFloatType(t1) && isFloatType(t2)) {
    semantic_warning(14, node->line);
    node->llink = makeNode(N_EXP_CAST, (A_NODE *)t2, NIL, node->llink);
    node->llink->type = t2;
    result = t2;
  } else if (t1 == t2)
    result = t1;
  else
    result = int_type;
  return result;
}

A_NODE *convertCastingConversion(A_NODE *node, A_TYPE *t1) {
  A_TYPE *t2;
  t2 = node->type;
  if (!isCompatibleType(t1, t2)) {
    semantic_warning(12, node->line);
    node = makeNode(N_EXP_CAST, (A_NODE *)t1, NIL, node);
    node->type = t1;
  }
  return node;
}

BOOLEAN isAllowableAssignmentConversion(
  A_TYPE *t1, A_TYPE *t2, A_NODE *node
) {  // t1 <--- t2

  if (isArithmeticType(t1) && isArithmeticType(t2))
    return TRUE;
  else if (isStructOrUnionType(t1) && isCompatibleType(t1, t2))
    return TRUE;
  else if (isPointerType(t1) && (isConstantZeroExp(node) || isPointerType(t2)))
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isAllowableCastingConversion(A_TYPE *t1, A_TYPE *t2) {  // t1 <--- t2
  if (isAnyIntegerType(t1) && (isScalarType(t2)))
    return TRUE;
  else if (isIntegralType(t1) && isArithmeticType(t2))
    return TRUE;
  else if (isFloatType(t1) && isArithmeticType(t2))
    return TRUE;
  else if (isPointerType(t1) && (isAnyIntegerType(t2) || isPointerType(t2)))
    return TRUE;
  else if (isVoidType(t1))
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isFloatType(A_TYPE *t) {
  if (t == float_type)
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isArithmeticType(A_TYPE *t) {
  if (t && t->kind == T_ENUM)
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isScalarType(A_TYPE *t) {
  if (t && ((t->kind == T_ENUM) || (t->kind == T_POINTER)))
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isAnyIntegerType(A_TYPE *t) {
  if (t && (t == int_type || t == char_type))
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isIntegralType(A_TYPE *t) {
  if (t && t->kind == T_ENUM && t != float_type)
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isFunctionType(A_TYPE *t) {
  if (t && t->kind == T_FUNC)
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isStructOrUnionType(A_TYPE *t) {
  if (t && (t->kind == T_STRUCT || t->kind == T_UNION))
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isPointerType(A_TYPE *t) {
  if (t && t->kind == T_POINTER)
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isIntType(A_TYPE *t) {
  if (t && t == int_type)
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isVoidType(A_TYPE *t) {
  if (t && t == void_type)
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isArrayType(A_TYPE *t) {
  if (t && t->kind == T_ARRAY)
    return TRUE;
  else
    return FALSE;
}

BOOLEAN isStringType(A_TYPE *t) {
  if (t && (t->kind == T_POINTER || t->kind == T_ARRAY)
      && t->element_type == char_type)
    return TRUE;
  else
    return FALSE;
}

// convert literal type
A_LITERAL checkTypeAndConvertLiteral(A_LITERAL result, A_TYPE *t, int ll) {
  if (result.type == int_type && t == int_type
      || result.type == char_type && t == char_type
      || result.type == float_type && t == float_type)
    ;
  else if (result.type == int_type && t == float_type) {
    result.type = float_type;
    result.value.f = result.value.i;
  } else if (result.type == int_type && t == char_type) {
    result.type = char_type;
    result.value.c = result.value.i;
  } else if (result.type == float_type && t == int_type) {
    result.type = int_type;
    result.value.i = result.value.f;
  } else if (result.type == char_type && t == int_type) {
    result.type = int_type;
    result.value.i = result.value.c;
  } else
    semantic_error(41, ll, NIL);

  return result;
}

A_LITERAL getTypeAndValueOfExpression(A_NODE *node) {
  A_TYPE *t;
  A_ID *id;
  A_LITERAL result, r;

  result.type = NIL;
  switch (node->name) {
    case N_EXP_IDENT:
      id = (A_ID *)node->clink;
      if (id->kind != ID_ENUM_LITERAL)
        semantic_error(19, node->line, id->name);
      else {
        result.type = int_type;
        result.value.i = id->init;
      }
      break;
    case N_EXP_INT_CONST:
      result.type = int_type;
      result.value.i = (int)node->clink;
      break;
    case N_EXP_CHAR_CONST:
      result.type = char_type;
      result.value.c = (char)node->clink;
      break;
    case N_EXP_FLOAT_CONST:
      result.type = float_type;
      result.value.f = atof((char *)node->clink);
      break;
    case N_EXP_STRING_LITERAL:
    case N_EXP_ARRAY:
    case N_EXP_FUNCTION_CALL:
    case N_EXP_STRUCT:
    case N_EXP_ARROW:
    case N_EXP_POST_INC:
    case N_EXP_PRE_INC:
    case N_EXP_POST_DEC:
    case N_EXP_PRE_DEC:
    case N_EXP_AMP:
    case N_EXP_STAR:
    case N_EXP_NOT:
      semantic_error(18, node->line, NIL);
      break;
    case N_EXP_MINUS:
      result = getTypeAndValueOfExpression(node->clink);
      if (result.type == int_type)
        result.value.i = -result.value.i;
      else if (result.type == float_type)
        result.value.f = -result.value.f;
      else
        semantic_error(18, node->line, NIL);
      break;
    case N_EXP_SIZE_EXP:
      t = sem_expression(node->clink);
      result.type = int_type;
      result.value.i = t->size;
      break;
    case N_EXP_SIZE_TYPE:
      result.type = int_type;
      result.value.i = sem_A_TYPE((A_TYPE *)node->clink);
      break;
    case N_EXP_CAST:
      result = getTypeAndValueOfExpression(node->rlink);
      result
        = checkTypeAndConvertLiteral(result, (A_TYPE *)node->llink, node->line);
      break;
    case N_EXP_MUL:
      result = getTypeAndValueOfExpression(node->llink);
      r = getTypeAndValueOfExpression(node->rlink);

      if (result.type == int_type && r.type == int_type) {
        result.type = int_type;
        result.value.i = result.value.i * r.value.i;
      } else if (result.type == int_type && r.type == float_type) {
        result.type = float_type;
        result.value.f = result.value.i * r.value.f;
      } else if (result.type == float_type && r.type == int_type) {
        result.type = float_type;
        result.value.f = result.value.f * r.value.i;
      } else if (result.type == float_type && r.type == float_type) {
        result.type = float_type;
        result.value.f = result.value.f * r.value.f;
      } else
        semantic_error(18, node->line, NIL);

      break;
    case N_EXP_DIV:
      result = getTypeAndValueOfExpression(node->llink);
      r = getTypeAndValueOfExpression(node->rlink);

      if (result.type == int_type && r.type == int_type) {
        result.type = int_type;
        result.value.i = result.value.i / r.value.i;
      } else if (result.type == int_type && r.type == float_type) {
        result.type = float_type;
        result.value.f = result.value.i / r.value.f;
      } else if (result.type == float_type && r.type == int_type) {
        result.type = float_type;
        result.value.f = result.value.f / r.value.i;
      } else if (result.type == float_type && r.type == float_type) {
        result.type = float_type;
        result.value.f = result.value.f / r.value.f;
      } else
        semantic_error(18, node->line, NIL);
      break;
    case N_EXP_MOD:
      result = getTypeAndValueOfExpression(node->llink);
      r = getTypeAndValueOfExpression(node->rlink);
      if (result.type == int_type && r.type == int_type)
        result.value.i = result.value.i % r.value.i;
      else
        semantic_error(18, node->line, NIL);
      break;
    case N_EXP_ADD:
      result = getTypeAndValueOfExpression(node->llink),
      r = getTypeAndValueOfExpression(node->rlink);

      if (result.type == int_type && r.type == int_type) {
        result.type = int_type;
        result.value.i = result.value.i + r.value.i;
      } else if (result.type == int_type && r.type == float_type) {
        result.type = float_type;
        result.value.f = result.value.i + r.value.f;
      } else if (result.type == float_type && r.type == int_type) {
        result.type = float_type;
        result.value.f = result.value.f + r.value.i;
      } else if (result.type == float_type && r.type == float_type) {
        result.type = float_type;
        result.value.f = result.value.f + r.value.f;
      } else
        semantic_error(18, node->line, NIL);

      break;
    case N_EXP_SUB:
      result = getTypeAndValueOfExpression(node->llink);
      r = getTypeAndValueOfExpression(node->rlink);
      if (result.type == int_type && r.type == int_type) {
        result.type = int_type;
        result.value.i = result.value.i - r.value.i;
      } else if (result.type == int_type && r.type == float_type) {
        result.type = float_type;
        result.value.f = result.value.i - r.value.f;
      } else if (result.type == float_type && r.type == int_type) {
        result.type = float_type;
        result.value.f = result.value.f - r.value.i;
      } else if (result.type == float_type && r.type == float_type) {
        result.type = float_type;
        result.value.f = result.value.f - r.value.f;
      } else
        semantic_error(18, node->line, NIL);

      break;
    case N_EXP_LSS:
    case N_EXP_GTR:
    case N_EXP_LEQ:
    case N_EXP_GEQ:
    case N_EXP_NEQ:
    case N_EXP_EQL:
    case N_EXP_AND:
    case N_EXP_OR:
    case N_EXP_ASSIGN:
      semantic_error(18, node->line, NIL);
      break;

    default:
      semantic_error(90, node->line, NIL);
      break;
  }
  return result;
}

void semantic_error(int i, int ll, char *s) {
  semantic_err++;
  printf("*** semantic error at line %d: ", ll);
  switch (i) {
    // errors in expression
    case 13:
      printf("arith type expr required in unary operation\n");
      break;
    case 18:
      printf("illegal constant expression \n");
      break;
    case 19:
      printf("illegal identifier %s in constant expression\n", s);
      break;
    case 21:
      printf("illegal type in function call expression\n");
      break;
    case 24:
      printf("incompatible type in additive expression\n");
      break;
    case 27:
      printf("scalar type expr required in expression\n");
      break;
    case 28:
      printf("arith type expression required in binary operation\n");
      break;
    case 29:
      printf("integral type expression required in expression\n");
      break;
    case 31:
      printf("pointer type expr required in pointer operation\n");
      break;
    case 32:
      printf("array type required in array expression\n");
      break;
    case 34:
      printf("too many arguments in function call\n");
      break;
    case 35:
      printf("too few arguments in function call\n");
      break;
    case 37:
      printf("illegal struct field identifier in struct reference expr\n");
      break;
    case 38:
      printf("illegal kind of identifier %s in expression\n", s);
      break;
    case 39:
      printf("illegal type size in sizeof operation\n");
      break;
    case 40:
      printf("illegal expression type in relational operation\n");
      break;
    case 41:
      printf("incompatible type in literal\n");
      break;

    //  erros in statement
    case 49:
      printf("scalar type expr required in middle of for-expr\n");
      break;
    case 50:
      printf("integral type expression required in statement\n");
      break;
    case 51:
      printf("illegal expression type in case label\n");
      break;
    case 57:
      printf("not permitted type conversion in return expression\n");
      break;
    case 58:
      printf("not permitted type casting in expression\n");
      break;
    case 59:
      printf("not permitted type conversion in argument\n");
      break;
    case 60:
      printf("expression is not an lvalue \n");
      break;
    case 71:
      printf("case label not within a switch statement \n");
      break;
    case 72:
      printf("default label not within a switch statement \n");
      break;
    case 73:
      printf("break statement not within loop or switch stmt\n");
      break;
    case 74:
      printf("continue statement not within a loop \n");
      break;

    // errors in type & declarator
    case 80:
      printf("undefined type\n");
      break;
    case 81:
      printf("integer type expression required in enumerator\n");
      break;
    case 82:
      printf("illegal array size or type\n");
      break;
    case 83:
      printf("illegal element type of array declarator\n");
      break;
    case 84:
      printf("illegal type in struct or union field\n");
      break;
    case 85:
      printf("invalid function return type\n");
      break;
    case 86:
      printf("illegal array size or empty array \n");
      break;
    case 89:
      printf("unknown identifier kind: %s\n", s);
      break;

    // misc errors
    case 90:
      printf("fatal compiler error in parse result\n");
      break;
    case 93:
      printf("too many literals in source program \n");
      break;
    default:
      printf("unknown \n");
      break;
  }
}

void semantic_warning(int i, int ll) {
  printf("--- warning at line %d:", ll);

  switch (i) {
    case 11:
      printf("incompatible types in assignment expression\n");
      break;
    case 12:
      printf("incompatible types in argument or return expr\n");
      break;
    case 14:
      printf("incompatible types in binary expression\n");
      break;
    case 16:
      printf("integer type expression is required\n");
      break;
    default:
      printf("unknown\n");
      break;
  }
}