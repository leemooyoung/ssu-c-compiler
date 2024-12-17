digit   [0-9]
letter  [a-zA-Z_]
delim   [ \t]
line    [\n]
ws      {delim}+

%{
#ifndef YYSTYPE_IS_DECLARED

#define YYSTYPE_IS_DECLARED 1
typedef long YYSTYPE;

#endif

#include "interp.tab.h"
#include "interp.h"

char *makeString(char *);
int parseId(char *);
%}

%%
{ws}                        { }
{line}                      { line_no++; return NEW_LINE; }
"\.global_word"             { return GLOBAL_WORD_SYM; }
"\.global_byte"             { return GLOBAL_BYTE_SYM; }
"\.literal"                 { return LITERAL_SYM; }
"\:"                        { return COLON; }
"\,"                        { return COMMA; }
(\-)?{digit}+               { yylval = atoi(yytext); return INTEGER; }
{digit}+\.{digit}+          { yylval = makeString(yytext); return FLOAT; }
{letter}({letter}|{digit})* { return parseId(yytext); }
\"([^"\n]|\\["\n])*\"       { yylval = makeString(yytext); return STRING; }
\'([^'\n]|\'\')\'           { yylval = *(yytext + 1); return CHAR; }
%%

char *makeString(char *s) {
  char *t;
  t = malloc(strlen(s) + 1);
  strcpy(t, s);
  return t;
}

int search_opcode(char *s) {
  int i;
  for (i = NOP - 1; i > 0; i--) {
    if (strcmp(opcode_name[i], s) == 0)
      break;
  }
  return i;
}

int parseId(char *s) {
  yylval = search_opcode(s); 
  if (yylval == 0) { 
    yylval = makeString(s);
    return IDENTIFIER;
  } else if (is_inst2(yylval)) {
    return INST2; 
  } else {
    return INST1; 
  }
}

int yywrap() {
  return 1;
}
