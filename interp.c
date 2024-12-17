#include "interp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interp.type.h"

extern int yyparse();

int line_no = 1;
int pc = 0;
struct {
  char *name;
  int addr;
} symbol[SYMBOL_MAX];
int dx = 0;
int stack[STACK_MAX];
INSTRUCTION code[CODE_MAX];
float *stack_f;
int *stack_i;
char *stack_c;
int syntax_err = 0;
int semantic_err = 0;

int p = 0,         // program counter
  b = 0,           // base register
  t = -1,          // stack top register
  hp = STACK_MAX;  // heap pointer register

char *opcode_name[]
  = {"OP_NULL", "LOD",  "LDX",  "LDXB",   "LDA",    "LITI", "STO",  "STOB",
     "STX",     "STXB", "SUBI", "SUBF",   "DIVI",   "DIVF", "ADDI", "ADDF",
     "OFFSET",  "MULI", "MULF", "MOD",    "LSSI",   "LSSF", "GTRI", "GTRF",
     "LEQI",    "LEQF", "GEQI", "GEQF",   "NEQI",   "NEQF", "EQLI", "EQLF",
     "NOT",     "OR",   "AND",  "CVTI",   "CVTF",   "JPC",  "JPCR", "JMP",
     "JPT",     "JPTR", "INT",  "INCI",   "INCF",   "DECI", "DECF", "SUP",
     "CAL",     "ADDR", "RET",  "MINUSI", "MINUSF", "LDI",  "LDIB", "POP"};

int search_symbol(char *s) {
  int i;
  for (i = dx; i > 0; i--) {
    if (strcmp(symbol[i].name, s) == 0) break;
  }
  return (i);
}

int get_symbol(char *s) {
  int i;
  i = search_symbol(s);
  if (i == 0) {
    i = ++dx;
    symbol[i].name = s;
    symbol[i].addr = 0;
  }
  return (i);
}

void put_symbol(char *s, int p) {
  int i;
  i = search_symbol(s);
  if (i)
    if (symbol[i].addr)
      assemble_error(2, s);
    else
      symbol[i].addr = p;
  else {
    dx++;
    symbol[dx].name = s;
    symbol[dx].addr = p;
  }
}

void put_data(int i, int k, char *s) {
  int a;
  if (k == 1)
    *(stack_i + i / 4) = (int)s;
  else if (k == 2)
    *(stack_f + i / 4) = atof(s);
  else if (k == 3) {
    *(s + strlen(s) - 1) = 0;
    strcpy(stack_c + i, s + 1);
  } else if (k == 4)
    *(stack_c + i) = (int)s;
  else
    assemble_error(100, NULL);
}

void gen_code(OPCODE op, int l, long a) {
  if (pc >= CODE_MAX)
    assemble_error(10, NULL);
  else {
    code[pc].f = op;
    code[pc].l = l;
    code[pc].a = a;
    pc++;
  }
}

int is_inst2(OPCODE op) {
  if (op == JMP || op == JPC || op == JPT || op == JPCR || op == JPTR
      || op == ADDR || op == SUP)
    return (1);
  else
    return (0);
}

void assem2() {
  int i, j;
  for (i = 0; i < pc; i++)
    if (is_inst2(code[i].f)) {
      j = code[i].a;
      if (symbol[j].addr == 0)
        assemble_error(1, symbol[j].name);
      else
        code[i].a = symbol[j].addr;
    }
}

void print_symbol() {
  int i;
  printf("======== symbol =========\n");
  for (i = 1; i <= dx; i++) {
    printf("%4d:  %s\t%d\n", i, symbol[i].name, symbol[i].addr);
  }
}

void print_code() {
  OPCODE op;
  int i;
  printf("========  code ==========\n");
  for (i = 0; i < pc; i++) {
    printf(
      "%4d:  %s\t%d,%d\n", i, opcode_name[code[i].f], code[i].l, code[i].a
    );
  }
}

void initialize() {
  stack_i = stack;
  stack_f = (float *)stack;
  stack_c = (char *)stack;
  put_symbol("printf", -1);
  put_symbol("malloc", -2);
  put_symbol("scanf", -3);
}

void main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("source file not given\n");
    exit(1);
  }

  if (argc == 2)
    if ((yyin = fopen(argv[1], "r")) == NULL) {
      printf("can not open input file: %s\n", argv[1]);
      exit(1);
    }

  initialize();
  yyparse();
  if (syntax_err) exit(1);
  print_symbol();
  assem2();
  if (semantic_err) exit(1);
  print_code();
  interp();
}

void assemble_error(int i, char *s) {
  switch (i) {
    case 1:
      printf("error: undefined identifier %s\n", s);
      break;
    case 2:
      printf("error: duplicated identifier %s\n", s);
      break;
    case 10:
      printf("error: too long code size\n");
      break;
    default:
      printf("error: unknown\n");
  }
  semantic_err++;
}

void dump_stack() {
  int j = 0, i = 0;
  printf("\n===========stack dump================\n");
  for (i = 0; i <= t; i++) {
    printf("%08x", i);
    if (i == b)
      printf("*");
    else
      printf(" ");
    printf(":  %08x   %d,%f\n", stack[i], stack[i], *(stack_f + i));
  }
  printf("\n=====================================\n");
}

void runtime_error(int i, int a) {
  printf("runtime error at pc %d : ", a);
  switch (i) {
    case 1:
      printf("devide by zero  \n");
      break;
    case 2:
      printf("array out of bound \n");
      break;
    case 3:
      printf("stack overflow \n");
      break;
    case 4:
      printf("unknown error in switch\n");
      break;
    case 100:
      printf("fatal error: unknown opcode\n");
      break;
    default:
      printf("unknown\n");
      break;
  }
  exit(1);
}

int base(int l) {
  if (l == 0)
    return (0);
  else
    return (b);
}

void interp() {
  INSTRUCTION i;
  int j, k, l, m;
  stack[0] = 0;
  stack[1] = 0;
  stack[2] = 0;

  printf("start execution\n");

  do {
    i = code[p++];
    // dump_stack();
    // printf("%d : %s, %d, %d\n", p - 1, opcode_name[i.f], i.l, i.a);
    switch (i.f) {
      case LOD:
        t++;
        stack[t] = stack[base(i.l) + i.a / 4];
        break;
      case LDI:
        stack[t] = stack[stack[t] / 4];
        break;
      case LDIB:
        stack[t] = *(stack_c + stack[t]);
        break;
      case LDX:
        t++;
        stack[t] = stack[stack[t - 1] / 4];
        break;
      case LDXB:
        t++;
        stack[t] = *(stack_c + stack[t - 1]);
        break;
      case LDA:
        stack[++t] = base(i.l) * 4 + i.a;
        break;
      case LITI:
        stack[++t] = i.a;
        break;
      case STO:
        t = t - 2;
        stack[stack[t + 1] / 4] = stack[t + 2];
        break;
      case STOB:
        t = t - 2;
        *(stack_c + stack[t + 1]) = stack[t + 2];
        break;
      case STX:
        t--;
        stack[stack[t] / 4] = stack[t + 1];
        stack[t] = stack[t + 1];
        break;
      case STXB:
        t--;
        *(stack_c + stack[t]) = stack[t + 1];
        stack[t] = stack[t + 1];
        break;
      case OFFSET:
        t--;
        stack[t] = stack[t] + stack[t + 1];
        break;
      case MOD:
        if (stack[t] == 0)
          runtime_error(1, p);
        else {
          t--;
          stack[t] = stack[t] % stack[t + 1];
        }
        break;
      case ADDI:
        t--;
        stack[t] = stack[t] + stack[t + 1];
        break;
      case SUBI:
        t--;
        stack[t] = stack[t] - stack[t + 1];
        break;
      case MULI:
        t--;
        stack[t] = stack[t] * stack[t + 1];
        break;
      case DIVI:
        if (stack[t] == 0)
          runtime_error(1, p);
        else {
          t--;
          stack[t] = stack[t] / stack[t + 1];
        }
        break;
      case ADDF:
        t--;
        *(stack_f + t) = *(stack_f + t) + *(stack_f + t + 1);
        break;
      case SUBF:
        t--;
        *(stack_f + t) = *(stack_f + t) - *(stack_f + t + 1);
        break;
      case MULF:
        t--;
        *(stack_f + t) = *(stack_f + t) * *(stack_f + t + 1);
        break;
      case DIVF:
        t--;
        *(stack_f + t) = *(stack_f + t) / *(stack_f + t + 1);
        break;

      case EQLI:
        t--;
        stack[t] = (stack[t] == stack[t + 1]) ? 1 : 0;
        break;
      case NEQI:
        t--;
        stack[t] = (stack[t] != stack[t + 1]) ? 1 : 0;
        break;
      case LSSI:
        t--;
        stack[t] = (stack[t] < stack[t + 1]) ? 1 : 0;
        break;
      case GEQI:
        t--;
        stack[t] = (stack[t] >= stack[t + 1]) ? 1 : 0;
        break;
      case GTRI:
        t--;
        stack[t] = (stack[t] > stack[t + 1]) ? 1 : 0;
        break;
      case LEQI:
        t--;
        stack[t] = (stack[t] <= stack[t + 1]) ? 1 : 0;
        break;

      case EQLF:
        t--;
        *(stack_f + t) = (*(stack_f + t) == *(stack_f + t + 1)) ? 1 : 0;
        break;
      case NEQF:
        t--;
        *(stack_f + t) = (*(stack_f + t) != *(stack_f + t + 1)) ? 1 : 0;
        break;
      case LSSF:
        t--;
        *(stack_f + t) = (*(stack_f + t) < *(stack_f + t + 1)) ? 1 : 0;
        break;
      case GEQF:
        t--;
        *(stack_f + t) = (*(stack_f + t) >= *(stack_f + t + 1)) ? 1 : 0;
        break;
      case GTRF:
        t--;
        *(stack_f + t) = (*(stack_f + t) > *(stack_f + t + 1)) ? 1 : 0;
        break;
      case LEQF:
        t--;
        *(stack_f + t) = (*(stack_f + t) <= *(stack_f + t + 1)) ? 1 : 0;
        break;

      case AND:
        t--;
        stack[t] = stack[t] && stack[t + 1];
        break;
      case OR:
        t--;
        stack[t] = stack[t] || stack[t + 1];
        break;
      case NOT:
        stack[t] = (stack[t] == 0) ? 1 : 0;
        break;
      case CVTI:
        stack[t] = (int)(*(stack_f + t));
        break;
      case CVTF:
        *(stack_f + t) = (float)stack[t];
        break;

      case JMP:
        p = i.a;
        break;
      case JPC:
        if (stack[t] == 0) p = i.a;
        t--;
        break;
      case JPCR:
        if (stack[t] == 0)
          p = i.a;
        else
          t--;
        break;
      case JPT:
        if (stack[t] != 0) p = i.a;
        t--;
        break;
      case JPTR:
        if (stack[t] != 0)
          p = i.a;
        else
          t--;
        break;
      case INT:
        t = t + i.a / 4;
        if (t >= 20000) runtime_error(3, p);
        break;
      case INCI:
        stack[t]++;
        break;
      case INCF:
        *(stack_f + t) += 1.0;
        break;
      case DECI:
        stack[t]--;
        break;
      case DECF:
        *(stack_f + t) -= 1.0;
        break;

      case POP:
        t = t - i.a;
        break;
      case MINUSF:
        *(stack_f + t) = -*(stack_f + t);
        break;
      case MINUSI:
        stack[t] = -stack[t];
        break;
      case RET:
        t = b - 1;
        p = stack[t + 3];
        b = stack[t + 2];
        break;
      case ADDR:
        t++;
        stack[t] = i.a;
        break;
      case SUP:
        stack[t + 1] = base(i.l);
        stack[t + 2] = b;
        stack[t + 3] = p;
        b = t + 1;
        p = i.a;
        break;
      case CAL:
        if (stack[t] > 0) {
          stack[t + 1] = b;
          stack[t + 2] = p;
          p = stack[t];
          stack[t] = base(i.l);
          b = t--;
          break;
        } else
          switch (-stack[t]) {  // library functions
            case 1:             // printf
              lib_printf();
              break;
            case 2:  // malloc
              lib_malloc();
              break;
            case 3:  // scanf
              lib_scanf();
              break;
            default:
              printf("library not yet implemented\n");
              break;
          }
        break;
      default:
        runtime_error(100, p);
        break;
    }
  } while (p);

  printf("end execution\n");
}
