#ifndef ML_AST_H
#define ML_AST_H

#include <memory>
#include <string>
#include <variant>

namespace copl::ml {

class Error {};

using IntValue = int;

using BoolValue = bool;

using Value = std::variant<
    IntValue,
    BoolValue
>;

std::string value_to_string(const Value & value);

using Result = std::variant<
    Error,
    Value
>;

class Plus {};

class Minus {};

class Times {};

class Lt {};

using Prim = std::variant<
    Plus,
    Minus,
    Times,
    Lt
>;

std::string prim_to_string(const Prim & prim);

using IntExp = int;

using BoolExp = bool;

class OpExp;

class IfExp;

using Exp = std::variant<
    IntExp,
    BoolExp,
    std::shared_ptr<const OpExp>,
    std::shared_ptr<const IfExp>
>;

std::string exp_to_string(const Exp & exp);

class OpExp {
public:
    OpExp(std::shared_ptr<const Exp> exp_left, Prim op, std::shared_ptr<const Exp> exp_right)
        : exp_left(exp_left), op(op), exp_right(exp_right) {
    }

    const std::shared_ptr<const Exp> exp_left;

    const Prim op;

    const std::shared_ptr<const Exp> exp_right;

    std::string to_string() const;
};

class IfExp {
public:
    IfExp(std::shared_ptr<const Exp> exp_cond,
          std::shared_ptr<const Exp> exp_true,
          std::shared_ptr<const Exp> exp_false)
        : exp_cond(exp_cond), exp_true(exp_true), exp_false(exp_false) {
    }

    const std::shared_ptr<const Exp> exp_cond;

    const std::shared_ptr<const Exp> exp_true;

    const std::shared_ptr<const Exp> exp_false;

    std::string to_string() const;
};
}

#endif // ML_AST_H
