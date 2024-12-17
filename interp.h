#ifndef __SSU_C_INTERP__
#define __SSU_C_INTERP__

#include <stdio.h>

#include "interp.type.h"

int search_symbol(char *);
int get_symbol(char *);
void put_symbol(char *, int);
void put_data(int, int, char *);
void gen_code(OPCODE, int, long);

int is_inst2(OPCODE);
void assem2();
void print_symbol();
void print_code();
void initialize();

void interp();
int base(int);
void dump_stack();

void assemble_error(int, char *);
void runtime_error(int, int);

void lib_printf();
void lib_scanf();
void lib_malloc();

extern FILE *yyin;
extern char *yytext;

extern int line_no;
extern int pc;

extern char *opcode_name[];
extern INSTRUCTION code[];
extern int stack[];
extern float *stack_f;
extern char *stack_c;

extern int syntax_err;

extern int t, b, hp;

#endif
