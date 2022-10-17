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
#line 1 "l22_parser.y"

//-- don't change *any* of these: if you do, you'll break the compiler.
#include <algorithm>
#include <memory>
#include <cstring>
#include <cdk/compiler.h>
#include <cdk/types/types.h>
#include ".auto/all_nodes.h"
#define LINE                         compiler->scanner()->lineno()
#define yylex()                      compiler->scanner()->scan()
#define yyerror(compiler, s)         compiler->scanner()->error(s)
//-- don't change *any* of these --- END!

#define NIL (new cdk::nil_node(LINE))

#line 87 "l22_parser.tab.c"

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

#include "l22_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tINTEGER = 3,                   /* tINTEGER  */
  YYSYMBOL_tFOREIGN = 4,                   /* tFOREIGN  */
  YYSYMBOL_tUSE = 5,                       /* tUSE  */
  YYSYMBOL_tPUBLIC = 6,                    /* tPUBLIC  */
  YYSYMBOL_tPRIVATE = 7,                   /* tPRIVATE  */
  YYSYMBOL_tREAL = 8,                      /* tREAL  */
  YYSYMBOL_tIDENTIFIER = 9,                /* tIDENTIFIER  */
  YYSYMBOL_tSTRING = 10,                   /* tSTRING  */
  YYSYMBOL_tBEGIN = 11,                    /* tBEGIN  */
  YYSYMBOL_tEND = 12,                      /* tEND  */
  YYSYMBOL_tINT_TYPE = 13,                 /* tINT_TYPE  */
  YYSYMBOL_tREAL_TYPE = 14,                /* tREAL_TYPE  */
  YYSYMBOL_tSTRING_TYPE = 15,              /* tSTRING_TYPE  */
  YYSYMBOL_tVOID_TYPE = 16,                /* tVOID_TYPE  */
  YYSYMBOL_tVAR = 17,                      /* tVAR  */
  YYSYMBOL_tWHILE = 18,                    /* tWHILE  */
  YYSYMBOL_tDO = 19,                       /* tDO  */
  YYSYMBOL_tIF = 20,                       /* tIF  */
  YYSYMBOL_tTHEN = 21,                     /* tTHEN  */
  YYSYMBOL_tELSE = 22,                     /* tELSE  */
  YYSYMBOL_tELIF = 23,                     /* tELIF  */
  YYSYMBOL_tWRITE = 24,                    /* tWRITE  */
  YYSYMBOL_tWRITELN = 25,                  /* tWRITELN  */
  YYSYMBOL_tINPUT = 26,                    /* tINPUT  */
  YYSYMBOL_tSTOP = 27,                     /* tSTOP  */
  YYSYMBOL_tAGAIN = 28,                    /* tAGAIN  */
  YYSYMBOL_tRETURN = 29,                   /* tRETURN  */
  YYSYMBOL_tRETURN_TYPE = 30,              /* tRETURN_TYPE  */
  YYSYMBOL_tSIZEOF = 31,                   /* tSIZEOF  */
  YYSYMBOL_tNULL = 32,                     /* tNULL  */
  YYSYMBOL_tNOT = 33,                      /* tNOT  */
  YYSYMBOL_tUNARY = 34,                    /* tUNARY  */
  YYSYMBOL_tCHANGE = 35,                   /* tCHANGE  */
  YYSYMBOL_tWITH = 36,                     /* tWITH  */
  YYSYMBOL_tDOTS = 37,                     /* tDOTS  */
  YYSYMBOL_tSWEEP = 38,                    /* tSWEEP  */
  YYSYMBOL_39_ = 39,                       /* '='  */
  YYSYMBOL_40_ = 40,                       /* '|'  */
  YYSYMBOL_41_ = 41,                       /* '&'  */
  YYSYMBOL_tEQ = 42,                       /* tEQ  */
  YYSYMBOL_tNE = 43,                       /* tNE  */
  YYSYMBOL_44_ = 44,                       /* '<'  */
  YYSYMBOL_45_ = 45,                       /* '>'  */
  YYSYMBOL_tGE = 46,                       /* tGE  */
  YYSYMBOL_tLE = 47,                       /* tLE  */
  YYSYMBOL_48_ = 48,                       /* '+'  */
  YYSYMBOL_49_ = 49,                       /* '-'  */
  YYSYMBOL_50_ = 50,                       /* '*'  */
  YYSYMBOL_51_ = 51,                       /* '/'  */
  YYSYMBOL_52_ = 52,                       /* '%'  */
  YYSYMBOL_53_ = 53,                       /* '('  */
  YYSYMBOL_54_ = 54,                       /* '['  */
  YYSYMBOL_55_ = 55,                       /* ';'  */
  YYSYMBOL_56_ = 56,                       /* ')'  */
  YYSYMBOL_57_ = 57,                       /* ':'  */
  YYSYMBOL_58_ = 58,                       /* '@'  */
  YYSYMBOL_59_ = 59,                       /* ','  */
  YYSYMBOL_60_ = 60,                       /* ']'  */
  YYSYMBOL_61_ = 61,                       /* '{'  */
  YYSYMBOL_62_ = 62,                       /* '}'  */
  YYSYMBOL_63_ = 63,                       /* '?'  */
  YYSYMBOL_YYACCEPT = 64,                  /* $accept  */
  YYSYMBOL_file = 65,                      /* file  */
  YYSYMBOL_program = 66,                   /* program  */
  YYSYMBOL_decls = 67,                     /* decls  */
  YYSYMBOL_decl = 68,                      /* decl  */
  YYSYMBOL_vardecl = 69,                   /* vardecl  */
  YYSYMBOL_fundecl = 70,                   /* fundecl  */
  YYSYMBOL_fun_def = 71,                   /* fun_def  */
  YYSYMBOL_fun_call = 72,                  /* fun_call  */
  YYSYMBOL_vars = 73,                      /* vars  */
  YYSYMBOL_var = 74,                       /* var  */
  YYSYMBOL_type = 75,                      /* type  */
  YYSYMBOL_type_void = 76,                 /* type_void  */
  YYSYMBOL_type_func = 77,                 /* type_func  */
  YYSYMBOL_args = 78,                      /* args  */
  YYSYMBOL_block = 79,                     /* block  */
  YYSYMBOL_instrs = 80,                    /* instrs  */
  YYSYMBOL_instr = 81,                     /* instr  */
  YYSYMBOL_block_instr = 82,               /* block_instr  */
  YYSYMBOL_elif = 83,                      /* elif  */
  YYSYMBOL_exprs = 84,                     /* exprs  */
  YYSYMBOL_expr = 85,                      /* expr  */
  YYSYMBOL_block_expr = 86,                /* block_expr  */
  YYSYMBOL_lval = 87,                      /* lval  */
  YYSYMBOL_string = 88                     /* string  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 81 "l22_parser.y"

//-- The rules below will be included in yyparse, the main parsing function.

#line 213 "l22_parser.tab.c"


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
#define YYFINAL  33
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   948

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  115
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  259

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


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
       2,     2,     2,     2,     2,     2,     2,    52,    41,     2,
      53,    56,    50,    48,    59,    49,     2,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    57,    55,
      44,    39,    45,    63,    58,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    60,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    61,    40,    62,     2,     2,     2,     2,
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
      35,    36,    37,    38,    42,    43,    46,    47
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    92,    92,    93,   101,   108,   109,   119,   120,   123,
     124,   125,   126,   128,   130,   132,   133,   134,   137,   138,
     139,   141,   142,   143,   145,   146,   155,   156,   157,   158,
     164,   165,   167,   168,   170,   171,   179,   180,   187,   195,
     196,   197,   198,   200,   201,   204,   208,   209,   210,   211,
     214,   215,   223,   224,   225,   232,   233,   234,   239,   250,
     251,   252,   253,   254,   255,   256,   258,   259,   260,   261,
     266,   267,   269,   271,   273,   276,   277,   278,   286,   287,
     288,   289,   297,   298,   299,   300,   302,   304,   306,   307,
     308,   309,   310,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   322,   323,   325,   326,   327,   328,   329,   331,
     335,   336,   339,   340,   343,   344
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
  "\"end of file\"", "error", "\"invalid token\"", "tINTEGER", "tFOREIGN",
  "tUSE", "tPUBLIC", "tPRIVATE", "tREAL", "tIDENTIFIER", "tSTRING",
  "tBEGIN", "tEND", "tINT_TYPE", "tREAL_TYPE", "tSTRING_TYPE",
  "tVOID_TYPE", "tVAR", "tWHILE", "tDO", "tIF", "tTHEN", "tELSE", "tELIF",
  "tWRITE", "tWRITELN", "tINPUT", "tSTOP", "tAGAIN", "tRETURN",
  "tRETURN_TYPE", "tSIZEOF", "tNULL", "tNOT", "tUNARY", "tCHANGE", "tWITH",
  "tDOTS", "tSWEEP", "'='", "'|'", "'&'", "tEQ", "tNE", "'<'", "'>'",
  "tGE", "tLE", "'+'", "'-'", "'*'", "'/'", "'%'", "'('", "'['", "';'",
  "')'", "':'", "'@'", "','", "']'", "'{'", "'}'", "'?'", "$accept",
  "file", "program", "decls", "decl", "vardecl", "fundecl", "fun_def",
  "fun_call", "vars", "var", "type", "type_void", "type_func", "args",
  "block", "instrs", "instr", "block_instr", "elif", "exprs", "expr",
  "block_expr", "lval", "string", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-83)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     544,    75,   105,   384,   -44,   -83,   -83,   -83,   -83,    22,
     105,    51,   -83,   544,   -83,    26,   -83,   -83,    -2,    39,
     -83,    46,   118,    -1,     4,    94,   127,     5,   317,   139,
     113,    18,    33,   -83,   -83,   -83,   -83,   116,     9,   160,
     486,   119,   121,   -83,   486,   125,   132,   -83,   -83,   -83,
     -83,   100,   112,   486,   486,   -83,   -83,   -83,   486,   124,
     -83,   498,   486,   498,   498,   498,   486,   415,   130,   250,
     -83,   117,   123,   354,   869,    -7,   170,   -83,   486,   -83,
     -83,   486,   -83,   -38,   142,   -83,   147,   401,   498,   -83,
     869,   -83,     1,   486,   486,   869,   -83,   486,   486,   498,
     498,   134,   869,   -83,   134,   -83,   869,    19,   498,   543,
     696,   149,   589,   -83,   -83,   140,   784,   654,   114,   -83,
     133,   -83,   354,   -83,   498,   498,   498,   498,   498,   498,
     498,   498,   498,   498,   498,   498,   498,   434,   498,   486,
     -83,   -83,   869,   -83,   869,   -83,   105,   -83,   -83,   167,
     143,   141,    11,   486,   -83,   -83,   869,   -83,   869,   -83,
     801,   818,   486,   498,   835,   498,   498,   498,   148,   -83,
     -83,   -83,   -30,   -83,   -83,   883,   543,   894,   894,   523,
     523,   523,   523,   186,   186,   -26,   -26,   -26,   -83,    20,
     675,   869,   -83,   -83,   105,   173,   105,   -83,   -83,   189,
     188,   869,   -83,   -83,   614,   639,   733,   467,   -83,   -83,
     -83,    30,    69,   105,   -83,   -44,   -44,   498,   498,   498,
     -83,    56,   -44,   -44,    86,    87,   -83,   126,   751,   769,
     715,   -83,   -83,   -83,   -44,   -44,   -44,   162,   -83,   498,
     498,   486,   -83,   -83,   -83,   498,   869,   869,   564,   198,
     852,   498,   498,   199,   869,   869,   -44,   126,   -83
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,    39,    40,    41,    45,     0,
       0,     0,     2,     0,     5,     0,     8,    15,     0,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     3,     6,     7,    38,     0,     0,
       0,     0,    14,    13,     0,     0,     9,    82,    83,   112,
     114,     0,     0,     0,     0,   108,    62,    61,    64,     0,
      85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     109,     0,    55,    56,    65,    86,    84,     4,     0,    42,
      43,     0,    47,    50,     0,    49,     0,     0,     0,   110,
       0,    23,    86,     0,     0,    12,    20,     0,     0,     0,
       0,    59,    78,    80,    60,    74,    63,    86,     0,   101,
       0,     0,     0,   102,   103,     0,     0,     0,     0,    53,
       0,    52,     0,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     107,   115,    17,    25,    16,    24,     0,    46,    48,     0,
       0,    36,     0,     0,    22,    21,    11,    19,    10,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   104,
     106,    33,     0,    54,    57,    93,    94,   100,    99,    95,
      96,    97,    98,    88,    89,    90,    91,    92,    31,     0,
       0,    87,    73,    51,     0,     0,     0,    38,   111,     0,
       0,    79,    81,   105,     0,     0,     0,     0,    32,    30,
     113,     0,     0,     0,    37,     0,     0,     0,     0,     0,
      35,     0,     0,     0,     0,     0,    72,    70,     0,     0,
       0,    34,    27,    29,     0,     0,     0,     0,    71,     0,
       0,     0,    26,    28,    75,     0,    66,    67,     0,     0,
       0,     0,     0,     0,    68,    69,     0,    76,    77
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -83,   -83,   206,   194,   -12,   -83,   -83,   -14,   -83,    32,
     -82,     8,    -6,   -83,   -37,   347,   -54,   -83,   -83,   -31,
     -51,   -28,   154,    88,   -83
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    11,    12,    13,    14,    15,    16,    89,    70,   150,
      17,    18,    19,    20,    84,    29,    71,    72,    73,   238,
     101,   102,   103,   107,    76
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,    35,    86,   104,    32,   151,    38,    37,    42,    23,
      24,    27,    90,    43,    46,   120,    95,    28,    31,   123,
     197,   146,     5,     6,     7,     8,   208,   137,   138,   162,
     106,    30,   139,   109,   110,   112,   113,   114,   116,   117,
     153,    74,    38,    38,   105,    74,    83,    83,    38,    38,
     142,    33,   115,   144,    82,    38,   140,    35,   163,   116,
     117,    32,    38,    10,   140,    90,    90,   172,   174,   156,
     158,   160,   161,   115,    38,    31,   209,    39,    79,   162,
     164,    36,   140,    39,    21,    40,   189,   222,     5,     6,
       7,     8,    22,    80,    74,   152,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   193,
     190,   191,   231,    39,   151,   162,    75,    47,     5,     6,
       7,     8,    48,    49,    50,   191,   223,    41,    92,    10,
      38,    39,    92,    44,   201,   191,    45,   204,   205,   206,
      55,    92,    92,   234,   235,    59,    60,    61,   236,   237,
      92,    77,    78,    99,    83,    81,   221,    75,    93,    10,
      94,    75,    64,    65,    97,   100,    92,    87,    88,    92,
     171,    98,    68,     5,     6,     7,     8,   108,   122,   121,
     141,    92,    92,   118,   166,    92,    92,   147,   212,   228,
     229,   230,   148,   162,    91,   173,   168,   194,    96,   195,
     196,   207,   211,   213,   152,    85,    92,   225,   215,   216,
      75,   246,   247,   248,    10,   245,   111,   250,   252,    34,
     256,   224,    69,   254,   255,    92,   258,    92,   214,     0,
       0,     0,   143,     0,     0,   145,   134,   135,   136,   137,
     138,    92,     0,     0,     0,     0,     0,   154,   155,     0,
      92,   157,   159,    47,     1,     2,     3,     0,    48,    49,
      50,     0,     0,     5,     6,     7,     8,     9,    51,     0,
      52,     0,     0,     0,    53,    54,    55,    56,    57,    58,
       0,    59,    60,    61,     0,     0,    62,     0,    63,     0,
       0,     0,     0,   192,     0,    92,     0,     0,    64,    65,
       0,     0,     0,    66,    67,     0,     0,   198,    68,     0,
       0,     0,   119,     0,     0,     0,   202,     0,     0,     0,
      47,     1,     2,     3,     0,    48,    49,    50,     0,    92,
       5,     6,     7,     8,     9,    51,     0,    52,     0,     0,
       0,    53,    54,    55,    56,    57,    58,     0,    59,    60,
      61,     0,     0,    62,     0,    63,     0,    47,     0,     0,
       0,     0,    48,    49,    50,    64,    65,     0,     0,     0,
      66,    67,    51,     0,    52,    68,     0,     0,    53,    54,
      55,    56,    57,    58,     0,    59,    60,    61,     0,     0,
      62,     0,    63,    25,     0,   249,     0,     5,     6,     7,
       8,    26,    64,    65,    47,     0,     0,    66,    88,    48,
      49,    50,    68,     0,     5,     6,     7,     8,    47,     0,
       0,     0,     0,    48,    49,    50,     0,    55,     5,     6,
       7,     8,    59,    60,    61,     0,     0,    47,    10,     0,
       0,    55,    48,    49,    50,     0,    59,    60,    61,    64,
      65,     0,     0,     0,    87,    67,     0,   149,     0,    68,
      55,     0,     0,    64,    65,    59,    60,    61,    66,    67,
      47,     0,     0,    68,     0,    48,    49,    50,     0,     0,
       0,     0,    64,    65,     0,     0,     0,    87,    88,    47,
     188,     0,    68,    55,    48,    49,    50,     0,    59,    60,
      61,    47,     0,     0,     0,     0,    48,    49,    50,     0,
       0,     0,    55,     0,     0,    64,    65,    59,    60,    61,
      87,    88,     0,   220,    55,    68,     0,     0,     0,    59,
      60,    61,     0,     0,    64,    65,     0,     0,     0,    87,
      88,     0,     0,     0,    68,     0,    64,    65,     1,     2,
       3,    66,    88,     0,     0,     4,    68,     5,     6,     7,
       8,     9,   226,   227,     0,     0,     0,     0,     0,   232,
     233,   132,   133,   134,   135,   136,   137,   138,     0,     0,
       0,   242,   243,   244,   251,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,    10,     0,
       0,     0,     0,   257,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   167,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   217,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   218,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,     0,
       0,     0,     0,     0,   170,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
       0,   165,     0,     0,     0,   210,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   241,     0,     0,     0,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     219,     0,     0,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   239,     0,
       0,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   240,     0,     0,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,     0,
     169,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,     0,   199,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,     0,   200,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
       0,   203,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,     0,   253,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138
};

static const yytype_int16 yycheck[] =
{
      28,    13,    39,    54,    10,    87,    44,     9,     9,     1,
       2,     3,    40,     9,     9,    69,    44,    61,    10,    73,
       9,    59,    13,    14,    15,    16,    56,    53,    54,    59,
      58,     9,    39,    61,    62,    63,    64,    65,    66,    67,
      39,    69,    44,    44,    58,    73,    38,    39,    44,    44,
      78,     0,    66,    81,    45,    44,    63,    69,    39,    87,
      88,    67,    44,    54,    63,    93,    94,   118,   122,    97,
      98,    99,   100,    87,    44,    67,    56,    44,    60,    59,
     108,    55,    63,    44,     9,    39,   137,    57,    13,    14,
      15,    16,    17,    60,   122,    87,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   146,
     138,   139,    56,    44,   196,    59,    28,     3,    13,    14,
      15,    16,     8,     9,    10,   153,    57,     9,    40,    54,
      44,    44,    44,    39,   162,   163,     9,   165,   166,   167,
      26,    53,    54,    57,    57,    31,    32,    33,    22,    23,
      62,    12,    39,    53,   146,    39,   207,    69,    39,    54,
      39,    73,    48,    49,    39,    53,    78,    53,    54,    81,
      56,    39,    58,    13,    14,    15,    16,    53,    55,    62,
      10,    93,    94,    53,    35,    97,    98,    45,   194,   217,
     218,   219,    45,    59,    40,    62,    56,    30,    44,    56,
      59,    53,   194,    30,   196,    45,   118,   213,    19,    21,
     122,   239,   240,   241,    54,    53,    62,   245,    20,    13,
      21,   213,    28,   251,   252,   137,   257,   139,   196,    -1,
      -1,    -1,    78,    -1,    -1,    81,    50,    51,    52,    53,
      54,   153,    -1,    -1,    -1,    -1,    -1,    93,    94,    -1,
     162,    97,    98,     3,     4,     5,     6,    -1,     8,     9,
      10,    -1,    -1,    13,    14,    15,    16,    17,    18,    -1,
      20,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    -1,    -1,    36,    -1,    38,    -1,
      -1,    -1,    -1,   139,    -1,   207,    -1,    -1,    48,    49,
      -1,    -1,    -1,    53,    54,    -1,    -1,   153,    58,    -1,
      -1,    -1,    62,    -1,    -1,    -1,   162,    -1,    -1,    -1,
       3,     4,     5,     6,    -1,     8,     9,    10,    -1,   241,
      13,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      -1,    24,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    -1,    -1,    36,    -1,    38,    -1,     3,    -1,    -1,
      -1,    -1,     8,     9,    10,    48,    49,    -1,    -1,    -1,
      53,    54,    18,    -1,    20,    58,    -1,    -1,    24,    25,
      26,    27,    28,    29,    -1,    31,    32,    33,    -1,    -1,
      36,    -1,    38,     9,    -1,   241,    -1,    13,    14,    15,
      16,    17,    48,    49,     3,    -1,    -1,    53,    54,     8,
       9,    10,    58,    -1,    13,    14,    15,    16,     3,    -1,
      -1,    -1,    -1,     8,     9,    10,    -1,    26,    13,    14,
      15,    16,    31,    32,    33,    -1,    -1,     3,    54,    -1,
      -1,    26,     8,     9,    10,    -1,    31,    32,    33,    48,
      49,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,
      26,    -1,    -1,    48,    49,    31,    32,    33,    53,    54,
       3,    -1,    -1,    58,    -1,     8,     9,    10,    -1,    -1,
      -1,    -1,    48,    49,    -1,    -1,    -1,    53,    54,     3,
      56,    -1,    58,    26,     8,     9,    10,    -1,    31,    32,
      33,     3,    -1,    -1,    -1,    -1,     8,     9,    10,    -1,
      -1,    -1,    26,    -1,    -1,    48,    49,    31,    32,    33,
      53,    54,    -1,    56,    26,    58,    -1,    -1,    -1,    31,
      32,    33,    -1,    -1,    48,    49,    -1,    -1,    -1,    53,
      54,    -1,    -1,    -1,    58,    -1,    48,    49,     4,     5,
       6,    53,    54,    -1,    -1,    11,    58,    13,    14,    15,
      16,    17,   215,   216,    -1,    -1,    -1,    -1,    -1,   222,
     223,    48,    49,    50,    51,    52,    53,    54,    -1,    -1,
      -1,   234,   235,   236,    20,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    54,    -1,
      -1,    -1,    -1,   256,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    60,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    35,    -1,    -1,    -1,    60,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    36,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      37,    -1,    -1,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    37,    -1,
      -1,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    37,    -1,    -1,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      56,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    -1,    56,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    56,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    56,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    56,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,    11,    13,    14,    15,    16,    17,
      54,    65,    66,    67,    68,    69,    70,    74,    75,    76,
      77,     9,    17,    75,    75,     9,    17,    75,    61,    79,
       9,    75,    76,     0,    66,    68,    55,     9,    44,    44,
      39,     9,     9,     9,    39,     9,     9,     3,     8,     9,
      10,    18,    20,    24,    25,    26,    27,    28,    29,    31,
      32,    33,    36,    38,    48,    49,    53,    54,    58,    67,
      72,    80,    81,    82,    85,    87,    88,    12,    39,    60,
      60,    39,    45,    75,    78,    45,    78,    53,    54,    71,
      85,    86,    87,    39,    39,    85,    86,    39,    39,    53,
      53,    84,    85,    86,    84,    71,    85,    87,    53,    85,
      85,    86,    85,    85,    85,    71,    85,    85,    53,    62,
      80,    62,    55,    80,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    39,
      63,    10,    85,    86,    85,    86,    59,    45,    45,    56,
      73,    74,    75,    39,    86,    86,    85,    86,    85,    86,
      85,    85,    59,    39,    85,    35,    35,    30,    56,    56,
      60,    56,    84,    62,    80,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    56,    84,
      85,    85,    86,    78,    30,    56,    59,     9,    86,    56,
      56,    85,    86,    56,    85,    85,    85,    53,    56,    56,
      60,    75,    76,    30,    73,    19,    21,    30,    30,    37,
      56,    84,    57,    57,    75,    76,    79,    79,    85,    85,
      85,    56,    79,    79,    57,    57,    22,    23,    83,    37,
      37,    36,    79,    79,    79,    53,    85,    85,    85,    86,
      85,    20,    20,    56,    85,    85,    21,    79,    83
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    65,    65,    66,    67,    67,    68,    68,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    70,    70,
      70,    70,    70,    70,    70,    70,    71,    71,    71,    71,
      72,    72,    72,    72,    72,    72,    73,    73,    74,    75,
      75,    75,    75,    75,    75,    76,    77,    77,    77,    77,
      78,    78,    79,    79,    79,    80,    80,    80,    80,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      82,    82,    82,    82,    82,    83,    83,    83,    84,    84,
      84,    84,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      86,    86,    87,    87,    88,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     3,     1,     2,     2,     1,     3,
       5,     5,     4,     3,     3,     1,     4,     4,     5,     5,
       4,     5,     5,     4,     4,     4,     7,     6,     7,     6,
       4,     3,     4,     3,     6,     5,     1,     3,     2,     1,
       1,     1,     3,     3,     1,     1,     4,     3,     4,     3,
       1,     3,     3,     3,     4,     1,     1,     3,     2,     2,
       2,     1,     1,     2,     1,     1,     8,     8,    10,    10,
       6,     7,     6,     3,     2,     2,     6,     7,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     3,     4,     3,     2,     1,     1,
       1,     3,     1,     4,     1,     2
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
        yyerror (compiler, YY_("syntax error: cannot back up")); \
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
                  Kind, Value, compiler); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, std::shared_ptr<cdk::compiler> compiler)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (compiler);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, std::shared_ptr<cdk::compiler> compiler)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, compiler);
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
                 int yyrule, std::shared_ptr<cdk::compiler> compiler)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], compiler);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, compiler); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, std::shared_ptr<cdk::compiler> compiler)
{
  YY_USE (yyvaluep);
  YY_USE (compiler);
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
yyparse (std::shared_ptr<cdk::compiler> compiler)
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
  case 2: /* file: program  */
#line 92 "l22_parser.y"
                      { compiler->ast((yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node), nullptr)); }
#line 1471 "l22_parser.tab.c"
    break;

  case 3: /* file: decls program  */
#line 93 "l22_parser.y"
                      { compiler->ast((yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node), (yyvsp[-1].sequence)));      }
#line 1477 "l22_parser.tab.c"
    break;

  case 4: /* program: tBEGIN block tEND  */
#line 101 "l22_parser.y"
                             { (yyval.node) = new l22::program_node(LINE, (yyvsp[-1].block)); }
#line 1483 "l22_parser.tab.c"
    break;

  case 5: /* decls: decl  */
#line 108 "l22_parser.y"
                    { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node));     }
#line 1489 "l22_parser.tab.c"
    break;

  case 6: /* decls: decls decl  */
#line 109 "l22_parser.y"
                    { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node), (yyvsp[-1].sequence)); }
#line 1495 "l22_parser.tab.c"
    break;

  case 7: /* decl: vardecl ';'  */
#line 119 "l22_parser.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 1501 "l22_parser.tab.c"
    break;

  case 8: /* decl: fundecl  */
#line 120 "l22_parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1507 "l22_parser.tab.c"
    break;

  case 9: /* vardecl: tPUBLIC type tIDENTIFIER  */
#line 123 "l22_parser.y"
                                                { (yyval.node) = new l22::variable_declaration_node(LINE, tPUBLIC, (yyvsp[-1].type), *(yyvsp[0].s), nullptr);     delete (yyvsp[0].s); }
#line 1513 "l22_parser.tab.c"
    break;

  case 10: /* vardecl: tPUBLIC type tIDENTIFIER '=' expr  */
#line 124 "l22_parser.y"
                                                { (yyval.node) = new l22::variable_declaration_node(LINE, tPUBLIC, (yyvsp[-3].type), *(yyvsp[-2].s), (yyvsp[0].expression));          delete (yyvsp[-2].s); }
#line 1519 "l22_parser.tab.c"
    break;

  case 11: /* vardecl: tPUBLIC tVAR tIDENTIFIER '=' expr  */
#line 125 "l22_parser.y"
                                                { (yyval.node) = new l22::variable_declaration_node(LINE, tPUBLIC, nullptr, *(yyvsp[-2].s), (yyvsp[0].expression));  delete (yyvsp[-2].s); }
#line 1525 "l22_parser.tab.c"
    break;

  case 12: /* vardecl: tPUBLIC tIDENTIFIER '=' expr  */
#line 126 "l22_parser.y"
                                                { (yyval.node) = new l22::variable_declaration_node(LINE, tPUBLIC, nullptr, *(yyvsp[-2].s), (yyvsp[0].expression));  delete (yyvsp[-2].s); }
#line 1531 "l22_parser.tab.c"
    break;

  case 13: /* vardecl: tUSE type tIDENTIFIER  */
#line 128 "l22_parser.y"
                                                { (yyval.node) = new l22::variable_declaration_node(LINE, tUSE, (yyvsp[-1].type), *(yyvsp[0].s), nullptr);        delete (yyvsp[0].s); }
#line 1537 "l22_parser.tab.c"
    break;

  case 14: /* vardecl: tFOREIGN type tIDENTIFIER  */
#line 130 "l22_parser.y"
                                                { (yyval.node) = new l22::variable_declaration_node(LINE, tFOREIGN, (yyvsp[-1].type), *(yyvsp[0].s), nullptr);    delete (yyvsp[0].s); }
#line 1543 "l22_parser.tab.c"
    break;

  case 15: /* vardecl: var  */
#line 132 "l22_parser.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 1549 "l22_parser.tab.c"
    break;

  case 16: /* vardecl: type tIDENTIFIER '=' expr  */
#line 133 "l22_parser.y"
                                                { (yyval.node) = new l22::variable_declaration_node(LINE, tPRIVATE, (yyvsp[-3].type), *(yyvsp[-2].s), (yyvsp[0].expression));         delete (yyvsp[-2].s); }
#line 1555 "l22_parser.tab.c"
    break;

  case 17: /* vardecl: tVAR tIDENTIFIER '=' expr  */
#line 134 "l22_parser.y"
                                                { (yyval.node) = new l22::variable_declaration_node(LINE, tPRIVATE, nullptr, *(yyvsp[-2].s), (yyvsp[0].expression)); delete (yyvsp[-2].s); }
#line 1561 "l22_parser.tab.c"
    break;

  case 18: /* fundecl: tPUBLIC type tIDENTIFIER '=' block_expr  */
#line 137 "l22_parser.y"
                                                   { (yyval.node) = new l22::variable_declaration_node(LINE, tPUBLIC, (yyvsp[-3].type), *(yyvsp[-2].s), (yyvsp[0].expression));          delete (yyvsp[-2].s); }
#line 1567 "l22_parser.tab.c"
    break;

  case 19: /* fundecl: tPUBLIC tVAR tIDENTIFIER '=' block_expr  */
#line 138 "l22_parser.y"
                                                   { (yyval.node) = new l22::variable_declaration_node(LINE, tPUBLIC, (yyvsp[0].expression)->type(), *(yyvsp[-2].s), (yyvsp[0].expression));  delete (yyvsp[-2].s); }
#line 1573 "l22_parser.tab.c"
    break;

  case 20: /* fundecl: tPUBLIC tIDENTIFIER '=' block_expr  */
#line 139 "l22_parser.y"
                                                   { (yyval.node) = new l22::variable_declaration_node(LINE, tPUBLIC, (yyvsp[0].expression)->type(), *(yyvsp[-2].s), (yyvsp[0].expression));  delete (yyvsp[-2].s); }
#line 1579 "l22_parser.tab.c"
    break;

  case 21: /* fundecl: tFOREIGN type tIDENTIFIER '=' block_expr  */
#line 141 "l22_parser.y"
                                                   { (yyval.node) = new l22::variable_declaration_node(LINE, tFOREIGN, (yyvsp[-3].type), *(yyvsp[-2].s), (yyvsp[0].expression));         delete (yyvsp[-2].s); }
#line 1585 "l22_parser.tab.c"
    break;

  case 22: /* fundecl: tFOREIGN tVAR tIDENTIFIER '=' block_expr  */
#line 142 "l22_parser.y"
                                                   { (yyval.node) = new l22::variable_declaration_node(LINE, tFOREIGN, (yyvsp[0].expression)->type(), *(yyvsp[-2].s), (yyvsp[0].expression)); delete (yyvsp[-2].s); }
#line 1591 "l22_parser.tab.c"
    break;

  case 23: /* fundecl: tFOREIGN tIDENTIFIER '=' block_expr  */
#line 143 "l22_parser.y"
                                                   { (yyval.node) = new l22::variable_declaration_node(LINE, tFOREIGN, (yyvsp[0].expression)->type(), *(yyvsp[-2].s), (yyvsp[0].expression)); delete (yyvsp[-2].s); }
#line 1597 "l22_parser.tab.c"
    break;

  case 24: /* fundecl: type tIDENTIFIER '=' block_expr  */
#line 145 "l22_parser.y"
                                                   { (yyval.node) = new l22::variable_declaration_node(LINE, tPRIVATE, (yyvsp[-3].type), *(yyvsp[-2].s), (yyvsp[0].expression));         delete (yyvsp[-2].s); }
#line 1603 "l22_parser.tab.c"
    break;

  case 25: /* fundecl: tVAR tIDENTIFIER '=' block_expr  */
#line 146 "l22_parser.y"
                                                   { (yyval.node) = new l22::variable_declaration_node(LINE, tPRIVATE, (yyvsp[0].expression)->type(), *(yyvsp[-2].s), (yyvsp[0].expression)); delete (yyvsp[-2].s); }
#line 1609 "l22_parser.tab.c"
    break;

  case 26: /* fun_def: '(' vars ')' tRETURN_TYPE type ':' block  */
#line 155 "l22_parser.y"
                                                          { (yyval.expression) = new l22::function_definition_node(LINE, (yyvsp[-2].type), (yyvsp[-5].sequence) ,(yyvsp[0].block));                           }
#line 1615 "l22_parser.tab.c"
    break;

  case 27: /* fun_def: '(' ')' tRETURN_TYPE type ':' block  */
#line 156 "l22_parser.y"
                                                          { (yyval.expression) = new l22::function_definition_node(LINE, (yyvsp[-2].type), new cdk::sequence_node(LINE), (yyvsp[0].block)); }
#line 1621 "l22_parser.tab.c"
    break;

  case 28: /* fun_def: '(' vars ')' tRETURN_TYPE type_void ':' block  */
#line 157 "l22_parser.y"
                                                          { (yyval.expression) = new l22::function_definition_node(LINE, (yyvsp[-2].type), (yyvsp[-5].sequence) ,(yyvsp[0].block));                           }
#line 1627 "l22_parser.tab.c"
    break;

  case 29: /* fun_def: '(' ')' tRETURN_TYPE type_void ':' block  */
#line 158 "l22_parser.y"
                                                          { (yyval.expression) = new l22::function_definition_node(LINE, (yyvsp[-2].type), new cdk::sequence_node(LINE), (yyvsp[0].block)); }
#line 1633 "l22_parser.tab.c"
    break;

  case 30: /* fun_call: expr '(' exprs ')'  */
#line 164 "l22_parser.y"
                                           { (yyval.expression) = new l22::function_call_node(LINE, (yyvsp[-3].expression), (yyvsp[-1].sequence));      }
#line 1639 "l22_parser.tab.c"
    break;

  case 31: /* fun_call: expr '(' ')'  */
#line 165 "l22_parser.y"
                                           { (yyval.expression) = new l22::function_call_node(LINE, (yyvsp[-2].expression));          }
#line 1645 "l22_parser.tab.c"
    break;

  case 32: /* fun_call: '@' '(' exprs ')'  */
#line 167 "l22_parser.y"
                                           { (yyval.expression) = new l22::function_call_node(LINE, nullptr ,(yyvsp[-1].sequence)); }
#line 1651 "l22_parser.tab.c"
    break;

  case 33: /* fun_call: '@' '(' ')'  */
#line 168 "l22_parser.y"
                                           { (yyval.expression) = new l22::function_call_node(LINE, nullptr);     }
#line 1657 "l22_parser.tab.c"
    break;

  case 34: /* fun_call: '(' fun_def ')' '(' exprs ')'  */
#line 170 "l22_parser.y"
                                           { (yyval.expression) = new l22::function_call_node(LINE, (yyvsp[-4].expression), (yyvsp[-1].sequence));      }
#line 1663 "l22_parser.tab.c"
    break;

  case 35: /* fun_call: '(' fun_def ')' '(' ')'  */
#line 171 "l22_parser.y"
                                           { (yyval.expression) = new l22::function_call_node(LINE, (yyvsp[-3].expression));          }
#line 1669 "l22_parser.tab.c"
    break;

  case 36: /* vars: var  */
#line 179 "l22_parser.y"
                        { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node));       }
#line 1675 "l22_parser.tab.c"
    break;

  case 37: /* vars: var ',' vars  */
#line 180 "l22_parser.y"
                        { 
                          std::reverse((yyvsp[0].sequence)->nodes().begin(), (yyvsp[0].sequence)->nodes().end()); 
                          (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[-2].node), (yyvsp[0].sequence)); 
                          std::reverse((yyval.sequence)->nodes().begin(), (yyval.sequence)->nodes().end());
                        }
#line 1685 "l22_parser.tab.c"
    break;

  case 38: /* var: type tIDENTIFIER  */
#line 187 "l22_parser.y"
                        { (yyval.node) = new l22::variable_declaration_node(LINE, tPRIVATE, (yyvsp[-1].type), *(yyvsp[0].s), nullptr); delete (yyvsp[0].s); }
#line 1691 "l22_parser.tab.c"
    break;

  case 39: /* type: tINT_TYPE  */
#line 195 "l22_parser.y"
                                   { (yyval.type) = cdk::primitive_type::create(4, cdk::TYPE_INT);                                            }
#line 1697 "l22_parser.tab.c"
    break;

  case 40: /* type: tREAL_TYPE  */
#line 196 "l22_parser.y"
                                   { (yyval.type) = cdk::primitive_type::create(8, cdk::TYPE_DOUBLE);                                         }
#line 1703 "l22_parser.tab.c"
    break;

  case 41: /* type: tSTRING_TYPE  */
#line 197 "l22_parser.y"
                                   { (yyval.type) = cdk::primitive_type::create(4, cdk::TYPE_STRING);                                         }
#line 1709 "l22_parser.tab.c"
    break;

  case 42: /* type: '[' type ']'  */
#line 198 "l22_parser.y"
                                   { (yyval.type) = cdk::reference_type::create(4, (yyvsp[-1].type));                                                       }
#line 1715 "l22_parser.tab.c"
    break;

  case 43: /* type: '[' type_void ']'  */
#line 200 "l22_parser.y"
                                   { (yyval.type) = cdk::reference_type::create(4, (yyvsp[-1].type));                                                       }
#line 1721 "l22_parser.tab.c"
    break;

  case 44: /* type: type_func  */
#line 201 "l22_parser.y"
                                   { (yyval.type) = (yyvsp[0].type); }
#line 1727 "l22_parser.tab.c"
    break;

  case 45: /* type_void: tVOID_TYPE  */
#line 204 "l22_parser.y"
                                   { (yyval.type) = cdk::primitive_type::create(4, cdk::TYPE_VOID);                                           }
#line 1733 "l22_parser.tab.c"
    break;

  case 46: /* type_func: type '<' args '>'  */
#line 208 "l22_parser.y"
                                   { (yyval.type) = cdk::functional_type::create(*(yyvsp[-1].iotypes), (yyvsp[-3].type));                                                    }
#line 1739 "l22_parser.tab.c"
    break;

  case 47: /* type_func: type '<' '>'  */
#line 209 "l22_parser.y"
                                   { (yyval.type) = cdk::functional_type::create(*(new std::vector<std::shared_ptr<cdk::basic_type>>()), (yyvsp[-2].type)); }
#line 1745 "l22_parser.tab.c"
    break;

  case 48: /* type_func: type_void '<' args '>'  */
#line 210 "l22_parser.y"
                                   { (yyval.type) = cdk::functional_type::create(*(yyvsp[-1].iotypes), (yyvsp[-3].type));                                                    }
#line 1751 "l22_parser.tab.c"
    break;

  case 49: /* type_func: type_void '<' '>'  */
#line 211 "l22_parser.y"
                                   { (yyval.type) = cdk::functional_type::create(*(new std::vector<std::shared_ptr<cdk::basic_type>>()), (yyvsp[-2].type)); }
#line 1757 "l22_parser.tab.c"
    break;

  case 50: /* args: type  */
#line 214 "l22_parser.y"
                                   { (yyval.iotypes) = new std::vector<std::shared_ptr<cdk::basic_type>>(); (yyval.iotypes)->insert((yyval.iotypes)->begin(), (yyvsp[0].type));         }
#line 1763 "l22_parser.tab.c"
    break;

  case 51: /* args: type ',' args  */
#line 215 "l22_parser.y"
                                   { (yyval.iotypes) = (yyvsp[0].iotypes); (yyval.iotypes)->insert((yyval.iotypes)->begin(), (yyvsp[-2].type));                                                          }
#line 1769 "l22_parser.tab.c"
    break;

  case 52: /* block: '{' instrs '}'  */
#line 223 "l22_parser.y"
                                      { (yyval.block) = new l22::block_node(LINE, new cdk::sequence_node(LINE), (yyvsp[-1].sequence)); }
#line 1775 "l22_parser.tab.c"
    break;

  case 53: /* block: '{' decls '}'  */
#line 224 "l22_parser.y"
                                      { (yyval.block) = new l22::block_node(LINE, (yyvsp[-1].sequence), new cdk::sequence_node(LINE)); }
#line 1781 "l22_parser.tab.c"
    break;

  case 54: /* block: '{' decls instrs '}'  */
#line 225 "l22_parser.y"
                                      { (yyval.block) = new l22::block_node(LINE, (yyvsp[-2].sequence), (yyvsp[-1].sequence));                           }
#line 1787 "l22_parser.tab.c"
    break;

  case 55: /* instrs: instr  */
#line 232 "l22_parser.y"
                            { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node)); }
#line 1793 "l22_parser.tab.c"
    break;

  case 56: /* instrs: block_instr  */
#line 233 "l22_parser.y"
                            { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node)); }
#line 1799 "l22_parser.tab.c"
    break;

  case 57: /* instrs: instr ';' instrs  */
#line 234 "l22_parser.y"
                            { 
                              std::reverse((yyvsp[0].sequence)->nodes().begin(), (yyvsp[0].sequence)->nodes().end()); 
                              (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[-2].node), (yyvsp[0].sequence)); 
                              std::reverse((yyval.sequence)->nodes().begin(), (yyval.sequence)->nodes().end()); 
                            }
#line 1809 "l22_parser.tab.c"
    break;

  case 58: /* instrs: block_instr instrs  */
#line 239 "l22_parser.y"
                            { 
                              std::reverse((yyvsp[0].sequence)->nodes().begin(), (yyvsp[0].sequence)->nodes().end()); 
                              (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[-1].node), (yyvsp[0].sequence)); 
                              std::reverse((yyval.sequence)->nodes().begin(), (yyval.sequence)->nodes().end()); 
                            }
#line 1819 "l22_parser.tab.c"
    break;

  case 59: /* instr: tWRITE exprs  */
#line 250 "l22_parser.y"
                            { (yyval.node) = new l22::write_node(LINE, (yyvsp[0].sequence), false); }
#line 1825 "l22_parser.tab.c"
    break;

  case 60: /* instr: tWRITELN exprs  */
#line 251 "l22_parser.y"
                            { (yyval.node) = new l22::write_node(LINE, (yyvsp[0].sequence), true);  }
#line 1831 "l22_parser.tab.c"
    break;

  case 61: /* instr: tAGAIN  */
#line 252 "l22_parser.y"
                            { (yyval.node) = new l22::again_node(LINE);            }
#line 1837 "l22_parser.tab.c"
    break;

  case 62: /* instr: tSTOP  */
#line 253 "l22_parser.y"
                            { (yyval.node) = new l22::stop_node(LINE);             }
#line 1843 "l22_parser.tab.c"
    break;

  case 63: /* instr: tRETURN expr  */
#line 254 "l22_parser.y"
                            { (yyval.node) = new l22::return_node(LINE, (yyvsp[0].expression));       }
#line 1849 "l22_parser.tab.c"
    break;

  case 64: /* instr: tRETURN  */
#line 255 "l22_parser.y"
                            { (yyval.node) = new l22::return_node(LINE, nullptr);  }
#line 1855 "l22_parser.tab.c"
    break;

  case 65: /* instr: expr  */
#line 256 "l22_parser.y"
                            { (yyval.node) = new l22::evaluation_node(LINE, (yyvsp[0].expression));   }
#line 1861 "l22_parser.tab.c"
    break;

  case 66: /* instr: tWITH expr tCHANGE expr tRETURN_TYPE expr tDOTS expr  */
#line 258 "l22_parser.y"
                                                                      { (yyval.node) = new l22::with_change_node(LINE, (yyvsp[-6].expression), (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1867 "l22_parser.tab.c"
    break;

  case 67: /* instr: tWITH block_expr tCHANGE expr tRETURN_TYPE expr tDOTS expr  */
#line 259 "l22_parser.y"
                                                                      { (yyval.node) = new l22::with_change_node(LINE, (yyvsp[-6].expression), (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1873 "l22_parser.tab.c"
    break;

  case 68: /* instr: tSWEEP expr tRETURN_TYPE expr tDOTS expr tWITH expr tIF expr  */
#line 260 "l22_parser.y"
                                                                           { (yyval.node) = new l22::sweep_node(LINE, (yyvsp[-8].expression), (yyvsp[-6].expression), (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1879 "l22_parser.tab.c"
    break;

  case 69: /* instr: tSWEEP expr tRETURN_TYPE expr tDOTS expr tWITH block_expr tIF expr  */
#line 261 "l22_parser.y"
                                                                           { (yyval.node) = new l22::sweep_node(LINE, (yyvsp[-8].expression), (yyvsp[-6].expression), (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1885 "l22_parser.tab.c"
    break;

  case 70: /* block_instr: tIF '(' expr ')' tTHEN block  */
#line 266 "l22_parser.y"
                                                   { (yyval.node) = new l22::if_node(LINE, (yyvsp[-3].expression), (yyvsp[0].block));          }
#line 1891 "l22_parser.tab.c"
    break;

  case 71: /* block_instr: tIF '(' expr ')' tTHEN block elif  */
#line 267 "l22_parser.y"
                                                   { (yyval.node) = new l22::if_else_node(LINE, (yyvsp[-4].expression), (yyvsp[-1].block), (yyvsp[0].node)); }
#line 1897 "l22_parser.tab.c"
    break;

  case 72: /* block_instr: tWHILE '(' expr ')' tDO block  */
#line 269 "l22_parser.y"
                                                   { (yyval.node) = new l22::while_node(LINE, (yyvsp[-3].expression), (yyvsp[0].block));       }
#line 1903 "l22_parser.tab.c"
    break;

  case 73: /* block_instr: lval '=' block_expr  */
#line 271 "l22_parser.y"
                                                   { (yyval.node) = new cdk::assignment_node(LINE, (yyvsp[-2].lvalue), (yyvsp[0].expression));  }
#line 1909 "l22_parser.tab.c"
    break;

  case 74: /* block_instr: tRETURN fun_def  */
#line 273 "l22_parser.y"
                                                   { (yyval.node) = new l22::return_node(LINE, (yyvsp[0].expression));          }
#line 1915 "l22_parser.tab.c"
    break;

  case 75: /* elif: tELSE block  */
#line 276 "l22_parser.y"
                                                   { (yyval.node) = (yyvsp[0].block);                                      }
#line 1921 "l22_parser.tab.c"
    break;

  case 76: /* elif: tELIF '(' expr ')' tTHEN block  */
#line 277 "l22_parser.y"
                                                   { (yyval.node) = new l22::if_node(LINE, (yyvsp[-3].expression), (yyvsp[0].block));          }
#line 1927 "l22_parser.tab.c"
    break;

  case 77: /* elif: tELIF '(' expr ')' tTHEN block elif  */
#line 278 "l22_parser.y"
                                                   { (yyval.node) = new l22::if_else_node(LINE, (yyvsp[-4].expression), (yyvsp[-1].block), (yyvsp[0].node)); }
#line 1933 "l22_parser.tab.c"
    break;

  case 78: /* exprs: expr  */
#line 286 "l22_parser.y"
                             { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].expression));     }
#line 1939 "l22_parser.tab.c"
    break;

  case 79: /* exprs: exprs ',' expr  */
#line 287 "l22_parser.y"
                             { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].expression), (yyvsp[-2].sequence)); }
#line 1945 "l22_parser.tab.c"
    break;

  case 80: /* exprs: block_expr  */
#line 288 "l22_parser.y"
                             { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].expression));     }
#line 1951 "l22_parser.tab.c"
    break;

  case 81: /* exprs: exprs ',' block_expr  */
#line 289 "l22_parser.y"
                             { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].expression), (yyvsp[-2].sequence)); }
#line 1957 "l22_parser.tab.c"
    break;

  case 82: /* expr: tINTEGER  */
#line 297 "l22_parser.y"
                                       { (yyval.expression) = new cdk::integer_node(LINE, (yyvsp[0].i));        }
#line 1963 "l22_parser.tab.c"
    break;

  case 83: /* expr: tREAL  */
#line 298 "l22_parser.y"
                                       { (yyval.expression) = new cdk::double_node(LINE, (yyvsp[0].d));         }
#line 1969 "l22_parser.tab.c"
    break;

  case 84: /* expr: string  */
#line 299 "l22_parser.y"
                                       { (yyval.expression) = new cdk::string_node(LINE, (yyvsp[0].s));         }
#line 1975 "l22_parser.tab.c"
    break;

  case 85: /* expr: tNULL  */
#line 300 "l22_parser.y"
                                       { (yyval.expression) = new l22::nullptr_node(LINE);            }
#line 1981 "l22_parser.tab.c"
    break;

  case 86: /* expr: lval  */
#line 302 "l22_parser.y"
                                       { (yyval.expression) = new cdk::rvalue_node(LINE, (yyvsp[0].lvalue));         }
#line 1987 "l22_parser.tab.c"
    break;

  case 87: /* expr: lval '=' expr  */
#line 304 "l22_parser.y"
                                       { (yyval.expression) = new cdk::assignment_node(LINE, (yyvsp[-2].lvalue), (yyvsp[0].expression)); }
#line 1993 "l22_parser.tab.c"
    break;

  case 88: /* expr: expr '+' expr  */
#line 306 "l22_parser.y"
                                      { (yyval.expression) = new cdk::add_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));        }
#line 1999 "l22_parser.tab.c"
    break;

  case 89: /* expr: expr '-' expr  */
#line 307 "l22_parser.y"
                                      { (yyval.expression) = new cdk::sub_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));        }
#line 2005 "l22_parser.tab.c"
    break;

  case 90: /* expr: expr '*' expr  */
#line 308 "l22_parser.y"
                                      { (yyval.expression) = new cdk::mul_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));        }
#line 2011 "l22_parser.tab.c"
    break;

  case 91: /* expr: expr '/' expr  */
#line 309 "l22_parser.y"
                                      { (yyval.expression) = new cdk::div_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));        }
#line 2017 "l22_parser.tab.c"
    break;

  case 92: /* expr: expr '%' expr  */
#line 310 "l22_parser.y"
                                      { (yyval.expression) = new cdk::mod_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));        }
#line 2023 "l22_parser.tab.c"
    break;

  case 93: /* expr: expr '|' expr  */
#line 312 "l22_parser.y"
                                       { (yyval.expression) = new cdk::or_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));         }
#line 2029 "l22_parser.tab.c"
    break;

  case 94: /* expr: expr '&' expr  */
#line 313 "l22_parser.y"
                                       { (yyval.expression) = new cdk::and_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));        }
#line 2035 "l22_parser.tab.c"
    break;

  case 95: /* expr: expr '<' expr  */
#line 314 "l22_parser.y"
                                      { (yyval.expression) = new cdk::lt_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));         }
#line 2041 "l22_parser.tab.c"
    break;

  case 96: /* expr: expr '>' expr  */
#line 315 "l22_parser.y"
                                      { (yyval.expression) = new cdk::gt_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));         }
#line 2047 "l22_parser.tab.c"
    break;

  case 97: /* expr: expr tGE expr  */
#line 316 "l22_parser.y"
                                      { (yyval.expression) = new cdk::ge_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));         }
#line 2053 "l22_parser.tab.c"
    break;

  case 98: /* expr: expr tLE expr  */
#line 317 "l22_parser.y"
                                       { (yyval.expression) = new cdk::le_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));         }
#line 2059 "l22_parser.tab.c"
    break;

  case 99: /* expr: expr tNE expr  */
#line 318 "l22_parser.y"
                                      { (yyval.expression) = new cdk::ne_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));         }
#line 2065 "l22_parser.tab.c"
    break;

  case 100: /* expr: expr tEQ expr  */
#line 319 "l22_parser.y"
                                      { (yyval.expression) = new cdk::eq_node(LINE, (yyvsp[-2].expression), (yyvsp[0].expression));         }
#line 2071 "l22_parser.tab.c"
    break;

  case 101: /* expr: tNOT expr  */
#line 320 "l22_parser.y"
                                       { (yyval.expression) = new cdk::not_node(LINE, (yyvsp[0].expression));            }
#line 2077 "l22_parser.tab.c"
    break;

  case 102: /* expr: '+' expr  */
#line 322 "l22_parser.y"
                                       { (yyval.expression) = new l22::identity_node(LINE, (yyvsp[0].expression));       }
#line 2083 "l22_parser.tab.c"
    break;

  case 103: /* expr: '-' expr  */
#line 323 "l22_parser.y"
                                       { (yyval.expression) = new cdk::neg_node(LINE, (yyvsp[0].expression));            }
#line 2089 "l22_parser.tab.c"
    break;

  case 104: /* expr: '(' expr ')'  */
#line 325 "l22_parser.y"
                                       { (yyval.expression) = (yyvsp[-1].expression);                                     }
#line 2095 "l22_parser.tab.c"
    break;

  case 105: /* expr: tSIZEOF '(' expr ')'  */
#line 326 "l22_parser.y"
                                       { (yyval.expression) = new l22::sizeof_node(LINE, (yyvsp[-1].expression));         }
#line 2101 "l22_parser.tab.c"
    break;

  case 106: /* expr: '[' expr ']'  */
#line 327 "l22_parser.y"
                                       { (yyval.expression) = new l22::stack_alloc_node(LINE, (yyvsp[-1].expression));    }
#line 2107 "l22_parser.tab.c"
    break;

  case 107: /* expr: lval '?'  */
#line 328 "l22_parser.y"
                                       { (yyval.expression) = new l22::address_of_node(LINE, (yyvsp[-1].lvalue));     }
#line 2113 "l22_parser.tab.c"
    break;

  case 108: /* expr: tINPUT  */
#line 329 "l22_parser.y"
                                       { (yyval.expression) = new l22::input_node(LINE);              }
#line 2119 "l22_parser.tab.c"
    break;

  case 109: /* expr: fun_call  */
#line 331 "l22_parser.y"
                                       { (yyval.expression) = (yyvsp[0].expression);                                     }
#line 2125 "l22_parser.tab.c"
    break;

  case 110: /* block_expr: fun_def  */
#line 335 "l22_parser.y"
                                                   { (yyval.expression) = (yyvsp[0].expression);                                      }
#line 2131 "l22_parser.tab.c"
    break;

  case 111: /* block_expr: lval '=' block_expr  */
#line 336 "l22_parser.y"
                                                   { (yyval.expression) = new cdk::assignment_node(LINE, (yyvsp[-2].lvalue), (yyvsp[0].expression));  }
#line 2137 "l22_parser.tab.c"
    break;

  case 112: /* lval: tIDENTIFIER  */
#line 339 "l22_parser.y"
                                       { (yyval.lvalue) = new cdk::variable_node(LINE, (yyvsp[0].s));       }
#line 2143 "l22_parser.tab.c"
    break;

  case 113: /* lval: expr '[' expr ']'  */
#line 340 "l22_parser.y"
                                       { (yyval.lvalue) = new l22::index_node(LINE, (yyvsp[-3].expression), (yyvsp[-1].expression));      }
#line 2149 "l22_parser.tab.c"
    break;

  case 114: /* string: tSTRING  */
#line 343 "l22_parser.y"
                                       { (yyval.s) = (yyvsp[0].s); }
#line 2155 "l22_parser.tab.c"
    break;

  case 115: /* string: string tSTRING  */
#line 344 "l22_parser.y"
                                       { 
                                        (yyval.s) = new std::string(*(yyvsp[-1].s) + *(yyvsp[0].s)); 
                                        delete (yyvsp[-1].s); 
                                        delete (yyvsp[0].s); 
                                       }
#line 2165 "l22_parser.tab.c"
    break;


#line 2169 "l22_parser.tab.c"

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
      yyerror (compiler, YY_("syntax error"));
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
                      yytoken, &yylval, compiler);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, compiler);
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
  yyerror (compiler, YY_("memory exhausted"));
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
                  yytoken, &yylval, compiler);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, compiler);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 351 "l22_parser.y"
