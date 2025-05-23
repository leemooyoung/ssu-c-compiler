#ifndef __SSU_C_PRINT_SEM__
#define __SSU_C_PRINT_SEM__

#include "type.h"

void print_sem_ast(A_NODE *);
void prt_sem_program(A_NODE *, int);

void prt_sem_initializer(A_NODE *, int);
void prt_sem_arg_expr_list(A_NODE *, int);
void prt_sem_statement(A_NODE *, int);
void prt_sem_statement_list(A_NODE *, int);
void prt_sem_for_expression(A_NODE *, int);
void prt_sem_expression(A_NODE *, int);
void prt_sem_A_TYPE(A_TYPE *, int);
void prt_sem_A_ID_LIST(A_ID *, int);
void prt_sem_A_ID(A_ID *, int);
void prt_sem_A_ID_NAME(A_ID *, int);
void prt_sem_LITERAL(int, int);
void prt_sem_integer(int, int);

#endif
