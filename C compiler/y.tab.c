/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include <bits/stdc++.h>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include <algorithm>
#include <vector>
//#include "symbol.h"
#include "SymbolInfo.h"
#include "SymbolTable.h"

//#define YYSTYPE SymbolInfo*

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int line_count;
extern int yylineno;
extern char* yytext;

FILE *fp, *fp2, *fp3;

//SymbolTable *table;

vector<string> vars;
vector<string> arrays;
vector<int> arraySize;

string varType;
int errors = 0;

int bucket = 20;

int labelCount=0;
int tempCount=0;

char *newLabel()
{
	char *lb= new char[4];
	strcpy(lb,"L");
	char b[3];
	sprintf(b,"%d", labelCount);
	labelCount++;
	strcat(lb,b);
	return lb;
}

char *newTemp()
{
	char *t= new char[4];
	strcpy(t,"t");
	char b[3];
	sprintf(b,"%d", tempCount);
	tempCount++;
	strcat(t,b);
	return t;
}

string optimization()
{
	string code;
	string line;
	string curr1="",curr2="";
	string prev1,prev2;
	string intermediate;

	ifstream asmCode ("code.asm");
  	
  	if (asmCode.is_open())
  	{
    	while ( getline (asmCode,line) )
    	{
      		if(line.find("MOV")<10 )
			{
				intermediate=line.substr(line.find(" ")+1);
				stringstream check1(intermediate);
				getline(check1, curr1, ',');
				getline(check1,curr2,',');
				if(!(prev1==curr2 && curr1==prev2))
				{
					code+=line+"\n";
				}
				prev1=curr1;
				prev2=curr2;
			}
			else{
				
				code+=line+"\n";
				prev1="";
				prev2="";
			}
    	}
    	
		
  	}
  
  	asmCode.close();
  	fp2= fopen("optimized_code.asm","w");
  	fclose(fp2);
	fp2= fopen("optimized_code.asm","a");
	fprintf(fp2, "%s", code.c_str());
  	return code;
}

SymbolTable symbolTable(bucket);

SymbolInfo code;

string println = "\n\nOUTDEC PROC\n PUSH AX\n PUSH BX\n PUSH CX\n PUSH DX\n OR AX, AX\n JGE _END_IF1\n PUSH AX\n MOV DL, '-'\n MOV AH, 2\n INT 21H\n POP AX\n NEG AX\n _END_IF1:\n XOR CX, CX\n MOV BX, 10D\n _REPEAT_1: \nXOR DX, DX\n DIV BX\n PUSH DX \n INC CX\n OR AX, AX\n JNE _REPEAT_1\n MOV AH, 2\n _PRINT_LOOP:\n POP DX \nOR DL, 30H\n INT 21H \nLOOP _PRINT_LOOP\n POP DX\n POP CX \nPOP BX \nPOP AX \nRET \nOUTDEC ENDP\n\n";
string push = "\n\tPUSH AX \n\tPUSH BX \n\tPUSH CX \n\tPUSH DX\n\n";
string pop = "\n\tPOP AX \n\tPOP BX \n\tPOP CX \n\tPOP DX\n\n \tRET \n\n";
string otherFunc = "";


void yyerror(char *s)
{
	fprintf(fp3, "Error at line %d : %s\n\n", line_count, s);
}



#line 191 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    FOR = 260,
    WHILE = 261,
    DO = 262,
    BREAK = 263,
    INT = 264,
    CHAR = 265,
    FLOAT = 266,
    DOUBLE = 267,
    VOID = 268,
    RETURN = 269,
    SWITCH = 270,
    CASE = 271,
    DEFAULT = 272,
    CONTINUE = 273,
    INCOP = 274,
    DECOP = 275,
    ASSIGNOP = 276,
    BITOP = 277,
    NOT = 278,
    LPAREN = 279,
    RPAREN = 280,
    LCURL = 281,
    RCURL = 282,
    LTHIRD = 283,
    RTHIRD = 284,
    COMMA = 285,
    SEMICOLON = 286,
    MULTI_COMMENT = 287,
    SINGLE_COMMENT = 288,
    STRING = 289,
    PRINTLN = 290,
    ID = 291,
    CONST_INT = 292,
    CONST_FLOAT = 293,
    CONST_CHAR = 294,
    ADDOP = 295,
    MULOP = 296,
    LOGICOP = 297,
    RELOP = 298,
    LOWER_THAN_ELSE = 299
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define DO 262
#define BREAK 263
#define INT 264
#define CHAR 265
#define FLOAT 266
#define DOUBLE 267
#define VOID 268
#define RETURN 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define CONTINUE 273
#define INCOP 274
#define DECOP 275
#define ASSIGNOP 276
#define BITOP 277
#define NOT 278
#define LPAREN 279
#define RPAREN 280
#define LCURL 281
#define RCURL 282
#define LTHIRD 283
#define RTHIRD 284
#define COMMA 285
#define SEMICOLON 286
#define MULTI_COMMENT 287
#define SINGLE_COMMENT 288
#define STRING 289
#define PRINTLN 290
#define ID 291
#define CONST_INT 292
#define CONST_FLOAT 293
#define CONST_CHAR 294
#define ADDOP 295
#define MULOP 296
#define LOGICOP 297
#define RELOP 298
#define LOWER_THAN_ELSE 299

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 126 "parser.y" /* yacc.c:355  */

	SymbolInfo *info;

#line 323 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 340 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   145

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  120

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   150,   150,   170,   175,   181,   185,   189,   195,   211,
     228,   251,   286,   291,   295,   300,   307,   307,   313,   313,
     320,   327,   335,   341,   349,   376,   399,   424,   450,   454,
     462,   467,   473,   479,   496,   509,   525,   541,   550,   560,
     566,   573,   599,   638,   643,   669,   674,   725,   730,   777,
     782,   834,   839,   887,   900,   911,   918,   933,   954,   960,
     966,   972,   980,   990,   995,  1000,  1004
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "DO",
  "BREAK", "INT", "CHAR", "FLOAT", "DOUBLE", "VOID", "RETURN", "SWITCH",
  "CASE", "DEFAULT", "CONTINUE", "INCOP", "DECOP", "ASSIGNOP", "BITOP",
  "NOT", "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD", "COMMA",
  "SEMICOLON", "MULTI_COMMENT", "SINGLE_COMMENT", "STRING", "PRINTLN",
  "ID", "CONST_INT", "CONST_FLOAT", "CONST_CHAR", "ADDOP", "MULOP",
  "LOGICOP", "RELOP", "LOWER_THAN_ELSE", "$accept", "start", "program",
  "unit", "func_declaration", "func_definition", "parameter_list",
  "compound_statement", "$@1", "$@2", "var_declaration", "type_specifier",
  "declaration_list", "statements", "statement", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
# endif

#define YYPACT_NINF -70

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-70)))

#define YYTABLE_NINF -19

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      90,   -70,   -70,   -70,    12,    90,   -70,   -70,   -70,   -70,
     -16,   -70,   -70,   -15,    18,    67,     2,    -1,   -70,    -5,
      -2,    19,    34,    38,    43,   -70,   -70,    11,    90,   -70,
     -70,    40,    84,    46,   -70,   -70,    55,    65,    72,    76,
      78,    -6,    -6,    -6,   -70,    87,    36,   -70,   -70,    -6,
     -70,   -70,    73,    48,   -70,   -70,    85,    81,   -70,    71,
     -21,    75,   -70,   -70,   -70,   -70,   -70,    -6,    94,    -6,
      83,    62,   -70,    98,    91,    -6,    -6,   -70,   100,   -70,
     -70,   -70,   -70,    -6,   -70,    -6,    -6,    -6,    -6,   101,
      94,   104,   -70,   -70,   108,   -70,   110,   106,   109,   -70,
     -70,    75,    97,   -70,    84,    -6,    84,   111,   -70,    -6,
     -70,   135,   115,   -70,   -70,   -70,    84,    84,   -70,   -70
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    21,    22,    23,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    26,     0,     0,     0,     0,    20,     0,
       0,    15,     0,    24,    16,     9,    11,     0,     0,    14,
      27,     0,     0,     0,     8,    10,    13,     0,     0,     0,
       0,     0,     0,     0,    39,     0,    41,    59,    60,     0,
      32,    30,     0,     0,    28,    31,    56,     0,    43,    45,
      47,    49,    51,    55,    19,    12,    25,     0,     0,     0,
       0,    56,    54,     0,     0,    64,     0,    53,    26,    17,
      29,    61,    62,     0,    40,     0,     0,     0,     0,     0,
       0,     0,    38,    58,     0,    66,     0,    63,     0,    44,
      46,    50,    48,    52,     0,     0,     0,     0,    57,     0,
      42,    34,     0,    36,    37,    65,     0,     0,    35,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -70,   -70,   -70,   136,   -70,   -70,   -70,   -11,   -70,   -70,
      47,    10,   -70,   -70,   -48,   -66,   -42,   -40,   -69,    58,
      57,    59,   -38,   -70,   -70,   -70
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    20,    50,    32,    33,
      51,    52,    14,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    96,    97
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      71,    70,    90,    73,    72,    80,    95,    71,    26,    15,
      10,    77,    11,    16,    99,    10,    35,    42,    43,    86,
      13,    24,    87,    27,   105,    21,    25,    89,    28,    91,
      46,    47,    48,    71,    49,    23,    98,    24,    36,    22,
     115,    71,    34,    71,    71,    71,    71,     9,    17,    18,
     103,    38,     9,    39,    40,    29,   111,     1,   113,     2,
      75,     3,    41,    30,    76,   112,    31,    71,   118,   119,
     -18,    42,    43,    64,    24,    79,     1,    37,     2,    44,
       3,    81,    82,    45,    46,    47,    48,    38,    49,    39,
      40,    65,    19,     1,    66,     2,    67,     3,    41,     1,
      68,     2,    69,     3,    81,    82,    83,    42,    43,    78,
      24,    74,    84,    85,    92,    44,    88,    42,    43,    45,
      46,    47,    48,    93,    49,    44,   104,    94,    16,   106,
      46,    47,    48,   107,    49,   108,   109,    86,   110,   116,
     117,    12,   114,   100,   102,   101
};

static const yytype_uint8 yycheck[] =
{
      42,    41,    68,    43,    42,    53,    75,    49,    19,    24,
       0,    49,     0,    28,    83,     5,    27,    23,    24,    40,
      36,    26,    43,    25,    90,    15,    31,    67,    30,    69,
      36,    37,    38,    75,    40,    36,    76,    26,    28,    37,
     109,    83,    31,    85,    86,    87,    88,     0,    30,    31,
      88,     3,     5,     5,     6,    36,   104,     9,   106,    11,
      24,    13,    14,    29,    28,   105,    28,   109,   116,   117,
      27,    23,    24,    27,    26,    27,     9,    37,    11,    31,
      13,    19,    20,    35,    36,    37,    38,     3,    40,     5,
       6,    36,    25,     9,    29,    11,    24,    13,    14,     9,
      24,    11,    24,    13,    19,    20,    21,    23,    24,    36,
      26,    24,    31,    42,    31,    31,    41,    23,    24,    35,
      36,    37,    38,    25,    40,    31,    25,    36,    28,    25,
      36,    37,    38,    25,    40,    25,    30,    40,    29,     4,
      25,     5,    31,    85,    87,    86
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    11,    13,    46,    47,    48,    49,    50,    55,
      56,     0,    48,    36,    57,    24,    28,    30,    31,    25,
      51,    56,    37,    36,    26,    31,    52,    25,    30,    36,
      29,    28,    53,    54,    31,    52,    56,    37,     3,     5,
       6,    14,    23,    24,    31,    35,    36,    37,    38,    40,
      52,    55,    56,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    27,    36,    29,    24,    24,    24,
      62,    61,    67,    62,    24,    24,    28,    67,    36,    27,
      59,    19,    20,    21,    31,    42,    40,    43,    41,    62,
      60,    62,    31,    25,    36,    63,    69,    70,    62,    63,
      64,    66,    65,    67,    25,    60,    25,    25,    25,    30,
      29,    59,    62,    59,    31,    63,     4,    25,    59,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    49,    49,
      50,    50,    51,    51,    51,    51,    53,    52,    54,    52,
      55,    56,    56,    56,    57,    57,    57,    57,    58,    58,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    60,
      60,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    67,    67,    67,    68,    68,    68,    68,
      68,    68,    68,    69,    69,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       6,     5,     4,     3,     2,     1,     0,     4,     0,     3,
       3,     1,     1,     1,     3,     6,     1,     4,     1,     2,
       1,     1,     1,     7,     5,     7,     5,     5,     3,     1,
       2,     1,     4,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     2,     2,     1,     1,     4,     3,     1,
       1,     2,     2,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 151 "parser.y" /* yacc.c:1646  */
    {
		//write your code in this block in all the similar blocks below
		(yyvsp[0].info)->code+= println;
		(yyvsp[0].info)->code+= otherFunc;
		(yyvsp[0].info)->code+= "END MAIN\n";
		vars.push_back("retValue");
		fprintf(fp2,".MODEL SMALL \n.STACK 100H \n.DATA\n");
		for(int i = 0; i<vars.size() ; i++){
			fprintf(fp2, "%s DW ?\n", vars[i].c_str());			
		}
		for(int i = 0 ; i< arrays.size() ; i++) {
			fprintf(fp2, "%s DW %d DUP(?)\n", arrays[i].c_str(), arraySize[i]);
		}
		fprintf(fp2, "\n.CODE\n");
		fprintf(fp2, "%s", (yyvsp[0].info)->code.c_str());

	}
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 171 "parser.y" /* yacc.c:1646  */
    {
			(yyval.info) = (yyvsp[-1].info);
			(yyval.info)->code += (yyvsp[0].info)->code;
		}
#line 1532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 176 "parser.y" /* yacc.c:1646  */
    {
		(yyval.info) = (yyvsp[0].info);
	}
#line 1540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 182 "parser.y" /* yacc.c:1646  */
    {
		(yyval.info) = (yyvsp[0].info);
	}
#line 1548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 186 "parser.y" /* yacc.c:1646  */
    {
		(yyval.info) = (yyvsp[0].info);
	}
#line 1556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 190 "parser.y" /* yacc.c:1646  */
    {
		(yyval.info) = (yyvsp[0].info);
	}
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 196 "parser.y" /* yacc.c:1646  */
    {
					

					SymbolInfo *t = symbolTable.lookUp((yyvsp[-4].info)->getName());
					if(t != NULL && (t->getType() == "FUNC_DEC" || t->getType() == "FUNC_DEF")) {
						fprintf(fp3,"Error at line no %d: function %s already declared\n\n", line_count, (yyvsp[-4].info)->getName().c_str());
						errors++;
					}
					else{
						symbolTable.insertinCurrentScope((yyvsp[-4].info)->getName(), "FUNC_DEC");
						SymbolInfo *temp = symbolTable.lookUp((yyvsp[-4].info)->getName());
						temp->setFuncRetType(varType);
					}

				}
#line 1584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 212 "parser.y" /* yacc.c:1646  */
    {
			
			
			SymbolInfo *t = symbolTable.lookUp((yyvsp[-3].info)->getName());
			if(t != NULL && (t->getType() == "FUNC_DEC" || t->getType() == "FUNC_DEF")) {
				fprintf(fp3,"Error at line no %d: function %s already declared\n\n", line_count, (yyvsp[-3].info)->getName().c_str());
				errors++;
			}
			else{
				symbolTable.insertinCurrentScope((yyvsp[-3].info)->getName(), "FUNC_DEC");
				SymbolInfo *temp = symbolTable.lookUp((yyvsp[-3].info)->getName());
				temp->setFuncRetType(varType);
			}
		}
#line 1603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 229 "parser.y" /* yacc.c:1646  */
    {	
					SymbolInfo *function = new SymbolInfo();
					SymbolInfo *t = symbolTable.lookUp((yyvsp[-4].info)->getName());
					if(t != NULL && t->getType() == "FUNC_DEF") {
						fprintf(fp3,"Error at line no %d: function %s already declared\n\n", line_count, (yyvsp[-4].info)->getName().c_str());
						errors++;
					}
					else if(t == NULL){
						symbolTable.insertinCurrentScope((yyvsp[-4].info)->getName(), "FUNC_DEF");
						SymbolInfo *temp = symbolTable.lookUp((yyvsp[-4].info)->getName());
						temp->setFuncRetType(varType);
					}

					if((yyvsp[-4].info)->getName()=="main"){
						(yyval.info) = function;
						(yyval.info)->code += (yyvsp[-4].info)->getName() + " PROC \n";
						(yyval.info)->code += (yyvsp[0].info)->code;
						(yyval.info)->code+="\tMOV AH,4CH\n\tINT 21H\n";
						(yyval.info)->code+="main ENDP\n";
					}
					
				}
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 252 "parser.y" /* yacc.c:1646  */
    {	

			SymbolInfo *function = new SymbolInfo();
			SymbolInfo *t = symbolTable.lookUp((yyvsp[-3].info)->getName());
			if(t != NULL && t->getType() == "FUNC_DEF") {
				fprintf(fp3,"Error at line no %d: function %s already declared\n\n", line_count, (yyvsp[-3].info)->getName().c_str());
				errors++;
			}
			else if(t == NULL){
				symbolTable.insertinCurrentScope((yyvsp[-3].info)->getName(), "FUNC_DEF");
				SymbolInfo *temp = symbolTable.lookUp((yyvsp[-3].info)->getName());
				temp->setFuncRetType(varType);
			}

			if((yyvsp[-3].info)->getName()=="main"){
	
				(yyval.info) = function;
				(yyval.info)->code += (yyvsp[-3].info)->getName() + " PROC \n";
				(yyval.info)->code += (yyvsp[0].info)->code;

				(yyval.info)->code+="\tMOV AH,4CH\n\tINT 21H\n";
				(yyval.info)->code+="main ENDP\n";
				//$$->code+="END main";
			}
			else{
				otherFunc += (yyvsp[-3].info)->getName() + " PROC \n" + push;
				otherFunc += (yyvsp[0].info)->code + pop;

				otherFunc += (yyvsp[-3].info)->getName() + " ENDP\n";
			}
		}
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 287 "parser.y" /* yacc.c:1646  */
    {
					
					//symbolTable.insertinCurrentScope($4->getName(), $4->getType());
				}
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 292 "parser.y" /* yacc.c:1646  */
    {
			
		}
#line 1683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 296 "parser.y" /* yacc.c:1646  */
    {
			
			//symbolTable.insertinCurrentScope($2->getName(), $2->getType());
		}
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 301 "parser.y" /* yacc.c:1646  */
    {
			
		}
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 307 "parser.y" /* yacc.c:1646  */
    {symbolTable.enterScope();}
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 308 "parser.y" /* yacc.c:1646  */
    {
						
						symbolTable.exitScope();
						(yyval.info) = (yyvsp[-1].info);
					}
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 313 "parser.y" /* yacc.c:1646  */
    {symbolTable.enterScope();}
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 314 "parser.y" /* yacc.c:1646  */
    {
				
				symbolTable.exitScope();
			}
#line 1731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 321 "parser.y" /* yacc.c:1646  */
    {
					

				}
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 328 "parser.y" /* yacc.c:1646  */
    {
					SymbolInfo *s = new SymbolInfo("INT", "INT");
					varType = "INT";
					(yyval.info) = s;
					//$$->setVarType(varType);

				}
#line 1752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 336 "parser.y" /* yacc.c:1646  */
    {
			SymbolInfo *s = new SymbolInfo("FLOAT", "FLOAT");
			varType = "FLOAT";
			(yyval.info) = s;
		}
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 342 "parser.y" /* yacc.c:1646  */
    {
			SymbolInfo *s = new SymbolInfo("VOID", "VOID");
			varType = "VOID";
			(yyval.info) =  s;
		}
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 350 "parser.y" /* yacc.c:1646  */
    {
					
					if(varType == "VOID") {
						fprintf(fp3,"Error at line no %d: type cannot be void\n\n", line_count);
						errors++;
					}
					else{
						SymbolInfo *t = symbolTable.lookUp((yyvsp[0].info)->getName());
						if(t != NULL) {
							fprintf(fp3,"Error at line no %d: variable %s already declared\n\n", line_count, (yyvsp[0].info)->getName().c_str());
							errors++;
						}
						else{
							symbolTable.insertinCurrentScope((yyvsp[0].info)->getName(), "VAR");
							SymbolInfo *temp = symbolTable.lookUp((yyvsp[0].info)->getName());
							temp->setVarType(varType);
							temp->setASMvar(temp->getASMvar()+to_string(symbolTable.idCount));
							if(find(vars.begin(), vars.end(), temp->getASMvar()) == vars.end()){
								vars.push_back(temp->getASMvar());
							}

							
						}
					}
					
				}
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 377 "parser.y" /* yacc.c:1646  */
    {
			
			if(varType == "VOID") {
						fprintf(fp3,"Error at line no %d: type cannot be void\n\n", line_count);
						errors++;
			}
			else{
				SymbolInfo *t = symbolTable.lookUp((yyvsp[-3].info)->getName());
				if(t != NULL && t->getType() == "ARRAY") {
					fprintf(fp3,"Error at line no %d: variable %s already declared\n\n", line_count, (yyvsp[-3].info)->getName().c_str());
					errors++;
				}
				else{
					symbolTable.insertinCurrentScope((yyvsp[-3].info)->getName(), "ARRAY");
					SymbolInfo *temp = symbolTable.lookUp((yyvsp[-3].info)->getName());
					temp->setVarType(varType);
					temp->setASMvar(temp->getASMvar()+to_string(symbolTable.idCount));
					int size = atoi(((yyvsp[-1].info)->getName().c_str()));
					temp->setArraySize(size);
				}
			}
		}
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 400 "parser.y" /* yacc.c:1646  */
    {
			

			if(varType == "VOID") {
						fprintf(fp3,"Error at line no %d: type cannot be void\n\n", line_count);
						errors++;
			}
			else{
				SymbolInfo *t = symbolTable.lookUp((yyvsp[0].info)->getName());
				if(t != NULL) {
					fprintf(fp3,"Error at line no %d: variable %s already declared\n\n", line_count, (yyvsp[0].info)->getName().c_str());
					errors++;
				}
				else{
					symbolTable.insertinCurrentScope((yyvsp[0].info)->getName(), "VAR");
					SymbolInfo *temp = symbolTable.lookUp((yyvsp[0].info)->getName());
					temp->setVarType(varType);
					temp->setASMvar(temp->getASMvar()+to_string(symbolTable.idCount));
					if(find(vars.begin(), vars.end(), temp->getASMvar()) == vars.end()){
						vars.push_back(temp->getASMvar());
					}
				}
			}
		}
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 425 "parser.y" /* yacc.c:1646  */
    {
			
			if(varType == "VOID") {
						fprintf(fp3,"Error at line no %d: type cannot be void\n\n", line_count);
						errors++;
			}
			else{
				SymbolInfo *t = symbolTable.lookUp((yyvsp[-3].info)->getName());
				if(t != NULL && t->getType() == "ARRAY") {
					fprintf(fp3,"Error at line no %d: variable %s already declared\n\n", line_count, (yyvsp[-3].info)->getName().c_str());
					errors++;
				}
				else{
					symbolTable.insertinCurrentScope((yyvsp[-3].info)->getName(), "ARRAY");
					SymbolInfo *temp = symbolTable.lookUp((yyvsp[-3].info)->getName());
					temp->setVarType(varType);
					temp->setASMvar(temp->getASMvar()+to_string(symbolTable.idCount));
					int size = atoi(((yyvsp[-1].info)->getName().c_str()));
					cout << size << endl;
					temp->setArraySize(size);
				}
			}
		}
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 451 "parser.y" /* yacc.c:1646  */
    {
				(yyval.info) = (yyvsp[0].info);
			}
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 455 "parser.y" /* yacc.c:1646  */
    {
			(yyval.info) = (yyvsp[-1].info);
			(yyval.info)->code += (yyvsp[0].info)->code;
			delete (yyvsp[0].info);
		}
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 463 "parser.y" /* yacc.c:1646  */
    {
				//fprintf(fp2,"At line no %d: statement : var_declaration\n\n", line_count);

			}
#line 1914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 468 "parser.y" /* yacc.c:1646  */
    {
	  		//fprintf(fp2,"At line no %d: statement : expression_statement\n\n", line_count);

	  		(yyval.info) = (yyvsp[0].info);
		}
#line 1924 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 474 "parser.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line no %d: statement : compound_statement\n\n", line_count);

			(yyval.info) = (yyvsp[0].info);
		}
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 480 "parser.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line no %d: statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n", line_count);

			(yyval.info) = (yyvsp[-4].info);
			char *label1 = newLabel();
			char *label2 = newLabel();
			(yyval.info)->code += string(label1) + ":\n";
			(yyval.info)->code+=(yyvsp[-3].info)->code;
			(yyval.info)->code+="\tMOV AX,"+(yyvsp[-3].info)->getASMvar()+"\n";
			(yyval.info)->code+="\tCMP AX , 0\n";
			(yyval.info)->code+="\tJE "+string(label2)+"\n";
			(yyval.info)->code+=(yyvsp[0].info)->code;
			(yyval.info)->code+=(yyvsp[-2].info)->code;
			(yyval.info)->code+="\tJMP "+string(label1)+"\n";
			(yyval.info)->code+=string(label2)+":\n";
		}
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 497 "parser.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line no %d: statement : IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE\n\n", line_count);
			
			(yyval.info)=(yyvsp[-2].info);		
			char *label=newLabel();
			(yyval.info)->code+="\tMOV AX,"+(yyvsp[-2].info)->getASMvar()+"\n";
			(yyval.info)->code+="\tCMP AX, 0\n";
			(yyval.info)->code+="\tJE "+string(label)+"\n";
			(yyval.info)->code+=(yyvsp[0].info)->code;
			(yyval.info)->code+=string(label)+":\n";

		}
#line 1972 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 510 "parser.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line no %d: statement : IF LPAREN expression RPAREN statement ELSE statement\n\n", line_count);
			(yyval.info) = (yyvsp[-4].info);
			char *label1 = newLabel();
			char *label2 = newLabel();
			(yyval.info)->code+="\tMOV AX,"+(yyvsp[-4].info)->getASMvar()+"\n";
			(yyval.info)->code+="\tCMP AX, 0\n";
			(yyval.info)->code+="\tJE "+string(label1)+"\n";
			(yyval.info)->code+=(yyvsp[-2].info)->code;
			(yyval.info)->code+="\tJMP " + string(label2) + "\n";
			(yyval.info)->code+=string(label1)+":\n";
			(yyval.info)->code+= (yyvsp[0].info)->code;
			(yyval.info)->code+=string(label2)+":\n";

		}
#line 1992 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 526 "parser.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line no %d: statement : WHILE LPAREN expression RPAREN statement\n\n", line_count);
			//$$ = new SymbolInfo();
			char * label1 = newLabel();
			char * label2 = newLabel();
			(yyval.info)->code = string(label1) + ":\n"; 
			(yyval.info)->code+=(yyvsp[-2].info)->code;
			(yyval.info)->code+="\tMOV AX,"+(yyvsp[-2].info)->getASMvar()+"\n";
			(yyval.info)->code+="\tCMP AX , 0\n";
			(yyval.info)->code+="\tJE "+string(label2)+"\n";
			(yyval.info)->code+=(yyvsp[0].info)->code;
			(yyval.info)->code+="\tJMP "+string(label1)+"\n";
			(yyval.info)->code+=string(label2)+":\n";

		}
#line 2012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 542 "parser.y" /* yacc.c:1646  */
    {
			SymbolInfo *t = symbolTable.lookUp((yyvsp[-2].info)->getName());
			if(t == NULL) cout << "null" << endl;
			(yyval.info) = t;
			(yyval.info) = new SymbolInfo();
			(yyval.info)->code += "\tMOV AX," + t->getASMvar() +"\n";
			(yyval.info)->code += "\tCALL OUTDEC\n";
		}
#line 2025 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 551 "parser.y" /* yacc.c:1646  */
    {
			(yyval.info) = (yyvsp[-1].info);
			(yyval.info)->code+="\tMOV DX," + (yyvsp[-1].info)->getASMvar() + "\n";
			(yyval.info)->code+="\tMOV retValue,DX\n";
			//$$->code+=pop;
			//$$->code+="\tRET \n";
		}
#line 2037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 561 "parser.y" /* yacc.c:1646  */
    {
							SymbolInfo *sem = new SymbolInfo();
							(yyval.info) = sem;
							(yyval.info)->code = "";
						}
#line 2047 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 567 "parser.y" /* yacc.c:1646  */
    {
				(yyval.info) = (yyvsp[-1].info);
				//$$->code += $2->code;
			}
#line 2056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 574 "parser.y" /* yacc.c:1646  */
    {
				
				SymbolInfo *t = symbolTable.lookUp((yyvsp[0].info)->getName());
				if(t == NULL) {
					fprintf(fp3,"Error at line no %d: Undeclared variable %s \n\n", line_count, (yyvsp[0].info)->getName().c_str());
					errors++;
				}
				else if(t!= NULL && t->getType() == "ARRAY"){
					fprintf(fp3,"Error at line no %d: Array without index \n\n", line_count);
					errors++;
				}
				else{
					SymbolInfo *id = new SymbolInfo(t->getName(), t->getType());
					(yyval.info) = id;
					(yyval.info)->setVarType(t->getVarType());
					//$$->setASMvar(id->getASMvar()+to_string(symbolTable.idCount));
					(yyval.info)->setASMvar(t->getASMvar());					
					if(find(vars.begin(), vars.end(), (yyval.info)->getASMvar()) == vars.end()){
						vars.push_back((yyval.info)->getASMvar());
					}
					//vars.push_back($$->getASMvar());
					//cout << $$->getVarType() << endl;
				}
				
			}
#line 2086 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 600 "parser.y" /* yacc.c:1646  */
    {
		
		SymbolInfo *t = symbolTable.lookUp((yyvsp[-3].info)->getName());
		if(t == NULL) {
			fprintf(fp3,"Error at line no %d: Undeclared variable %s \n\n", line_count, (yyvsp[-3].info)->getName().c_str());
			errors++;
		}
		else if(t!= NULL && t->getType() == "VAR"){
			fprintf(fp3,"Error at line no %d: Not an array \n\n", line_count);
			errors++;
		}
		else if((yyvsp[-1].info)->getVarType() != "INT"){
			fprintf(fp3,"Error at line no %d: Non-integer Array Index\n\n", line_count);
			errors++;
		}
		else{
			SymbolInfo *id = new SymbolInfo(t->getName(), t->getType());
			(yyval.info) = id;
			(yyval.info)->setArraySize(t->getArraySize());
			(yyval.info)->setASMvar(id->getASMvar() + to_string(symbolTable.idCount));
			cout << "line count " << line_count << " " << (yyval.info)->getASMvar() << endl;
			if(find(arrays.begin(), arrays.end(), (yyval.info)->getASMvar()) == arrays.end()){
				arrays.push_back((yyval.info)->getASMvar());
				arraySize.push_back(t->getArraySize());
			}
			//arrays.push_back($$->getASMvar());
			//arraySize.push_back(t->getArraySize());
			(yyval.info)->setVarType(t->getVarType());
			(yyval.info)->code=(yyvsp[-1].info)->code ;
			(yyval.info)->code += "\tMOV BX," +(yyvsp[-1].info)->getASMvar() +"\n";
			//$$->code += "\tADD BX, BX\n";
					
			//delete $3;
		}
		//$$->code += $3->code;
	}
#line 2127 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 639 "parser.y" /* yacc.c:1646  */
    {
				
				(yyval.info) = (yyvsp[0].info);
			}
#line 2136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 644 "parser.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line no %d: expression : variable ASSIGNOP logic_expression\n\n", line_count);
			
			if((yyvsp[-2].info)->getVarType() == "INT" && (yyvsp[0].info)->getVarType() == "FLOAT"){
				fprintf(fp3,"Warning at line no %d: Assigning float type to integer\n\n", line_count);
				errors++;
			}
			if((yyvsp[-2].info)->getVarType() == "FLOAT" && (yyvsp[0].info)->getVarType() == "INT"){
				fprintf(fp3,"Warning at line no %d: Assigning int type to float\n\n", line_count);
				errors++;
			}
			(yyval.info) = (yyvsp[-2].info);
			(yyval.info)->code=(yyvsp[0].info)->code+(yyvsp[-2].info)->code;
			(yyval.info)->code+="\tMOV AX,"+(yyvsp[0].info)->getASMvar()+"\n";
			if((yyval.info)->getType()=="ARRAY"){ 
				(yyval.info)->code+= "\tMOV  "+(yyvsp[-2].info)->getASMvar()+"[BX], AX\n";
			}
				
			else{
				(yyval.info)->code+= "\tMOV "+(yyvsp[-2].info)->getASMvar()+",AX\n";
			}
			//delete $3;
		}
#line 2164 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 670 "parser.y" /* yacc.c:1646  */
    {
					
					(yyval.info) = (yyvsp[0].info);
				}
#line 2173 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 675 "parser.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line no %d: logic_expression : rel_expression LOGICOP rel_expression\n\n", line_count);
			(yyval.info)=(yyvsp[-2].info);
			(yyval.info)->code+=(yyvsp[0].info)->code;
			char * label1 = newLabel();
			char * label2 = newLabel();
			char * t = newTemp();
			(yyval.info)->setVarType("INT");
			if((yyvsp[-2].info)->getVarType() != (yyvsp[0].info)->getVarType()){
				fprintf(fp3,"Error at line no %d: Type Mismatch\n\n", line_count);
				errors++;
			}
			else{
				if((yyvsp[-1].info)->getName() == "&&"){
					(yyval.info)->code += "\tMOV AX," + (yyvsp[-2].info)->getASMvar() +"\n";
					(yyval.info)->code += "\tCMP AX , 0\n";
				 	(yyval.info)->code += "\tJE " + string(label1) +"\n";
					(yyval.info)->code += "\tMOV AX," + (yyvsp[0].info)->getASMvar() +"\n";
					(yyval.info)->code += "\tCMP AX , 0\n";
					(yyval.info)->code += "\tJE " + string(label1) +"\n";
					(yyval.info)->code += "\tMOV " + string(t) + ",1\n";
					(yyval.info)->code += "\tJMP " + string(label2) + "\n";
					(yyval.info)->code += string(label1) + ":\n" ;
					(yyval.info)->code += "\tMOV " + string(t) + ",0\n";
					(yyval.info)->code += string(label2) + ":\n";
					(yyval.info)->setASMvar(t);
					vars.push_back(t);
				}
				else if((yyvsp[-1].info)->getName()=="||"){
					(yyval.info)->code += "\tMOV AX," + (yyvsp[-2].info)->getASMvar() +"\n";
					(yyval.info)->code += "\tCMP AX , 0\n";
				 	(yyval.info)->code += "\tJNE " + string(label1) +"\n";
					(yyval.info)->code += "\tMOV AX," + (yyvsp[0].info)->getASMvar() +"\n";
					(yyval.info)->code += "\tCMP AX , 0\n";
					(yyval.info)->code += "\tJNE " + string(label1) +"\n";
					(yyval.info)->code += "\tMOV " + string(t) + ",0\n";
					(yyval.info)->code += "\tJMP " + string(label2) + "\n";
					(yyval.info)->code += string(label1) + ":\n" ;
					(yyval.info)->code += "\tMOV " + string(t) + ",1\n";
					(yyval.info)->code += string(label2) + ":\n";
					(yyval.info)->setASMvar(t);
					vars.push_back(t);
				}
				//delete $3;
			}
			

		}
#line 2226 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 726 "parser.y" /* yacc.c:1646  */
    {
					
					(yyval.info) = (yyvsp[0].info);
				}
#line 2235 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 731 "parser.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line no %d: rel_expression	: simple_expression RELOP simple_expression\n\n", line_count);
			(yyval.info)=(yyvsp[-2].info);
			(yyval.info)->code+=(yyvsp[0].info)->code;
			(yyval.info)->code+="\tMOV AX," + (yyvsp[-2].info)->getASMvar()+"\n";
			(yyval.info)->code+="\tCMP AX, " + (yyvsp[0].info)->getASMvar()+"\n";
			(yyval.info)->setType("VAR");
			(yyval.info)->setVarType("INT");
			if((yyvsp[-2].info)->getVarType() != (yyvsp[0].info)->getVarType()){
				fprintf(fp3,"Error at line no %d: Type Mismatch\n\n", line_count);
				errors++;
			}
			else{
				char *t=newTemp();
				char *label1=newLabel();
				char *label2=newLabel();
				if((yyvsp[-1].info)->getName()=="<"){
					(yyval.info)->code+="\tJL " + string(label1)+"\n";
				}
				else if((yyvsp[-1].info)->getName()=="<="){
					(yyval.info)->code+="\tJLE " + string(label1)+"\n";
				}
				else if((yyvsp[-1].info)->getName()==">"){
					(yyval.info)->code+="\tJG " + string(label1)+"\n";
				}
				else if((yyvsp[-1].info)->getName()==">="){
					(yyval.info)->code+="\tJGE " + string(label1)+"\n";
				}
				else if((yyvsp[-1].info)->getName()=="=="){
					(yyval.info)->code+="\tJE " + string(label1)+"\n";
				}
				else if((yyvsp[-1].info)->getName()=="!="){
					(yyval.info)->code+="\tJNE " + string(label1)+"\n";
				}
				(yyval.info)->code+="\tMOV "+string(t) +",0\n";
				(yyval.info)->code+="\tJMP "+string(label2) +"\n";
				(yyval.info)->code+=string(label1)+":\n";
				(yyval.info)->code+= "\tMOV "+string(t)+",1\n";
				(yyval.info)->code+=string(label2)+":\n";
				(yyval.info)->setASMvar(t);
				vars.push_back(t);
				//delete $3;
			}
		}
#line 2284 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 778 "parser.y" /* yacc.c:1646  */
    {
						
						(yyval.info) = (yyvsp[0].info);
					}
#line 2293 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 783 "parser.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line no %d: simple_expression : simple_expression ADDOP term\n\n", line_count);
			
			(yyval.info)=(yyvsp[-2].info);
			(yyval.info)->code+=(yyvsp[0].info)->code;
			
			if((yyvsp[-2].info)->getVarType() == "FLOAT" || (yyvsp[0].info)->getVarType() == "FLOAT"){
				(yyval.info)->setType("VAR");
				(yyval.info)->setVarType("FLOAT");
				if((yyvsp[-1].info)->getName()=="+"){
					char* t = newTemp();
					(yyval.info)->code += "\tMOV AX," + (yyvsp[-2].info)->getASMvar() + "\n";
					(yyval.info)->code += "\tADD AX," + (yyvsp[0].info)->getASMvar() + "\n";
					(yyval.info)->code += "\tMOV " + string(t) +" , AX\n";
					(yyval.info)->setASMvar(string(t));
					vars.push_back(t);
				}
				else if((yyvsp[-1].info)->getName() == "-"){
					char* t = newTemp();
					(yyval.info)->code += "\tMOV AX," + (yyvsp[-2].info)->getASMvar() + "\n";
					(yyval.info)->code += "\tSUB AX, " + (yyvsp[0].info)->getASMvar() + "\n";
					(yyval.info)->code += "\tMOV " + string(t) +",AX\n";
					(yyval.info)->setASMvar(string(t));
					vars.push_back(t);
				}
			}
			else{
				(yyval.info)->setType("VAR");
				(yyval.info)->setVarType("INT");
				if((yyvsp[-1].info)->getName()=="+"){
					char* t = newTemp();
					(yyval.info)->code += "\tMOV AX," + (yyvsp[-2].info)->getASMvar() + "\n";
					(yyval.info)->code += "\tADD AX, " + (yyvsp[0].info)->getASMvar() + "\n";
					(yyval.info)->code += "\tMOV " + string(t) +",AX\n";
					(yyval.info)->setASMvar(string(t));
					vars.push_back(t);
				}
				else if((yyvsp[-1].info)->getName() == "-"){
					char* t = newTemp();
					(yyval.info)->code += "\tMOV AX," + (yyvsp[-2].info)->getASMvar() + "\n";
					(yyval.info)->code += "\tSUB AX, " + (yyvsp[0].info)->getASMvar() + "\n";
					(yyval.info)->code += "\tMOV " + string(t) +",AX\n";
					(yyval.info)->setASMvar(string(t));
					vars.push_back(t);
				}
			}
			//$$->code += $1->code;
			//delete $3;
		}
#line 2347 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 835 "parser.y" /* yacc.c:1646  */
    {
			
			(yyval.info) = (yyvsp[0].info);
		}
#line 2356 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 840 "parser.y" /* yacc.c:1646  */
    {
		fprintf(fp3,"At line no %d: term :	term MULOP unary_expression\n\n", line_count);
		
		(yyval.info)=(yyvsp[-2].info);
		(yyval.info)->code += (yyvsp[0].info)->code;
		(yyval.info)->code += "\tMOV AX,"+ (yyvsp[-2].info)->getASMvar()+"\n";
		(yyval.info)->code += "\tMOV BX,"+ (yyvsp[0].info)->getASMvar() +"\n";
		
		char *t=newTemp();
		
		if((yyvsp[-1].info)->getName() == "*"){
			if((yyvsp[-2].info)->getVarType() == "FLOAT" || (yyvsp[0].info)->getVarType() == "FLOAT"){
				(yyval.info)->setVarType("FLOAT");
				(yyval.info)->setType("VAR");
			}
			(yyval.info)->code += "\tMUL BX\n";
			(yyval.info)->code += "\tMOV "+ string(t) + ",AX\n";
			(yyval.info)->setASMvar(string(t));
			vars.push_back(t);
		}
		else if((yyvsp[-1].info)->getName() == "/"){
			if((yyvsp[-2].info)->getVarType() == "FLOAT" || (yyvsp[0].info)->getVarType() == "FLOAT"){
				(yyval.info)->setVarType("FLOAT");
				(yyval.info)->setType("VAR");
			}
			(yyval.info)->code += "\tXOR DX , DX\n";
			(yyval.info)->code += "\tDIV BX\n";
			(yyval.info)->code += "\tMOV "+ string(t) + ",AX\n";
			(yyval.info)->setASMvar(string(t));
			vars.push_back(t);
		}
		else if((yyvsp[-1].info)->getName() == "%"){
			if((yyvsp[-2].info)->getVarType() == "FLOAT" || (yyvsp[0].info)->getVarType() == "FLOAT"){
				fprintf(fp3,"Error at line no %d: Integer operand on modulus operator\n\n", line_count, (yyvsp[-2].info)->getName().c_str());
				errors++;
			}
			(yyval.info)->setVarType("FLOAT");
			(yyval.info)->setType("VAR");
			(yyval.info)->code += "\tXOR DX , DX\n";
			(yyval.info)->code += "\tDIV BX\n";
			(yyval.info)->code += "\tMOV "+ string(t) + ",AX\n";
			(yyval.info)->setASMvar(string(t));
			vars.push_back(t);
		}
	}
#line 2406 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 888 "parser.y" /* yacc.c:1646  */
    {
					//fprintf(fp2,"At line no %d: unary_expression : ADDOP unary_expression\n\n", line_count);
					if((yyvsp[-1].info)->getName() == "+"){
						(yyval.info) = (yyvsp[0].info);
					}
					else if((yyvsp[-1].info)->getName() == "-"){
						(yyval.info) = (yyvsp[0].info);
						(yyval.info)->code += "\tMOV AX," + (yyvsp[0].info)->getASMvar() + "\n";
						(yyval.info)->code += "\tNEG AX\n";
						(yyval.info)->code += "\tMOV " + (yyvsp[0].info)->getASMvar() + ",AX\n";
					}
				}
#line 2423 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 901 "parser.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line no %d: unary_expression : NOT unary_expression\n\n", line_count);
			(yyval.info) = (yyvsp[0].info);
			char *t=newTemp();
			(yyval.info)->code="\tMOV AX," + (yyvsp[0].info)->getASMvar() + "\n";
			(yyval.info)->code+="\tNOT AX\n";
			(yyval.info)->code+="\tMOV "+string(t)+",AX\n";
			(yyval.info)->setASMvar(string(t));
			vars.push_back(t);
		}
#line 2438 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 912 "parser.y" /* yacc.c:1646  */
    {
			
			(yyval.info) = (yyvsp[0].info);
		}
#line 2447 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 919 "parser.y" /* yacc.c:1646  */
    {
			//fprintf(fp2,"At line no %d: factor : variable\n\n", line_count);
			(yyval.info) = (yyvsp[0].info);
			if((yyvsp[0].info)->getType() == "ARRAY"){
				char *t = newTemp();
				(yyval.info)->code+="\tMOV AX," + (yyvsp[0].info)->getASMvar() + "[BX]\n";
				(yyval.info)->code+= "\tMOV " + string(t) + ",AX\n";
				(yyval.info)->setASMvar(string(t));
				vars.push_back(t);
			}
			else{

			}
		}
#line 2466 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 934 "parser.y" /* yacc.c:1646  */
    {
			
			
			SymbolInfo *t = symbolTable.lookUp((yyvsp[-3].info)->getName());
			if(t == NULL) {
				fprintf(fp3,"Error at line no %d: Undeclared function %s \n\n", line_count, (yyvsp[-3].info)->getName().c_str());
				errors++;
			}
			else{
				if(t->getFuncRetType() == "VOID"){
					fprintf(fp3,"Error at line no %d: void function %s called as a part of expression\n\n", line_count, (yyvsp[-3].info)->getName().c_str());
					errors++;
				}
				else{
					(yyval.info) = t;
					(yyval.info)->code += "\tCALL " + (yyval.info)->getASMvar() + "\n";
				}
			}

	}
#line 2491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 955 "parser.y" /* yacc.c:1646  */
    {
			
			//fprintf(fp2,"At line no %d: factor : LPAREN expression RPAREN\n\n", line_count);
			(yyval.info) = (yyvsp[-1].info);
	}
#line 2501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 961 "parser.y" /* yacc.c:1646  */
    {
			
			(yyvsp[0].info)->setVarType("INT");
			(yyval.info) = (yyvsp[0].info);
	}
#line 2511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 967 "parser.y" /* yacc.c:1646  */
    {
			
			(yyvsp[0].info)->setVarType("FLOAT");
			(yyval.info) = (yyvsp[0].info);
	}
#line 2521 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 973 "parser.y" /* yacc.c:1646  */
    {
			
			(yyval.info) = (yyvsp[-1].info);
			(yyval.info)->code += "\tMOV AX," + (yyval.info)->getASMvar()+ "\n";
			(yyval.info)->code += "\tINC AX\n";
			(yyval.info)->code += "\tMOV " + (yyval.info)->getASMvar() + ",AX\n";
	}
#line 2533 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 981 "parser.y" /* yacc.c:1646  */
    {
			
			(yyval.info) = (yyvsp[-1].info);
			(yyval.info)->code += "\tMOV AX," + (yyval.info)->getASMvar()+ "\n";
			(yyval.info)->code += "\tDEC AX\n";
			(yyval.info)->code += "\tMOV " + (yyval.info)->getASMvar() + ",AX\n"; 
	}
#line 2545 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 991 "parser.y" /* yacc.c:1646  */
    {
					
				}
#line 2553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 995 "parser.y" /* yacc.c:1646  */
    {
				(yyval.info) = new SymbolInfo();
			}
#line 2561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1001 "parser.y" /* yacc.c:1646  */
    {
				
			}
#line 2569 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1005 "parser.y" /* yacc.c:1646  */
    {
			
		}
#line 2577 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2581 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1011 "parser.y" /* yacc.c:1906  */

int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	fp2= fopen(argv[2],"w");
	fclose(fp2);
	fp3= fopen(argv[3],"w");
	fclose(fp3);
	
	fp2= fopen(argv[2],"a");
	fp3= fopen(argv[3],"a");
	

	yyin=fp;
	yyparse();
	
	//symbolTable.printAll();

	fprintf(fp3,"Total Lines : %d \n\n", line_count);
	fprintf(fp3,"Total Errors : %d \n\n", errors);

	fclose(fp2);
	fclose(fp3);

	optimization();
	
	return 0;
}

