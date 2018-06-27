%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */ 
#include "mc_scanner.hpp"
#undef  YY_DECL
#define YY_DECL int MC::MC_Scanner::yylex( MC::MC_Parser::semantic_type * const lval, MC::MC_Parser::location_type *loc )

/* typedef to make the returns for the tokens shorter */
using token = MC::MC_Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="MC::MC_Scanner"
%option noyywrap case-insensitive
%option c++

%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}
ADD	{ return token::ADD; }
ALL	{ return token::ALL; }
ALTER	{ return token::ALTER; }
ANALYZE	{ return token::ANALYZE; }

  /* Hack for BETWEEN ... AND ... 
   * return token::special AND token if BETWEEN seen
   */
AND	{ return token::ANDOP; }
ANY     { return token::ANY; }
AS	{ return token::AS; }
ASC	{ return token::ASC; }
AUTO_INCREMENT	{ return token::AUTO_INCREMENT; }
BEFORE	{ return token::BEFORE; }
INT8|BIGINT	{ return token::BIGINT; }
BINARY	{ return token::BINARY; }
BIT	{ return token::BIT; }
BLOB	{ return token::BLOB; }
BOTH	{ return token::BOTH; }
BY	{ return token::BY; }
CALL	{ return token::CALL; }
CASCADE	{ return token::CASCADE; }
CASE	{ return token::CASE; }
CHANGE	{ return token::CHANGE; }
CHAR(ACTER)?	{ return token::CHAR; }
CHECK	{ return token::CHECK; }
COLLATE	{ return token::COLLATE; }
COLUMN	{ return token::COLUMN; }
COMMENT	{ return token::COMMENT; }
CONDITION	{ return token::CONDITION; }
CONSTRAINT	{ return token::CONSTRAINT; }
CONTINUE	{ return token::CONTINUE; }
CONVERT	{ return token::CONVERT; }
CREATE	{ return token::CREATE; }
CROSS	{ return token::CROSS; }
CURRENT_DATE	{ return token::CURRENT_DATE; }
CURRENT_TIME	{ return token::CURRENT_TIME; }
CURRENT_TIMESTAMP	{ return token::CURRENT_TIMESTAMP; }
CURRENT_USER	{ return token::CURRENT_USER; }
CURSOR	{ return token::CURSOR; }
DATABASE	{ return token::DATABASE; }
DATABASES	{ return token::DATABASES; }
DATE	{ return token::DATE; }
DATETIME	{ return token::DATETIME; }
DAY_HOUR	{ return token::DAY_HOUR; }
DAY_MICROSECOND	{ return token::DAY_MICROSECOND; }
DAY_MINUTE	{ return token::DAY_MINUTE; }
DAY_SECOND	{ return token::DAY_SECOND; }
NUMERIC|DEC|DECIMAL	{ return token::DECIMAL; }
DECLARE	{ return token::DECLARE; }
DEFAULT	{ return token::DEFAULT; }
DELAYED	{ return token::DELAYED; }
DELETE	{ return token::DELETE; }
DESCRIBE	{ return token::DESCRIBE; }
DETERMINISTIC	{ return token::DETERMINISTIC; }
DISTINCT	{ return token::DISTINCT; }
DISTINCTROW	{ return token::DISTINCTROW; }
DIV	{ return token::DIV; }
FLOAT8|DOUBLE	{ return token::DOUBLE; }
DROP	{ return token::DROP; }
DUAL	{ return token::DUAL; }
EACH	{ return token::EACH; }
ELSE	{ return token::ELSE; }
ELSEIF	{ return token::ELSEIF; }
END	{ return token::END; }
ENUM { return token::ENUM; }
ESCAPED	{ return token::ESCAPED; }
EXIT	{ return token::EXIT; }
EXPLAIN	{ return token::EXPLAIN; }
FETCH	{ return token::FETCH; }
FLOAT4?	{ return token::FLOAT; }
FOR	{ return token::FOR; }
FORCE	{ return token::FORCE; }
FOREIGN	{ return token::FOREIGN; }
FROM	{ return token::FROM; }
FULLTEXT	{ return token::FULLTEXT; }
GRANT	{ return token::GRANT; }
GROUP	{ return token::GROUP; }
HAVING	{ return token::HAVING; }
HIGH_PRIORITY	{ return token::HIGH_PRIORITY; }
HOUR_MICROSECOND	{ return token::HOUR_MICROSECOND; }
HOUR_MINUTE	{ return token::HOUR_MINUTE; }
HOUR_SECOND	{ return token::HOUR_SECOND; }
IF	{ return token::IF; }
IGNORE	{ return token::IGNORE; }
IN	{ return token::IN; }
INFILE	{ return token::INFILE; }
INNER	{ return token::INNER; }
INOUT	{ return token::INOUT; }
INSENSITIVE	{ return token::INSENSITIVE; }
INSERT	{ return token::INSERT; }
INT4?|INTEGER	{ return token::INTEGER; }
INTERVAL	{ return token::INTERVAL; }
INTO	{ return token::INTO; }
IS	{ return token::IS; }
ITERATE	{ return token::ITERATE; }
JOIN	{ return token::JOIN; }
INDEX|KEY	{ return token::KEY; }
KEYS	{ return token::KEYS; }
KILL	{ return token::KILL; }
LEADING	{ return token::LEADING; }
LEAVE	{ return token::LEAVE; }
LEFT	{ return token::LEFT; }
LIKE	{ return token::LIKE; }
LIMIT	{ return token::LIMIT; }
LINES	{ return token::LINES; }
LOAD	{ return token::LOAD; }
LOCALTIME	{ return token::LOCALTIME; }
LOCALTIMESTAMP	{ return token::LOCALTIMESTAMP; }
LOCK	{ return token::LOCK; }
LONG	{ return token::LONG; }
LONGBLOB	{ return token::LONGBLOB; }
LONGTEXT	{ return token::LONGTEXT; }
LOOP	{ return token::LOOP; }
LOW_PRIORITY	{ return token::LOW_PRIORITY; }
MATCH	{ return token::MATCH; }
MEDIUMBLOB	{ return token::MEDIUMBLOB; }
MIDDLEINT|MEDIUMINT	{ return token::MEDIUMINT; }
MEDIUMTEXT	{ return token::MEDIUMTEXT; }
MINUTE_MICROSECOND	{ return token::MINUTE_MICROSECOND; }
MINUTE_SECOND	{ return token::MINUTE_SECOND; }
MOD	{ return token::MOD; }
MODIFIES	{ return token::MODIFIES; }
NATURAL	{ return token::NATURAL; }
NOT	{ return token::NOT; }
NO_WRITE_TO_BINLOG	{ return token::NO_WRITE_TO_BINLOG; }
NULL	{ return token::NULLX; }
NUMBER	{ return token::NUMBER; }
ON	{ return token::ON; }
ON[ \t\n]+DUPLICATE { return token::ONDUPLICATE; } /* hack due to limited lookahead */
OPTIMIZE	{ return token::OPTIMIZE; }
OPTION	{ return token::OPTION; }
OPTIONALLY	{ return token::OPTIONALLY; }
OR	{ return token::OR; }
ORDER	{ return token::ORDER; }
OUT	{ return token::OUT; }
OUTER	{ return token::OUTER; }
OUTFILE	{ return token::OUTFILE; }
PRECISION	{ return token::PRECISION; }
PRIMARY	{ return token::PRIMARY; }
PROCEDURE	{ return token::PROCEDURE; }
PURGE	{ return token::PURGE; }
QUICK	{ return token::QUICK; }
READ	{ return token::READ; }
READS	{ return token::READS; }
REAL	{ return token::REAL; }
REFERENCES	{ return token::REFERENCES; }
REGEXP|RLIKE	{ return token::REGEXP; }
RELEASE	{ return token::RELEASE; }
RENAME	{ return token::RENAME; }
REPEAT	{ return token::REPEAT; }
REPLACE	{ return token::REPLACE; }
REQUIRE	{ return token::REQUIRE; }
RESTRICT	{ return token::RESTRICT; }
RETURN	{ return token::RETURN; }
REVOKE	{ return token::REVOKE; }
RIGHT	{ return token::RIGHT; }
ROLLUP	{ return token::ROLLUP; }
SCHEMA	{ return token::SCHEMA; }
SCHEMAS	{ return token::SCHEMAS; }
SECOND_MICROSECOND	{ return token::SECOND_MICROSECOND; }
SELECT	{ return token::SELECT; }
SENSITIVE	{ return token::SENSITIVE; }
SEPARATOR	{ return token::SEPARATOR; }
SET	{ return token::SET; }
INT2|SMALLINT	{ return token::SMALLINT; }
SOME	{ return token::SOME; }
SONAME	{ return token::SONAME; }
SPATIAL	{ return token::SPATIAL; }
SPECIFIC	{ return token::SPECIFIC; }
SQL	{ return token::SQL; }
SQLEXCEPTION	{ return token::SQLEXCEPTION; }
SQLSTATE	{ return token::SQLSTATE; }
SQLWARNING	{ return token::SQLWARNING; }
SQL_BIG_RESULT	{ return token::SQL_BIG_RESULT; }
SQL_CALC_FOUND_ROWS	{ return token::SQL_CALC_FOUND_ROWS; }
SQL_SMALL_RESULT	{ return token::SQL_SMALL_RESULT; }
SSL	{ return token::SSL; }
STARTING	{ return token::STARTING; }
STRAIGHT_JOIN	{ return token::STRAIGHT_JOIN; }
TABLE	{ return token::TABLE; }
TEMPORARY	{ return token::TEMPORARY; }
TERMINATED	{ return token::TERMINATED; }
TEXT	{ return token::TEXT; }
THEN	{ return token::THEN; }
INT1|TINYINT	{ return token::TINYINT; }
TINYTEXT	{ return token::TINYTEXT; }
TO	{ return token::TO; }
TRAILING	{ return token::TRAILING; }
TRIGGER	{ return token::TRIGGER; }
UNDO	{ return token::UNDO; }
UNION	{ return token::UNION; }
UNIQUE	{ return token::UNIQUE; }
UNLOCK	{ return token::UNLOCK; }
UNSIGNED	{ return token::UNSIGNED; }
UPDATE	{ return token::UPDATE; }
USAGE	{ return token::USAGE; }
USE	{ return token::USE; }
USING	{ return token::USING; }
UTC_DATE	{ return token::UTC_DATE; }
UTC_TIME	{ return token::UTC_TIME; }
UTC_TIMESTAMP	{ return token::UTC_TIMESTAMP; }
VALUES?	{ return token::VALUES; }
VARBINARY	{ return token::VARBINARY; }
VARCHAR(ACTER)?	{ return token::VARCHAR; }
VARYING	{ return token::VARYING; }
WHEN	{ return token::WHEN; }
WHERE	{ return token::WHERE; }
WHILE	{ return token::WHILE; }
WITH	{ return token::WITH; }
WRITE	{ return token::WRITE; }
XOR	{ return token::XOR; }
quit {return token::QUIT;}
show {return token::show;}
desc {return token::desc;}
-?[0-9]+	        { yylval->build<int>(atoi(yytext)); return token::INTNUM; }

-?[0-9]+"."[0-9]* |
-?"."[0-9]+	|
-?[0-9]+E[-+]?[0-9]+	|
-?[0-9]+"."[0-9]*E[-+]?[0-9]+ |
-?"."[0-9]*E[-+]?[0-9]+	{ yylval->build<float>(atof(yytext)) ;
                                  return token::APPROXNUM; }
TRUE	{ yylval->build<bool>(true); return token::BOOL; }
UNKNOWN	{ yylval->build<bool>(false); return token::BOOL; }
FALSE	{ yylval->build<bool>(false); return token::BOOL; }

'(\\.|''|[^'\n])*'	|
\"(\\.|\"\"|[^"\n])*\"  { yylval->build<std::string>(yytext); return token::STRING; }

[-+&~|^/%*(),.;!]   { return yytext[0]; }
"&&"		{ return token::ANDOP; }
"||"            { return token::OR; }

"="	{ yylval->build<int>(4); return token::COMPARISON; }
"<=>"	{ yylval->build<int>(12); return token::COMPARISON; }
">="	{ yylval->build<int>(6); return token::COMPARISON; }
">"	{ yylval->build<int>(2); return token::COMPARISON; }
"<="	{ yylval->build<int>(5); return token::COMPARISON; }
"<"	{ yylval->build<int>(1); return token::COMPARISON; }
"!="	|
"<>"	{ yylval->build<int>(3); return token::COMPARISON; }

[A-Za-z][A-Za-z0-9_]*	{ yylval->build<std::string>(yytext);
                          return token::NAME; }
@[0-9a-z_.$]+ |
@\"[^"\n]+\" |
@`[^`\n]+` |
@'[^'\n]+' { yylval->build<std::string>(strdup(yytext+1)); return token::USERVAR; }

	/* everything else */
[ \t\n]         /* white space */
.               {  }
%%


