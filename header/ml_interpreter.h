#ifndef ML_INTERPRETER_H
#define ML_INTERPRETER_H

#include <memory>

#include "ml_ast.h"

namespace copl::ml {

class MLInterpreter {
public:
    std::shared_ptr<const Result> evaluate(const std::shared_ptr<const Exp> & exp);
};
}

#endif // ML_INTERPRETER_H
