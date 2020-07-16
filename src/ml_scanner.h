#ifndef ML_SCANNER_H
#define ML_SCANNER_H

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "ml_parser.tab.hpp"
#include "location.hh"

namespace copl::ml {

class MLScanner : public yyFlexLexer {
public:
    MLScanner(std::istream * in) : yyFlexLexer(in) {
    };

    virtual ~MLScanner() {
    }

    // get rid of override virtual function warning
    using FlexLexer::yylex;

    // YY_DECL defined in mc_lexer.l
    // Method body created by flex in mc_lexer.yy.cc
    virtual int yylex(copl::ml::MLParser::semantic_type * const lval,
                      copl::ml::MLParser::location_type * location);

private:
    copl::ml::MLParser::semantic_type * yylval = nullptr;
};
}

#endif // define ML_SCANNER_H
