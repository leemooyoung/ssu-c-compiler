/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "ssu_c.y"

// extern int line_no;
#include <stdio.h>
#include <stdlib.h>
int yyerror();
extern int yylex();

#line 79 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    TYPE_IDENTIFIER = 259,         /* TYPE_IDENTIFIER  */
    FLOAT_CONSTANT = 260,          /* FLOAT_CONSTANT  */
    INTEGER_CONSTANT = 261,        /* INTEGER_CONSTANT  */
    CHARACTER_CONSTANT = 262,      /* CHARACTER_CONSTANT  */
    STRING_LITERAL = 263,          /* STRING_LITERAL  */
    PLUS = 264,                    /* PLUS  */
    MINUS = 265,                   /* MINUS  */
    PLUSPLUS = 266,                /* PLUSPLUS  */
    MINUSMINUS = 267,              /* MINUSMINUS  */
    BAR = 268,                     /* BAR  */
    AMP = 269,                     /* AMP  */
    BARBAR = 270,                  /* BARBAR  */
    AMPAMP = 271,                  /* AMPAMP  */
    ARROW = 272,                   /* ARROW  */
    SEMICOLON = 273,               /* SEMICOLON  */
    LSS = 274,                     /* LSS  */
    GTR = 275,                     /* GTR  */
    LEQ = 276,                     /* LEQ  */
    GEQ = 277,                     /* GEQ  */
    EQL = 278,                     /* EQL  */
    NEQ = 279,                     /* NEQ  */
    DOTDOTDOT = 280,               /* DOTDOTDOT  */
    LP = 281,                      /* LP  */
    RP = 282,                      /* RP  */
    LB = 283,                      /* LB  */
    RB = 284,                      /* RB  */
    LR = 285,                      /* LR  */
    RR = 286,                      /* RR  */
    PERIOD = 287,                  /* PERIOD  */
    COMMA = 288,                   /* COMMA  */
    EXCL = 289,                    /* EXCL  */
    STAR = 290,                    /* STAR  */
    SLASH = 291,                   /* SLASH  */
    PERCENT = 292,                 /* PERCENT  */
    ASSIGN = 293,                  /* ASSIGN  */
    COLON = 294,                   /* COLON  */
    AUTO_SYM = 295,                /* AUTO_SYM  */
    STATIC_SYM = 296,              /* STATIC_SYM  */
    TYPEDEF_SYM = 297,             /* TYPEDEF_SYM  */
    STRUCT_SYM = 298,              /* STRUCT_SYM  */
    ENUM_SYM = 299,                /* ENUM_SYM  */
    SIZEOF_SYM = 300,              /* SIZEOF_SYM  */
    UNION_SYM = 301,               /* UNION_SYM  */
    IF_SYM = 302,                  /* IF_SYM  */
    ELSE_SYM = 303,                /* ELSE_SYM  */
    WHILE_SYM = 304,               /* WHILE_SYM  */
    DO_SYM = 305,                  /* DO_SYM  */
    FOR_SYM = 306,                 /* FOR_SYM  */
    CONTINUE_SYM = 307,            /* CONTINUE_SYM  */
    BREAK_SYM = 308,               /* BREAK_SYM  */
    RETURN_SYM = 309,              /* RETURN_SYM  */
    SWITCH_SYM = 310,              /* SWITCH_SYM  */
    CASE_SYM = 311,                /* CASE_SYM  */
    DEFAULT_SYM = 312              /* DEFAULT_SYM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IDENTIFIER 258
#define TYPE_IDENTIFIER 259
#define FLOAT_CONSTANT 260
#define INTEGER_CONSTANT 261
#define CHARACTER_CONSTANT 262
#define STRING_LITERAL 263
#define PLUS 264
#define MINUS 265
#define PLUSPLUS 266
#define MINUSMINUS 267
#define BAR 268
#define AMP 269
#define BARBAR 270
#define AMPAMP 271
#define ARROW 272
#define SEMICOLON 273
#define LSS 274
#define GTR 275
#define LEQ 276
#define GEQ 277
#define EQL 278
#define NEQ 279
#define DOTDOTDOT 280
#define LP 281
#define RP 282
#define LB 283
#define RB 284
#define LR 285
#define RR 286
#define PERIOD 287
#define COMMA 288
#define EXCL 289
#define STAR 290
#define SLASH 291
#define PERCENT 292
#define ASSIGN 293
#define COLON 294
#define AUTO_SYM 295
#define STATIC_SYM 296
#define TYPEDEF_SYM 297
#define STRUCT_SYM 298
#define ENUM_SYM 299
#define SIZEOF_SYM 300
#define UNION_SYM 301
#define IF_SYM 302
#define ELSE_SYM 303
#define WHILE_SYM 304
#define DO_SYM 305
#define FOR_SYM 306
#define CONTINUE_SYM 307
#define BREAK_SYM 308
#define RETURN_SYM 309
#define SWITCH_SYM 310
#define CASE_SYM 311
#define DEFAULT_SYM 312

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_TYPE_IDENTIFIER = 4,            /* TYPE_IDENTIFIER  */
  YYSYMBOL_FLOAT_CONSTANT = 5,             /* FLOAT_CONSTANT  */
  YYSYMBOL_INTEGER_CONSTANT = 6,           /* INTEGER_CONSTANT  */
  YYSYMBOL_CHARACTER_CONSTANT = 7,         /* CHARACTER_CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 8,             /* STRING_LITERAL  */
  YYSYMBOL_PLUS = 9,                       /* PLUS  */
  YYSYMBOL_MINUS = 10,                     /* MINUS  */
  YYSYMBOL_PLUSPLUS = 11,                  /* PLUSPLUS  */
  YYSYMBOL_MINUSMINUS = 12,                /* MINUSMINUS  */
  YYSYMBOL_BAR = 13,                       /* BAR  */
  YYSYMBOL_AMP = 14,                       /* AMP  */
  YYSYMBOL_BARBAR = 15,                    /* BARBAR  */
  YYSYMBOL_AMPAMP = 16,                    /* AMPAMP  */
  YYSYMBOL_ARROW = 17,                     /* ARROW  */
  YYSYMBOL_SEMICOLON = 18,                 /* SEMICOLON  */
  YYSYMBOL_LSS = 19,                       /* LSS  */
  YYSYMBOL_GTR = 20,                       /* GTR  */
  YYSYMBOL_LEQ = 21,                       /* LEQ  */
  YYSYMBOL_GEQ = 22,                       /* GEQ  */
  YYSYMBOL_EQL = 23,                       /* EQL  */
  YYSYMBOL_NEQ = 24,                       /* NEQ  */
  YYSYMBOL_DOTDOTDOT = 25,                 /* DOTDOTDOT  */
  YYSYMBOL_LP = 26,                        /* LP  */
  YYSYMBOL_RP = 27,                        /* RP  */
  YYSYMBOL_LB = 28,                        /* LB  */
  YYSYMBOL_RB = 29,                        /* RB  */
  YYSYMBOL_LR = 30,                        /* LR  */
  YYSYMBOL_RR = 31,                        /* RR  */
  YYSYMBOL_PERIOD = 32,                    /* PERIOD  */
  YYSYMBOL_COMMA = 33,                     /* COMMA  */
  YYSYMBOL_EXCL = 34,                      /* EXCL  */
  YYSYMBOL_STAR = 35,                      /* STAR  */
  YYSYMBOL_SLASH = 36,                     /* SLASH  */
  YYSYMBOL_PERCENT = 37,                   /* PERCENT  */
  YYSYMBOL_ASSIGN = 38,                    /* ASSIGN  */
  YYSYMBOL_COLON = 39,                     /* COLON  */
  YYSYMBOL_AUTO_SYM = 40,                  /* AUTO_SYM  */
  YYSYMBOL_STATIC_SYM = 41,                /* STATIC_SYM  */
  YYSYMBOL_TYPEDEF_SYM = 42,               /* TYPEDEF_SYM  */
  YYSYMBOL_STRUCT_SYM = 43,                /* STRUCT_SYM  */
  YYSYMBOL_ENUM_SYM = 44,                  /* ENUM_SYM  */
  YYSYMBOL_SIZEOF_SYM = 45,                /* SIZEOF_SYM  */
  YYSYMBOL_UNION_SYM = 46,                 /* UNION_SYM  */
  YYSYMBOL_IF_SYM = 47,                    /* IF_SYM  */
  YYSYMBOL_ELSE_SYM = 48,                  /* ELSE_SYM  */
  YYSYMBOL_WHILE_SYM = 49,                 /* WHILE_SYM  */
  YYSYMBOL_DO_SYM = 50,                    /* DO_SYM  */
  YYSYMBOL_FOR_SYM = 51,                   /* FOR_SYM  */
  YYSYMBOL_CONTINUE_SYM = 52,              /* CONTINUE_SYM  */
  YYSYMBOL_BREAK_SYM = 53,                 /* BREAK_SYM  */
  YYSYMBOL_RETURN_SYM = 54,                /* RETURN_SYM  */
  YYSYMBOL_SWITCH_SYM = 55,                /* SWITCH_SYM  */
  YYSYMBOL_CASE_SYM = 56,                  /* CASE_SYM  */
  YYSYMBOL_DEFAULT_SYM = 57,               /* DEFAULT_SYM  */
  YYSYMBOL_YYACCEPT = 58,                  /* $accept  */
  YYSYMBOL_program = 59,                   /* program  */
  YYSYMBOL_translation_unit = 60,          /* translation_unit  */
  YYSYMBOL_external_declaration = 61,      /* external_declaration  */
  YYSYMBOL_function_definition = 62,       /* function_definition  */
  YYSYMBOL_declaration_list_opt = 63,      /* declaration_list_opt  */
  YYSYMBOL_declaration_list = 64,          /* declaration_list  */
  YYSYMBOL_declaration = 65,               /* declaration  */
  YYSYMBOL_declaration_specifiers = 66,    /* declaration_specifiers  */
  YYSYMBOL_storage_class_specifier = 67,   /* storage_class_specifier  */
  YYSYMBOL_init_declarator_list_opt = 68,  /* init_declarator_list_opt  */
  YYSYMBOL_init_declarator_list = 69,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 70,           /* init_declarator  */
  YYSYMBOL_initializer = 71,               /* initializer  */
  YYSYMBOL_initializer_list = 72,          /* initializer_list  */
  YYSYMBOL_type_specifier = 73,            /* type_specifier  */
  YYSYMBOL_struct_type_specifier = 74,     /* struct_type_specifier  */
  YYSYMBOL_struct_or_union = 75,           /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 76,   /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 77,        /* struct_declaration  */
  YYSYMBOL_struct_declarator_list = 78,    /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 79,         /* struct_declarator  */
  YYSYMBOL_enum_type_specifier = 80,       /* enum_type_specifier  */
  YYSYMBOL_enumerator_list = 81,           /* enumerator_list  */
  YYSYMBOL_enumerator = 82,                /* enumerator  */
  YYSYMBOL_declarator = 83,                /* declarator  */
  YYSYMBOL_pointer = 84,                   /* pointer  */
  YYSYMBOL_direct_declarator = 85,         /* direct_declarator  */
  YYSYMBOL_parameter_type_list_opt = 86,   /* parameter_type_list_opt  */
  YYSYMBOL_parameter_type_list = 87,       /* parameter_type_list  */
  YYSYMBOL_parameter_list = 88,            /* parameter_list  */
  YYSYMBOL_parameter_declaration = 89,     /* parameter_declaration  */
  YYSYMBOL_abstract_declarator_opt = 90,   /* abstract_declarator_opt  */
  YYSYMBOL_abstract_declarator = 91,       /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 92, /* direct_abstract_declarator  */
  YYSYMBOL_statement_list_opt = 93,        /* statement_list_opt  */
  YYSYMBOL_statement_list = 94,            /* statement_list  */
  YYSYMBOL_statement = 95,                 /* statement  */
  YYSYMBOL_labeled_statement = 96,         /* labeled_statement  */
  YYSYMBOL_compound_statement = 97,        /* compound_statement  */
  YYSYMBOL_expression_statement = 98,      /* expression_statement  */
  YYSYMBOL_selection_statement = 99,       /* selection_statement  */
  YYSYMBOL_iteration_statement = 100,      /* iteration_statement  */
  YYSYMBOL_for_expression = 101,           /* for_expression  */
  YYSYMBOL_expression_opt = 102,           /* expression_opt  */
  YYSYMBOL_jump_statement = 103,           /* jump_statement  */
  YYSYMBOL_arg_expression_list_opt = 104,  /* arg_expression_list_opt  */
  YYSYMBOL_arg_expression_list = 105,      /* arg_expression_list  */
  YYSYMBOL_constant_expression_opt = 106,  /* constant_expression_opt  */
  YYSYMBOL_constant_expression = 107,      /* constant_expression  */
  YYSYMBOL_expression = 108,               /* expression  */
  YYSYMBOL_comma_expression = 109,         /* comma_expression  */
  YYSYMBOL_assignment_expression = 110,    /* assignment_expression  */
  YYSYMBOL_conditional_expression = 111,   /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 112,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 113,   /* logical_and_expression  */
  YYSYMBOL_bitwise_or_expression = 114,    /* bitwise_or_expression  */
  YYSYMBOL_bitwise_xor_expression = 115,   /* bitwise_xor_expression  */
  YYSYMBOL_bitwise_and_expression = 116,   /* bitwise_and_expression  */
  YYSYMBOL_equality_expression = 117,      /* equality_expression  */
  YYSYMBOL_relational_expression = 118,    /* relational_expression  */
  YYSYMBOL_shift_expression = 119,         /* shift_expression  */
  YYSYMBOL_additive_expression = 120,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 121, /* multiplicative_expression  */
  YYSYMBOL_cast_expression = 122,          /* cast_expression  */
  YYSYMBOL_unary_expression = 123,         /* unary_expression  */
  YYSYMBOL_postfix_expression = 124,       /* postfix_expression  */
  YYSYMBOL_primary_expression = 125,       /* primary_expression  */
  YYSYMBOL_type_name = 126                 /* type_name  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   452

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  69
/* YYNRULES -- Number of rules.  */
#define YYNRULES  165
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  282

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   312


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    67,    67,    70,    71,    74,    75,    78,    79,    82,
      83,    86,    87,    90,    93,    94,    95,    96,    99,   100,
     101,   104,   105,   108,   109,   112,   113,   115,   116,   119,
     120,   123,   124,   125,   128,   129,   130,   133,   134,   137,
     138,   141,   144,   145,   148,   151,   152,   153,   156,   157,
     160,   161,   163,   164,   167,   168,   171,   172,   173,   174,
     177,   178,   181,   182,   185,   186,   189,   190,   193,   194,
     197,   198,   199,   202,   203,   204,   205,   206,   209,   210,
     213,   214,   217,   218,   219,   220,   221,   222,   225,   226,
     229,   232,   233,   236,   237,   238,   241,   242,   243,   246,
     249,   250,   253,   254,   255,   259,   260,   263,   264,   267,
     268,   271,   274,   277,   280,   281,   284,   287,   288,   291,
     292,   295,   298,   301,   304,   305,   306,   309,   310,   311,
     312,   313,   316,   319,   320,   321,   324,   325,   326,   327,
     330,   331,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   346,   347,   348,   349,   350,   351,   352,   355,
     356,   357,   358,   359,   360,   363
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "TYPE_IDENTIFIER", "FLOAT_CONSTANT", "INTEGER_CONSTANT",
  "CHARACTER_CONSTANT", "STRING_LITERAL", "PLUS", "MINUS", "PLUSPLUS",
  "MINUSMINUS", "BAR", "AMP", "BARBAR", "AMPAMP", "ARROW", "SEMICOLON",
  "LSS", "GTR", "LEQ", "GEQ", "EQL", "NEQ", "DOTDOTDOT", "LP", "RP", "LB",
  "RB", "LR", "RR", "PERIOD", "COMMA", "EXCL", "STAR", "SLASH", "PERCENT",
  "ASSIGN", "COLON", "AUTO_SYM", "STATIC_SYM", "TYPEDEF_SYM", "STRUCT_SYM",
  "ENUM_SYM", "SIZEOF_SYM", "UNION_SYM", "IF_SYM", "ELSE_SYM", "WHILE_SYM",
  "DO_SYM", "FOR_SYM", "CONTINUE_SYM", "BREAK_SYM", "RETURN_SYM",
  "SWITCH_SYM", "CASE_SYM", "DEFAULT_SYM", "$accept", "program",
  "translation_unit", "external_declaration", "function_definition",
  "declaration_list_opt", "declaration_list", "declaration",
  "declaration_specifiers", "storage_class_specifier",
  "init_declarator_list_opt", "init_declarator_list", "init_declarator",
  "initializer", "initializer_list", "type_specifier",
  "struct_type_specifier", "struct_or_union", "struct_declaration_list",
  "struct_declaration", "struct_declarator_list", "struct_declarator",
  "enum_type_specifier", "enumerator_list", "enumerator", "declarator",
  "pointer", "direct_declarator", "parameter_type_list_opt",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "abstract_declarator_opt", "abstract_declarator",
  "direct_abstract_declarator", "statement_list_opt", "statement_list",
  "statement", "labeled_statement", "compound_statement",
  "expression_statement", "selection_statement", "iteration_statement",
  "for_expression", "expression_opt", "jump_statement",
  "arg_expression_list_opt", "arg_expression_list",
  "constant_expression_opt", "constant_expression", "expression",
  "comma_expression", "assignment_expression", "conditional_expression",
  "logical_or_expression", "logical_and_expression",
  "bitwise_or_expression", "bitwise_xor_expression",
  "bitwise_and_expression", "equality_expression", "relational_expression",
  "shift_expression", "additive_expression", "multiplicative_expression",
  "cast_expression", "unary_expression", "postfix_expression",
  "primary_expression", "type_name", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-177)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     298,  -177,  -177,     9,    38,  -177,  -177,  -177,  -177,    36,
    -177,    49,   298,  -177,  -177,  -177,     9,   273,   273,  -177,
      39,  -177,    63,    14,    20,    73,  -177,   103,   142,  -177,
    -177,    89,   120,  -177,   101,  -177,  -177,   133,    53,   273,
    -177,    20,   273,   353,  -177,   142,   123,    97,  -177,  -177,
       9,   340,  -177,    53,     9,    24,  -177,   231,   273,  -177,
       9,     8,   143,  -177,   139,  -177,  -177,  -177,  -177,  -177,
    -177,   353,   353,   394,   394,   353,   286,   353,   353,   407,
     165,  -177,  -177,  -177,  -177,  -177,   172,   184,  -177,  -177,
    -177,   -14,   171,  -177,   104,    74,  -177,   160,   112,  -177,
     110,   353,  -177,   142,  -177,   167,   340,  -177,  -177,   158,
      29,  -177,  -177,  -177,  -177,  -177,   177,   180,   231,   181,
     197,   198,   353,   192,   353,   190,   189,   231,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,   214,  -177,   227,   353,  -177,
      50,  -177,  -177,   106,  -177,    76,  -177,  -177,  -177,   353,
    -177,  -177,  -177,    77,   206,   217,  -177,  -177,   286,  -177,
    -177,   353,   353,   353,   353,   353,   353,   353,   353,   353,
     353,   353,   353,   353,   353,  -177,  -177,   243,   353,   353,
     244,  -177,  -177,  -177,  -177,   119,  -177,  -177,     9,   353,
     353,   199,   353,  -177,  -177,   232,  -177,   353,   212,   231,
    -177,  -177,  -177,   225,   229,   230,   106,   273,   353,  -177,
    -177,   182,   131,  -177,  -177,   353,   233,   184,  -177,   171,
     171,  -177,  -177,  -177,  -177,    74,    74,  -177,  -177,  -177,
    -177,  -177,   236,   221,  -177,   235,  -177,  -177,   340,  -177,
     245,   247,   249,   252,   240,  -177,   272,   231,  -177,  -177,
    -177,  -177,   276,   275,  -177,  -177,  -177,   353,  -177,  -177,
     231,   231,   353,   231,   353,   231,  -177,  -177,  -177,  -177,
     257,  -177,   279,  -177,   289,  -177,   231,   290,   353,  -177,
    -177,  -177
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    56,    33,     0,    54,    18,    19,    20,    37,     0,
      38,     0,     2,     3,     5,     6,    21,    15,    14,    31,
       0,    32,     0,     0,    53,     0,    55,    47,     0,     1,
       4,     0,    22,    23,    25,    17,    16,    36,     0,     9,
       8,    52,    60,   109,    57,     0,    50,     0,    48,    13,
       0,     0,     7,     0,     0,     0,    39,    78,    10,    11,
      21,    68,     0,    61,    62,    64,   159,   161,   160,   162,
     163,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   116,   117,   119,   121,
     122,   123,   124,   127,   132,   133,   136,   140,   142,   152,
       0,     0,    46,     0,    24,    25,     0,    26,    27,     0,
       0,    42,    44,    35,    40,    91,     0,     0,     0,     0,
       0,     0,   100,     0,     0,     0,     0,    79,    80,    82,
      83,    84,    85,    86,    87,     0,    12,    60,   109,    66,
      71,    67,    69,    70,    59,     0,   149,   140,   148,     0,
     143,   144,   145,    68,     0,     0,   147,   146,     0,   150,
      58,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,   158,     0,   105,     0,
       0,    45,    51,    49,    29,     0,    34,    41,     0,     0,
       0,     0,   100,   103,   104,     0,   101,     0,     0,     0,
      90,    81,    92,     0,     0,     0,    72,    60,   109,    63,
      65,    60,    71,   165,   164,     0,     0,   118,   120,   125,
     126,   128,   129,   130,   131,   134,   135,   137,   138,   139,
     115,   156,     0,   106,   107,     0,   155,    28,     0,    43,
       0,     0,     0,     0,     0,   102,     0,     0,    89,    76,
      73,    74,     0,     0,   141,   151,   154,     0,   153,    30,
       0,     0,     0,     0,   100,     0,    88,    77,    75,   108,
      93,    96,     0,    98,     0,    95,     0,     0,   100,    94,
      97,    99
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -177,  -177,  -177,   297,  -177,  -177,  -177,     2,     6,  -177,
    -177,  -177,   260,  -101,  -177,    -1,  -177,  -177,   258,   -34,
    -177,   130,  -177,   277,   220,    11,    -2,   -19,   -39,  -177,
    -177,   191,   200,  -107,  -120,  -177,  -177,  -105,  -177,    16,
    -177,  -177,  -177,  -177,  -176,  -177,  -177,  -177,  -131,   -50,
     -43,  -177,  -159,  -177,  -177,   164,   173,  -177,  -177,  -177,
       3,    46,  -177,    27,   -46,    12,  -177,  -177,   176
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    11,    12,    13,    14,    57,    58,    15,    61,    17,
      31,    32,    33,   107,   185,    18,    19,    20,    55,    56,
     110,   111,    21,    47,    48,    22,    23,    24,   203,    63,
      64,    65,   141,   142,   143,   126,   127,   128,   129,   130,
     131,   132,   133,   243,   195,   134,   232,   233,    80,    81,
     135,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   155
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      82,   108,    26,    62,    41,   184,    16,   205,    82,   163,
     164,     1,     1,   191,    25,   230,   244,     1,    16,   234,
     206,   114,   201,    35,    36,   146,   148,    34,     2,   152,
     204,   156,   157,   154,   137,     3,   138,    54,    40,    27,
       3,    59,    37,     4,     4,    60,    42,   187,    43,    29,
      52,   182,    54,     1,    54,   113,   108,     2,    82,   140,
     136,   105,   188,    82,    60,   112,    28,     8,     9,    38,
      10,   105,   139,     4,   198,   114,   137,   253,   138,   196,
       2,    82,   153,   147,   147,   150,   151,   147,   274,   147,
     147,   159,   206,    39,   248,    82,     8,     9,   269,    10,
      44,   209,   281,   211,   204,   138,   154,    49,    54,   171,
     172,   173,     4,   169,   170,   154,     5,     6,     7,     8,
       9,    41,    10,   175,   176,   227,   228,   229,   102,   177,
     103,    39,   207,    45,   208,   140,   235,   259,   178,    51,
     179,   181,   266,   103,   180,    46,   240,   241,    25,   196,
     237,   212,   238,    50,   246,   270,   271,   211,   273,   138,
     275,   101,     2,    53,   153,    82,   219,   220,   252,   254,
     144,   279,   145,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,     2,   161,   108,   186,
     165,   166,   167,   168,   160,    82,   225,   226,   174,   112,
     162,     8,     9,   189,    10,    51,   190,   192,   211,   212,
     138,   221,   222,   223,   224,   193,   194,     4,   197,   272,
     200,   196,     5,     6,     7,     8,     9,   147,    10,   199,
       1,     2,   202,   214,    66,   196,    67,    68,    69,    70,
      71,    72,    73,    74,   215,    75,   231,   236,   242,   115,
     245,   247,   249,   137,   257,   138,   250,    76,   264,   251,
     255,    39,     4,   256,   258,    77,    78,     5,     6,     7,
       8,     9,   260,    10,   261,   262,    79,     2,   116,   263,
     117,   118,   119,   120,   121,   122,   123,   124,   125,    66,
       2,    67,    68,    69,    70,    71,    72,    73,    74,   265,
      75,     1,     2,   267,   268,   276,   277,   278,   280,    30,
     104,   109,    76,     5,     6,     7,     8,     9,   239,    10,
      77,    78,   100,   183,     3,   217,     5,     6,     7,     8,
       9,    79,    10,     4,   216,   218,   210,     0,     5,     6,
       7,     8,     9,    66,    10,    67,    68,    69,    70,    71,
      72,    73,    74,   213,    75,     0,    66,     0,    67,    68,
      69,    70,    71,    72,    73,    74,    76,    75,     0,     0,
     106,     0,     0,     0,    77,    78,     0,     0,     0,    76,
       0,     0,     0,     0,     0,    79,     0,    77,    78,     0,
       0,     0,     0,     0,     0,     0,     0,    66,    79,    67,
      68,    69,    70,    71,    72,    73,    74,     0,    75,     0,
      66,     0,    67,    68,    69,    70,    71,    72,    73,    74,
     149,    75,     0,     0,     0,     0,     0,     0,    77,    78,
       0,     0,     0,   158,     0,     0,     0,     0,     0,    79,
       0,    77,    78,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    79
};

static const yytype_int16 yycheck[] =
{
      43,    51,     4,    42,    23,   106,     0,   138,    51,    23,
      24,     3,     3,   118,     3,   174,   192,     3,    12,   178,
     140,    55,   127,    17,    18,    71,    72,    16,     4,    75,
     137,    77,    78,    76,    26,    26,    28,    38,    22,     3,
      26,    39,     3,    35,    35,    39,    26,    18,    28,     0,
      34,   101,    53,     3,    55,    31,   106,     4,   101,    61,
      58,    50,    33,   106,    58,    54,    30,    43,    44,    30,
      46,    60,    61,    35,   124,   109,    26,   208,    28,   122,
       4,   124,    76,    71,    72,    73,    74,    75,   264,    77,
      78,    79,   212,    30,   199,   138,    43,    44,   257,    46,
      27,    25,   278,    26,   211,    28,   149,    18,   109,    35,
      36,    37,    35,     9,    10,   158,    40,    41,    42,    43,
      44,   140,    46,    11,    12,   171,   172,   173,    31,    17,
      33,    30,    26,    30,    28,   137,   179,   238,    26,    38,
      28,    31,   247,    33,    32,     3,   189,   190,   137,   192,
      31,   153,    33,    33,   197,   260,   261,    26,   263,    28,
     265,    38,     4,    30,   158,   208,   163,   164,   207,   215,
      27,   276,    33,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,     4,    15,   238,    31,
      19,    20,    21,    22,    29,   238,   169,   170,    38,   188,
      16,    43,    44,    26,    46,    38,    26,    26,    26,   211,
      28,   165,   166,   167,   168,    18,    18,    35,    26,   262,
      31,   264,    40,    41,    42,    43,    44,   215,    46,    39,
       3,     4,    18,    27,     3,   278,     5,     6,     7,     8,
       9,    10,    11,    12,    27,    14,     3,     3,    49,    18,
      18,    39,    27,    26,    33,    28,    27,    26,    18,    29,
      27,    30,    35,    27,    29,    34,    35,    40,    41,    42,
      43,    44,    27,    46,    27,    26,    45,     4,    47,    27,
      49,    50,    51,    52,    53,    54,    55,    56,    57,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    27,
      14,     3,     4,    27,    29,    48,    27,    18,    18,    12,
      50,    53,    26,    40,    41,    42,    43,    44,   188,    46,
      34,    35,    45,   103,    26,   161,    40,    41,    42,    43,
      44,    45,    46,    35,   158,   162,   145,    -1,    40,    41,
      42,    43,    44,     3,    46,     5,     6,     7,     8,     9,
      10,    11,    12,   153,    14,    -1,     3,    -1,     5,     6,
       7,     8,     9,    10,    11,    12,    26,    14,    -1,    -1,
      30,    -1,    -1,    -1,    34,    35,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    45,     5,
       6,     7,     8,     9,    10,    11,    12,    -1,    14,    -1,
       3,    -1,     5,     6,     7,     8,     9,    10,    11,    12,
      26,    14,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    26,    35,    40,    41,    42,    43,    44,
      46,    59,    60,    61,    62,    65,    66,    67,    73,    74,
      75,    80,    83,    84,    85,    83,    84,     3,    30,     0,
      61,    68,    69,    70,    83,    66,    66,     3,    30,    30,
      97,    85,    26,    28,    27,    30,     3,    81,    82,    18,
      33,    38,    97,    30,    73,    76,    77,    63,    64,    65,
      66,    66,    86,    87,    88,    89,     3,     5,     6,     7,
       8,     9,    10,    11,    12,    14,    26,    34,    35,    45,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      81,    38,    31,    33,    70,    83,    30,    71,   107,    76,
      78,    79,    83,    31,    77,    18,    47,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    93,    94,    95,    96,
      97,    98,    99,   100,   103,   108,    65,    26,    28,    83,
      84,    90,    91,    92,    27,    33,   122,   123,   122,    26,
     123,   123,   122,    66,   108,   126,   122,   122,    26,   123,
      29,    15,    16,    23,    24,    19,    20,    21,    22,     9,
      10,    35,    36,    37,    38,    11,    12,    17,    26,    28,
      32,    31,   107,    82,    71,    72,    31,    18,    33,    26,
      26,    95,    26,    18,    18,   102,   108,    26,   107,    39,
      31,    95,    18,    86,    91,   106,    92,    26,    28,    25,
      89,    26,    84,    90,    27,    27,   126,   113,   114,   118,
     118,   119,   119,   119,   119,   121,   121,   122,   122,   122,
     110,     3,   104,   105,   110,   108,     3,    31,    33,    79,
     108,   108,    49,   101,   102,    18,   108,    39,    95,    27,
      27,    29,    86,   106,   122,    27,    27,    33,    29,    71,
      27,    27,    26,    27,    18,    27,    95,    27,    29,   110,
      95,    95,   108,    95,   102,    95,    48,    27,    18,    95,
      18,   102
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    58,    59,    60,    60,    61,    61,    62,    62,    63,
      63,    64,    64,    65,    66,    66,    66,    66,    67,    67,
      67,    68,    68,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    73,    73,    74,    74,    74,    75,    75,    76,
      76,    77,    78,    78,    79,    80,    80,    80,    81,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    85,    85,
      86,    86,    87,    87,    88,    88,    89,    89,    90,    90,
      91,    91,    91,    92,    92,    92,    92,    92,    93,    93,
      94,    94,    95,    95,    95,    95,    95,    95,    96,    96,
      97,    98,    98,    99,    99,    99,   100,   100,   100,   101,
     102,   102,   103,   103,   103,   104,   104,   105,   105,   106,
     106,   107,   108,   109,   110,   110,   111,   112,   112,   113,
     113,   114,   115,   116,   117,   117,   117,   118,   118,   118,
     118,   118,   119,   120,   120,   120,   121,   121,   121,   121,
     122,   122,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   125,   125,   125,   125,   126
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     2,     0,
       1,     1,     2,     3,     1,     1,     2,     2,     1,     1,
       1,     0,     1,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     1,     5,     4,     2,     1,     1,     1,
       2,     3,     1,     3,     1,     5,     4,     2,     1,     3,
       1,     3,     2,     1,     1,     2,     1,     3,     4,     4,
       0,     1,     1,     3,     1,     3,     2,     2,     0,     1,
       1,     1,     2,     3,     3,     4,     3,     4,     0,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     4,     3,
       4,     1,     2,     5,     7,     5,     5,     7,     5,     5,
       0,     1,     3,     2,     2,     0,     1,     1,     3,     0,
       1,     1,     1,     1,     1,     3,     1,     1,     3,     1,
       3,     1,     1,     1,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     1,     3,     3,     1,     3,     3,     3,
       1,     4,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     4,     1,     4,     4,     3,     3,     2,     2,     1,
       1,     1,     1,     1,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {

#line 1599 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 365 "ssu_c.y"


// extern char *yytext;

int yyerror(char *s) {
    // printf("line %d: %s near %s\n", line_no, s, yytext);
    printf("%s\n", s);
    exit(1);
}
