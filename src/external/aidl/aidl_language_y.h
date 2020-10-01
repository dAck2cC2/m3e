/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison GLR parsers in C++
   
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

/* C++ GLR parser skeleton written by Akim Demaille.  */

#ifndef PARSER_HEADER_H
# define PARSER_HEADER_H



#include <string>
#include <iostream>

/* Using locations.  */
#define YYLSP_NEEDED 1


namespace yy {

/* Line 236 of glr.cc  */
#line 51 "aidl_language_y.h"
  class position;
  class location;

} // yy

/* Line 239 of glr.cc  */
#line 58 "aidl_language_y.h"

#include "location.hh"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).begin  = YYRHSLOC (Rhs, 1).begin;			\
	  (Current).end    = YYRHSLOC (Rhs, N).end;			\
	}								\
      else								\
	{								\
	  (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;	\
	}								\
    while (/*CONSTCOND*/ 0)
#endif


namespace yy {

/* Line 267 of glr.cc  */
#line 90 "aidl_language_y.h"
  /// A Bison parser.
  class parser
  {
  public:
    /// Symbol semantic values.
#ifndef YYSTYPE
    union semantic_type
    {

/* Line 274 of glr.cc  */
#line 20 "aidl_language_y.yy"

    AidlToken* token;
    int integer;
    std::string *str;
    AidlType::Annotation annotation;
    AidlType::Annotation annotation_list;
    AidlType* type;
    AidlType* unannotated_type;
    AidlArgument* arg;
    AidlArgument::Direction direction;
    std::vector<std::unique_ptr<AidlArgument>>* arg_list;
    AidlMethod* method;
    AidlMember* constant;
    std::vector<std::unique_ptr<AidlMember>>* members;
    AidlQualifiedName* qname;
    AidlInterface* interface_obj;
    AidlParcelable* parcelable;
    AidlDocument* parcelable_list;



/* Line 274 of glr.cc  */
#line 124 "aidl_language_y.h"
    };
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;
    /// Tokens.
    struct token
    {
      /* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     INTERFACE = 259,
     ONEWAY = 260,
     C_STR = 261,
     HEXVALUE = 262,
     INTVALUE = 263,
     IN = 264,
     OUT = 265,
     INOUT = 266,
     PACKAGE = 267,
     IMPORT = 268,
     PARCELABLE = 269,
     CPP_HEADER = 270,
     CONST = 271,
     INT = 272,
     STRING = 273,
     ANNOTATION_NULLABLE = 274,
     ANNOTATION_UTF8 = 275,
     ANNOTATION_UTF8_CPP = 276
   };
#endif

    };
    /// Token type.
    typedef token::yytokentype token_type;

    /// Build a parser object.
    parser (Parser* ps_yyarg);
    virtual ~parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

    /// The current debugging stream.
    std::ostream& debug_stream () const;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);

  private:

  public:
    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);
  private:

#if YYDEBUG
  public:
    /// \brief Report a symbol value on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_value_print_ (int yytype,
					 const semantic_type* yyvaluep,
					 const location_type* yylocationp);
    /// \brief Report a symbol on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_print_ (int yytype,
				   const semantic_type* yyvaluep,
				   const location_type* yylocationp);
  private:
    /* Debugging.  */
    int yydebug_;
    std::ostream* yycdebug_;
#endif


    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg        Why this token is reclaimed.
    /// \param yytype       The symbol type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    inline void yydestruct_ (const char* yymsg,
			     int yytype,
			     semantic_type* yyvaluep,
			     location_type* yylocationp);


    /* User arguments.  */
    Parser* ps;
  };



#ifndef YYSTYPE
# define YYSTYPE yy::parser::semantic_type
#endif
#ifndef YYLTYPE
# define YYLTYPE yy::parser::location_type
#endif


} // yy

/* Line 371 of glr.cc  */
#line 246 "aidl_language_y.h"


#endif /* ! defined PARSER_HEADER_H */
