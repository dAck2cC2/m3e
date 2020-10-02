/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison GLR parsers in C
   
      Copyright (C) 2002-2006, 2009-2010 Free Software Foundation, Inc.
   
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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.cc"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 1




/* Copy the first part of user declarations.  */

/* Line 171 of glr.c  */
#line 17 "hidl-gen_y.yy"


#include "AST.h"
#include "Annotation.h"
#include "ArrayType.h"
#include "CompoundType.h"
#include "ConstantExpression.h"
#include "DocComment.h"
#include "EnumType.h"
#include "Interface.h"
#include "Location.h"
#include "Method.h"
#include "RefType.h"
#include "Scope.h"
#include "TypeDef.h"
#include "VectorType.h"

#include "hidl-gen_y.h"

#include <android-base/logging.h>
#include <hidl-util/FQName.h>
#include <hidl-util/StringHelper.h>
#include <stdio.h>

#if defined(__linux__) // M3E:
#include <algorithm>
#endif

using namespace android;

extern int yylex(yy::parser::semantic_type*, yy::parser::location_type*, void*, Scope** const);

void enterScope(AST* /* ast */, Scope** scope, Scope* container) {
    CHECK(container->parent() == (*scope));
    *scope = container;
}

void leaveScope(AST* ast, Scope** scope) {
    CHECK((*scope) != ast->getRootScope());
    *scope = (*scope)->parent();
}

::android::Location convertYYLoc(const yy::parser::location_type &loc) {
    return ::android::Location(
            ::android::Position(*(loc.begin.filename), loc.begin.line, loc.begin.column),
            ::android::Position(*(loc.end.filename), loc.end.line, loc.end.column)
    );
}

bool isValidInterfaceField(const std::string& identifier, std::string *errorMsg) {
    static const std::vector<std::string> reserved({
        // Injected names to C++ interfaces by auto-generated code
        "isRemote", "descriptor", "hidlStaticBlock", "onTransact",
        "castFrom", "Proxy", "Stub", "getService",

        // Injected names to Java interfaces by auto-generated code
        "asInterface", "castFrom", "getService", "toString",

        // Inherited methods from IBase is detected in addMethod. Not added here
        // because we need hidl-gen to compile IBase.

        // Inherited names by interfaces from IInterface / IBinder
        "onAsBinder", "asBinder", "queryLocalInterface", "getInterfaceDescriptor", "isBinderAlive",
        "pingBinder", "dump", "transact", "checkSubclass", "attachObject", "findObject",
        "detachObject", "localBinder", "remoteBinder", "mImpl",

        // Inherited names from HidlInstrumentor
        "InstrumentationEvent", "configureInstrumentation", "registerInstrumentationCallbacks",
        "isInstrumentationLib", "mInstrumentationCal1lbacks", "mEnableInstrumentation",
        "mInstrumentationLibPackage", "mInterfaceName",

        // Collide with names in BsFoo
        "mImpl", "addOnewayTask", "mOnewayQueue",

        // Inherited names from Java IHwInterface
        "asBinder",
    });
    if (std::find(reserved.begin(), reserved.end(), identifier) != reserved.end()) {
        *errorMsg = identifier + " cannot be a name inside an interface";
        return false;
    }
    return true;
}

bool isValidStructField(const std::string& identifier, std::string *errorMsg) {
    static const std::vector<std::string> reserved({
        // Injected names to structs and unions by auto-generated code
        "readEmbeddedFromParcel", "writeEmbeddedToParcel", "readVectorFromParcel",
        "writeVectorToParcel", "writeEmbeddedToBlob",
    });
    if (std::find(reserved.begin(), reserved.end(), identifier) != reserved.end()) {
        *errorMsg = identifier + " cannot be a name inside an struct or union";
        return false;
    }
    return true;
}

bool isValidIdentifier(const std::string& identifier, std::string *errorMsg) {
    static const std::vector<std::string> keywords({
        "uint8_t", "uint16_t", "uint32_t", "uint64_t",
        "int8_t", "int16_t", "int32_t", "int64_t", "bool", "float", "double",
        "interface", "struct", "union", "string", "vec", "enum", "ref", "handle",
        "package", "import", "typedef", "generates", "oneway", "extends",
        "fmq_sync", "fmq_unsync",
    });
    static const std::vector<std::string> cppKeywords({
        "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit",
        "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch",
        "char", "char16_t", "char32_t", "class", "compl", "concept", "const", "constexpr",
        "const_cast", "continue", "decltype", "default", "delete", "do", "double",
        "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float",
        "for", "friend", "goto", "if", "inline", "int", "import", "long", "module", "mutable",
        "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq",
        "private", "protected", "public", "register", "reinterpret_cast", "requires", "return",
        "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct",
        "switch", "synchronized", "template", "this", "thread_local", "throw", "true", "try",
        "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void",
        "volatile", "wchar_t", "while", "xor", "xor_eq",
    });
    static const std::vector<std::string> javaKeywords({
        "abstract", "continue", "for", "new", "switch", "assert", "default", "goto", "package",
        "synchronized", "boolean", "do", "if", "private", "this", "break", "double",
        "implements", "protected", "throw", "byte", "else", "import", "public", "throws",
        "case", "enum", "instanceof", "return", "transient", "catch", "extends", "int",
        "short", "try", "char", "final", "interface", "static", "void", "class", "finally",
        "long", "strictfp", "volatile", "const", "float", "native", "super", "while",
    });
    static const std::vector<std::string> cppCollide({
        "size_t", "offsetof",
    });

    // errors
    if (std::find(keywords.begin(), keywords.end(), identifier) != keywords.end()) {
        *errorMsg = identifier + " is a HIDL keyword "
            "and is therefore not a valid identifier";
        return false;
    }
    if (std::find(cppKeywords.begin(), cppKeywords.end(), identifier) != cppKeywords.end()) {
        *errorMsg = identifier + " is a C++ keyword "
            "and is therefore not a valid identifier";
        return false;
    }
    if (std::find(javaKeywords.begin(), javaKeywords.end(), identifier) != javaKeywords.end()) {
        *errorMsg = identifier + " is a Java keyword "
            "and is therefore not a valid identifier";
        return false;
    }
    if (std::find(cppCollide.begin(), cppCollide.end(), identifier) != cppCollide.end()) {
        *errorMsg = identifier + " collides with reserved names in C++ code "
            "and is therefore not a valid identifier";
        return false;
    }
    if (StringHelper::StartsWith(identifier, "_hidl_")) {
        *errorMsg = identifier + " starts with _hidl_ "
            "and is therefore not a valid identifier";
        return false;
    }
    if (StringHelper::StartsWith(identifier, "hidl_")) {
        *errorMsg = identifier + " starts with hidl_ "
            "and is therefore not a valid identifier";
        return false;
    }
    if (StringHelper::EndsWith(identifier, "_cb")) {
        *errorMsg = identifier + " ends with _cb "
            "and is therefore not a valid identifier";
        return false;
    }

    return true;
}

// Return true if identifier is an acceptable name for an UDT.
bool isValidTypeName(const std::string& identifier, std::string *errorMsg) {
    if (!isValidIdentifier(identifier, errorMsg)) {
        return false;
    }

    if (identifier == "toString") {
        *errorMsg = identifier + " is not a valid type name";
        return false;
    }

    return true;
}



/* Line 171 of glr.c  */
#line 246 "hidl-gen_y.cpp"



#include "hidl-gen_y.h"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template,
   here we set the default value of $$ to a zeroed-out value.
   Since the default value is undefined, this behavior is
   technically correct.  */
static YYSTYPE yyval_default;

/* Copy the second part of user declarations.  */

/* Line 242 of glr.c  */
#line 280 "hidl-gen_y.cpp"

static void yyerror (yy::parser::location_type *yylocationp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope, const char* msg);

/* Line 242 of glr.c  */
#line 285 "hidl-gen_y.cpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#ifdef __cplusplus
   typedef bool yybool;
#else
   typedef unsigned char yybool;
#endif
#define yytrue 1
#define yyfalse 0

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(env) setjmp (env)
# define YYLONGJMP(env, val) longjmp (env, val)
#endif

/*-----------------.
| GCC extensions.  |
`-----------------*/

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5) \
      || (defined __STRICT_ANSI__ && __STRICT_ANSI__))
#  define __attribute__(Spec) /* empty */
# endif
#endif

#define YYOPTIONAL_LOC(Name) Name

#ifndef YYASSERT
# define YYASSERT(condition) ((void) ((condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   534

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  136
/* YYNRULES -- Number of states.  */
#define YYNSTATES  238
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 10
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,     2,     2,    41,    28,     2,
      48,    49,    39,    37,    50,    38,     2,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    23,    53,
      31,    51,    32,    22,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    55,    27,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,    26,    46,    43,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    24,    25,    29,
      30,    33,    34,    35,    36,    44,    45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     8,    12,    14,    17,    20,    22,    24,
      25,    28,    32,    33,    37,    39,    43,    47,    51,    53,
      57,    59,    63,    65,    69,    71,    75,    78,    80,    81,
      83,    85,    87,    89,    93,    95,    99,   103,   106,   107,
     110,   111,   114,   115,   118,   121,   122,   124,   127,   130,
     132,   135,   138,   141,   144,   147,   148,   156,   160,   162,
     164,   170,   174,   178,   182,   186,   190,   194,   198,   202,
     206,   210,   214,   218,   222,   226,   230,   234,   238,   242,
     245,   248,   251,   254,   258,   262,   265,   267,   269,   276,
     284,   295,   296,   298,   302,   305,   307,   309,   311,   312,
     317,   321,   322,   325,   328,   330,   332,   336,   339,   342,
     344,   346,   349,   350,   351,   353,   354,   360,   365,   368,
     370,   372,   376,   377,   379,   383,   387,   393,   395,   400,
     407,   412,   417,   419,   421,   423,   425
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const signed char yyrhs[] =
{
      57,     0,    -1,     3,    74,    76,    79,    -1,    74,    76,
      79,    -1,     3,    -1,    58,     3,    -1,    58,    46,    -1,
       8,    -1,     8,    -1,    -1,    61,    62,    -1,    47,     8,
      63,    -1,    -1,    48,    64,    49,    -1,    65,    -1,    64,
      50,    65,    -1,     8,    51,    66,    -1,     8,    51,    68,
      -1,    16,    -1,    52,    67,    46,    -1,    16,    -1,    67,
      50,    16,    -1,    86,    -1,    52,    69,    46,    -1,    86,
      -1,    69,    50,    86,    -1,     1,    53,    -1,    53,    -1,
      -1,     6,    -1,    60,    -1,    72,    -1,    14,    -1,    13,
       6,    71,    -1,     1,    -1,     9,     6,    71,    -1,     9,
      60,    71,    -1,     9,    70,    -1,    -1,    76,    75,    -1,
      -1,     5,    73,    -1,    -1,    78,    80,    -1,    78,    87,
      -1,    -1,    70,    -1,    79,    80,    -1,    58,    81,    -1,
      81,    -1,    61,    82,    -1,    92,    71,    -1,   102,    71,
      -1,    85,    71,    -1,    83,    71,    -1,    -1,    12,    60,
      77,    84,    52,    78,    46,    -1,    17,   110,    60,    -1,
      10,    -1,    72,    -1,    86,    22,    86,    23,    86,    -1,
      86,    24,    86,    -1,    86,    25,    86,    -1,    86,    26,
      86,    -1,    86,    27,    86,    -1,    86,    28,    86,    -1,
      86,    30,    86,    -1,    86,    29,    86,    -1,    86,    31,
      86,    -1,    86,    32,    86,    -1,    86,    34,    86,    -1,
      86,    33,    86,    -1,    86,    36,    86,    -1,    86,    35,
      86,    -1,    86,    37,    86,    -1,    86,    38,    86,    -1,
      86,    39,    86,    -1,    86,    40,    86,    -1,    86,    41,
      86,    -1,    37,    86,    -1,    38,    86,    -1,    42,    86,
      -1,    43,    86,    -1,    48,    86,    49,    -1,    48,     1,
      49,    -1,    58,    88,    -1,    88,    -1,    70,    -1,    61,
      59,    48,    89,    49,    71,    -1,    61,    20,    59,    48,
      89,    49,    71,    -1,    61,    59,    48,    89,    49,     7,
      48,    89,    49,    71,    -1,    -1,    90,    -1,    89,    50,
      90,    -1,   110,    59,    -1,   110,    -1,    15,    -1,    18,
      -1,    -1,    91,    60,    93,    94,    -1,    52,    95,    46,
      -1,    -1,    95,    96,    -1,    58,    97,    -1,    97,    -1,
      70,    -1,   111,    59,    71,    -1,    98,    53,    -1,    61,
      99,    -1,    92,    -1,   102,    -1,    23,    73,    -1,    -1,
      -1,    50,    -1,    -1,     4,    60,   100,   103,   104,    -1,
      52,   107,   101,    46,    -1,    58,   106,    -1,   106,    -1,
      59,    -1,    59,    51,    86,    -1,    -1,   105,    -1,   107,
      50,   105,    -1,     1,    50,   105,    -1,   107,    50,     1,
      50,   105,    -1,    73,    -1,    19,    31,   110,    32,    -1,
      19,    31,    19,    31,   110,    35,    -1,   108,    54,    86,
      55,    -1,   109,    54,    86,    55,    -1,   108,    -1,   109,
      -1,    12,    -1,   110,    -1,    98,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   334,   334,   335,   339,   340,   345,   353,   365,   378,
     381,   389,   397,   400,   407,   412,   420,   424,   431,   436,
     440,   445,   453,   458,   462,   467,   475,   483,   485,   492,
     502,   515,   519,   526,   538,   547,   555,   563,   567,   569,
     573,   574,   577,   579,   592,   617,   619,   620,   624,   629,
     633,   652,   653,   654,   655,   660,   659,   720,   733,   742,
     754,   758,   759,   760,   761,   762,   763,   764,   765,   766,
     767,   768,   769,   770,   771,   772,   773,   774,   775,   776,
     777,   778,   779,   780,   781,   790,   795,   801,   802,   811,
     820,   838,   841,   850,   862,   866,   881,   882,   887,   886,
     905,   909,   910,   922,   927,   930,   931,   944,   962,   971,
     972,   976,   977,   980,   982,   987,   986,  1014,  1018,  1023,
    1027,  1031,  1039,  1040,  1045,  1050,  1057,  1067,  1068,  1073,
    1082,  1086,  1094,  1095,  1096,  1104,  1105
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"doc comment\"", "\"keyword `enum`\"",
  "\"keyword `extends`\"", "\"fully-qualified name\"",
  "\"keyword `generates`\"", "\"identifier\"", "\"keyword `import`\"",
  "\"integer value\"", "\"float value\"", "\"keyword `interface`\"",
  "\"keyword `package`\"", "\"type\"", "\"keyword `struct`\"",
  "\"string literal\"", "\"keyword `typedef`\"", "\"keyword `union`\"",
  "\"templated type\"", "\"keyword `oneway`\"", "\"unknown character\"",
  "'?'", "':'", "LOGICAL_OR", "LOGICAL_AND", "'|'", "'^'", "'&'", "NEQ",
  "EQUALITY", "'<'", "'>'", "GEQ", "LEQ", "RSHIFT", "LSHIFT", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'!'", "'~'", "UNARY_PLUS", "UNARY_MINUS", "'}'",
  "'@'", "'('", "')'", "','", "'='", "'{'", "';'", "'['", "']'", "$accept",
  "program", "doc_comments", "valid_identifier", "valid_type_name",
  "opt_annotations", "annotation", "opt_annotation_params",
  "annotation_params", "annotation_param", "annotation_string_value",
  "annotation_string_values", "annotation_const_expr_value",
  "annotation_const_expr_values", "error_stmt", "require_semicolon",
  "fqname", "fqtype", "package", "import_stmt", "imports", "opt_extends",
  "interface_declarations", "type_declarations",
  "commentable_type_declaration", "type_declaration",
  "type_declaration_body", "interface_declaration", "$@1",
  "typedef_declaration", "const_expr", "commentable_method_declaration",
  "method_declaration", "typed_vars", "typed_var",
  "struct_or_union_keyword", "named_struct_or_union_declaration", "$@2",
  "struct_or_union_body", "field_declarations",
  "commentable_field_declaration", "field_declaration",
  "annotated_compound_declaration", "compound_declaration",
  "enum_storage_type", "opt_comma", "named_enum_declaration", "$@3",
  "enum_declaration_body", "commentable_enum_value", "enum_value",
  "enum_values", "array_type_base", "array_type", "type",
  "type_or_inplace_compound_declaration", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    56,    57,    57,    58,    58,    58,    59,    60,    61,
      61,    62,    63,    63,    64,    64,    65,    65,    66,    66,
      67,    67,    68,    68,    69,    69,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    75,    76,    76,
      77,    77,    78,    78,    78,    79,    79,    79,    80,    80,
      81,    82,    82,    82,    82,    84,    83,    85,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    87,    87,    88,    88,    88,
      88,    89,    89,    89,    90,    90,    91,    91,    93,    92,
      94,    95,    95,    96,    96,    97,    97,    97,    98,    99,
      99,   100,   100,   101,   101,   103,   102,   104,   105,   105,
     106,   106,   107,   107,   107,   107,   107,   108,   108,   108,
     109,   109,   110,   110,   110,   111,   111
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     4,     3,     1,     2,     2,     1,     1,     0,
       2,     3,     0,     3,     1,     3,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     2,     1,     0,     1,
       1,     1,     1,     3,     1,     3,     3,     2,     0,     2,
       0,     2,     0,     2,     2,     0,     1,     2,     2,     1,
       2,     2,     2,     2,     2,     0,     7,     3,     1,     1,
       5,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     3,     3,     2,     1,     1,     6,     7,
      10,     0,     1,     3,     2,     1,     1,     1,     0,     4,
       3,     0,     2,     2,     1,     1,     3,     2,     2,     1,
       1,     2,     0,     0,     1,     0,     5,     4,     2,     1,
       1,     3,     0,     1,     3,     3,     5,     1,     4,     6,
       4,     4,     1,     1,     1,     1,     1
};

/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const unsigned char yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const unsigned char yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error.  */
static const unsigned char yydefact[] =
{
       0,    34,     0,     0,     0,    38,    38,    28,     1,     0,
       0,    27,    33,     0,     0,    46,    39,     9,     9,    26,
      28,     8,    28,    37,     4,     9,     0,    47,    49,    35,
      36,     5,     6,    48,     0,     0,    96,     0,    97,     0,
      10,    50,    28,    28,     0,    28,    28,   112,    40,    29,
     134,    32,     0,    30,    31,   127,   132,   133,     0,    12,
      54,    53,    98,    51,    52,     0,   115,     0,    55,     0,
       0,     0,    57,     0,    11,     0,   111,     0,    41,     0,
       0,     0,    58,     0,     0,     0,     0,     0,    59,     0,
       0,     0,     0,    14,   101,    99,     0,   116,    42,     0,
     128,    79,    80,    81,    82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   130,   131,     0,    13,
       0,     0,     0,     7,     0,   120,   123,   119,   113,     0,
       0,    84,    83,     0,    61,    62,    63,    64,    65,    67,
      66,    68,    69,    71,    70,    73,    72,    74,    75,    76,
      77,    78,    18,     0,    16,    17,    22,    15,   100,     0,
       0,   105,   102,   104,   136,   135,     0,     0,   118,     0,
       0,     0,    56,     0,     0,    87,    43,    44,    86,   129,
       0,    20,     0,     0,    24,   103,   109,   108,   110,   107,
      28,   125,   121,     0,   124,   117,    85,     0,     0,    60,
      19,     0,    23,     0,   106,     0,     0,    91,    21,    25,
     126,    91,     0,    92,    95,     0,    28,     0,    94,    28,
       0,    88,    93,    89,    91,     0,    28,    90
};

/* YYPDEFGOTO[NTERM-NUM].  */
static const short int yydefgoto[] =
{
      -1,     4,   134,   135,    53,    26,    40,    74,    92,    93,
     164,   192,   165,   193,    15,    12,    88,    55,     5,    16,
       9,    68,   139,    17,    27,    28,    41,    42,    79,    43,
      89,   187,   188,   222,   223,    44,    45,    75,    95,   131,
     172,   173,   174,   197,    66,   181,    46,    77,    97,   136,
     137,   138,    56,    57,   224,   176
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -207
static const short int yypact[] =
{
      63,  -207,    77,    24,    36,  -207,  -207,    17,  -207,    71,
      71,  -207,  -207,    40,    90,  -207,  -207,    37,    82,  -207,
      17,  -207,    17,  -207,  -207,    21,   249,  -207,  -207,  -207,
    -207,  -207,  -207,  -207,    99,    99,  -207,   289,  -207,   118,
    -207,  -207,    17,    17,    99,    17,    17,   104,   129,  -207,
    -207,  -207,   114,  -207,  -207,  -207,    98,   102,    99,   115,
    -207,  -207,  -207,  -207,  -207,   111,  -207,   111,  -207,   301,
     281,   281,  -207,   157,  -207,   127,  -207,   132,  -207,   142,
     158,   170,  -207,   281,   281,   281,   281,    93,  -207,   306,
     338,   154,   110,  -207,  -207,  -207,    31,  -207,  -207,   301,
    -207,  -207,  -207,  -207,  -207,   166,   370,   281,   281,   281,
     281,   281,   281,   281,   281,   281,   281,   281,   281,   281,
     281,   281,   281,   281,   281,   281,  -207,  -207,   242,  -207,
     157,   136,   164,  -207,   165,   171,  -207,  -207,   173,   209,
      80,  -207,  -207,   398,   435,   451,   466,   480,   493,   317,
     317,   345,   345,   345,   345,   137,   137,   147,   147,  -207,
    -207,  -207,  -207,   262,  -207,  -207,   418,  -207,  -207,   189,
      69,  -207,  -207,  -207,   167,  -207,   217,     8,  -207,   281,
     103,   182,  -207,   229,   149,  -207,  -207,  -207,  -207,  -207,
     281,  -207,   -37,    64,   418,  -207,  -207,  -207,  -207,  -207,
      17,  -207,   418,   181,  -207,  -207,  -207,   217,   186,   418,
    -207,   222,  -207,   281,  -207,     8,   191,   289,  -207,   418,
    -207,   289,   121,  -207,   217,   150,     7,   289,  -207,    17,
     192,  -207,  -207,  -207,   289,   169,    17,  -207
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -207,  -207,   -10,  -115,    88,  -104,  -207,  -207,  -207,   112,
    -207,  -207,  -207,  -207,   -11,   -20,   -36,   -55,   241,  -207,
     239,  -207,  -207,   244,   120,   -21,  -207,  -207,  -207,  -207,
     -66,  -207,    68,  -206,    30,  -207,    92,  -207,  -207,  -207,
    -207,    91,  -207,  -207,  -207,  -207,    95,  -207,  -207,   -72,
     135,  -207,  -207,  -207,   -31,  -207
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -123
static const short int yytable[] =
{
      29,    54,    30,    23,    33,    90,    58,    25,    25,   210,
      76,    24,    78,   211,   230,   225,   133,   101,   102,   103,
     104,   106,    60,    61,    31,    63,    64,   170,   235,    54,
       7,    54,   132,    54,    24,   184,     8,    -3,    81,   133,
      24,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
      11,   200,   166,    54,     1,   170,     2,    32,   140,   208,
      11,   -45,    13,    34,   -45,   -45,     3,  -122,     1,   184,
      14,  -122,    -2,   -45,    36,    24,   -45,    38,   -45,   -45,
       3,    13,   216,    19,   105,    54,    20,   194,    21,    49,
     175,    21,    22,    82,   203,   201,    24,    21,   204,   228,
     212,   133,   100,   202,   213,   189,    39,    49,   -45,    21,
     171,   169,    47,    48,   209,    51,    59,    65,   185,   183,
      83,    84,    62,    54,    67,    85,    86,    13,   175,    24,
      -9,    87,    49,   220,    21,    69,    72,   219,    50,  -114,
      51,    -9,    70,    34,    -9,    52,    71,   133,   171,   129,
     130,    35,    33,    73,    36,    91,    37,    38,    31,   207,
     226,   227,   185,   133,   121,   122,   123,   124,   125,    94,
     214,    54,   168,    -9,    96,    54,   123,   124,   125,    99,
      13,    54,    31,    -9,    98,    49,    39,    21,    54,   229,
     227,    50,   100,    51,    -9,   128,   231,    -9,    52,   233,
      13,    32,    24,    -9,   177,   141,   237,    -9,   236,   227,
     199,    -9,   179,   180,    -9,   133,    -9,    -9,   205,    -9,
      13,   215,    31,    -9,   217,    32,    -9,    -9,   218,   221,
     234,    -9,   167,     6,    -9,    10,    -9,    -9,    49,    -9,
      21,   206,    82,    34,    18,   182,    -9,   232,   162,   186,
     195,    35,   196,     0,    36,   198,    37,    38,    49,   178,
      21,     0,    82,     0,     0,    32,    -9,     0,   191,    83,
      84,     0,     0,     0,    85,    86,     0,    49,     0,    21,
      87,    82,     0,     0,   163,    49,    39,    21,     0,    83,
      84,    50,     0,    51,    85,    86,     0,    49,    52,    21,
      87,     0,     0,    50,     0,    51,     0,     0,    83,    84,
      80,     0,     0,    85,    86,     0,     0,     0,   107,    87,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,     0,
     107,   126,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     119,   120,   121,   122,   123,   124,   125,     0,     0,     0,
       0,     0,   107,   127,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,     0,   142,
     107,   190,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     107,     0,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned char yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short int yyconfl[] =
{
       0
};

static const short int yycheck[] =
{
      20,    37,    22,    14,    25,    71,    37,    17,    18,    46,
      65,     3,    67,    50,     7,   221,     8,    83,    84,    85,
      86,    87,    42,    43,     3,    45,    46,   131,   234,    65,
       6,    67,     1,    69,     3,   139,     0,     0,    69,     8,
       3,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      53,   176,   128,    99,     1,   169,     3,    46,    99,   184,
      53,     0,     1,     4,     3,     4,    13,    46,     1,   183,
       9,    50,     0,    12,    15,     3,    15,    18,    17,    18,
      13,     1,   207,    53,     1,   131,     6,   163,     8,     6,
     131,     8,    14,    10,     1,   177,     3,     8,   180,   224,
      46,     8,    32,   179,    50,    35,    47,     6,    47,     8,
     131,   131,    34,    35,   190,    14,     8,    23,   139,   139,
      37,    38,    44,   169,     5,    42,    43,     1,   169,     3,
       4,    48,     6,   215,     8,    31,    58,   213,    12,    46,
      14,    15,    54,     4,    18,    19,    54,     8,   169,    49,
      50,    12,   183,    48,    15,     8,    17,    18,     3,    20,
      49,    50,   183,     8,    37,    38,    39,    40,    41,    52,
     200,   217,    46,    47,    52,   221,    39,    40,    41,    31,
       1,   227,     3,     4,    52,     6,    47,     8,   234,    49,
      50,    12,    32,    14,    15,    51,   226,    18,    19,   229,
       1,    46,     3,     4,    50,    49,   236,     8,    49,    50,
      53,    12,    51,    50,    15,     8,    17,    18,    46,    20,
       1,    50,     3,     4,    48,    46,    47,     8,    16,    48,
      48,    12,   130,     2,    15,     6,    17,    18,     6,    20,
       8,   183,    10,     4,    10,    46,    47,   227,    16,   139,
     169,    12,   170,    -1,    15,   170,    17,    18,     6,   134,
       8,    -1,    10,    -1,    -1,    46,    47,    -1,    16,    37,
      38,    -1,    -1,    -1,    42,    43,    -1,     6,    -1,     8,
      48,    10,    -1,    -1,    52,     6,    47,     8,    -1,    37,
      38,    12,    -1,    14,    42,    43,    -1,     6,    19,     8,
      48,    -1,    -1,    12,    -1,    14,    -1,    -1,    37,    38,
      19,    -1,    -1,    42,    43,    -1,    -1,    -1,    22,    48,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      22,    55,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    22,    55,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      22,    -1,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     1,     3,    13,    57,    74,    74,     6,     0,    76,
      76,    53,    71,     1,     9,    70,    75,    79,    79,    53,
       6,     8,    60,    70,     3,    58,    61,    80,    81,    71,
      71,     3,    46,    81,     4,    12,    15,    17,    18,    47,
      62,    82,    83,    85,    91,    92,   102,    60,    60,     6,
      12,    14,    19,    60,    72,    73,   108,   109,   110,     8,
      71,    71,    60,    71,    71,    23,   100,     5,    77,    31,
      54,    54,    60,    48,    63,    93,    73,   103,    73,    84,
      19,   110,    10,    37,    38,    42,    43,    48,    72,    86,
      86,     8,    64,    65,    52,    94,    52,   104,    52,    31,
      32,    86,    86,    86,    86,     1,    86,    22,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    55,    55,    51,    49,
      50,    95,     1,     8,    58,    59,   105,   106,   107,    78,
     110,    49,    49,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    16,    52,    66,    68,    86,    65,    46,    58,
      61,    70,    96,    97,    98,   110,   111,    50,   106,    51,
      50,   101,    46,    58,    61,    70,    80,    87,    88,    35,
      23,    16,    67,    69,    86,    97,    92,    99,   102,    53,
      59,   105,    86,     1,   105,    46,    88,    20,    59,    86,
      46,    50,    46,    50,    71,    50,    59,    48,    16,    86,
     105,    48,    89,    90,   110,    89,    49,    50,    59,    49,
       7,    71,    90,    71,    48,    89,    49,    71
};


/* Prevent warning if -Wmissing-prototypes.  */
int yyparse (yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope);

/* Error token number */
#define YYTERROR 1

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */


#define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))							\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))

/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# define YY_LOCATION_PRINT(File, Loc)			\
    fprintf (File, "%d.%d-%d.%d",			\
	     (Loc).first_line, (Loc).first_column,	\
	     (Loc).last_line,  (Loc).last_column)
#endif


#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#define YYLEX yylex (&yylval, &yylloc, scanner, scope)


#undef yynerrs
#define yynerrs (yystackp->yyerrcnt)
#undef yychar
#define yychar (yystackp->yyrawchar)
#undef yylval
#define yylval (yystackp->yyval)
#undef yylloc
#define yylloc (yystackp->yyloc)


static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)							     \
   do { YYRESULTTAG yyflag = YYE; if (yyflag != yyok) return yyflag; }	     \
   while (YYID (0))

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))


/*--------------------.
| Print this symbol.  |
`--------------------*/

static void
yy_symbol_print (FILE *, int yytype, const yy::parser::semantic_type *yyvaluep, const yy::parser::location_type *yylocationp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  YYUSE (yyparser);
  YYUSE (scanner);
  YYUSE (ast);
  YYUSE (scope);
  yyparser.yy_symbol_print_ (yytype, yyvaluep, yylocationp);
}


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			    \
do {									    \
  if (yydebug)								    \
    {									    \
      YYFPRINTF (stderr, "%s ", Title);					    \
      yy_symbol_print (stderr, Type,					    \
		       Value, Location, yyparser, scanner, ast, scope);  \
      YYFPRINTF (stderr, "\n");						    \
    }									    \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

#else /* !YYDEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
# if (! defined __cplusplus \
      || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	  && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL))
#  define YYSTACKEXPANDABLE 1
# else
#  define YYSTACKEXPANDABLE 0
# endif
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)			\
  do {							\
    if (Yystack->yyspaceLeft < YYHEADROOM)		\
      yyexpandGLRStack (Yystack);			\
  } while (YYID (0))
#else
# define YY_RESERVE_GLRSTACK(Yystack)			\
  do {							\
    if (Yystack->yyspaceLeft < YYHEADROOM)		\
      yyMemoryExhausted (Yystack);			\
  } while (YYID (0))
#endif


#if YYERROR_VERBOSE

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
static size_t
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
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
    return strlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef short int yySymbol;

/** Item references, as in LALR(1) machine */
typedef short int yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yyStateNum yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the first token produced by my symbol */
  size_t yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
  /** Source location for this state.  */
  YYLTYPE yyloc;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  size_t yysize, yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;
  /* To compute the location of the error token.  */
  yyGLRStackItem yyerror_range[3];

  int yyerrcnt;
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;

  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  size_t yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

static void yyFail (yyGLRStack* yystackp, YYLTYPE *yylocp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope, const char* yymsg)
  __attribute__ ((__noreturn__));
static void
yyFail (yyGLRStack* yystackp, YYLTYPE *yylocp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope, const char* yymsg)
{
  if (yymsg != NULL)
    yyerror (yylocp, yyparser, scanner, ast, scope, yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

static void yyMemoryExhausted (yyGLRStack* yystackp)
  __attribute__ ((__noreturn__));
static void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

#if YYDEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char*
yytokenName (yySymbol yytoken)
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}
#endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) __attribute__ ((__unused__));
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  yyGLRState* s;
  int i;
  s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
      YYASSERT (s->yyresolved);
      yyvsp[i].yystate.yyresolved = yytrue;
      yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      yyvsp[i].yystate.yyloc = s->yyloc;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     __attribute__ ((__unused__));
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
/*ARGSUSED*/ static YYRESULTTAG
yyuserAction (yyRuleNum yyn, int yyrhslen, yyGLRStackItem* yyvsp,
	      YYSTYPE* yyvalp,
	      YYLTYPE* YYOPTIONAL_LOC (yylocp),
	      yyGLRStack* yystackp
	      , yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  yybool yynormal __attribute__ ((__unused__)) =
    (yystackp->yysplitPoint == NULL);
  int yylow;
  YYUSE (yyparser);
  YYUSE (scanner);
  YYUSE (ast);
  YYUSE (scope);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, N, yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)						     \
  return yyerror (yylocp, yyparser, scanner, ast, scope, YY_("syntax error: cannot back up")),     \
	 yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  YYLLOC_DEFAULT ((*yylocp), (yyvsp - yyrhslen), yyrhslen);
  yystackp->yyerror_range[1].yystate.yyloc = *yylocp;

  switch (yyn)
    {
        case 4:

/* Line 936 of glr.c  */
#line 339 "hidl-gen_y.yy"
    { ((*yyvalp).docComment) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.docComment); }
    break;

  case 5:

/* Line 936 of glr.c  */
#line 341 "hidl-gen_y.yy"
    {
        (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.docComment)->merge((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.docComment));
        ((*yyvalp).docComment) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.docComment);
      }
    break;

  case 6:

/* Line 936 of glr.c  */
#line 346 "hidl-gen_y.yy"
    {
        std::cerr << "ERROR: Doc comments must preceed what they describe at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yyloc) << "\n";
        YYERROR;
      }
    break;

  case 7:

/* Line 936 of glr.c  */
#line 354 "hidl-gen_y.yy"
    {
        std::string errorMsg;
        if (!isValidIdentifier((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str), &errorMsg)) {
            std::cerr << "ERROR: " << errorMsg << " at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc) << "\n";
            YYERROR;
        }
        ((*yyvalp).str) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str);
      }
    break;

  case 8:

/* Line 936 of glr.c  */
#line 366 "hidl-gen_y.yy"
    {
        std::string errorMsg;
        if (!isValidTypeName((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str), &errorMsg)) {
            std::cerr << "ERROR: " << errorMsg << " at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc) << "\n";
            YYERROR;
        }
        ((*yyvalp).str) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str);
      }
    break;

  case 9:

/* Line 936 of glr.c  */
#line 378 "hidl-gen_y.yy"
    {
          ((*yyvalp).annotations) = new std::vector<Annotation *>;
      }
    break;

  case 10:

/* Line 936 of glr.c  */
#line 382 "hidl-gen_y.yy"
    {
          ((*yyvalp).annotations) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.annotations);
          ((*yyvalp).annotations)->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.annotation));
      }
    break;

  case 11:

/* Line 936 of glr.c  */
#line 390 "hidl-gen_y.yy"
    {
          ((*yyvalp).annotation) = new Annotation((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.annotationParams));
      }
    break;

  case 12:

/* Line 936 of glr.c  */
#line 397 "hidl-gen_y.yy"
    {
          ((*yyvalp).annotationParams) = new AnnotationParamVector;
      }
    break;

  case 13:

/* Line 936 of glr.c  */
#line 401 "hidl-gen_y.yy"
    {
          ((*yyvalp).annotationParams) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.annotationParams);
      }
    break;

  case 14:

/* Line 936 of glr.c  */
#line 408 "hidl-gen_y.yy"
    {
          ((*yyvalp).annotationParams) = new AnnotationParamVector;
          ((*yyvalp).annotationParams)->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.annotationParam));
      }
    break;

  case 15:

/* Line 936 of glr.c  */
#line 413 "hidl-gen_y.yy"
    {
          ((*yyvalp).annotationParams) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.annotationParams);
          ((*yyvalp).annotationParams)->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.annotationParam));
      }
    break;

  case 16:

/* Line 936 of glr.c  */
#line 421 "hidl-gen_y.yy"
    {
          ((*yyvalp).annotationParam) = new StringAnnotationParam((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.str), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.stringVec));
      }
    break;

  case 17:

/* Line 936 of glr.c  */
#line 425 "hidl-gen_y.yy"
    {
          ((*yyvalp).annotationParam) = new ConstantExpressionAnnotationParam((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.str), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constExprVec));
      }
    break;

  case 18:

/* Line 936 of glr.c  */
#line 432 "hidl-gen_y.yy"
    {
          ((*yyvalp).stringVec) = new std::vector<std::string>;
          ((*yyvalp).stringVec)->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str));
      }
    break;

  case 19:

/* Line 936 of glr.c  */
#line 436 "hidl-gen_y.yy"
    { ((*yyvalp).stringVec) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.stringVec); }
    break;

  case 20:

/* Line 936 of glr.c  */
#line 441 "hidl-gen_y.yy"
    {
          ((*yyvalp).stringVec) = new std::vector<std::string>;
          ((*yyvalp).stringVec)->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str));
      }
    break;

  case 21:

/* Line 936 of glr.c  */
#line 446 "hidl-gen_y.yy"
    {
          ((*yyvalp).stringVec) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.stringVec);
          ((*yyvalp).stringVec)->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.str));
      }
    break;

  case 22:

/* Line 936 of glr.c  */
#line 454 "hidl-gen_y.yy"
    {
          ((*yyvalp).constExprVec) = new std::vector<ConstantExpression *>;
          ((*yyvalp).constExprVec)->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.constantExpression));
      }
    break;

  case 23:

/* Line 936 of glr.c  */
#line 458 "hidl-gen_y.yy"
    { ((*yyvalp).constExprVec) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.constExprVec); }
    break;

  case 24:

/* Line 936 of glr.c  */
#line 463 "hidl-gen_y.yy"
    {
          ((*yyvalp).constExprVec) = new std::vector<ConstantExpression *>;
          ((*yyvalp).constExprVec)->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.constantExpression));
      }
    break;

  case 25:

/* Line 936 of glr.c  */
#line 468 "hidl-gen_y.yy"
    {
          ((*yyvalp).constExprVec) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constExprVec);
          ((*yyvalp).constExprVec)->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression));
      }
    break;

  case 26:

/* Line 936 of glr.c  */
#line 476 "hidl-gen_y.yy"
    {
      ((*yyvalp).str) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.str);
      ast->addSyntaxError();
    }
    break;

  case 28:

/* Line 936 of glr.c  */
#line 485 "hidl-gen_y.yy"
    {
          std::cerr << "ERROR: missing ; at " << (*yylocp) << "\n";
          ast->addSyntaxError();
      }
    break;

  case 29:

/* Line 936 of glr.c  */
#line 493 "hidl-gen_y.yy"
    {
          ((*yyvalp).fqName) = new FQName();
          if(!FQName::parse((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str), ((*yyvalp).fqName))) {
              std::cerr << "ERROR: FQName '" << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str) << "' is not valid at "
                        << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc)
                        << ".\n";
              YYERROR;
          }
      }
    break;

  case 30:

/* Line 936 of glr.c  */
#line 503 "hidl-gen_y.yy"
    {
          ((*yyvalp).fqName) = new FQName();
          if(!FQName::parse((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str), ((*yyvalp).fqName))) {
              std::cerr << "ERROR: FQName '" << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str) << "' is not valid at "
                        << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc)
                        << ".\n";
              YYERROR;
          }
      }
    break;

  case 31:

/* Line 936 of glr.c  */
#line 516 "hidl-gen_y.yy"
    {
          ((*yyvalp).referenceToType) = new Reference<Type>(*(((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.fqName), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc)));
      }
    break;

  case 32:

/* Line 936 of glr.c  */
#line 520 "hidl-gen_y.yy"
    {
          ((*yyvalp).referenceToType) = new Reference<Type>((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.type), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc)));
      }
    break;

  case 33:

/* Line 936 of glr.c  */
#line 527 "hidl-gen_y.yy"
    {
          if (!ast->setPackage((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str))) {
              std::cerr << "ERROR: Malformed package identifier '"
                        << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str)
                        << "' at "
                        << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc)
                        << "\n";

              YYERROR;
          }
      }
    break;

  case 34:

/* Line 936 of glr.c  */
#line 539 "hidl-gen_y.yy"
    {
      std::cerr << "ERROR: Package statement must be at the beginning of the file (" << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc) << ")\n";
      ((*yyvalp).str) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str);
      ast->addSyntaxError();
    }
    break;

  case 35:

/* Line 936 of glr.c  */
#line 548 "hidl-gen_y.yy"
    {
          if (!ast->addImport((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str))) {
              std::cerr << "ERROR: Unable to import '" << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str) << "' at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc)
                        << "\n";
              ast->addSyntaxError();
          }
      }
    break;

  case 36:

/* Line 936 of glr.c  */
#line 556 "hidl-gen_y.yy"
    {
          if (!ast->addImport((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str))) {
              std::cerr << "ERROR: Unable to import '" << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str) << "' at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc)
                        << "\n";
              ast->addSyntaxError();
          }
      }
    break;

  case 40:

/* Line 936 of glr.c  */
#line 573 "hidl-gen_y.yy"
    { ((*yyvalp).referenceToType) = nullptr; }
    break;

  case 41:

/* Line 936 of glr.c  */
#line 574 "hidl-gen_y.yy"
    { ((*yyvalp).referenceToType) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.referenceToType); }
    break;

  case 43:

/* Line 936 of glr.c  */
#line 580 "hidl-gen_y.yy"
    {
          CHECK((*scope)->isInterface());

          std::string errorMsg;
          if ((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.type) != nullptr && (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.type)->isNamedType() &&
              !isValidInterfaceField(static_cast<NamedType*>((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.type))->localName().c_str(),
                    &errorMsg)) {
              std::cerr << "ERROR: " << errorMsg << " at "
                        << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yyloc) << "\n";
              YYERROR;
          }
      }
    break;

  case 44:

/* Line 936 of glr.c  */
#line 593 "hidl-gen_y.yy"
    {
          CHECK((*scope)->isInterface());

          std::string errorMsg;
          if ((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.method) != nullptr &&
              !isValidInterfaceField((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.method)->name().c_str(), &errorMsg)) {
              std::cerr << "ERROR: " << errorMsg << " at "
                        << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yyloc) << "\n";
              YYERROR;
          }

          if ((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.method) != nullptr) {
            Interface *iface = static_cast<Interface*>(*scope);
            if (!iface->addMethod((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.method))) {
                std::cerr << "ERROR: Unable to add method '" << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.method)->name()
                          << "' at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yyloc) << "\n";

                YYERROR;
            }
          }
          // ignore if $2 is nullptr (from error recovery)
      }
    break;

  case 48:

/* Line 936 of glr.c  */
#line 625 "hidl-gen_y.yy"
    {
        (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.type)->setDocComment((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.docComment));
        ((*yyvalp).type) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.type);
      }
    break;

  case 49:

/* Line 936 of glr.c  */
#line 629 "hidl-gen_y.yy"
    { ((*yyvalp).type) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.type); }
    break;

  case 50:

/* Line 936 of glr.c  */
#line 634 "hidl-gen_y.yy"
    {
          if (!(((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.type)->isTypeDef()) {
              CHECK((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.type)->isScope());
              static_cast<Scope*>((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.type))->setAnnotations((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.annotations));
          } else if (!(((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.annotations)->empty()) {
              // Since typedefs are always resolved to their target it makes
              // little sense to annotate them and have their annotations
              // impose semantics other than their target type.
              std::cerr << "ERROR: typedefs cannot be annotated at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yyloc)
                        << "\n";

              YYERROR;
          }
          ((*yyvalp).type) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.type);
      }
    break;

  case 55:

/* Line 936 of glr.c  */
#line 660 "hidl-gen_y.yy"
    {
          Reference<Type>* superType = (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.referenceToType);
          bool isIBase = ast->package().package() == gIBaseFqName.package();

          if (isIBase) {
              if (superType != nullptr) {
                  std::cerr << "ERROR: IBase must not extend any interface at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yyloc)
                        << "\n";

                  YYERROR;
              }
              superType = new Reference<Type>();
          } else {
              if (!ast->addImport(gIBaseFqName.string().c_str())) {
                  std::cerr << "ERROR: Unable to automatically import '"
                            << gIBaseFqName.string()
                            << "' at " << (*yylocp)
                            << "\n";
                  YYERROR;
              }

              if (superType == nullptr) {
                  superType = new Reference<Type>(gIBaseFqName, convertYYLoc((*yylocp)));
              }
          }

          if ((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str)[0] != 'I') {
              std::cerr << "ERROR: All interface names must start with an 'I' "
                        << "prefix at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc) << "\n";

              YYERROR;
          }

          if (*scope != ast->getRootScope()) {
              std::cerr << "ERROR: All interface must declared in "
                        << "global scope at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc) << "\n";

              YYERROR;
          }

          Interface* iface = new Interface(
              (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str), ast->makeFullName((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str), *scope), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc)),
              *scope, *superType, ast->getFileHash());

          enterScope(ast, scope, iface);
      }
    break;

  case 56:

/* Line 936 of glr.c  */
#line 707 "hidl-gen_y.yy"
    {
          CHECK((*scope)->isInterface());

          Interface *iface = static_cast<Interface *>(*scope);
          CHECK(iface->addAllReservedMethods());

          leaveScope(ast, scope);
          ast->addScopedType(iface, *scope);
          ((*yyvalp).type) = iface;
      }
    break;

  case 57:

/* Line 936 of glr.c  */
#line 721 "hidl-gen_y.yy"
    {
          // The reason we wrap the given type in a TypeDef is simply to suppress
          // emitting any type definitions later on, since this is just an alias
          // to a type defined elsewhere.
          TypeDef* typeDef = new TypeDef(
              (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.str), ast->makeFullName((((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.str), *scope), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc)), *scope, *(((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.referenceToType));
          ast->addScopedType(typeDef, *scope);
          ((*yyvalp).type) = typeDef;
      }
    break;

  case 58:

/* Line 936 of glr.c  */
#line 733 "hidl-gen_y.yy"
    {
          ((*yyvalp).constantExpression) = LiteralConstantExpression::tryParse((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str));

          if (((*yyvalp).constantExpression) == nullptr) {
              std::cerr << "ERROR: Could not parse literal: "
                        << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str) << " at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc) << ".\n";
              YYERROR;
          }
      }
    break;

  case 59:

/* Line 936 of glr.c  */
#line 743 "hidl-gen_y.yy"
    {
          if(!(((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.fqName)->isValidValueName()) {
              std::cerr << "ERROR: '" << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.fqName)->string()
                        << "' does not refer to an enum value at "
                        << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc) << ".\n";
              YYERROR;
          }

          ((*yyvalp).constantExpression) = new ReferenceConstantExpression(
              Reference<LocalIdentifier>(*(((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.fqName), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc))), (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.fqName)->string());
      }
    break;

  case 60:

/* Line 936 of glr.c  */
#line 755 "hidl-gen_y.yy"
    {
          ((*yyvalp).constantExpression) = new TernaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (5))].yystate.yysemantics.yysval.constantExpression), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (5))].yystate.yysemantics.yysval.constantExpression), (((yyGLRStackItem const *)yyvsp)[YYFILL ((5) - (5))].yystate.yysemantics.yysval.constantExpression));
      }
    break;

  case 61:

/* Line 936 of glr.c  */
#line 758 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "||", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 62:

/* Line 936 of glr.c  */
#line 759 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "&&", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 63:

/* Line 936 of glr.c  */
#line 760 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "|" , (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 64:

/* Line 936 of glr.c  */
#line 761 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "^" , (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 65:

/* Line 936 of glr.c  */
#line 762 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "&" , (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 66:

/* Line 936 of glr.c  */
#line 763 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "==", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 67:

/* Line 936 of glr.c  */
#line 764 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "!=", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 68:

/* Line 936 of glr.c  */
#line 765 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "<" , (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 69:

/* Line 936 of glr.c  */
#line 766 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), ">" , (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 70:

/* Line 936 of glr.c  */
#line 767 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "<=", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 71:

/* Line 936 of glr.c  */
#line 768 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), ">=", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 72:

/* Line 936 of glr.c  */
#line 769 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "<<", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 73:

/* Line 936 of glr.c  */
#line 770 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), ">>", (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 74:

/* Line 936 of glr.c  */
#line 771 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "+" , (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 75:

/* Line 936 of glr.c  */
#line 772 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "-" , (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 76:

/* Line 936 of glr.c  */
#line 773 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "*" , (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 77:

/* Line 936 of glr.c  */
#line 774 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "/" , (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 78:

/* Line 936 of glr.c  */
#line 775 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new BinaryConstantExpression((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.constantExpression), "%" , (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 79:

/* Line 936 of glr.c  */
#line 776 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new UnaryConstantExpression("+", (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 80:

/* Line 936 of glr.c  */
#line 777 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new UnaryConstantExpression("-", (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 81:

/* Line 936 of glr.c  */
#line 778 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new UnaryConstantExpression("!", (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 82:

/* Line 936 of glr.c  */
#line 779 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = new UnaryConstantExpression("~", (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.constantExpression)); }
    break;

  case 83:

/* Line 936 of glr.c  */
#line 780 "hidl-gen_y.yy"
    { ((*yyvalp).constantExpression) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.constantExpression); }
    break;

  case 84:

/* Line 936 of glr.c  */
#line 782 "hidl-gen_y.yy"
    {
        ast->addSyntaxError();
        // to avoid segfaults
        ((*yyvalp).constantExpression) = ConstantExpression::Zero(ScalarType::KIND_INT32).release();
      }
    break;

  case 85:

/* Line 936 of glr.c  */
#line 791 "hidl-gen_y.yy"
    {
        if ((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.method) != nullptr) (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.method)->setDocComment((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.docComment));
        ((*yyvalp).method) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.method);
      }
    break;

  case 86:

/* Line 936 of glr.c  */
#line 796 "hidl-gen_y.yy"
    {
        ((*yyvalp).method) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.method);
      }
    break;

  case 87:

/* Line 936 of glr.c  */
#line 801 "hidl-gen_y.yy"
    { ((*yyvalp).method) = nullptr; }
    break;

  case 88:

/* Line 936 of glr.c  */
#line 803 "hidl-gen_y.yy"
    {
          ((*yyvalp).method) = new Method((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (6))].yystate.yysemantics.yysval.str) /* name */,
                          (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (6))].yystate.yysemantics.yysval.typedVars) /* args */,
                          new std::vector<NamedReference<Type>*> /* results */,
                          false /* oneway */,
                          (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (6))].yystate.yysemantics.yysval.annotations) /* annotations */,
                          convertYYLoc((*yylocp)));
      }
    break;

  case 89:

/* Line 936 of glr.c  */
#line 812 "hidl-gen_y.yy"
    {
          ((*yyvalp).method) = new Method((((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (7))].yystate.yysemantics.yysval.str) /* name */,
                          (((yyGLRStackItem const *)yyvsp)[YYFILL ((5) - (7))].yystate.yysemantics.yysval.typedVars) /* args */,
                          new std::vector<NamedReference<Type>*> /* results */,
                          true /* oneway */,
                          (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (7))].yystate.yysemantics.yysval.annotations) /* annotations */,
                          convertYYLoc((*yylocp)));
      }
    break;

  case 90:

/* Line 936 of glr.c  */
#line 821 "hidl-gen_y.yy"
    {
          if ((((yyGLRStackItem const *)yyvsp)[YYFILL ((8) - (10))].yystate.yysemantics.yysval.typedVars)->empty()) {
              std::cerr << "ERROR: generates clause used without result at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (10))].yystate.yyloc) << "\n";
              ast->addSyntaxError();
          }

          ((*yyvalp).method) = new Method((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (10))].yystate.yysemantics.yysval.str) /* name */,
                          (((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (10))].yystate.yysemantics.yysval.typedVars) /* args */,
                          (((yyGLRStackItem const *)yyvsp)[YYFILL ((8) - (10))].yystate.yysemantics.yysval.typedVars) /* results */,
                          false /* oneway */,
                          (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (10))].yystate.yysemantics.yysval.annotations) /* annotations */,
                          convertYYLoc((*yylocp)));
      }
    break;

  case 91:

/* Line 936 of glr.c  */
#line 838 "hidl-gen_y.yy"
    {
          ((*yyvalp).typedVars) = new TypedVarVector();
      }
    break;

  case 92:

/* Line 936 of glr.c  */
#line 842 "hidl-gen_y.yy"
    {
          ((*yyvalp).typedVars) = new TypedVarVector();
          if (!((*yyvalp).typedVars)->add((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.typedVar))) {
              std::cerr << "ERROR: duplicated argument or result name "
                  << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.typedVar)->name() << " at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc) << "\n";
              ast->addSyntaxError();
          }
      }
    break;

  case 93:

/* Line 936 of glr.c  */
#line 851 "hidl-gen_y.yy"
    {
          ((*yyvalp).typedVars) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.typedVars);
          if (!((*yyvalp).typedVars)->add((((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.typedVar))) {
              std::cerr << "ERROR: duplicated argument or result name "
                  << (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.typedVar)->name() << " at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yyloc) << "\n";
              ast->addSyntaxError();
          }
      }
    break;

  case 94:

/* Line 936 of glr.c  */
#line 863 "hidl-gen_y.yy"
    {
          ((*yyvalp).typedVar) = new NamedReference<Type>((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.str), *(((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.referenceToType), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yyloc)));
      }
    break;

  case 95:

/* Line 936 of glr.c  */
#line 867 "hidl-gen_y.yy"
    {
          ((*yyvalp).typedVar) = new NamedReference<Type>("", *(((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.referenceToType), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc)));

          const std::string typeName = ((*yyvalp).typedVar)->isResolved()
              ? ((*yyvalp).typedVar)->get()->typeName() : ((*yyvalp).typedVar)->getLookupFqName().string();

          std::cerr << "ERROR: variable of type " << typeName
              << " is missing a variable name at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc) << "\n";
          ast->addSyntaxError();
      }
    break;

  case 96:

/* Line 936 of glr.c  */
#line 881 "hidl-gen_y.yy"
    { ((*yyvalp).compoundStyle) = CompoundType::STYLE_STRUCT; }
    break;

  case 97:

/* Line 936 of glr.c  */
#line 882 "hidl-gen_y.yy"
    { ((*yyvalp).compoundStyle) = CompoundType::STYLE_UNION; }
    break;

  case 98:

/* Line 936 of glr.c  */
#line 887 "hidl-gen_y.yy"
    {
          CompoundType *container = new CompoundType(
              (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.compoundStyle), (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.str), ast->makeFullName((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.str), *scope), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yyloc)), *scope);
          enterScope(ast, scope, container);
      }
    break;

  case 99:

/* Line 936 of glr.c  */
#line 893 "hidl-gen_y.yy"
    {
          CHECK((*scope)->isCompoundType());
          CompoundType *container = static_cast<CompoundType *>(*scope);
          container->setFields((((yyGLRStackItem const *)yyvsp)[YYFILL ((4) - (4))].yystate.yysemantics.yysval.fields));

          leaveScope(ast, scope);
          ast->addScopedType(container, *scope);
          ((*yyvalp).type) = container;
      }
    break;

  case 100:

/* Line 936 of glr.c  */
#line 905 "hidl-gen_y.yy"
    { ((*yyvalp).fields) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.fields); }
    break;

  case 101:

/* Line 936 of glr.c  */
#line 909 "hidl-gen_y.yy"
    { ((*yyvalp).fields) = new std::vector<NamedReference<Type>*>; }
    break;

  case 102:

/* Line 936 of glr.c  */
#line 911 "hidl-gen_y.yy"
    {
          ((*yyvalp).fields) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.fields);

          // Compound declaration or error
          if ((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.field) != nullptr) {
              ((*yyvalp).fields)->push_back((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.field));
          }
      }
    break;

  case 103:

/* Line 936 of glr.c  */
#line 923 "hidl-gen_y.yy"
    {
      if ((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.field) != nullptr) (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.field)->setDocComment((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.docComment));
      ((*yyvalp).field) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.field);
    }
    break;

  case 104:

/* Line 936 of glr.c  */
#line 927 "hidl-gen_y.yy"
    { ((*yyvalp).field) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.field); }
    break;

  case 105:

/* Line 936 of glr.c  */
#line 930 "hidl-gen_y.yy"
    { ((*yyvalp).field) = nullptr; }
    break;

  case 106:

/* Line 936 of glr.c  */
#line 932 "hidl-gen_y.yy"
    {
          CHECK((*scope)->isCompoundType());

          std::string errorMsg;
          if (static_cast<CompoundType *>(*scope)->style() == CompoundType::STYLE_STRUCT &&
              !isValidStructField((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str), &errorMsg)) {
              std::cerr << "ERROR: " << errorMsg << " at "
                        << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc) << "\n";
              YYERROR;
          }
          ((*yyvalp).field) = new NamedReference<Type>((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str), *(((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.referenceToType), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc)));
      }
    break;

  case 107:

/* Line 936 of glr.c  */
#line 945 "hidl-gen_y.yy"
    {
          CHECK((*scope)->isCompoundType());

          std::string errorMsg;
          if (static_cast<CompoundType *>(*scope)->style() == CompoundType::STYLE_STRUCT &&
              (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.type) != nullptr && (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.type)->isNamedType() &&
              !isValidStructField(static_cast<NamedType*>((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.type))->localName().c_str(), &errorMsg)) {
              std::cerr << "ERROR: " << errorMsg << " at "
                        << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yyloc) << "\n";
              YYERROR;
          }
          // Returns fields only
          ((*yyvalp).field) = nullptr;
      }
    break;

  case 108:

/* Line 936 of glr.c  */
#line 963 "hidl-gen_y.yy"
    {
          CHECK((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.type)->isScope());
          static_cast<Scope*>((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.type))->setAnnotations((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.annotations));
          ((*yyvalp).type) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.type);
      }
    break;

  case 109:

/* Line 936 of glr.c  */
#line 971 "hidl-gen_y.yy"
    { ((*yyvalp).type) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.type); }
    break;

  case 110:

/* Line 936 of glr.c  */
#line 972 "hidl-gen_y.yy"
    { ((*yyvalp).type) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.type); }
    break;

  case 111:

/* Line 936 of glr.c  */
#line 976 "hidl-gen_y.yy"
    { ((*yyvalp).referenceToType) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.referenceToType); }
    break;

  case 112:

/* Line 936 of glr.c  */
#line 977 "hidl-gen_y.yy"
    { ((*yyvalp).referenceToType) = nullptr; }
    break;

  case 115:

/* Line 936 of glr.c  */
#line 987 "hidl-gen_y.yy"
    {
          auto storageType = (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.referenceToType);

          if (storageType == nullptr) {
              std::cerr << "ERROR: Must explicitly specify enum storage type for "
                        << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str) << " at " << (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc) << "\n";
              ast->addSyntaxError();
              storageType = new Reference<Type>(
                  new ScalarType(ScalarType::KIND_INT64, *scope), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc)));
          }

          EnumType* enumType = new EnumType(
              (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str), ast->makeFullName((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yysemantics.yysval.str), *scope), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (3))].yystate.yyloc)), *storageType, *scope);
          enterScope(ast, scope, enumType);
      }
    break;

  case 116:

/* Line 936 of glr.c  */
#line 1003 "hidl-gen_y.yy"
    {
          CHECK((*scope)->isEnum());
          EnumType* enumType = static_cast<EnumType*>(*scope);

          leaveScope(ast, scope);
          ast->addScopedType(enumType, *scope);
          ((*yyvalp).type) = enumType;
      }
    break;

  case 117:

/* Line 936 of glr.c  */
#line 1014 "hidl-gen_y.yy"
    { ((*yyvalp).enumValues) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (4))].yystate.yysemantics.yysval.enumValues); }
    break;

  case 118:

/* Line 936 of glr.c  */
#line 1019 "hidl-gen_y.yy"
    {
        (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.enumValue)->setDocComment((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (2))].yystate.yysemantics.yysval.docComment));
        ((*yyvalp).enumValue) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((2) - (2))].yystate.yysemantics.yysval.enumValue);
      }
    break;

  case 119:

/* Line 936 of glr.c  */
#line 1023 "hidl-gen_y.yy"
    { ((*yyvalp).enumValue) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.enumValue); }
    break;

  case 120:

/* Line 936 of glr.c  */
#line 1028 "hidl-gen_y.yy"
    {
          ((*yyvalp).enumValue) = new EnumValue((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.str) /* name */, nullptr /* value */, convertYYLoc((*yylocp)));
      }
    break;

  case 121:

/* Line 936 of glr.c  */
#line 1032 "hidl-gen_y.yy"
    {
          ((*yyvalp).enumValue) = new EnumValue((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (3))].yystate.yysemantics.yysval.str) /* name */, (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.constantExpression) /* value */, convertYYLoc((*yylocp)));
      }
    break;

  case 122:

/* Line 936 of glr.c  */
#line 1039 "hidl-gen_y.yy"
    { /* do nothing */ }
    break;

  case 123:

/* Line 936 of glr.c  */
#line 1041 "hidl-gen_y.yy"
    {
          CHECK((*scope)->isEnum());
          static_cast<EnumType *>(*scope)->addValue((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.enumValue));
      }
    break;

  case 124:

/* Line 936 of glr.c  */
#line 1046 "hidl-gen_y.yy"
    {
          CHECK((*scope)->isEnum());
          static_cast<EnumType *>(*scope)->addValue((((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.enumValue));
      }
    break;

  case 125:

/* Line 936 of glr.c  */
#line 1051 "hidl-gen_y.yy"
    {
          ast->addSyntaxError();

          CHECK((*scope)->isEnum());
          static_cast<EnumType *>(*scope)->addValue((((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (3))].yystate.yysemantics.yysval.enumValue));
      }
    break;

  case 126:

/* Line 936 of glr.c  */
#line 1058 "hidl-gen_y.yy"
    {
          ast->addSyntaxError();

          CHECK((*scope)->isEnum());
          static_cast<EnumType *>(*scope)->addValue((((yyGLRStackItem const *)yyvsp)[YYFILL ((5) - (5))].yystate.yysemantics.yysval.enumValue));
      }
    break;

  case 127:

/* Line 936 of glr.c  */
#line 1067 "hidl-gen_y.yy"
    { ((*yyvalp).referenceToType) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.referenceToType); }
    break;

  case 128:

/* Line 936 of glr.c  */
#line 1069 "hidl-gen_y.yy"
    {
          (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yysemantics.yysval.templatedType)->setElementType(*(((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (4))].yystate.yysemantics.yysval.referenceToType));
          ((*yyvalp).referenceToType) = new Reference<Type>((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yysemantics.yysval.templatedType), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yyloc)));
      }
    break;

  case 129:

/* Line 936 of glr.c  */
#line 1074 "hidl-gen_y.yy"
    {
          (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (6))].yystate.yysemantics.yysval.templatedType)->setElementType(*(((yyGLRStackItem const *)yyvsp)[YYFILL ((5) - (6))].yystate.yysemantics.yysval.referenceToType));
          (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (6))].yystate.yysemantics.yysval.templatedType)->setElementType(Reference<Type>((((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (6))].yystate.yysemantics.yysval.templatedType), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (6))].yystate.yyloc))));
          ((*yyvalp).referenceToType) = new Reference<Type>((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (6))].yystate.yysemantics.yysval.templatedType), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (6))].yystate.yyloc)));
      }
    break;

  case 130:

/* Line 936 of glr.c  */
#line 1083 "hidl-gen_y.yy"
    {
          ((*yyvalp).arrayType) = new ArrayType(*(((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yysemantics.yysval.referenceToType), (((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (4))].yystate.yysemantics.yysval.constantExpression), *scope);
      }
    break;

  case 131:

/* Line 936 of glr.c  */
#line 1087 "hidl-gen_y.yy"
    {
          ((*yyvalp).arrayType) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (4))].yystate.yysemantics.yysval.arrayType);
          ((*yyvalp).arrayType)->appendDimension((((yyGLRStackItem const *)yyvsp)[YYFILL ((3) - (4))].yystate.yysemantics.yysval.constantExpression));
      }
    break;

  case 132:

/* Line 936 of glr.c  */
#line 1094 "hidl-gen_y.yy"
    { ((*yyvalp).referenceToType) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.referenceToType); }
    break;

  case 133:

/* Line 936 of glr.c  */
#line 1095 "hidl-gen_y.yy"
    { ((*yyvalp).referenceToType) = new Reference<Type>((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.arrayType), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc))); }
    break;

  case 134:

/* Line 936 of glr.c  */
#line 1097 "hidl-gen_y.yy"
    {
          // "interface" is a synonym of android.hidl.base@1.0::IBase
          ((*yyvalp).referenceToType) = new Reference<Type>(gIBaseFqName, convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc)));
      }
    break;

  case 135:

/* Line 936 of glr.c  */
#line 1104 "hidl-gen_y.yy"
    { ((*yyvalp).referenceToType) = (((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.referenceToType); }
    break;

  case 136:

/* Line 936 of glr.c  */
#line 1106 "hidl-gen_y.yy"
    {
          ((*yyvalp).referenceToType) = new Reference<Type>((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yysemantics.yysval.type), convertYYLoc((((yyGLRStackItem const *)yyvsp)[YYFILL ((1) - (1))].yystate.yyloc)));
      }
    break;



/* Line 936 of glr.c  */
#line 2645 "hidl-gen_y.cpp"
      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


/*ARGSUSED*/ static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYUSE (yy0);
  YYUSE (yy1);

  switch (yyn)
    {
      
      default: break;
    }
}

			      /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (yyparser);
  YYUSE (scanner);
  YYUSE (ast);
  YYUSE (scope);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yystos[yys->yylrState],
		&yys->yysemantics.yysval, &yys->yyloc, yyparser, scanner, ast, scope);
  else
    {
#if YYDEBUG
      if (yydebug)
	{
	  if (yys->yysemantics.yyfirstVal)
	    YYFPRINTF (stderr, "%s unresolved ", yymsg);
	  else
	    YYFPRINTF (stderr, "%s incomplete ", yymsg);
	  yy_symbol_print (stderr, yystos[yys->yylrState],
			   NULL, &yys->yyloc, yyparser, scanner, ast, scope);
	  YYFPRINTF (stderr, "\n");
	}
#endif

      if (yys->yysemantics.yyfirstVal)
	{
	  yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
	  yyGLRState *yyrh;
	  int yyn;
	  for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
	       yyn > 0;
	       yyrh = yyrh->yypred, yyn -= 1)
	    yydestroyGLRState (yymsg, yyrh, yyparser, scanner, ast, scope);
	}
    }
}

/** Left-hand-side symbol for rule #RULE.  */
static inline yySymbol
yylhsNonterm (yyRuleNum yyrule)
{
  return yyr1[yyrule];
}

#define yyis_pact_ninf(yystate) \
  ((yystate) == YYPACT_NINF)

/** True iff LR state STATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yyStateNum yystate)
{
  return yyis_pact_ninf (yypact[yystate]);
}

/** The default reduction for STATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yyStateNum yystate)
{
  return yydefact[yystate];
}

#define yyis_table_ninf(yytable_value) \
  YYID (0)

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *CONFLICTS to a pointer into yyconfl to 0-terminated list of
 *  conflicting reductions.
 */
static inline void
yygetLRActions (yyStateNum yystate, int yytoken,
		int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yyis_table_ninf (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

static inline yyStateNum
yyLRgotoState (yyStateNum yystate, yySymbol yylhs)
{
  int yyr;
  yyr = yypgoto[yylhs - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yylhs - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

				/* GLRStates */

/** Return a fresh GLRStackItem.  Callers should call
 * YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 * headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  RULENUM on the semantic values in RHS to the list of
 *  alternative actions for STATE.  Assumes that RHS comes from
 *  stack #K of *STACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, size_t yyk, yyGLRState* yystate,
		     yyGLRState* rhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  yynewOption->yystate = rhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
      yynewOption->yyloc = yylloc;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

				/* GLRStacks */

/** Initialize SET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates = (yyGLRState**) YYMALLOC (16 * sizeof yyset->yystates[0]);
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = NULL;
  yyset->yylookaheadNeeds =
    (yybool*) YYMALLOC (16 * sizeof yyset->yylookaheadNeeds[0]);
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize STACK to a single empty stack, with total maximum
 *  capacity for all stacks of SIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, size_t yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems =
    (yyGLRStackItem*) YYMALLOC (yysize * sizeof yystackp->yynextFree[0]);
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = NULL;
  yystackp->yylastDeleted = NULL;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
  &((YYTOITEMS) - ((YYFROMITEMS) - (yyGLRStackItem*) (YYX)))->YYTYPE

/** If STACK is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  size_t yysize, yynewSize;
  size_t yyn;
  yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems = (yyGLRStackItem*) YYMALLOC (yynewSize * sizeof yynewItems[0]);
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*(yybool *) yyp0)
	{
	  yyGLRState* yys0 = &yyp0->yystate;
	  yyGLRState* yys1 = &yyp1->yystate;
	  if (yys0->yypred != NULL)
	    yys1->yypred =
	      YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
	  if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != NULL)
	    yys1->yysemantics.yyfirstVal =
	      YYRELOC(yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
	}
      else
	{
	  yySemanticOption* yyv0 = &yyp0->yyoption;
	  yySemanticOption* yyv1 = &yyp1->yyoption;
	  if (yyv0->yystate != NULL)
	    yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
	  if (yyv0->yynext != NULL)
	    yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
	}
    }
  if (yystackp->yysplitPoint != NULL)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
				 yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != NULL)
      yystackp->yytops.yystates[yyn] =
	YYRELOC (yystackp->yyitems, yynewItems,
		 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that S is a GLRState somewhere on STACK, update the
 *  splitpoint of STACK, if needed, so that it is at least as deep as
 *  S.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != NULL && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #K in STACK.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yytops.yystates[yyk] != NULL)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = NULL;
}

/** Undelete the last stack that was marked as deleted.  Can only be
    done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == NULL || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = NULL;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  size_t yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == NULL)
	{
	  if (yyi == yyj)
	    {
	      YYDPRINTF ((stderr, "Removing dead stacks.\n"));
	    }
	  yystackp->yytops.yysize -= 1;
	}
      else
	{
	  yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
	  /* In the current implementation, it's unnecessary to copy
	     yystackp->yytops.yylookaheadNeeds[yyi] since, after
	     yyremoveDeletes returns, the parser immediately either enters
	     deterministic operation or shifts a token.  However, it doesn't
	     hurt, and the code might evolve to need it.  */
	  yystackp->yytops.yylookaheadNeeds[yyj] =
	    yystackp->yytops.yylookaheadNeeds[yyi];
	  if (yyj != yyi)
	    {
	      YYDPRINTF ((stderr, "Rename stack %lu -> %lu.\n",
			  (unsigned long int) yyi, (unsigned long int) yyj));
	    }
	  yyj += 1;
	}
      yyi += 1;
    }
}

/** Shift to a new state on stack #K of STACK, corresponding to LR state
 * LRSTATE, at input position POSN, with (resolved) semantic value SVAL.  */
static inline void
yyglrShift (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
	    size_t yyposn,
	    YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yysval = *yyvalp;
  yynewState->yyloc = *yylocp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #K of YYSTACK, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
		 size_t yyposn, yyGLRState* rhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = NULL;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, rhs, yyrule);
}

/** Pop the symbols consumed by reduction #RULE from the top of stack
 *  #K of STACK, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *VALP to the resulting value,
 *  and *LOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
	    YYSTYPE* yyvalp, YYLTYPE* yylocp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == NULL)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* rhs = (yyGLRStackItem*) yystackp->yytops.yystates[yyk];
      YYASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      return yyuserAction (yyrule, yynrhs, rhs,
			   yyvalp, yylocp, yystackp, yyparser, scanner, ast, scope);
    }
  else
    {
      /* At present, doAction is never called in nondeterministic
       * mode, so this branch is never taken.  It is here in
       * anticipation of a future feature that will allow immediate
       * evaluation of selected actions in nondeterministic mode.  */
      int yyi;
      yyGLRState* yys;
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
	= yystackp->yytops.yystates[yyk];
      if (yynrhs == 0)
	/* Set default location.  */
	yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yys->yyloc;
      for (yyi = 0; yyi < yynrhs; yyi += 1)
	{
	  yys = yys->yypred;
	  YYASSERT (yys);
	}
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
			   yyvalp, yylocp, yystackp, yyparser, scanner, ast, scope);
    }
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)		\
do {					\
  if (yydebug)				\
    yy_reduce_print Args;		\
} while (YYID (0))

/*----------------------------------------------------------.
| Report that the RULE is going to be reduced on stack #K.  |
`----------------------------------------------------------*/

/*ARGSUSED*/ static inline void
yy_reduce_print (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
		 YYSTYPE* yyvalp, YYLTYPE* yylocp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  int yynrhs = yyrhsLength (yyrule);
  yybool yynormal __attribute__ ((__unused__)) =
    (yystackp->yysplitPoint == NULL);
  yyGLRStackItem* yyvsp = (yyGLRStackItem*) yystackp->yytops.yystates[yyk];
  int yylow = 1;
  int yyi;
  YYUSE (yyvalp);
  YYUSE (yylocp);
  YYUSE (yyparser);
  YYUSE (scanner);
  YYUSE (ast);
  YYUSE (scope);
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu):\n",
	     (unsigned long int) yyk, yyrule - 1,
	     (unsigned long int) yyrline[yyrule]);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(((yyGLRStackItem const *)yyvsp)[YYFILL ((yyi + 1) - (yynrhs))].yystate.yysemantics.yysval)
		       , &(((yyGLRStackItem const *)yyvsp)[YYFILL ((yyi + 1) - (yynrhs))].yystate.yyloc)		       , yyparser, scanner, ast, scope);
      YYFPRINTF (stderr, "\n");
    }
}
#endif

/** Pop items off stack #K of STACK according to grammar rule RULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with RULE and store its value with the
 *  newly pushed state, if FORCEEVAL or if STACK is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #K from
 *  the STACK.  In this case, the (necessarily deferred) semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
	     yybool yyforceEval, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  size_t yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == NULL)
    {
      YYSTYPE yysval;
      YYLTYPE yyloc;

      YY_REDUCE_PRINT ((yystackp, yyk, yyrule, &yysval, &yyloc, yyparser, scanner, ast, scope));
      YYCHK (yydoAction (yystackp, yyk, yyrule, &yysval,
			 &yyloc, yyparser, scanner, ast, scope));
      YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyrule], &yysval, &yyloc);
      yyglrShift (yystackp, yyk,
		  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
				 yylhsNonterm (yyrule)),
		  yyposn, &yysval, &yyloc);
    }
  else
    {
      size_t yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yyStateNum yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
	   0 < yyn; yyn -= 1)
	{
	  yys = yys->yypred;
	  YYASSERT (yys);
	}
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
		  "Reduced stack %lu by rule #%d; action deferred.  Now in state %d.\n",
		  (unsigned long int) yyk, yyrule - 1, yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
	if (yyi != yyk && yystackp->yytops.yystates[yyi] != NULL)
	  {
	    yyGLRState* yyp, *yysplit = yystackp->yysplitPoint;
	    yyp = yystackp->yytops.yystates[yyi];
	    while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
	      {
		if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
		  {
		    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
		    yymarkStackDeleted (yystackp, yyk);
		    YYDPRINTF ((stderr, "Merging stack %lu into stack %lu.\n",
				(unsigned long int) yyk,
				(unsigned long int) yyi));
		    return yyok;
		  }
		yyp = yyp->yypred;
	      }
	  }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static size_t
yysplitStack (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yysplitPoint == NULL)
    {
      YYASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yysize >= yystackp->yytops.yycapacity)
    {
      yyGLRState** yynewStates;
      yybool* yynewLookaheadNeeds;

      yynewStates = NULL;

      if (yystackp->yytops.yycapacity
	  > (YYSIZEMAX / (2 * sizeof yynewStates[0])))
	yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      yynewStates =
	(yyGLRState**) YYREALLOC (yystackp->yytops.yystates,
				  (yystackp->yytops.yycapacity
				   * sizeof yynewStates[0]));
      if (yynewStates == NULL)
	yyMemoryExhausted (yystackp);
      yystackp->yytops.yystates = yynewStates;

      yynewLookaheadNeeds =
	(yybool*) YYREALLOC (yystackp->yytops.yylookaheadNeeds,
			     (yystackp->yytops.yycapacity
			      * sizeof yynewLookaheadNeeds[0]));
      if (yynewLookaheadNeeds == NULL)
	yyMemoryExhausted (yystackp);
      yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize-1;
}

/** True iff Y0 and Y1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
	   yyn = yyrhsLength (yyy0->yyrule);
	   yyn > 0;
	   yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
	if (yys0->yyposn != yys1->yyposn)
	  return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (Y0,Y1), destructively merge the
 *  alternative semantic values for the RHS-symbols of Y1 and Y0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       yyn > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
	break;
      else if (yys0->yyresolved)
	{
	  yys1->yyresolved = yytrue;
	  yys1->yysemantics.yysval = yys0->yysemantics.yysval;
	}
      else if (yys1->yyresolved)
	{
	  yys0->yyresolved = yytrue;
	  yys0->yysemantics.yysval = yys1->yysemantics.yysval;
	}
      else
	{
	  yySemanticOption** yyz0p;
	  yySemanticOption* yyz1;
	  yyz0p = &yys0->yysemantics.yyfirstVal;
	  yyz1 = yys1->yysemantics.yyfirstVal;
	  while (YYID (yytrue))
	    {
	      if (yyz1 == *yyz0p || yyz1 == NULL)
		break;
	      else if (*yyz0p == NULL)
		{
		  *yyz0p = yyz1;
		  break;
		}
	      else if (*yyz0p < yyz1)
		{
		  yySemanticOption* yyz = *yyz0p;
		  *yyz0p = yyz1;
		  yyz1 = yyz1->yynext;
		  (*yyz0p)->yynext = yyz;
		}
	      yyz0p = &(*yyz0p)->yynext;
	    }
	  yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
	}
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
	return 0;
      else
	return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yyGLRState* yys,
				   yyGLRStack* yystackp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope);


/** Resolve the previous N states starting at and including state S.  If result
 *  != yyok, some states may have been left unresolved possibly with empty
 *  semantic option chains.  Regardless of whether result = yyok, each state
 *  has been left with consistent data so that yydestroyGLRState can be invoked
 *  if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
		 yyGLRStack* yystackp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp, yyparser, scanner, ast, scope));
      if (! yys->yyresolved)
	YYCHK (yyresolveValue (yys, yystackp, yyparser, scanner, ast, scope));
    }
  return yyok;
}

/** Resolve the states for the RHS of OPT, perform its user action, and return
 *  the semantic value and location.  Regardless of whether result = yyok, all
 *  RHS states have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
		 YYSTYPE* yyvalp, YYLTYPE* yylocp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs;
  int yychar_current;
  YYSTYPE yylval_current;
  YYLTYPE yylloc_current;
  YYRESULTTAG yyflag;

  yynrhs = yyrhsLength (yyopt->yyrule);
  yyflag = yyresolveStates (yyopt->yystate, yynrhs, yystackp, yyparser, scanner, ast, scope);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
	yydestroyGLRState ("Cleanup: popping", yys, yyparser, scanner, ast, scope);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yyopt->yystate->yyloc;
  yychar_current = yychar;
  yylval_current = yylval;
  yylloc_current = yylloc;
  yychar = yyopt->yyrawchar;
  yylval = yyopt->yyval;
  yylloc = yyopt->yyloc;
  yyflag = yyuserAction (yyopt->yyrule, yynrhs,
			   yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
			   yyvalp, yylocp, yystackp, yyparser, scanner, ast, scope);
  yychar = yychar_current;
  yylval = yylval_current;
  yylloc = yylloc_current;
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == NULL)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, empty>\n",
	       yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
	       yyx->yyrule - 1);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
	       yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
	       yyx->yyrule - 1, (unsigned long int) (yys->yyposn + 1),
	       (unsigned long int) yyx->yystate->yyposn);
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
	{
	  if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
	    YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
		       yytokenName (yyrhs[yyprhs[yyx->yyrule]+yyi-1]));
	  else
	    YYFPRINTF (stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent+2, "",
		       yytokenName (yyrhs[yyprhs[yyx->yyrule]+yyi-1]),
		       (unsigned long int) (yystates[yyi - 1]->yyposn + 1),
		       (unsigned long int) yystates[yyi]->yyposn);
	}
      else
	yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

/*ARGSUSED*/ static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
		   yySemanticOption* yyx1, YYLTYPE *yylocp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  YYUSE (yyx0);
  YYUSE (yyx1);

#if YYDEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyreportTree (yyx0, 2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyreportTree (yyx1, 2);
  YYFPRINTF (stderr, "\n");
#endif

  yyerror (yylocp, yyparser, scanner, ast, scope, YY_("syntax is ambiguous"));
  return yyabort;
}

/** Starting at and including state S1, resolve the location for each of the
 *  previous N1 states that is unresolved.  The first semantic option of a state
 *  is always chosen.  */
static void
yyresolveLocations (yyGLRState* yys1, int yyn1,
		    yyGLRStack *yystackp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1, yystackp, yyparser, scanner, ast, scope);
      if (!yys1->yyresolved)
	{
	  yySemanticOption *yyoption;
	  yyGLRStackItem yyrhsloc[1 + YYMAXRHS];
	  int yynrhs;
	  int yychar_current;
	  YYSTYPE yylval_current;
	  YYLTYPE yylloc_current;
	  yyoption = yys1->yysemantics.yyfirstVal;
	  YYASSERT (yyoption != NULL);
	  yynrhs = yyrhsLength (yyoption->yyrule);
	  if (yynrhs > 0)
	    {
	      yyGLRState *yys;
	      int yyn;
	      yyresolveLocations (yyoption->yystate, yynrhs,
				  yystackp, yyparser, scanner, ast, scope);
	      for (yys = yyoption->yystate, yyn = yynrhs;
		   yyn > 0;
		   yys = yys->yypred, yyn -= 1)
		yyrhsloc[yyn].yystate.yyloc = yys->yyloc;
	    }
	  else
	    {
	      /* Both yyresolveAction and yyresolveLocations traverse the GSS
		 in reverse rightmost order.  It is only necessary to invoke
		 yyresolveLocations on a subforest for which yyresolveAction
		 would have been invoked next had an ambiguity not been
		 detected.  Thus the location of the previous state (but not
		 necessarily the previous state itself) is guaranteed to be
		 resolved already.  */
	      yyGLRState *yyprevious = yyoption->yystate;
	      yyrhsloc[0].yystate.yyloc = yyprevious->yyloc;
	    }
	  yychar_current = yychar;
	  yylval_current = yylval;
	  yylloc_current = yylloc;
	  yychar = yyoption->yyrawchar;
	  yylval = yyoption->yyval;
	  yylloc = yyoption->yyloc;
	  YYLLOC_DEFAULT ((yys1->yyloc), yyrhsloc, yynrhs);
	  yychar = yychar_current;
	  yylval = yylval_current;
	  yylloc = yylloc_current;
	}
    }
}

/** Resolve the ambiguity represented in state S, perform the indicated
 *  actions, and set the semantic value of S.  If result != yyok, the chain of
 *  semantic options in S has been cleared instead or it has been left
 *  unmodified except that redundant options may have been removed.  Regardless
 *  of whether result = yyok, S has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest;
  yySemanticOption** yypp;
  yybool yymerge;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;
  YYLTYPE *yylocp = &yys->yyloc;

  yybest = yyoptionList;
  yymerge = yyfalse;
  for (yypp = &yyoptionList->yynext; *yypp != NULL; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
	{
	  yymergeOptionSets (yybest, yyp);
	  *yypp = yyp->yynext;
	}
      else
	{
	  switch (yypreference (yybest, yyp))
	    {
	    case 0:
	      yyresolveLocations (yys, 1, yystackp, yyparser, scanner, ast, scope);
	      return yyreportAmbiguity (yybest, yyp, yylocp, yyparser, scanner, ast, scope);
	      break;
	    case 1:
	      yymerge = yytrue;
	      break;
	    case 2:
	      break;
	    case 3:
	      yybest = yyp;
	      yymerge = yyfalse;
	      break;
	    default:
	      /* This cannot happen so it is not worth a YYASSERT (yyfalse),
		 but some compilers complain if the default case is
		 omitted.  */
	      break;
	    }
	  yypp = &yyp->yynext;
	}
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval,
				yylocp, yyparser, scanner, ast, scope);
      if (yyflag == yyok)
	for (yyp = yybest->yynext; yyp != NULL; yyp = yyp->yynext)
	  {
	    if (yyprec == yydprec[yyp->yyrule])
	      {
		YYSTYPE yysval_other;
		YYLTYPE yydummy;
		yyflag = yyresolveAction (yyp, yystackp, &yysval_other,
					  &yydummy, yyparser, scanner, ast, scope);
		if (yyflag != yyok)
		  {
		    yydestruct ("Cleanup: discarding incompletely merged value for",
				yystos[yys->yylrState],
				&yysval, yylocp, yyparser, scanner, ast, scope);
		    break;
		  }
		yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
	      }
	  }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval, yylocp, yyparser, scanner, ast, scope);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yysval = yysval;
    }
  else
    yys->yysemantics.yyfirstVal = NULL;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  if (yystackp->yysplitPoint != NULL)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
	   yys != yystackp->yysplitPoint;
	   yys = yys->yypred, yyn += 1)
	continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
			     , yyparser, scanner, ast, scope));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystackp)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == NULL)
    return;

  for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = NULL;
       yyp != yystackp->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = ((yyGLRStackItem*) yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = NULL;
  yystackp->yylastDeleted = NULL;

  while (yyr != NULL)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, size_t yyk,
		   size_t yyposn, YYLTYPE *yylocp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  int yyaction;
  const short int* yyconflicts;
  yyRuleNum yyrule;

  while (yystackp->yytops.yystates[yyk] != NULL)
    {
      yyStateNum yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YYDPRINTF ((stderr, "Stack %lu Entering state %d\n",
		  (unsigned long int) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
	{
	  yyrule = yydefaultAction (yystate);
	  if (yyrule == 0)
	    {
	      YYDPRINTF ((stderr, "Stack %lu dies.\n",
			  (unsigned long int) yyk));
	      yymarkStackDeleted (yystackp, yyk);
	      return yyok;
	    }
	  YYCHK (yyglrReduce (yystackp, yyk, yyrule, yyfalse, yyparser, scanner, ast, scope));
	}
      else
	{
	  yySymbol yytoken;
	  yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;
	  if (yychar == YYEMPTY)
	    {
	      YYDPRINTF ((stderr, "Reading a token: "));
	      yychar = YYLEX;
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

	  yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);

	  while (*yyconflicts != 0)
	    {
	      size_t yynewStack = yysplitStack (yystackp, yyk);
	      YYDPRINTF ((stderr, "Splitting off stack %lu from %lu.\n",
			  (unsigned long int) yynewStack,
			  (unsigned long int) yyk));
	      YYCHK (yyglrReduce (yystackp, yynewStack,
				  *yyconflicts, yyfalse, yyparser, scanner, ast, scope));
	      YYCHK (yyprocessOneStack (yystackp, yynewStack,
					yyposn, yylocp, yyparser, scanner, ast, scope));
	      yyconflicts += 1;
	    }

	  if (yyisShiftAction (yyaction))
	    break;
	  else if (yyisErrorAction (yyaction))
	    {
	      YYDPRINTF ((stderr, "Stack %lu dies.\n",
			  (unsigned long int) yyk));
	      yymarkStackDeleted (yystackp, yyk);
	      break;
	    }
	  else
	    YYCHK (yyglrReduce (yystackp, yyk, -yyaction,
				yyfalse, yyparser, scanner, ast, scope));
	}
    }
  return yyok;
}

/*ARGSUSED*/ static void
yyreportSyntaxError (yyGLRStack* yystackp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  if (yystackp->yyerrState == 0)
    {
#if YYERROR_VERBOSE
      int yyn;
      yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
      if (YYPACT_NINF < yyn && yyn <= YYLAST)
	{
	  yySymbol yytoken = YYTRANSLATE (yychar);
	  size_t yysize0 = yytnamerr (NULL, yytokenName (yytoken));
	  size_t yysize = yysize0;
	  size_t yysize1;
	  yybool yysize_overflow = yyfalse;
	  char* yymsg = NULL;
	  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;
	  char *yyfmt;
	  char const *yyf;
	  static char const yyunexpected[] = "syntax error, unexpected %s";
	  static char const yyexpecting[] = ", expecting %s";
	  static char const yyor[] = " or %s";
	  char yyformat[sizeof yyunexpected
			+ sizeof yyexpecting - 1
			+ ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
			   * (sizeof yyor - 1))];
	  char const *yyprefix = yyexpecting;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn + 1;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 1;

	  yyarg[0] = yytokenName (yytoken);
	  yyfmt = yystpcpy (yyformat, yyunexpected);

	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
		  {
		    yycount = 1;
		    yysize = yysize0;
		    yyformat[sizeof yyunexpected - 1] = '\0';
		    break;
		  }
		yyarg[yycount++] = yytokenName (yyx);
		yysize1 = yysize + yytnamerr (NULL, yytokenName (yyx));
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + strlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow)
	    yymsg = (char *) YYMALLOC (yysize);

	  if (yymsg)
	    {
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
		{
		  if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		    {
		      yyp += yytnamerr (yyp, yyarg[yyi++]);
		      yyf += 2;
		    }
		  else
		    {
		      yyp++;
		      yyf++;
		    }
		}
	      yyerror (&yylloc, yyparser, scanner, ast, scope, yymsg);
	      YYFREE (yymsg);
	    }
	  else
	    {
	      yyerror (&yylloc, yyparser, scanner, ast, scope, YY_("syntax error"));
	      yyMemoryExhausted (yystackp);
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (&yylloc, yyparser, scanner, ast, scope, YY_("syntax error"));
      yynerrs += 1;
    }
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
/*ARGSUSED*/ static void
yyrecoverSyntaxError (yyGLRStack* yystackp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  size_t yyk;
  int yyj;

  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (YYID (yytrue))
      {
	yySymbol yytoken;
	if (yychar == YYEOF)
	  yyFail (yystackp, &yylloc, yyparser, scanner, ast, scope, NULL);
	if (yychar != YYEMPTY)
	  {
	    /* We throw away the lookahead, but the error range
	       of the shifted error token must take it into account.  */
	    yyGLRState *yys = yystackp->yytops.yystates[0];
	    yyGLRStackItem yyerror_range[3];
	    yyerror_range[1].yystate.yyloc = yys->yyloc;
	    yyerror_range[2].yystate.yyloc = yylloc;
	    YYLLOC_DEFAULT ((yys->yyloc), yyerror_range, 2);
	    yytoken = YYTRANSLATE (yychar);
	    yydestruct ("Error: discarding",
			yytoken, &yylval, &yylloc, yyparser, scanner, ast, scope);
	  }
	YYDPRINTF ((stderr, "Reading a token: "));
	yychar = YYLEX;
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
	yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
	if (yyis_pact_ninf (yyj))
	  return;
	yyj += yytoken;
	if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
	  {
	    if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
	      return;
	  }
	else if (yytable[yyj] != 0 && ! yyis_table_ninf (yytable[yyj]))
	  return;
      }

  /* Reduce to one stack.  */
  for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
    if (yystackp->yytops.yystates[yyk] != NULL)
      break;
  if (yyk >= yystackp->yytops.yysize)
    yyFail (yystackp, &yylloc, yyparser, scanner, ast, scope, NULL);
  for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
    yymarkStackDeleted (yystackp, yyk);
  yyremoveDeletes (yystackp);
  yycompressStack (yystackp);

  /* Now pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != NULL)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      yyj = yypact[yys->yylrState];
      if (! yyis_pact_ninf (yyj))
	{
	  yyj += YYTERROR;
	  if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR
	      && yyisShiftAction (yytable[yyj]))
	    {
	      /* Shift the error token having adjusted its location.  */
	      YYLTYPE yyerrloc;
	      yystackp->yyerror_range[2].yystate.yyloc = yylloc;
	      YYLLOC_DEFAULT (yyerrloc, (yystackp->yyerror_range), 2);
	      YY_SYMBOL_PRINT ("Shifting", yystos[yytable[yyj]],
			       &yylval, &yyerrloc);
	      yyglrShift (yystackp, 0, yytable[yyj],
			  yys->yyposn, &yylval, &yyerrloc);
	      yys = yystackp->yytops.yystates[0];
	      break;
	    }
	}
      yystackp->yyerror_range[1].yystate.yyloc = yys->yyloc;
      if (yys->yypred != NULL)
	yydestroyGLRState ("Error: popping", yys, yyparser, scanner, ast, scope);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == NULL)
    yyFail (yystackp, &yylloc, yyparser, scanner, ast, scope, NULL);
}

#define YYCHK1(YYE)							     \
  do {									     \
    switch (YYE) {							     \
    case yyok:								     \
      break;								     \
    case yyabort:							     \
      goto yyabortlab;							     \
    case yyaccept:							     \
      goto yyacceptlab;							     \
    case yyerr:								     \
      goto yyuser_error;						     \
    default:								     \
      goto yybuglab;							     \
    }									     \
  } while (YYID (0))


/*----------.
| yyparse.  |
`----------*/

int
yyparse (yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  size_t yyposn;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif


  /* User initialization code.  */
  
/* Line 2331 of glr.c  */
#line 204 "hidl-gen_y.yy"
{
    // Initialize the initial location.
    yylloc.begin.filename = yylloc.end.filename =
        const_cast<std::string *>(&ast->getFilename());
}

/* Line 2331 of glr.c  */
#line 4076 "hidl-gen_y.cpp"

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval, &yylloc);
  yyposn = 0;

  while (YYID (yytrue))
    {
      /* For efficiency, we have two loops, the first of which is
	 specialized to deterministic operation (single stack, no
	 potential ambiguity).  */
      /* Standard mode */
      while (YYID (yytrue))
	{
	  yyRuleNum yyrule;
	  int yyaction;
	  const short int* yyconflicts;

	  yyStateNum yystate = yystack.yytops.yystates[0]->yylrState;
	  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
	  if (yystate == YYFINAL)
	    goto yyacceptlab;
	  if (yyisDefaultedState (yystate))
	    {
	      yyrule = yydefaultAction (yystate);
	      if (yyrule == 0)
		{
		  yystack.yyerror_range[1].yystate.yyloc = yylloc;
		  yyreportSyntaxError (&yystack, yyparser, scanner, ast, scope);
		  goto yyuser_error;
		}
	      YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue, yyparser, scanner, ast, scope));
	    }
	  else
	    {
	      yySymbol yytoken;
	      if (yychar == YYEMPTY)
		{
		  YYDPRINTF ((stderr, "Reading a token: "));
		  yychar = YYLEX;
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

	      yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
	      if (*yyconflicts != 0)
		break;
	      if (yyisShiftAction (yyaction))
		{
		  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
		  yychar = YYEMPTY;
		  yyposn += 1;
		  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval, &yylloc);
		  if (0 < yystack.yyerrState)
		    yystack.yyerrState -= 1;
		}
	      else if (yyisErrorAction (yyaction))
		{
		  yystack.yyerror_range[1].yystate.yyloc = yylloc;
		  yyreportSyntaxError (&yystack, yyparser, scanner, ast, scope);
		  goto yyuser_error;
		}
	      else
		YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue, yyparser, scanner, ast, scope));
	    }
	}

      while (YYID (yytrue))
	{
	  yySymbol yytoken_to_shift;
	  size_t yys;

	  for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
	    yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

	  /* yyprocessOneStack returns one of three things:

	      - An error flag.  If the caller is yyprocessOneStack, it
		immediately returns as well.  When the caller is finally
		yyparse, it jumps to an error label via YYCHK1.

	      - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
		(&yystack, yys), which sets the top state of yys to NULL.  Thus,
		yyparse's following invocation of yyremoveDeletes will remove
		the stack.

	      - yyok, when ready to shift a token.

	     Except in the first case, yyparse will invoke yyremoveDeletes and
	     then shift the next token onto all remaining stacks.  This
	     synchronization of the shift (that is, after all preceding
	     reductions on all stacks) helps prevent double destructor calls
	     on yylval in the event of memory exhaustion.  */

	  for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
	    YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn, &yylloc, yyparser, scanner, ast, scope));
	  yyremoveDeletes (&yystack);
	  if (yystack.yytops.yysize == 0)
	    {
	      yyundeleteLastStack (&yystack);
	      if (yystack.yytops.yysize == 0)
		yyFail (&yystack, &yylloc, yyparser, scanner, ast, scope, YY_("syntax error"));
	      YYCHK1 (yyresolveStack (&yystack, yyparser, scanner, ast, scope));
	      YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
	      yystack.yyerror_range[1].yystate.yyloc = yylloc;
	      yyreportSyntaxError (&yystack, yyparser, scanner, ast, scope);
	      goto yyuser_error;
	    }

	  /* If any yyglrShift call fails, it will fail after shifting.  Thus,
	     a copy of yylval will already be on stack 0 in the event of a
	     failure in the following loop.  Thus, yychar is set to YYEMPTY
	     before the loop to make sure the user destructor for yylval isn't
	     called twice.  */
	  yytoken_to_shift = YYTRANSLATE (yychar);
	  yychar = YYEMPTY;
	  yyposn += 1;
	  for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
	    {
	      int yyaction;
	      const short int* yyconflicts;
	      yyStateNum yystate = yystack.yytops.yystates[yys]->yylrState;
	      yygetLRActions (yystate, yytoken_to_shift, &yyaction,
			      &yyconflicts);
	      /* Note that yyconflicts were handled by yyprocessOneStack.  */
	      YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) yys));
	      YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
	      yyglrShift (&yystack, yys, yyaction, yyposn,
			  &yylval, &yylloc);
	      YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
			  (unsigned long int) yys,
			  yystack.yytops.yystates[yys]->yylrState));
	    }

	  if (yystack.yytops.yysize == 1)
	    {
	      YYCHK1 (yyresolveStack (&yystack, yyparser, scanner, ast, scope));
	      YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
	      yycompressStack (&yystack);
	      break;
	    }
	}
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack, yyparser, scanner, ast, scope);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YYASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (&yylloc, yyparser, scanner, ast, scope, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
		YYTRANSLATE (yychar),
		&yylval, &yylloc, yyparser, scanner, ast, scope);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
	{
	  size_t yysize = yystack.yytops.yysize;
	  size_t yyk;
	  for (yyk = 0; yyk < yysize; yyk += 1)
	    if (yystates[yyk])
	      {
		while (yystates[yyk])
		  {
		    yyGLRState *yys = yystates[yyk];
		    yystack.yyerror_range[1].yystate.yyloc = yys->yyloc;
		    if (yys->yypred != NULL)
		      yydestroyGLRState ("Cleanup: popping", yys, yyparser, scanner, ast, scope);
		    yystates[yyk] = yys->yypred;
		    yystack.yynextFree -= 1;
		    yystack.yyspaceLeft += 1;
		  }
		break;
	      }
	}
      yyfreeGLRStack (&yystack);
    }

  /* Make sure YYID is used.  */
  return YYID (yyresult);
}

/* DEBUGGING ONLY */
#if YYDEBUG
static void yypstack (yyGLRStack* yystackp, size_t yyk)
  __attribute__ ((__unused__));
static void yypdumpstack (yyGLRStack* yystackp) __attribute__ ((__unused__));

static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@%lu", yys->yylrState,
             (unsigned long int) yys->yyposn);
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == NULL)
    YYFPRINTF (stderr, "<null>");
  else
    yy_yypstack (yyst);
  YYFPRINTF (stderr, "\n");
}

static void
yypstack (yyGLRStack* yystackp, size_t yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)							     \
    ((YYX) == NULL ? -1 : (yyGLRStackItem*) (YYX) - yystackp->yyitems)


static void
yypdumpstack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yyp;
  size_t yyi;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YYFPRINTF (stderr, "%3lu. ",
                 (unsigned long int) (yyp - yystackp->yyitems));
      if (*(yybool *) yyp)
	{
	  YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
		     yyp->yystate.yyresolved, yyp->yystate.yylrState,
		     (unsigned long int) yyp->yystate.yyposn,
		     (long int) YYINDEX (yyp->yystate.yypred));
	  if (! yyp->yystate.yyresolved)
	    YYFPRINTF (stderr, ", firstVal: %ld",
		       (long int) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
	}
      else
	{
	  YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
		     yyp->yyoption.yyrule - 1,
		     (long int) YYINDEX (yyp->yyoption.yystate),
		     (long int) YYINDEX (yyp->yyoption.yynext));
	}
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
	       (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
  YYFPRINTF (stderr, "\n");
}
#endif



/* Line 2634 of glr.c  */
#line 1111 "hidl-gen_y.yy"


void yy::parser::error(
        const yy::parser::location_type &where,
        const std::string &errstr) {
    std::cerr << "ERROR: " << errstr << " at " << where << "\n";
}


/* Line 2634 of glr.c  */
#line 4386 "hidl-gen_y.cpp"
/*------------------.
| Report an error.  |
`------------------*/

static void
yyerror (yy::parser::location_type *yylocationp, yy::parser& yyparser, void* scanner, android::AST* const ast, android::Scope** const scope, const char* msg)
{
  YYUSE (yyparser);
  YYUSE (scanner);
  YYUSE (ast);
  YYUSE (scope);
  yyparser.error (*yylocationp, msg);
}



namespace yy {

/* Line 2634 of glr.c  */
#line 4406 "hidl-gen_y.cpp"
  /// Build a parser object.
  parser::parser (void* scanner_yyarg, android::AST* const ast_yyarg, android::Scope** const scope_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      ast (ast_yyarg),
      scope (scope_yyarg)
  {
  }

  parser::~parser ()
  {
  }

  int
  parser::parse ()
  {
    return ::yyparse (*this, scanner, ast, scope);
  }

#if YYDEBUG
  /*--------------------.
  | Print this symbol.  |
  `--------------------*/

  inline void
  parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    /* Pacify ``unused variable'' warnings.  */
    YYUSE (yyvaluep);
    YYUSE (yylocationp);
    switch (yytype)
      {
          default:
	  break;
      }
  }


  void
  parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < YYNTOKENS ? "token" : "nterm")
	       << ' ' << yytname[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }

  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }

#endif

} // yy

/* Line 2634 of glr.c  */
#line 4491 "hidl-gen_y.cpp"




