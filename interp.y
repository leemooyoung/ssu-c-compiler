%{
#ifndef YYSTYPE_IS_DECLARED

#define YYSTYPE_IS_DECLARED 1
typedef long YYSTYPE;

#endif

#include <stdio.h>
#include <string.h>

#include "interp.type.h"
#include "interp.h"

int yyerror();
extern int yylex();
%}

%token
NEW_LINE
COLON
COMMA
IDENTIFIER
INST1
INST2
INTEGER
FLOAT
STRING
CHAR
GLOBAL_WORD_SYM
GLOBAL_BYTE_SYM
LITERAL_SYM
%%
program
	: command_list
	;
command_list
	: command
	| command_list command
command
	: NEW_LINE
	| IDENTIFIER COLON NEW_LINE	
		{ put_symbol($1, pc); }
	| INST1 INTEGER COMMA INTEGER NEW_LINE
		{ gen_code($1, $2, $4); }
	| INST2 INTEGER COMMA IDENTIFIER NEW_LINE
		{ gen_code($1, $2, get_symbol($4)); }
	| directive INTEGER INTEGER NEW_LINE
		{ put_data($2, 1, $3); }
	| directive INTEGER FLOAT NEW_LINE
		{ put_data($2, 2, $3); }
	| directive INTEGER STRING NEW_LINE
		{ put_data($2, 3, $3); }
	| GLOBAL_BYTE_SYM INTEGER INTEGER NEW_LINE
		{ put_data($2, 4, $3); }
	;
directive
	: GLOBAL_WORD_SYM
	| LITERAL_SYM
	;
%%

int yyerror (char *s) {
	syntax_err++;
	printf("syntax error at line %d: near %s\n", line_no, yytext);
	print_code();
}
