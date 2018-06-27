// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "mc_parser.tab.hh"

// User implementation prologue.

#line 51 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 28 "mc_parser.yy" // lalr1.cc:413

   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   /* include for all driver functions */
   #include "mc_driver.hpp"
   #include "./API.h"

#undef yylex
#define yylex scanner.yylex

#line 65 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 6 "mc_parser.yy" // lalr1.cc:479
namespace MC {
#line 151 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  MC_Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  MC_Parser::MC_Parser (MC_Scanner  &scanner_yyarg, MC_Driver  &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  MC_Parser::~MC_Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  MC_Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  MC_Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  MC_Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 33: // BOOL
        value.copy< bool > (other.value);
        break;

      case 34: // APPROXNUM
        value.copy< float > (other.value);
        break;

      case 14: // COMPARISON
      case 32: // INTNUM
      case 256: // column_list
      case 257: // select_expr_list
      case 259: // table_references
      case 263: // delete_opts
      case 264: // delete_list
      case 267: // insert_opts
      case 270: // insert_vals_list
      case 276: // create_col_list
      case 279: // column_atts
      case 280: // opt_length
      case 281: // opt_binary
      case 282: // opt_uz
      case 284: // data_type
        value.copy< int > (other.value);
        break;

      case 27: // WORD
      case 29: // HLH
      case 30: // NAME
      case 31: // STRING
      case 35: // USERVAR
        value.copy< std::string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  MC_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 33: // BOOL
        value.copy< bool > (v);
        break;

      case 34: // APPROXNUM
        value.copy< float > (v);
        break;

      case 14: // COMPARISON
      case 32: // INTNUM
      case 256: // column_list
      case 257: // select_expr_list
      case 259: // table_references
      case 263: // delete_opts
      case 264: // delete_list
      case 267: // insert_opts
      case 270: // insert_vals_list
      case 276: // create_col_list
      case 279: // column_atts
      case 280: // opt_length
      case 281: // opt_binary
      case 282: // opt_uz
      case 284: // data_type
        value.copy< int > (v);
        break;

      case 27: // WORD
      case 29: // HLH
      case 30: // NAME
      case 31: // STRING
      case 35: // USERVAR
        value.copy< std::string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  MC_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  MC_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const bool v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MC_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const float v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MC_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  MC_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  MC_Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  MC_Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 33: // BOOL
        value.template destroy< bool > ();
        break;

      case 34: // APPROXNUM
        value.template destroy< float > ();
        break;

      case 14: // COMPARISON
      case 32: // INTNUM
      case 256: // column_list
      case 257: // select_expr_list
      case 259: // table_references
      case 263: // delete_opts
      case 264: // delete_list
      case 267: // insert_opts
      case 270: // insert_vals_list
      case 276: // create_col_list
      case 279: // column_atts
      case 280: // opt_length
      case 281: // opt_binary
      case 282: // opt_uz
      case 284: // data_type
        value.template destroy< int > ();
        break;

      case 27: // WORD
      case 29: // HLH
      case 30: // NAME
      case 31: // STRING
      case 35: // USERVAR
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  MC_Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  MC_Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 33: // BOOL
        value.move< bool > (s.value);
        break;

      case 34: // APPROXNUM
        value.move< float > (s.value);
        break;

      case 14: // COMPARISON
      case 32: // INTNUM
      case 256: // column_list
      case 257: // select_expr_list
      case 259: // table_references
      case 263: // delete_opts
      case 264: // delete_list
      case 267: // insert_opts
      case 270: // insert_vals_list
      case 276: // create_col_list
      case 279: // column_atts
      case 280: // opt_length
      case 281: // opt_binary
      case 282: // opt_uz
      case 284: // data_type
        value.move< int > (s.value);
        break;

      case 27: // WORD
      case 29: // HLH
      case 30: // NAME
      case 31: // STRING
      case 35: // USERVAR
        value.move< std::string > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  MC_Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  MC_Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  MC_Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  MC_Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  MC_Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  MC_Parser::by_type::type_get () const
  {
    return type;
  }
  // Implementation of make_symbol for each symbol type.
  MC_Parser::symbol_type
  MC_Parser::make_END (const location_type& l)
  {
    return symbol_type (token::END, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ASSIGN (const location_type& l)
  {
    return symbol_type (token::ASSIGN, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_OR (const location_type& l)
  {
    return symbol_type (token::OR, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_XOR (const location_type& l)
  {
    return symbol_type (token::XOR, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ANDOP (const location_type& l)
  {
    return symbol_type (token::ANDOP, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_IN (const location_type& l)
  {
    return symbol_type (token::IN, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_IS (const location_type& l)
  {
    return symbol_type (token::IS, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LIKE (const location_type& l)
  {
    return symbol_type (token::LIKE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_REGEXP (const location_type& l)
  {
    return symbol_type (token::REGEXP, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_NOT (const location_type& l)
  {
    return symbol_type (token::NOT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_BETWEEN (const location_type& l)
  {
    return symbol_type (token::BETWEEN, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_COMPARISON (const int& v, const location_type& l)
  {
    return symbol_type (token::COMPARISON, v, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_MOD (const location_type& l)
  {
    return symbol_type (token::MOD, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_UMINUS (const location_type& l)
  {
    return symbol_type (token::UMINUS, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_UPPER (const location_type& l)
  {
    return symbol_type (token::UPPER, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LOWER (const location_type& l)
  {
    return symbol_type (token::LOWER, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_WORD (const std::string& v, const location_type& l)
  {
    return symbol_type (token::WORD, v, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_NEWLINE (const location_type& l)
  {
    return symbol_type (token::NEWLINE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_HLH (const std::string& v, const location_type& l)
  {
    return symbol_type (token::HLH, v, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_NAME (const std::string& v, const location_type& l)
  {
    return symbol_type (token::NAME, v, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_STRING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::STRING, v, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_INTNUM (const int& v, const location_type& l)
  {
    return symbol_type (token::INTNUM, v, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_BOOL (const bool& v, const location_type& l)
  {
    return symbol_type (token::BOOL, v, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_APPROXNUM (const float& v, const location_type& l)
  {
    return symbol_type (token::APPROXNUM, v, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_USERVAR (const std::string& v, const location_type& l)
  {
    return symbol_type (token::USERVAR, v, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ADD (const location_type& l)
  {
    return symbol_type (token::ADD, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ALL (const location_type& l)
  {
    return symbol_type (token::ALL, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ALTER (const location_type& l)
  {
    return symbol_type (token::ALTER, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ANALYZE (const location_type& l)
  {
    return symbol_type (token::ANALYZE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_AND (const location_type& l)
  {
    return symbol_type (token::AND, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ANY (const location_type& l)
  {
    return symbol_type (token::ANY, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_AS (const location_type& l)
  {
    return symbol_type (token::AS, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ASC (const location_type& l)
  {
    return symbol_type (token::ASC, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_AUTO_INCREMENT (const location_type& l)
  {
    return symbol_type (token::AUTO_INCREMENT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_BEFORE (const location_type& l)
  {
    return symbol_type (token::BEFORE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_BIGINT (const location_type& l)
  {
    return symbol_type (token::BIGINT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_BINARY (const location_type& l)
  {
    return symbol_type (token::BINARY, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_BIT (const location_type& l)
  {
    return symbol_type (token::BIT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_BLOB (const location_type& l)
  {
    return symbol_type (token::BLOB, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_BOTH (const location_type& l)
  {
    return symbol_type (token::BOTH, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_BY (const location_type& l)
  {
    return symbol_type (token::BY, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CALL (const location_type& l)
  {
    return symbol_type (token::CALL, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CASCADE (const location_type& l)
  {
    return symbol_type (token::CASCADE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CASE (const location_type& l)
  {
    return symbol_type (token::CASE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CHANGE (const location_type& l)
  {
    return symbol_type (token::CHANGE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CHAR (const location_type& l)
  {
    return symbol_type (token::CHAR, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CHECK (const location_type& l)
  {
    return symbol_type (token::CHECK, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_COLLATE (const location_type& l)
  {
    return symbol_type (token::COLLATE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_COLUMN (const location_type& l)
  {
    return symbol_type (token::COLUMN, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_COMMENT (const location_type& l)
  {
    return symbol_type (token::COMMENT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CONDITION (const location_type& l)
  {
    return symbol_type (token::CONDITION, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CONSTRAINT (const location_type& l)
  {
    return symbol_type (token::CONSTRAINT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CONTINUE (const location_type& l)
  {
    return symbol_type (token::CONTINUE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CONVERT (const location_type& l)
  {
    return symbol_type (token::CONVERT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CREATE (const location_type& l)
  {
    return symbol_type (token::CREATE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CROSS (const location_type& l)
  {
    return symbol_type (token::CROSS, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CURRENT_DATE (const location_type& l)
  {
    return symbol_type (token::CURRENT_DATE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CURRENT_TIME (const location_type& l)
  {
    return symbol_type (token::CURRENT_TIME, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CURRENT_TIMESTAMP (const location_type& l)
  {
    return symbol_type (token::CURRENT_TIMESTAMP, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CURRENT_USER (const location_type& l)
  {
    return symbol_type (token::CURRENT_USER, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_CURSOR (const location_type& l)
  {
    return symbol_type (token::CURSOR, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DATABASE (const location_type& l)
  {
    return symbol_type (token::DATABASE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DATABASES (const location_type& l)
  {
    return symbol_type (token::DATABASES, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DATE (const location_type& l)
  {
    return symbol_type (token::DATE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DATETIME (const location_type& l)
  {
    return symbol_type (token::DATETIME, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DAY_HOUR (const location_type& l)
  {
    return symbol_type (token::DAY_HOUR, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DAY_MICROSECOND (const location_type& l)
  {
    return symbol_type (token::DAY_MICROSECOND, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DAY_MINUTE (const location_type& l)
  {
    return symbol_type (token::DAY_MINUTE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DAY_SECOND (const location_type& l)
  {
    return symbol_type (token::DAY_SECOND, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DECIMAL (const location_type& l)
  {
    return symbol_type (token::DECIMAL, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DECLARE (const location_type& l)
  {
    return symbol_type (token::DECLARE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DEFAULT (const location_type& l)
  {
    return symbol_type (token::DEFAULT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DELAYED (const location_type& l)
  {
    return symbol_type (token::DELAYED, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DELETE (const location_type& l)
  {
    return symbol_type (token::DELETE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DESC (const location_type& l)
  {
    return symbol_type (token::DESC, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DESCRIBE (const location_type& l)
  {
    return symbol_type (token::DESCRIBE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DETERMINISTIC (const location_type& l)
  {
    return symbol_type (token::DETERMINISTIC, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DISTINCT (const location_type& l)
  {
    return symbol_type (token::DISTINCT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DISTINCTROW (const location_type& l)
  {
    return symbol_type (token::DISTINCTROW, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DIV (const location_type& l)
  {
    return symbol_type (token::DIV, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DOUBLE (const location_type& l)
  {
    return symbol_type (token::DOUBLE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DROP (const location_type& l)
  {
    return symbol_type (token::DROP, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_DUAL (const location_type& l)
  {
    return symbol_type (token::DUAL, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_EACH (const location_type& l)
  {
    return symbol_type (token::EACH, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ELSE (const location_type& l)
  {
    return symbol_type (token::ELSE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ELSEIF (const location_type& l)
  {
    return symbol_type (token::ELSEIF, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ENCLOSED (const location_type& l)
  {
    return symbol_type (token::ENCLOSED, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ENUM (const location_type& l)
  {
    return symbol_type (token::ENUM, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ESCAPED (const location_type& l)
  {
    return symbol_type (token::ESCAPED, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_EXIT (const location_type& l)
  {
    return symbol_type (token::EXIT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_EXPLAIN (const location_type& l)
  {
    return symbol_type (token::EXPLAIN, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_FETCH (const location_type& l)
  {
    return symbol_type (token::FETCH, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_FLOAT (const location_type& l)
  {
    return symbol_type (token::FLOAT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_FOR (const location_type& l)
  {
    return symbol_type (token::FOR, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_FORCE (const location_type& l)
  {
    return symbol_type (token::FORCE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_FOREIGN (const location_type& l)
  {
    return symbol_type (token::FOREIGN, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_FROM (const location_type& l)
  {
    return symbol_type (token::FROM, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_FULLTEXT (const location_type& l)
  {
    return symbol_type (token::FULLTEXT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_GRANT (const location_type& l)
  {
    return symbol_type (token::GRANT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_GROUP (const location_type& l)
  {
    return symbol_type (token::GROUP, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_HAVING (const location_type& l)
  {
    return symbol_type (token::HAVING, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_HIGH_PRIORITY (const location_type& l)
  {
    return symbol_type (token::HIGH_PRIORITY, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_HOUR_MICROSECOND (const location_type& l)
  {
    return symbol_type (token::HOUR_MICROSECOND, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_HOUR_MINUTE (const location_type& l)
  {
    return symbol_type (token::HOUR_MINUTE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_HOUR_SECOND (const location_type& l)
  {
    return symbol_type (token::HOUR_SECOND, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_IF (const location_type& l)
  {
    return symbol_type (token::IF, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_IGNORE (const location_type& l)
  {
    return symbol_type (token::IGNORE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_INDEX (const location_type& l)
  {
    return symbol_type (token::INDEX, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_INFILE (const location_type& l)
  {
    return symbol_type (token::INFILE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_INNER (const location_type& l)
  {
    return symbol_type (token::INNER, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_INOUT (const location_type& l)
  {
    return symbol_type (token::INOUT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_INSENSITIVE (const location_type& l)
  {
    return symbol_type (token::INSENSITIVE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_INSERT (const location_type& l)
  {
    return symbol_type (token::INSERT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_INT (const location_type& l)
  {
    return symbol_type (token::INT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_INTEGER (const location_type& l)
  {
    return symbol_type (token::INTEGER, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_INTERVAL (const location_type& l)
  {
    return symbol_type (token::INTERVAL, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_INTO (const location_type& l)
  {
    return symbol_type (token::INTO, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ITERATE (const location_type& l)
  {
    return symbol_type (token::ITERATE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_JOIN (const location_type& l)
  {
    return symbol_type (token::JOIN, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_KEY (const location_type& l)
  {
    return symbol_type (token::KEY, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_KEYS (const location_type& l)
  {
    return symbol_type (token::KEYS, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_KILL (const location_type& l)
  {
    return symbol_type (token::KILL, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LEADING (const location_type& l)
  {
    return symbol_type (token::LEADING, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LEAVE (const location_type& l)
  {
    return symbol_type (token::LEAVE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LEFT (const location_type& l)
  {
    return symbol_type (token::LEFT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LIMIT (const location_type& l)
  {
    return symbol_type (token::LIMIT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LINES (const location_type& l)
  {
    return symbol_type (token::LINES, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LOAD (const location_type& l)
  {
    return symbol_type (token::LOAD, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LOCALTIME (const location_type& l)
  {
    return symbol_type (token::LOCALTIME, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LOCALTIMESTAMP (const location_type& l)
  {
    return symbol_type (token::LOCALTIMESTAMP, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LOCK (const location_type& l)
  {
    return symbol_type (token::LOCK, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LONG (const location_type& l)
  {
    return symbol_type (token::LONG, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LONGBLOB (const location_type& l)
  {
    return symbol_type (token::LONGBLOB, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LONGTEXT (const location_type& l)
  {
    return symbol_type (token::LONGTEXT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LOOP (const location_type& l)
  {
    return symbol_type (token::LOOP, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_LOW_PRIORITY (const location_type& l)
  {
    return symbol_type (token::LOW_PRIORITY, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_MATCH (const location_type& l)
  {
    return symbol_type (token::MATCH, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_MEDIUMBLOB (const location_type& l)
  {
    return symbol_type (token::MEDIUMBLOB, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_MEDIUMINT (const location_type& l)
  {
    return symbol_type (token::MEDIUMINT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_MEDIUMTEXT (const location_type& l)
  {
    return symbol_type (token::MEDIUMTEXT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_MINUTE_MICROSECOND (const location_type& l)
  {
    return symbol_type (token::MINUTE_MICROSECOND, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_MINUTE_SECOND (const location_type& l)
  {
    return symbol_type (token::MINUTE_SECOND, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_MODIFIES (const location_type& l)
  {
    return symbol_type (token::MODIFIES, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_NATURAL (const location_type& l)
  {
    return symbol_type (token::NATURAL, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_NO_WRITE_TO_BINLOG (const location_type& l)
  {
    return symbol_type (token::NO_WRITE_TO_BINLOG, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_NULLX (const location_type& l)
  {
    return symbol_type (token::NULLX, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_NUMBER (const location_type& l)
  {
    return symbol_type (token::NUMBER, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ON (const location_type& l)
  {
    return symbol_type (token::ON, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ONDUPLICATE (const location_type& l)
  {
    return symbol_type (token::ONDUPLICATE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_OPTIMIZE (const location_type& l)
  {
    return symbol_type (token::OPTIMIZE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_OPTION (const location_type& l)
  {
    return symbol_type (token::OPTION, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_OPTIONALLY (const location_type& l)
  {
    return symbol_type (token::OPTIONALLY, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ORDER (const location_type& l)
  {
    return symbol_type (token::ORDER, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_OUT (const location_type& l)
  {
    return symbol_type (token::OUT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_OUTER (const location_type& l)
  {
    return symbol_type (token::OUTER, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_OUTFILE (const location_type& l)
  {
    return symbol_type (token::OUTFILE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_PRECISION (const location_type& l)
  {
    return symbol_type (token::PRECISION, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_PRIMARY (const location_type& l)
  {
    return symbol_type (token::PRIMARY, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_PROCEDURE (const location_type& l)
  {
    return symbol_type (token::PROCEDURE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_PURGE (const location_type& l)
  {
    return symbol_type (token::PURGE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_QUICK (const location_type& l)
  {
    return symbol_type (token::QUICK, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_READ (const location_type& l)
  {
    return symbol_type (token::READ, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_READS (const location_type& l)
  {
    return symbol_type (token::READS, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_REAL (const location_type& l)
  {
    return symbol_type (token::REAL, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_REFERENCES (const location_type& l)
  {
    return symbol_type (token::REFERENCES, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_RELEASE (const location_type& l)
  {
    return symbol_type (token::RELEASE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_RENAME (const location_type& l)
  {
    return symbol_type (token::RENAME, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_REPEAT (const location_type& l)
  {
    return symbol_type (token::REPEAT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_REPLACE (const location_type& l)
  {
    return symbol_type (token::REPLACE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_REQUIRE (const location_type& l)
  {
    return symbol_type (token::REQUIRE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_RESTRICT (const location_type& l)
  {
    return symbol_type (token::RESTRICT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_RETURN (const location_type& l)
  {
    return symbol_type (token::RETURN, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_REVOKE (const location_type& l)
  {
    return symbol_type (token::REVOKE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_RIGHT (const location_type& l)
  {
    return symbol_type (token::RIGHT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_ROLLUP (const location_type& l)
  {
    return symbol_type (token::ROLLUP, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SCHEMA (const location_type& l)
  {
    return symbol_type (token::SCHEMA, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SCHEMAS (const location_type& l)
  {
    return symbol_type (token::SCHEMAS, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SECOND_MICROSECOND (const location_type& l)
  {
    return symbol_type (token::SECOND_MICROSECOND, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SELECT (const location_type& l)
  {
    return symbol_type (token::SELECT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SENSITIVE (const location_type& l)
  {
    return symbol_type (token::SENSITIVE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SEPARATOR (const location_type& l)
  {
    return symbol_type (token::SEPARATOR, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SET (const location_type& l)
  {
    return symbol_type (token::SET, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SHOW (const location_type& l)
  {
    return symbol_type (token::SHOW, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SMALLINT (const location_type& l)
  {
    return symbol_type (token::SMALLINT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SOME (const location_type& l)
  {
    return symbol_type (token::SOME, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SONAME (const location_type& l)
  {
    return symbol_type (token::SONAME, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SPATIAL (const location_type& l)
  {
    return symbol_type (token::SPATIAL, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SPECIFIC (const location_type& l)
  {
    return symbol_type (token::SPECIFIC, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SQL (const location_type& l)
  {
    return symbol_type (token::SQL, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SQLEXCEPTION (const location_type& l)
  {
    return symbol_type (token::SQLEXCEPTION, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SQLSTATE (const location_type& l)
  {
    return symbol_type (token::SQLSTATE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SQLWARNING (const location_type& l)
  {
    return symbol_type (token::SQLWARNING, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SQL_BIG_RESULT (const location_type& l)
  {
    return symbol_type (token::SQL_BIG_RESULT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SQL_CALC_FOUND_ROWS (const location_type& l)
  {
    return symbol_type (token::SQL_CALC_FOUND_ROWS, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SQL_SMALL_RESULT (const location_type& l)
  {
    return symbol_type (token::SQL_SMALL_RESULT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_SSL (const location_type& l)
  {
    return symbol_type (token::SSL, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_STARTING (const location_type& l)
  {
    return symbol_type (token::STARTING, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_STRAIGHT_JOIN (const location_type& l)
  {
    return symbol_type (token::STRAIGHT_JOIN, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_TABLE (const location_type& l)
  {
    return symbol_type (token::TABLE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_TEMPORARY (const location_type& l)
  {
    return symbol_type (token::TEMPORARY, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_TEXT (const location_type& l)
  {
    return symbol_type (token::TEXT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_TERMINATED (const location_type& l)
  {
    return symbol_type (token::TERMINATED, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_THEN (const location_type& l)
  {
    return symbol_type (token::THEN, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_TINYINT (const location_type& l)
  {
    return symbol_type (token::TINYINT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_TINYTEXT (const location_type& l)
  {
    return symbol_type (token::TINYTEXT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_TO (const location_type& l)
  {
    return symbol_type (token::TO, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_TRAILING (const location_type& l)
  {
    return symbol_type (token::TRAILING, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_TRIGGER (const location_type& l)
  {
    return symbol_type (token::TRIGGER, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_UNDO (const location_type& l)
  {
    return symbol_type (token::UNDO, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_UNION (const location_type& l)
  {
    return symbol_type (token::UNION, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_UNIQUE (const location_type& l)
  {
    return symbol_type (token::UNIQUE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_UNLOCK (const location_type& l)
  {
    return symbol_type (token::UNLOCK, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_UNSIGNED (const location_type& l)
  {
    return symbol_type (token::UNSIGNED, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_UPDATE (const location_type& l)
  {
    return symbol_type (token::UPDATE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_USAGE (const location_type& l)
  {
    return symbol_type (token::USAGE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_USE (const location_type& l)
  {
    return symbol_type (token::USE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_USING (const location_type& l)
  {
    return symbol_type (token::USING, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_UTC_DATE (const location_type& l)
  {
    return symbol_type (token::UTC_DATE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_UTC_TIME (const location_type& l)
  {
    return symbol_type (token::UTC_TIME, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_UTC_TIMESTAMP (const location_type& l)
  {
    return symbol_type (token::UTC_TIMESTAMP, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_VALUES (const location_type& l)
  {
    return symbol_type (token::VALUES, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_VARBINARY (const location_type& l)
  {
    return symbol_type (token::VARBINARY, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_VARCHAR (const location_type& l)
  {
    return symbol_type (token::VARCHAR, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_VARYING (const location_type& l)
  {
    return symbol_type (token::VARYING, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_WHEN (const location_type& l)
  {
    return symbol_type (token::WHEN, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_WHERE (const location_type& l)
  {
    return symbol_type (token::WHERE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_WHILE (const location_type& l)
  {
    return symbol_type (token::WHILE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_WITH (const location_type& l)
  {
    return symbol_type (token::WITH, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_WRITE (const location_type& l)
  {
    return symbol_type (token::WRITE, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_QUIT (const location_type& l)
  {
    return symbol_type (token::QUIT, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_FSUBSTRING (const location_type& l)
  {
    return symbol_type (token::FSUBSTRING, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_FTRIM (const location_type& l)
  {
    return symbol_type (token::FTRIM, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_FDATE_ADD (const location_type& l)
  {
    return symbol_type (token::FDATE_ADD, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_FDATE_SUB (const location_type& l)
  {
    return symbol_type (token::FDATE_SUB, l);
  }

  MC_Parser::symbol_type
  MC_Parser::make_FCOUNT (const location_type& l)
  {
    return symbol_type (token::FCOUNT, l);
  }



  // by_state.
  inline
  MC_Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  MC_Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  MC_Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  MC_Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  MC_Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  MC_Parser::symbol_number_type
  MC_Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  MC_Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  MC_Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 33: // BOOL
        value.move< bool > (that.value);
        break;

      case 34: // APPROXNUM
        value.move< float > (that.value);
        break;

      case 14: // COMPARISON
      case 32: // INTNUM
      case 256: // column_list
      case 257: // select_expr_list
      case 259: // table_references
      case 263: // delete_opts
      case 264: // delete_list
      case 267: // insert_opts
      case 270: // insert_vals_list
      case 276: // create_col_list
      case 279: // column_atts
      case 280: // opt_length
      case 281: // opt_binary
      case 282: // opt_uz
      case 284: // data_type
        value.move< int > (that.value);
        break;

      case 27: // WORD
      case 29: // HLH
      case 30: // NAME
      case 31: // STRING
      case 35: // USERVAR
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  MC_Parser::stack_symbol_type&
  MC_Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 33: // BOOL
        value.copy< bool > (that.value);
        break;

      case 34: // APPROXNUM
        value.copy< float > (that.value);
        break;

      case 14: // COMPARISON
      case 32: // INTNUM
      case 256: // column_list
      case 257: // select_expr_list
      case 259: // table_references
      case 263: // delete_opts
      case 264: // delete_list
      case 267: // insert_opts
      case 270: // insert_vals_list
      case 276: // create_col_list
      case 279: // column_atts
      case 280: // opt_length
      case 281: // opt_binary
      case 282: // opt_uz
      case 284: // data_type
        value.copy< int > (that.value);
        break;

      case 27: // WORD
      case 29: // HLH
      case 30: // NAME
      case 31: // STRING
      case 35: // USERVAR
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  MC_Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  MC_Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  MC_Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  MC_Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  MC_Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  MC_Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  MC_Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  MC_Parser::debug_level_type
  MC_Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  MC_Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline MC_Parser::state_type
  MC_Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  MC_Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  MC_Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  MC_Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 33: // BOOL
        yylhs.value.build< bool > ();
        break;

      case 34: // APPROXNUM
        yylhs.value.build< float > ();
        break;

      case 14: // COMPARISON
      case 32: // INTNUM
      case 256: // column_list
      case 257: // select_expr_list
      case 259: // table_references
      case 263: // delete_opts
      case 264: // delete_list
      case 267: // insert_opts
      case 270: // insert_vals_list
      case 276: // create_col_list
      case 279: // column_atts
      case 280: // opt_length
      case 281: // opt_binary
      case 282: // opt_uz
      case 284: // data_type
        yylhs.value.build< int > ();
        break;

      case 27: // WORD
      case 29: // HLH
      case 30: // NAME
      case 31: // STRING
      case 35: // USERVAR
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 311 "mc_parser.yy" // lalr1.cc:859
    { std::cout<<"minisql > ";}
#line 2350 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 312 "mc_parser.yy" // lalr1.cc:859
    {std::cout<<"minisql > ";}
#line 2356 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 314 "mc_parser.yy" // lalr1.cc:859
    { API::select_value(driver.stmt);driver.Clear(4);}
#line 2362 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 315 "mc_parser.yy" // lalr1.cc:859
    {std::cout<<"quit"<<std::endl;API::save();return 0;}
#line 2368 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 324 "mc_parser.yy" // lalr1.cc:859
    { std::cout<<"SELECT "<< yystack_[3].value.as< int > () <<" "<< yystack_[1].value.as< int > () << std::endl;driver.addcolunm(yystack_[3].value.as< int > ()); }
#line 2374 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 328 "mc_parser.yy" // lalr1.cc:859
    { }
#line 2380 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 330 "mc_parser.yy" // lalr1.cc:859
    { std::cout<<yystack_[0].value.as< std::string > ()<<std::endl; }
#line 2386 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 331 "mc_parser.yy" // lalr1.cc:859
    {  yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1; }
#line 2392 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 334 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1; }
#line 2398 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 335 "mc_parser.yy" // lalr1.cc:859
    {yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1; }
#line 2404 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 336 "mc_parser.yy" // lalr1.cc:859
    {  yylhs.value.as< int > () = -1;driver.selectAll(); }
#line 2410 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 342 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1; }
#line 2416 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 343 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1; }
#line 2422 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 350 "mc_parser.yy" // lalr1.cc:859
    {driver.addTableName(yystack_[0].value.as< std::string > ());}
#line 2428 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 355 "mc_parser.yy" // lalr1.cc:859
    {  API::delete_Value(driver.stmt);driver.Clear(5);}
#line 2434 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 360 "mc_parser.yy" // lalr1.cc:859
    { driver.addTableName(yystack_[1].value.as< std::string > ()); }
#line 2440 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 363 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 0; }
#line 2446 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 369 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2452 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 371 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1; }
#line 2458 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 373 "mc_parser.yy" // lalr1.cc:859
    {  yylhs.value.as< int > () = yystack_[3].value.as< int > () + 1; }
#line 2464 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 381 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2470 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 387 "mc_parser.yy" // lalr1.cc:859
    { API::insert_value(driver.stmt);driver.Clear(3); }
#line 2476 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 391 "mc_parser.yy" // lalr1.cc:859
    { driver.addTableName(yystack_[3].value.as< std::string > ());}
#line 2482 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 394 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 0; }
#line 2488 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 401 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2494 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 404 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2500 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 405 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2506 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 37:
#line 408 "mc_parser.yy" // lalr1.cc:859
    { std::cout<< yystack_[0].value.as< int > () << std::endl;driver.addValue(yystack_[0].value.as< int > ());}
#line 2512 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 38:
#line 409 "mc_parser.yy" // lalr1.cc:859
    { std::cout<< yystack_[0].value.as< float > () << std::endl;driver.addValue(yystack_[0].value.as< float > ());}
#line 2518 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 39:
#line 410 "mc_parser.yy" // lalr1.cc:859
    { std::cout<< yystack_[0].value.as< std::string > () << std::endl;driver.addValue(yystack_[0].value.as< std::string > ());}
#line 2524 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 411 "mc_parser.yy" // lalr1.cc:859
    { }
#line 2530 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 415 "mc_parser.yy" // lalr1.cc:859
    {
    
    API::createIndex(driver.indexInfo);
    driver.Clear(2);
    }
#line 2540 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 423 "mc_parser.yy" // lalr1.cc:859
    {driver.addIndexParam(yystack_[5].value.as< std::string > (),yystack_[3].value.as< std::string > (),yystack_[1].value.as< std::string > ());}
#line 2546 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 427 "mc_parser.yy" // lalr1.cc:859
    {
   
    API::dropIndex(driver.indexInfo);
    driver.Clear(2);}
#line 2555 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 433 "mc_parser.yy" // lalr1.cc:859
    {
    driver.addIndexParam(yystack_[0].value.as< std::string > (),"","");
    }
#line 2563 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 439 "mc_parser.yy" // lalr1.cc:859
    {
    API::dropTable(driver.tableInfo);
    driver.Clear(0);
}
#line 2572 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 444 "mc_parser.yy" // lalr1.cc:859
    {driver.addTableInfoTableName(yystack_[0].value.as< std::string > ());}
#line 2578 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 449 "mc_parser.yy" // lalr1.cc:859
    { 
    //driver.emit("STMT");
    API::createTable(driver.tableInfo);
    driver.Clear(0);}
#line 2587 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 456 "mc_parser.yy" // lalr1.cc:859
    { 
       //driver.emit("CREATETABLE");
       driver.addTableInfoTableName(yystack_[3].value.as< std::string > ());}
#line 2595 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 461 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 1; }
#line 2601 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 462 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1; }
#line 2607 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 465 "mc_parser.yy" // lalr1.cc:859
    { 
                    //driver.emit("STARTCOL"); 
                    }
#line 2615 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 468 "mc_parser.yy" // lalr1.cc:859
    { //driver.emit("COLUMNDEF");
                   driver.addColunm(yystack_[2].value.as< std::string > (),yystack_[1].value.as< int > (),yystack_[0].value.as< int > ());
                   std::cout<<"i am datatype"<<yystack_[1].value.as< int > ()<<std::endl;
                   //std::cout << $2 <<" "<< $3 <<" " << $4 << std::endl;
                   }
#line 2625 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 474 "mc_parser.yy" // lalr1.cc:859
    { driver.addConstraint(yystack_[1].value.as< std::string > (),3);}
#line 2631 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 475 "mc_parser.yy" // lalr1.cc:859
    { }
#line 2637 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 476 "mc_parser.yy" // lalr1.cc:859
    { driver.addConstraint(yystack_[1].value.as< std::string > (),4);}
#line 2643 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 479 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 0; }
#line 2649 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 480 "mc_parser.yy" // lalr1.cc:859
    {  yylhs.value.as< int > () = yystack_[2].value.as< int > () + 1; }
#line 2655 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 482 "mc_parser.yy" // lalr1.cc:859
    {  yylhs.value.as< int > () = yystack_[4].value.as< int > () + 2; }
#line 2661 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 60:
#line 483 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[1].value.as< int > () + 2; }
#line 2667 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 484 "mc_parser.yy" // lalr1.cc:859
    {  yylhs.value.as< int > () = yystack_[2].value.as< int > () + 3; }
#line 2673 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 62:
#line 487 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 0; }
#line 2679 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 488 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[1].value.as< int > (); }
#line 2685 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 489 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[3].value.as< int > () + 1000*yystack_[1].value.as< int > (); }
#line 2691 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 492 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 0; }
#line 2697 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 493 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 4000; }
#line 2703 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 496 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 0; }
#line 2709 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 497 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[1].value.as< int > () | 1000; }
#line 2715 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 501 "mc_parser.yy" // lalr1.cc:859
    { driver.emit("COLCHARSET"); }
#line 2721 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 502 "mc_parser.yy" // lalr1.cc:859
    { driver.emit("COLCOLLATE");  }
#line 2727 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 506 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 40000 + yystack_[1].value.as< int > () + yystack_[0].value.as< int > (); }
#line 2733 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 73:
#line 507 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 50000 + yystack_[1].value.as< int > () + yystack_[0].value.as< int > (); }
#line 2739 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 508 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 80000 + yystack_[1].value.as< int > () + yystack_[0].value.as< int > (); }
#line 2745 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 509 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 90000 + yystack_[1].value.as< int > () + yystack_[0].value.as< int > (); }
#line 2751 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 510 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 120000 + yystack_[1].value.as< int > (); }
#line 2757 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 511 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 130000 + yystack_[2].value.as< int > (); }
#line 2763 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 512 "mc_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int > () = 171000 + yystack_[1].value.as< int > (); }
#line 2769 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 519 "mc_parser.yy" // lalr1.cc:859
    { driver.pushCol(yystack_[0].value.as< std::string > ());}
#line 2775 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 520 "mc_parser.yy" // lalr1.cc:859
    {  driver.pushValue(yystack_[0].value.as< std::string > ());}
#line 2781 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 81:
#line 521 "mc_parser.yy" // lalr1.cc:859
    {  driver.pushValue(yystack_[0].value.as< int > ()); }
#line 2787 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 522 "mc_parser.yy" // lalr1.cc:859
    {  driver.pushValue(yystack_[0].value.as< float > ());}
#line 2793 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 523 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2799 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 526 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2805 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 527 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2811 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 528 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2817 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 529 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2823 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 530 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2829 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 531 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2835 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 532 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2841 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 533 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2847 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 534 "mc_parser.yy" // lalr1.cc:859
    { }
#line 2853 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 535 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2859 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 94:
#line 536 "mc_parser.yy" // lalr1.cc:859
    {  driver.oppop(yystack_[1].value.as< int > ());}
#line 2865 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 537 "mc_parser.yy" // lalr1.cc:859
    {}
#line 2871 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 96:
#line 538 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2877 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 539 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2883 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 540 "mc_parser.yy" // lalr1.cc:859
    {  }
#line 2889 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 99:
#line 543 "mc_parser.yy" // lalr1.cc:859
    { driver.emit("ISNULL"); }
#line 2895 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 100:
#line 544 "mc_parser.yy" // lalr1.cc:859
    { driver.emit("ISNULL"); driver.emit("NOT"); }
#line 2901 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 545 "mc_parser.yy" // lalr1.cc:859
    { driver.emit("ISBOOL"); }
#line 2907 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 546 "mc_parser.yy" // lalr1.cc:859
    { driver.emit("ISBOOL"); driver.emit("NOT"); }
#line 2913 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
    break;


#line 2917 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  MC_Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  MC_Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int MC_Parser::yypact_ninf_ = -217;

  const signed char MC_Parser::yytable_ninf_ = -8;

  const short int
  MC_Parser::yypact_[] =
  {
     -56,  -120,  -217,  -118,  -217,    75,  -217,     0,  -213,  -217,
    -217,  -217,  -217,  -217,  -217,  -217,    17,    32,   -17,    58,
      65,   -31,   106,   106,   106,  -217,  -217,  -217,  -217,  -217,
    -217,   100,  -101,  -217,   108,  -217,  -142,  -217,   -47,  -134,
    -117,   102,  -100,  -217,  -217,  -217,   105,   156,   156,  -217,
     106,   113,   106,   106,   106,   106,    -6,   -10,   106,   106,
     106,   106,   106,   106,  -217,   115,   -89,   135,  -217,  -204,
    -212,   113,   126,   -92,   108,  -217,  -177,  -217,  -217,  -217,
     147,   174,   189,   -22,  -217,  -217,   -27,   197,    55,    55,
    -217,  -217,  -217,  -217,   -91,   -86,   -78,    42,  -216,  -217,
     149,  -217,   106,  -217,   113,  -177,  -117,   153,   -46,   113,
    -217,  -217,  -217,   -64,   157,   160,   153,   -51,   -89,  -217,
     -52,   108,  -177,  -217,  -217,  -217,  -186,   -50,  -217,  -217,
     -49,   -48,  -181,   170,  -217,   -45,   -45,   -45,   -45,   -45,
     158,   -37,  -217,  -217,   190,  -217,     6,   -26,  -217,  -217,
    -217,   -28,   191,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
     192,    -8,  -217,  -217,  -217,  -217,  -179,   -24,  -217,  -169,
      86,     3,     3,     3,     3,    86,   -23,    72,  -217,    99,
     -19,     6,  -217,     6,   199,  -217,    40,   202,  -217,  -217,
    -217,  -217,   153,   -13,  -167,   -15,   205,  -217,    86,  -165,
    -217,  -217,  -217,  -217
  };

  const unsigned char
  MC_Parser::yydefact_[] =
  {
       0,     0,    21,     0,    30,     0,     5,     0,     0,     4,
      19,    28,    41,    43,    45,    47,     0,     0,     0,     0,
       0,    32,     0,     0,     0,    13,    79,    80,    81,    83,
      82,     0,     0,    11,    14,     1,     0,     2,     0,     0,
      25,     0,     0,    44,    46,    31,     0,    96,    97,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     0,    51,     0,    23,    25,
       0,     0,     0,    33,    98,    18,     7,    15,    17,    12,
      92,    93,    91,     0,   101,    99,     0,    94,    84,    85,
      86,    87,    88,    89,     0,     0,     0,     0,     0,    49,
       0,    26,     0,    20,     0,     7,    25,     0,     0,     0,
       6,   102,   100,     0,     0,     0,     0,     0,    51,    48,
       0,     8,     7,    22,    24,     9,     0,     0,    16,    95,
       0,     0,     0,     0,    50,    62,    62,    62,    62,    62,
      65,     0,    56,    27,     0,    34,     0,    29,    42,    55,
      54,     0,     0,    69,    67,    67,    67,    67,    66,    69,
       0,    52,    10,    39,    37,    38,     0,     0,    53,     0,
      76,    74,    75,    72,    73,    78,     0,     0,    58,     0,
      60,     0,    35,     0,     0,    63,     0,     0,    68,    69,
      57,    61,     0,    40,     0,     0,     0,    71,    77,     0,
      36,    64,    70,    59
  };

  const short int
  MC_Parser::yypgoto_[] =
  {
    -217,  -217,   230,   152,   -62,   -90,  -217,   193,   -41,   132,
    -217,  -217,  -217,   201,   137,  -217,  -217,  -217,  -217,  -217,
     -32,  -217,  -217,  -217,  -217,  -217,   128,  -217,  -217,   -38,
    -217,   -36,  -143,  -217,    -5
  };

  const short int
  MC_Parser::yydefgoto_[] =
  {
      -1,     7,     8,     9,   103,   126,    32,    33,    76,    77,
      78,    10,    18,    42,    68,    11,    21,    46,   108,   147,
     166,    12,    13,    14,    15,    98,    99,   100,   161,   153,
     159,   171,   170,   142,    34
  };

  const short int
  MC_Parser::yytable_[] =
  {
      35,    22,    23,   177,   135,    83,    51,    71,    24,     1,
      16,   111,    19,    40,   110,   104,   175,    47,    48,    49,
      26,    27,    28,    29,    30,    31,   132,    84,     2,    95,
     105,   118,   102,    37,   119,    72,     3,   163,   164,   136,
     165,    96,    -7,   123,    67,    74,   198,    38,    80,    81,
      82,   137,    87,    88,    89,    90,    91,    92,    93,   102,
     143,   144,    39,   122,   145,     1,   144,     4,   181,   150,
     109,   182,   138,   139,    60,    61,    62,    63,   184,    97,
     181,   185,   144,   200,     2,   203,    22,    23,    43,    17,
      41,    20,     3,    24,    25,    44,    45,   121,   154,   155,
     156,   157,   199,    50,    64,    26,    27,    28,    29,    30,
      31,    65,    53,    54,    55,    66,    56,    22,    23,   172,
     173,   174,    57,     4,    24,    58,    59,    60,    61,    62,
      63,    67,    69,     5,   112,    73,    26,    27,    28,    29,
      30,    31,   186,    75,   187,    94,    52,    72,   178,   193,
      85,   194,    54,    55,   101,    56,   106,   107,   114,   140,
     179,    57,     5,   115,    58,    59,    60,    61,    62,    63,
      57,   116,   117,    58,    59,    60,    61,    62,    63,   120,
      55,   141,    56,   125,     6,   127,   129,   130,    57,     5,
     131,    58,    59,    60,    61,    62,    63,    56,   133,   146,
     151,   148,   149,    57,   152,   158,    58,    59,    60,    61,
      62,    63,   160,   180,    58,    59,    60,    61,    62,    63,
     162,   167,   168,   169,   176,   183,   188,   189,   190,   191,
     192,   195,   196,   197,   181,   201,   202,    36,   113,    86,
       6,   128,    70,   124,     0,    79,   134
  };

  const short int
  MC_Parser::yycheck_[] =
  {
       0,    11,    12,    11,    56,    11,   107,   107,    18,    65,
     130,    33,   130,    30,    76,   227,   159,    22,    23,    24,
      30,    31,    32,    33,    34,    35,   116,    33,    84,   118,
      71,   247,   236,   246,   250,   247,    92,    31,    32,    91,
      34,   130,   246,   105,   248,    50,   189,    30,    53,    54,
      55,   103,    57,    58,    59,    60,    61,    62,    63,   236,
     122,   247,    30,   104,   250,    65,   247,   123,   247,   250,
     247,   250,   124,   125,    19,    20,    21,    22,   247,   168,
     247,   250,   247,   250,    84,   250,    11,    12,    30,   209,
     107,   209,    92,    18,    19,    30,   127,   102,   136,   137,
     138,   139,   192,     3,   246,    30,    31,    32,    33,    34,
      35,   158,     4,     5,     6,   249,     8,    11,    12,   155,
     156,   157,    14,   123,    18,    17,    18,    19,    20,    21,
      22,   248,    30,   189,   156,    30,    30,    31,    32,    33,
      34,    35,    56,    30,    58,    30,   247,   247,   156,   181,
     156,   183,     5,     6,    19,     8,    30,   249,   249,   211,
     168,    14,   189,   249,    17,    18,    19,    20,    21,    22,
      14,   249,   130,    17,    18,    19,    20,    21,    22,    30,
       6,   233,     8,    30,   240,   231,   250,    30,    14,   189,
      30,    17,    18,    19,    20,    21,    22,     8,   249,   249,
      30,   250,   250,    14,   249,    47,    17,    18,    19,    20,
      21,    22,   249,   221,    17,    18,    19,    20,    21,    22,
      30,   247,   250,    32,    32,   249,   223,   250,   156,   130,
     249,    32,   192,    31,   247,   250,    31,     7,    86,   249,
     240,   109,    41,   106,    -1,    52,   118
  };

  const unsigned short int
  MC_Parser::yystos_[] =
  {
       0,    65,    84,    92,   123,   189,   240,   252,   253,   254,
     262,   266,   272,   273,   274,   275,   130,   209,   263,   130,
     209,   267,    11,    12,    18,    19,    30,    31,    32,    33,
      34,    35,   257,   258,   285,     0,   253,   246,    30,    30,
      30,   107,   264,    30,    30,   127,   268,   285,   285,   285,
       3,   107,   247,     4,     5,     6,     8,    14,    17,    18,
      19,    20,    21,    22,   246,   158,   249,   248,   265,    30,
     264,   107,   247,    30,   285,    30,   259,   260,   261,   258,
     285,   285,   285,    11,    33,   156,   249,   285,   285,   285,
     285,   285,   285,   285,    30,   118,   130,   168,   276,   277,
     278,    19,   236,   255,   227,   259,    30,   249,   269,   247,
     255,    33,   156,   254,   249,   249,   249,   130,   247,   250,
      30,   285,   259,   255,   265,    30,   256,   231,   260,   250,
      30,    30,   256,   249,   277,    56,    91,   103,   124,   125,
     211,   233,   284,   255,   247,   250,   249,   270,   250,   250,
     250,    30,   249,   280,   280,   280,   280,   280,    47,   281,
     249,   279,    30,    31,    32,    34,   271,   247,   250,    32,
     283,   282,   282,   282,   282,   283,    32,    11,   156,   168,
     221,   247,   250,   249,   247,   250,    56,    58,   223,   250,
     156,   130,   249,   271,   271,    32,   192,    31,   283,   256,
     250,   250,    31,   250
  };

  const unsigned short int
  MC_Parser::yyr1_[] =
  {
       0,   251,   252,   252,   253,   253,   254,   255,   255,   256,
     256,   257,   257,   257,   258,   259,   259,   260,   261,   253,
     262,   263,   262,   264,   264,   265,   265,   262,   253,   266,
     267,   268,   268,   269,   269,   270,   270,   271,   271,   271,
     271,   253,   272,   253,   273,   253,   274,   253,   275,   276,
     276,   278,   277,   277,   277,   277,   279,   279,   279,   279,
     279,   279,   280,   280,   280,   281,   281,   282,   282,   283,
     283,   283,   284,   284,   284,   284,   284,   284,   284,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285
  };

  const unsigned char
  MC_Parser::yyr2_[] =
  {
       0,     2,     2,     3,     1,     1,     5,     0,     2,     1,
       3,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       5,     0,     6,     2,     4,     0,     2,     7,     1,     7,
       0,     1,     0,     0,     3,     3,     5,     1,     1,     1,
       3,     1,     8,     1,     3,     1,     3,     1,     6,     1,
       3,     0,     4,     5,     4,     4,     0,     3,     2,     5,
       2,     3,     0,     3,     5,     0,     1,     0,     2,     0,
       4,     3,     3,     3,     3,     3,     3,     5,     3,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       2,     3,     3,     3,     3,     5,     2,     2,     3,     3,
       4,     3,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const MC_Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "ASSIGN", "OR", "XOR",
  "ANDOP", "IN", "IS", "LIKE", "REGEXP", "NOT", "'!'", "BETWEEN",
  "COMPARISON", "'|'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", "MOD",
  "'^'", "UMINUS", "UPPER", "LOWER", "WORD", "NEWLINE", "HLH", "NAME",
  "STRING", "INTNUM", "BOOL", "APPROXNUM", "USERVAR", "ADD", "ALL",
  "ALTER", "ANALYZE", "AND", "ANY", "AS", "ASC", "AUTO_INCREMENT",
  "BEFORE", "BIGINT", "BINARY", "BIT", "BLOB", "BOTH", "BY", "CALL",
  "CASCADE", "CASE", "CHANGE", "CHAR", "CHECK", "COLLATE", "COLUMN",
  "COMMENT", "CONDITION", "CONSTRAINT", "CONTINUE", "CONVERT", "CREATE",
  "CROSS", "CURRENT_DATE", "CURRENT_TIME", "CURRENT_TIMESTAMP",
  "CURRENT_USER", "CURSOR", "DATABASE", "DATABASES", "DATE", "DATETIME",
  "DAY_HOUR", "DAY_MICROSECOND", "DAY_MINUTE", "DAY_SECOND", "DECIMAL",
  "DECLARE", "DEFAULT", "DELAYED", "DELETE", "DESC", "DESCRIBE",
  "DETERMINISTIC", "DISTINCT", "DISTINCTROW", "DIV", "DOUBLE", "DROP",
  "DUAL", "EACH", "ELSE", "ELSEIF", "ENCLOSED", "ENUM", "ESCAPED", "EXIT",
  "EXPLAIN", "FETCH", "FLOAT", "FOR", "FORCE", "FOREIGN", "FROM",
  "FULLTEXT", "GRANT", "GROUP", "HAVING", "HIGH_PRIORITY",
  "HOUR_MICROSECOND", "HOUR_MINUTE", "HOUR_SECOND", "IF", "IGNORE",
  "INDEX", "INFILE", "INNER", "INOUT", "INSENSITIVE", "INSERT", "INT",
  "INTEGER", "INTERVAL", "INTO", "ITERATE", "JOIN", "KEY", "KEYS", "KILL",
  "LEADING", "LEAVE", "LEFT", "LIMIT", "LINES", "LOAD", "LOCALTIME",
  "LOCALTIMESTAMP", "LOCK", "LONG", "LONGBLOB", "LONGTEXT", "LOOP",
  "LOW_PRIORITY", "MATCH", "MEDIUMBLOB", "MEDIUMINT", "MEDIUMTEXT",
  "MINUTE_MICROSECOND", "MINUTE_SECOND", "MODIFIES", "NATURAL",
  "NO_WRITE_TO_BINLOG", "NULLX", "NUMBER", "ON", "ONDUPLICATE", "OPTIMIZE",
  "OPTION", "OPTIONALLY", "ORDER", "OUT", "OUTER", "OUTFILE", "PRECISION",
  "PRIMARY", "PROCEDURE", "PURGE", "QUICK", "READ", "READS", "REAL",
  "REFERENCES", "RELEASE", "RENAME", "REPEAT", "REPLACE", "REQUIRE",
  "RESTRICT", "RETURN", "REVOKE", "RIGHT", "ROLLUP", "SCHEMA", "SCHEMAS",
  "SECOND_MICROSECOND", "SELECT", "SENSITIVE", "SEPARATOR", "SET", "SHOW",
  "SMALLINT", "SOME", "SONAME", "SPATIAL", "SPECIFIC", "SQL",
  "SQLEXCEPTION", "SQLSTATE", "SQLWARNING", "SQL_BIG_RESULT",
  "SQL_CALC_FOUND_ROWS", "SQL_SMALL_RESULT", "SSL", "STARTING",
  "STRAIGHT_JOIN", "TABLE", "TEMPORARY", "TEXT", "TERMINATED", "THEN",
  "TINYINT", "TINYTEXT", "TO", "TRAILING", "TRIGGER", "UNDO", "UNION",
  "UNIQUE", "UNLOCK", "UNSIGNED", "UPDATE", "USAGE", "USE", "USING",
  "UTC_DATE", "UTC_TIME", "UTC_TIMESTAMP", "VALUES", "VARBINARY",
  "VARCHAR", "VARYING", "WHEN", "WHERE", "WHILE", "WITH", "WRITE", "QUIT",
  "FSUBSTRING", "FTRIM", "FDATE_ADD", "FDATE_SUB", "FCOUNT", "';'", "','",
  "'.'", "'('", "')'", "$accept", "stmt_list", "stmt", "select_stmt",
  "opt_where", "column_list", "select_expr_list", "select_expr",
  "table_references", "table_reference", "table_factor", "delete_stmt",
  "delete_opts", "delete_list", "opt_dot_star", "insert_stmt",
  "insert_opts", "opt_into", "opt_col_names", "insert_vals_list",
  "insert_vals", "create_index_stmt", "drop_index_stmt", "drop_table_stmt",
  "create_table_stmt", "create_col_list", "create_definition", "$@1",
  "column_atts", "opt_length", "opt_binary", "opt_uz", "opt_csc",
  "data_type", "expr", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  MC_Parser::yyrline_[] =
  {
       0,   311,   311,   312,   314,   315,   321,   327,   328,   330,
     331,   334,   335,   336,   339,   342,   343,   346,   350,   355,
     358,   363,   366,   371,   372,   376,   376,   378,   387,   388,
     394,   397,   397,   400,   401,   404,   405,   408,   409,   410,
     411,   415,   422,   427,   433,   439,   444,   449,   455,   461,
     462,   465,   465,   474,   475,   476,   479,   480,   481,   482,
     483,   484,   487,   488,   489,   492,   493,   496,   497,   500,
     501,   502,   506,   507,   508,   509,   510,   511,   512,   519,
     520,   521,   522,   523,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   540,   543,
     544,   545,   546
  };

  // Print the state stack on the debug stream.
  void
  MC_Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  MC_Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  MC_Parser::token_number_type
  MC_Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    12,     2,     2,     2,    21,    16,     2,
     249,   250,    19,    17,   247,    18,   248,    20,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   246,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    23,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    15,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    13,    14,    22,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245
    };
    const unsigned int user_token_number_max_ = 491;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 6 "mc_parser.yy" // lalr1.cc:1167
} // MC
#line 3540 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.cc" // lalr1.cc:1167
#line 548 "mc_parser.yy" // lalr1.cc:1168



void 
MC::MC_Parser::error( const location_type &l, const std::string &err_message )
{
   std::cout << "Error: " << err_message << " at " << l << "\n";
}
