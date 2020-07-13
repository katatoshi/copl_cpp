%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace { copl::ml }
/**
 * bison 3.3.2 change
 * %define parser_class_name to this, updated
 * should work for previous bison versions as
 * well. -jcb 24 Jan 2020
 */
%define api.parser.class { MLParser }

%code requires{
#include <memory>

#include "ml_ast.h"

namespace copl::ml {
    class MLDriver;
    class MLScanner;
}

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { MLScanner & scanner }
%parse-param { MLDriver & driver }

%code{
#include <cstdlib>
#include <fstream>
#include <iostream>

/* include for all driver functions */
#include "ml_driver.h"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token <copl::ml::IntExp> INT
%token <copl::ml::BoolExp> BOOL
%token PLUS
%token MINUS
%token TIMES
%token LT
%token IF
%token THEN
%token ELSE
%token LP
%token RP
%token END_OF_EXP
%token END_OF_FILE
%nterm <std::shared_ptr<const copl::ml::Exp>> exp
%nterm <std::shared_ptr<const copl::ml::Exp>> exp_lt
%nterm <std::shared_ptr<const copl::ml::Exp>> exp_plus
%nterm <std::shared_ptr<const copl::ml::Exp>> exp_times
%nterm <std::shared_ptr<const copl::ml::Exp>> exp_primary
%locations

%%

result
    : exp END_OF_EXP {
        driver.set_parsed_exp($1);
        return 0;
    }
    | END_OF_FILE {
        driver.eof_found = true;
        return 0;
    }
    ;
exp
    : exp_lt
    | IF exp THEN exp ELSE exp {
        $$ = copl::ml::create_if_exp($2, $4, $6);
    }
    | exp_lt LT IF exp THEN exp ELSE exp {
        $$ = copl::ml::create_lt_op_exp($1, create_if_exp($4, $6, $8));
    }
    | exp_plus PLUS IF exp THEN exp ELSE exp {
        $$ = copl::ml::create_plus_op_exp($1, create_if_exp($4, $6, $8));
    }
    | exp_plus MINUS IF exp THEN exp ELSE exp {
        $$ = copl::ml::create_minus_op_exp($1, create_if_exp($4, $6, $8));
    }
    | exp_times TIMES IF exp THEN exp ELSE exp {
        $$ = copl::ml::create_times_op_exp($1, create_if_exp($4, $6, $8));
    }
    ;
exp_lt
    : exp_plus
    | exp_lt LT exp_plus {
        $$ = copl::ml::create_lt_op_exp($1, $3);
    }
    ;
exp_plus
    : exp_times
    | exp_plus PLUS exp_times {
        $$ = copl::ml::create_plus_op_exp($1, $3);
    }
    | exp_plus MINUS exp_times {
        $$ = copl::ml::create_minus_op_exp($1, $3);
    }
    ;
exp_times
    : exp_primary
    | exp_times TIMES exp_primary {
        $$ = copl::ml::create_times_op_exp($1, $3);
    }
    ;
exp_primary
    : INT {
        $$ = copl::ml::create_int_exp($1);
    }
    | MINUS INT {
        $$ = copl::ml::create_int_exp(-$2);
    }
    | BOOL {
        $$ = copl::ml::create_bool_exp($1);
    }
    | LP exp RP {
        $$ = $2;
    }
    ;

%%

void copl::ml::MLParser::error(const location_type & location,
                               const std::string & err_message) {
    std::cerr << "Error: " << err_message << " at " << location << "\n";
}
