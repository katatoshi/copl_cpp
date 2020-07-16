%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */
#include "ml_scanner.h"
#undef  YY_DECL
#define YY_DECL int copl::ml::MLScanner::yylex(copl::ml::MLParser::semantic_type * const lval, copl::ml::MLParser::location_type * loc)

/* typedef to make the returns for the tokens shorter */
using token = copl::ml::MLParser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return (token::END_OF_FILE)

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="copl::ml::MLScanner"
%option noyywrap
%option c++

%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

"+" return token::PLUS;
"-" return token::MINUS;
"*" return token::TIMES;
"<" return token::LT;
"if" return token::IF;
"then" return token::THEN;
"else" return token::ELSE;
[0-9]+ {
    /**
     * Section 10.1.5.1 of the 3.0.2 Bison Manual says the
     * following should work:
     * yylval.build(yytext);
     * but it doesn't.
     * ref: http://goo.gl/KLn0w2
     */
    auto value = std::stoi(yytext);
    yylval->build<int>(value);
    return token::INT;
}
"false" {
    yylval->build<bool>(false);
    return token::BOOL;
}
"true" {
    yylval->build<bool>(true);
    return token::BOOL;
}
"(" return token::LP;
")" return token::RP;
";;\n" {
    loc->lines();
    return token::END_OF_EXP;
}
\n {
    loc->lines();
    std::cout << "  ";
}
[\t ] ;
<<EOF>> return token::END_OF_FILE;
. return yytext[0];
%%
