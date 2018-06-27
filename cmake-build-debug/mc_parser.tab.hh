// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file /home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.hh
 ** Define the MC::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_HOME_KK_CLIONPROJECTS_MINI_CMAKE_BUILD_DEBUG_MC_PARSER_TAB_HH_INCLUDED
# define YY_YY_HOME_KK_CLIONPROJECTS_MINI_CMAKE_BUILD_DEBUG_MC_PARSER_TAB_HH_INCLUDED
// //                    "%code requires" blocks.
#line 9 "mc_parser.yy" // lalr1.cc:377

   namespace MC {
      class MC_Driver;
      class MC_Scanner;
   }
// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif


#line 60 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.hh" // lalr1.cc:377

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
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

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 6 "mc_parser.yy" // lalr1.cc:377
namespace MC {
#line 137 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.hh" // lalr1.cc:377



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class MC_Parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // BOOL
      char dummy1[sizeof(bool)];

      // APPROXNUM
      char dummy2[sizeof(float)];

      // COMPARISON
      // INTNUM
      // column_list
      // select_expr_list
      // table_references
      // delete_opts
      // delete_list
      // insert_opts
      // insert_vals_list
      // create_col_list
      // column_atts
      // opt_length
      // opt_binary
      // opt_uz
      // data_type
      char dummy3[sizeof(int)];

      // WORD
      // HLH
      // NAME
      // STRING
      // USERVAR
      char dummy4[sizeof(std::string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        END = 0,
        ASSIGN = 258,
        OR = 259,
        XOR = 260,
        ANDOP = 261,
        IN = 262,
        IS = 263,
        LIKE = 264,
        REGEXP = 265,
        NOT = 266,
        BETWEEN = 267,
        COMPARISON = 268,
        MOD = 269,
        UMINUS = 270,
        UPPER = 271,
        LOWER = 272,
        WORD = 273,
        NEWLINE = 274,
        HLH = 275,
        NAME = 276,
        STRING = 277,
        INTNUM = 278,
        BOOL = 279,
        APPROXNUM = 280,
        USERVAR = 281,
        ADD = 282,
        ALL = 283,
        ALTER = 284,
        ANALYZE = 285,
        AND = 286,
        ANY = 287,
        AS = 288,
        ASC = 289,
        AUTO_INCREMENT = 290,
        BEFORE = 291,
        BIGINT = 292,
        BINARY = 293,
        BIT = 294,
        BLOB = 295,
        BOTH = 296,
        BY = 297,
        CALL = 298,
        CASCADE = 299,
        CASE = 300,
        CHANGE = 301,
        CHAR = 302,
        CHECK = 303,
        COLLATE = 304,
        COLUMN = 305,
        COMMENT = 306,
        CONDITION = 307,
        CONSTRAINT = 308,
        CONTINUE = 309,
        CONVERT = 310,
        CREATE = 311,
        CROSS = 312,
        CURRENT_DATE = 313,
        CURRENT_TIME = 314,
        CURRENT_TIMESTAMP = 315,
        CURRENT_USER = 316,
        CURSOR = 317,
        DATABASE = 318,
        DATABASES = 319,
        DATE = 320,
        DATETIME = 321,
        DAY_HOUR = 322,
        DAY_MICROSECOND = 323,
        DAY_MINUTE = 324,
        DAY_SECOND = 325,
        DECIMAL = 326,
        DECLARE = 327,
        DEFAULT = 328,
        DELAYED = 329,
        DELETE = 330,
        DESC = 331,
        DESCRIBE = 332,
        DETERMINISTIC = 333,
        DISTINCT = 334,
        DISTINCTROW = 335,
        DIV = 336,
        DOUBLE = 337,
        DROP = 338,
        DUAL = 339,
        EACH = 340,
        ELSE = 341,
        ELSEIF = 342,
        ENCLOSED = 343,
        ENUM = 344,
        ESCAPED = 345,
        EXIT = 346,
        EXPLAIN = 347,
        FETCH = 348,
        FLOAT = 349,
        FOR = 350,
        FORCE = 351,
        FOREIGN = 352,
        FROM = 353,
        FULLTEXT = 354,
        GRANT = 355,
        GROUP = 356,
        HAVING = 357,
        HIGH_PRIORITY = 358,
        HOUR_MICROSECOND = 359,
        HOUR_MINUTE = 360,
        HOUR_SECOND = 361,
        IF = 362,
        IGNORE = 363,
        INDEX = 364,
        INFILE = 365,
        INNER = 366,
        INOUT = 367,
        INSENSITIVE = 368,
        INSERT = 369,
        INT = 370,
        INTEGER = 371,
        INTERVAL = 372,
        INTO = 373,
        ITERATE = 374,
        JOIN = 375,
        KEY = 376,
        KEYS = 377,
        KILL = 378,
        LEADING = 379,
        LEAVE = 380,
        LEFT = 381,
        LIMIT = 382,
        LINES = 383,
        LOAD = 384,
        LOCALTIME = 385,
        LOCALTIMESTAMP = 386,
        LOCK = 387,
        LONG = 388,
        LONGBLOB = 389,
        LONGTEXT = 390,
        LOOP = 391,
        LOW_PRIORITY = 392,
        MATCH = 393,
        MEDIUMBLOB = 394,
        MEDIUMINT = 395,
        MEDIUMTEXT = 396,
        MINUTE_MICROSECOND = 397,
        MINUTE_SECOND = 398,
        MODIFIES = 399,
        NATURAL = 400,
        NO_WRITE_TO_BINLOG = 401,
        NULLX = 402,
        NUMBER = 403,
        ON = 404,
        ONDUPLICATE = 405,
        OPTIMIZE = 406,
        OPTION = 407,
        OPTIONALLY = 408,
        ORDER = 409,
        OUT = 410,
        OUTER = 411,
        OUTFILE = 412,
        PRECISION = 413,
        PRIMARY = 414,
        PROCEDURE = 415,
        PURGE = 416,
        QUICK = 417,
        READ = 418,
        READS = 419,
        REAL = 420,
        REFERENCES = 421,
        RELEASE = 422,
        RENAME = 423,
        REPEAT = 424,
        REPLACE = 425,
        REQUIRE = 426,
        RESTRICT = 427,
        RETURN = 428,
        REVOKE = 429,
        RIGHT = 430,
        ROLLUP = 431,
        SCHEMA = 432,
        SCHEMAS = 433,
        SECOND_MICROSECOND = 434,
        SELECT = 435,
        SENSITIVE = 436,
        SEPARATOR = 437,
        SET = 438,
        SHOW = 439,
        SMALLINT = 440,
        SOME = 441,
        SONAME = 442,
        SPATIAL = 443,
        SPECIFIC = 444,
        SQL = 445,
        SQLEXCEPTION = 446,
        SQLSTATE = 447,
        SQLWARNING = 448,
        SQL_BIG_RESULT = 449,
        SQL_CALC_FOUND_ROWS = 450,
        SQL_SMALL_RESULT = 451,
        SSL = 452,
        STARTING = 453,
        STRAIGHT_JOIN = 454,
        TABLE = 455,
        TEMPORARY = 456,
        TEXT = 457,
        TERMINATED = 458,
        THEN = 459,
        TINYINT = 460,
        TINYTEXT = 461,
        TO = 462,
        TRAILING = 463,
        TRIGGER = 464,
        UNDO = 465,
        UNION = 466,
        UNIQUE = 467,
        UNLOCK = 468,
        UNSIGNED = 469,
        UPDATE = 470,
        USAGE = 471,
        USE = 472,
        USING = 473,
        UTC_DATE = 474,
        UTC_TIME = 475,
        UTC_TIMESTAMP = 476,
        VALUES = 477,
        VARBINARY = 478,
        VARCHAR = 479,
        VARYING = 480,
        WHEN = 481,
        WHERE = 482,
        WHILE = 483,
        WITH = 484,
        WRITE = 485,
        QUIT = 486,
        FSUBSTRING = 487,
        FTRIM = 488,
        FDATE_ADD = 489,
        FDATE_SUB = 490,
        FCOUNT = 491
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const bool v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const float v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const int v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_OR (const location_type& l);

    static inline
    symbol_type
    make_XOR (const location_type& l);

    static inline
    symbol_type
    make_ANDOP (const location_type& l);

    static inline
    symbol_type
    make_IN (const location_type& l);

    static inline
    symbol_type
    make_IS (const location_type& l);

    static inline
    symbol_type
    make_LIKE (const location_type& l);

    static inline
    symbol_type
    make_REGEXP (const location_type& l);

    static inline
    symbol_type
    make_NOT (const location_type& l);

    static inline
    symbol_type
    make_BETWEEN (const location_type& l);

    static inline
    symbol_type
    make_COMPARISON (const int& v, const location_type& l);

    static inline
    symbol_type
    make_MOD (const location_type& l);

    static inline
    symbol_type
    make_UMINUS (const location_type& l);

    static inline
    symbol_type
    make_UPPER (const location_type& l);

    static inline
    symbol_type
    make_LOWER (const location_type& l);

    static inline
    symbol_type
    make_WORD (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_NEWLINE (const location_type& l);

    static inline
    symbol_type
    make_HLH (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_NAME (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_STRING (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_INTNUM (const int& v, const location_type& l);

    static inline
    symbol_type
    make_BOOL (const bool& v, const location_type& l);

    static inline
    symbol_type
    make_APPROXNUM (const float& v, const location_type& l);

    static inline
    symbol_type
    make_USERVAR (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_ADD (const location_type& l);

    static inline
    symbol_type
    make_ALL (const location_type& l);

    static inline
    symbol_type
    make_ALTER (const location_type& l);

    static inline
    symbol_type
    make_ANALYZE (const location_type& l);

    static inline
    symbol_type
    make_AND (const location_type& l);

    static inline
    symbol_type
    make_ANY (const location_type& l);

    static inline
    symbol_type
    make_AS (const location_type& l);

    static inline
    symbol_type
    make_ASC (const location_type& l);

    static inline
    symbol_type
    make_AUTO_INCREMENT (const location_type& l);

    static inline
    symbol_type
    make_BEFORE (const location_type& l);

    static inline
    symbol_type
    make_BIGINT (const location_type& l);

    static inline
    symbol_type
    make_BINARY (const location_type& l);

    static inline
    symbol_type
    make_BIT (const location_type& l);

    static inline
    symbol_type
    make_BLOB (const location_type& l);

    static inline
    symbol_type
    make_BOTH (const location_type& l);

    static inline
    symbol_type
    make_BY (const location_type& l);

    static inline
    symbol_type
    make_CALL (const location_type& l);

    static inline
    symbol_type
    make_CASCADE (const location_type& l);

    static inline
    symbol_type
    make_CASE (const location_type& l);

    static inline
    symbol_type
    make_CHANGE (const location_type& l);

    static inline
    symbol_type
    make_CHAR (const location_type& l);

    static inline
    symbol_type
    make_CHECK (const location_type& l);

    static inline
    symbol_type
    make_COLLATE (const location_type& l);

    static inline
    symbol_type
    make_COLUMN (const location_type& l);

    static inline
    symbol_type
    make_COMMENT (const location_type& l);

    static inline
    symbol_type
    make_CONDITION (const location_type& l);

    static inline
    symbol_type
    make_CONSTRAINT (const location_type& l);

    static inline
    symbol_type
    make_CONTINUE (const location_type& l);

    static inline
    symbol_type
    make_CONVERT (const location_type& l);

    static inline
    symbol_type
    make_CREATE (const location_type& l);

    static inline
    symbol_type
    make_CROSS (const location_type& l);

    static inline
    symbol_type
    make_CURRENT_DATE (const location_type& l);

    static inline
    symbol_type
    make_CURRENT_TIME (const location_type& l);

    static inline
    symbol_type
    make_CURRENT_TIMESTAMP (const location_type& l);

    static inline
    symbol_type
    make_CURRENT_USER (const location_type& l);

    static inline
    symbol_type
    make_CURSOR (const location_type& l);

    static inline
    symbol_type
    make_DATABASE (const location_type& l);

    static inline
    symbol_type
    make_DATABASES (const location_type& l);

    static inline
    symbol_type
    make_DATE (const location_type& l);

    static inline
    symbol_type
    make_DATETIME (const location_type& l);

    static inline
    symbol_type
    make_DAY_HOUR (const location_type& l);

    static inline
    symbol_type
    make_DAY_MICROSECOND (const location_type& l);

    static inline
    symbol_type
    make_DAY_MINUTE (const location_type& l);

    static inline
    symbol_type
    make_DAY_SECOND (const location_type& l);

    static inline
    symbol_type
    make_DECIMAL (const location_type& l);

    static inline
    symbol_type
    make_DECLARE (const location_type& l);

    static inline
    symbol_type
    make_DEFAULT (const location_type& l);

    static inline
    symbol_type
    make_DELAYED (const location_type& l);

    static inline
    symbol_type
    make_DELETE (const location_type& l);

    static inline
    symbol_type
    make_DESC (const location_type& l);

    static inline
    symbol_type
    make_DESCRIBE (const location_type& l);

    static inline
    symbol_type
    make_DETERMINISTIC (const location_type& l);

    static inline
    symbol_type
    make_DISTINCT (const location_type& l);

    static inline
    symbol_type
    make_DISTINCTROW (const location_type& l);

    static inline
    symbol_type
    make_DIV (const location_type& l);

    static inline
    symbol_type
    make_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_DROP (const location_type& l);

    static inline
    symbol_type
    make_DUAL (const location_type& l);

    static inline
    symbol_type
    make_EACH (const location_type& l);

    static inline
    symbol_type
    make_ELSE (const location_type& l);

    static inline
    symbol_type
    make_ELSEIF (const location_type& l);

    static inline
    symbol_type
    make_ENCLOSED (const location_type& l);

    static inline
    symbol_type
    make_ENUM (const location_type& l);

    static inline
    symbol_type
    make_ESCAPED (const location_type& l);

    static inline
    symbol_type
    make_EXIT (const location_type& l);

    static inline
    symbol_type
    make_EXPLAIN (const location_type& l);

    static inline
    symbol_type
    make_FETCH (const location_type& l);

    static inline
    symbol_type
    make_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_FOR (const location_type& l);

    static inline
    symbol_type
    make_FORCE (const location_type& l);

    static inline
    symbol_type
    make_FOREIGN (const location_type& l);

    static inline
    symbol_type
    make_FROM (const location_type& l);

    static inline
    symbol_type
    make_FULLTEXT (const location_type& l);

    static inline
    symbol_type
    make_GRANT (const location_type& l);

    static inline
    symbol_type
    make_GROUP (const location_type& l);

    static inline
    symbol_type
    make_HAVING (const location_type& l);

    static inline
    symbol_type
    make_HIGH_PRIORITY (const location_type& l);

    static inline
    symbol_type
    make_HOUR_MICROSECOND (const location_type& l);

    static inline
    symbol_type
    make_HOUR_MINUTE (const location_type& l);

    static inline
    symbol_type
    make_HOUR_SECOND (const location_type& l);

    static inline
    symbol_type
    make_IF (const location_type& l);

    static inline
    symbol_type
    make_IGNORE (const location_type& l);

    static inline
    symbol_type
    make_INDEX (const location_type& l);

    static inline
    symbol_type
    make_INFILE (const location_type& l);

    static inline
    symbol_type
    make_INNER (const location_type& l);

    static inline
    symbol_type
    make_INOUT (const location_type& l);

    static inline
    symbol_type
    make_INSENSITIVE (const location_type& l);

    static inline
    symbol_type
    make_INSERT (const location_type& l);

    static inline
    symbol_type
    make_INT (const location_type& l);

    static inline
    symbol_type
    make_INTEGER (const location_type& l);

    static inline
    symbol_type
    make_INTERVAL (const location_type& l);

    static inline
    symbol_type
    make_INTO (const location_type& l);

    static inline
    symbol_type
    make_ITERATE (const location_type& l);

    static inline
    symbol_type
    make_JOIN (const location_type& l);

    static inline
    symbol_type
    make_KEY (const location_type& l);

    static inline
    symbol_type
    make_KEYS (const location_type& l);

    static inline
    symbol_type
    make_KILL (const location_type& l);

    static inline
    symbol_type
    make_LEADING (const location_type& l);

    static inline
    symbol_type
    make_LEAVE (const location_type& l);

    static inline
    symbol_type
    make_LEFT (const location_type& l);

    static inline
    symbol_type
    make_LIMIT (const location_type& l);

    static inline
    symbol_type
    make_LINES (const location_type& l);

    static inline
    symbol_type
    make_LOAD (const location_type& l);

    static inline
    symbol_type
    make_LOCALTIME (const location_type& l);

    static inline
    symbol_type
    make_LOCALTIMESTAMP (const location_type& l);

    static inline
    symbol_type
    make_LOCK (const location_type& l);

    static inline
    symbol_type
    make_LONG (const location_type& l);

    static inline
    symbol_type
    make_LONGBLOB (const location_type& l);

    static inline
    symbol_type
    make_LONGTEXT (const location_type& l);

    static inline
    symbol_type
    make_LOOP (const location_type& l);

    static inline
    symbol_type
    make_LOW_PRIORITY (const location_type& l);

    static inline
    symbol_type
    make_MATCH (const location_type& l);

    static inline
    symbol_type
    make_MEDIUMBLOB (const location_type& l);

    static inline
    symbol_type
    make_MEDIUMINT (const location_type& l);

    static inline
    symbol_type
    make_MEDIUMTEXT (const location_type& l);

    static inline
    symbol_type
    make_MINUTE_MICROSECOND (const location_type& l);

    static inline
    symbol_type
    make_MINUTE_SECOND (const location_type& l);

    static inline
    symbol_type
    make_MODIFIES (const location_type& l);

    static inline
    symbol_type
    make_NATURAL (const location_type& l);

    static inline
    symbol_type
    make_NO_WRITE_TO_BINLOG (const location_type& l);

    static inline
    symbol_type
    make_NULLX (const location_type& l);

    static inline
    symbol_type
    make_NUMBER (const location_type& l);

    static inline
    symbol_type
    make_ON (const location_type& l);

    static inline
    symbol_type
    make_ONDUPLICATE (const location_type& l);

    static inline
    symbol_type
    make_OPTIMIZE (const location_type& l);

    static inline
    symbol_type
    make_OPTION (const location_type& l);

    static inline
    symbol_type
    make_OPTIONALLY (const location_type& l);

    static inline
    symbol_type
    make_ORDER (const location_type& l);

    static inline
    symbol_type
    make_OUT (const location_type& l);

    static inline
    symbol_type
    make_OUTER (const location_type& l);

    static inline
    symbol_type
    make_OUTFILE (const location_type& l);

    static inline
    symbol_type
    make_PRECISION (const location_type& l);

    static inline
    symbol_type
    make_PRIMARY (const location_type& l);

    static inline
    symbol_type
    make_PROCEDURE (const location_type& l);

    static inline
    symbol_type
    make_PURGE (const location_type& l);

    static inline
    symbol_type
    make_QUICK (const location_type& l);

    static inline
    symbol_type
    make_READ (const location_type& l);

    static inline
    symbol_type
    make_READS (const location_type& l);

    static inline
    symbol_type
    make_REAL (const location_type& l);

    static inline
    symbol_type
    make_REFERENCES (const location_type& l);

    static inline
    symbol_type
    make_RELEASE (const location_type& l);

    static inline
    symbol_type
    make_RENAME (const location_type& l);

    static inline
    symbol_type
    make_REPEAT (const location_type& l);

    static inline
    symbol_type
    make_REPLACE (const location_type& l);

    static inline
    symbol_type
    make_REQUIRE (const location_type& l);

    static inline
    symbol_type
    make_RESTRICT (const location_type& l);

    static inline
    symbol_type
    make_RETURN (const location_type& l);

    static inline
    symbol_type
    make_REVOKE (const location_type& l);

    static inline
    symbol_type
    make_RIGHT (const location_type& l);

    static inline
    symbol_type
    make_ROLLUP (const location_type& l);

    static inline
    symbol_type
    make_SCHEMA (const location_type& l);

    static inline
    symbol_type
    make_SCHEMAS (const location_type& l);

    static inline
    symbol_type
    make_SECOND_MICROSECOND (const location_type& l);

    static inline
    symbol_type
    make_SELECT (const location_type& l);

    static inline
    symbol_type
    make_SENSITIVE (const location_type& l);

    static inline
    symbol_type
    make_SEPARATOR (const location_type& l);

    static inline
    symbol_type
    make_SET (const location_type& l);

    static inline
    symbol_type
    make_SHOW (const location_type& l);

    static inline
    symbol_type
    make_SMALLINT (const location_type& l);

    static inline
    symbol_type
    make_SOME (const location_type& l);

    static inline
    symbol_type
    make_SONAME (const location_type& l);

    static inline
    symbol_type
    make_SPATIAL (const location_type& l);

    static inline
    symbol_type
    make_SPECIFIC (const location_type& l);

    static inline
    symbol_type
    make_SQL (const location_type& l);

    static inline
    symbol_type
    make_SQLEXCEPTION (const location_type& l);

    static inline
    symbol_type
    make_SQLSTATE (const location_type& l);

    static inline
    symbol_type
    make_SQLWARNING (const location_type& l);

    static inline
    symbol_type
    make_SQL_BIG_RESULT (const location_type& l);

    static inline
    symbol_type
    make_SQL_CALC_FOUND_ROWS (const location_type& l);

    static inline
    symbol_type
    make_SQL_SMALL_RESULT (const location_type& l);

    static inline
    symbol_type
    make_SSL (const location_type& l);

    static inline
    symbol_type
    make_STARTING (const location_type& l);

    static inline
    symbol_type
    make_STRAIGHT_JOIN (const location_type& l);

    static inline
    symbol_type
    make_TABLE (const location_type& l);

    static inline
    symbol_type
    make_TEMPORARY (const location_type& l);

    static inline
    symbol_type
    make_TEXT (const location_type& l);

    static inline
    symbol_type
    make_TERMINATED (const location_type& l);

    static inline
    symbol_type
    make_THEN (const location_type& l);

    static inline
    symbol_type
    make_TINYINT (const location_type& l);

    static inline
    symbol_type
    make_TINYTEXT (const location_type& l);

    static inline
    symbol_type
    make_TO (const location_type& l);

    static inline
    symbol_type
    make_TRAILING (const location_type& l);

    static inline
    symbol_type
    make_TRIGGER (const location_type& l);

    static inline
    symbol_type
    make_UNDO (const location_type& l);

    static inline
    symbol_type
    make_UNION (const location_type& l);

    static inline
    symbol_type
    make_UNIQUE (const location_type& l);

    static inline
    symbol_type
    make_UNLOCK (const location_type& l);

    static inline
    symbol_type
    make_UNSIGNED (const location_type& l);

    static inline
    symbol_type
    make_UPDATE (const location_type& l);

    static inline
    symbol_type
    make_USAGE (const location_type& l);

    static inline
    symbol_type
    make_USE (const location_type& l);

    static inline
    symbol_type
    make_USING (const location_type& l);

    static inline
    symbol_type
    make_UTC_DATE (const location_type& l);

    static inline
    symbol_type
    make_UTC_TIME (const location_type& l);

    static inline
    symbol_type
    make_UTC_TIMESTAMP (const location_type& l);

    static inline
    symbol_type
    make_VALUES (const location_type& l);

    static inline
    symbol_type
    make_VARBINARY (const location_type& l);

    static inline
    symbol_type
    make_VARCHAR (const location_type& l);

    static inline
    symbol_type
    make_VARYING (const location_type& l);

    static inline
    symbol_type
    make_WHEN (const location_type& l);

    static inline
    symbol_type
    make_WHERE (const location_type& l);

    static inline
    symbol_type
    make_WHILE (const location_type& l);

    static inline
    symbol_type
    make_WITH (const location_type& l);

    static inline
    symbol_type
    make_WRITE (const location_type& l);

    static inline
    symbol_type
    make_QUIT (const location_type& l);

    static inline
    symbol_type
    make_FSUBSTRING (const location_type& l);

    static inline
    symbol_type
    make_FTRIM (const location_type& l);

    static inline
    symbol_type
    make_FDATE_ADD (const location_type& l);

    static inline
    symbol_type
    make_FDATE_SUB (const location_type& l);

    static inline
    symbol_type
    make_FCOUNT (const location_type& l);


    /// Build a parser object.
    MC_Parser (MC_Scanner  &scanner_yyarg, MC_Driver  &driver_yyarg);
    virtual ~MC_Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    MC_Parser (const MC_Parser&);
    MC_Parser& operator= (const MC_Parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short int yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (int t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short int yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned short int yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned short int yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 246,     ///< Last index in yytable_.
      yynnts_ = 35,  ///< Number of nonterminal symbols.
      yyfinal_ = 35, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 251  ///< Number of tokens.
    };


    // User arguments.
    MC_Scanner  &scanner;
    MC_Driver  &driver;
  };


#line 6 "mc_parser.yy" // lalr1.cc:377
} // MC
#line 1864 "/home/kk/CLionProjects/mini/cmake-build-debug/mc_parser.tab.hh" // lalr1.cc:377




#endif // !YY_YY_HOME_KK_CLIONPROJECTS_MINI_CMAKE_BUILD_DEBUG_MC_PARSER_TAB_HH_INCLUDED
