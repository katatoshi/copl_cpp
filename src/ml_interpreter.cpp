#include "ml_interpreter.h"

namespace copl::ml {

std::shared_ptr<const Value> MLInterpreter::evaluate(const std::shared_ptr<const Exp> & exp) {
    if (!exp) {
        return std::shared_ptr<const Value>();
    }

    struct visitor {

        visitor(MLInterpreter * interpreter)
            : interpreter(interpreter) {
        }

        MLInterpreter * interpreter;

        std::shared_ptr<const Value> operator()(IntExp int_exp) {
            IntValue int_value = int_exp;
            return std::make_shared<const Value>(int_value);
        }

        std::shared_ptr<const Value> operator()(BoolExp bool_exp) {
            BoolValue bool_value = bool_exp;
            return std::make_shared<const Value>(bool_value);
        }

        std::shared_ptr<const Value> operator()(const std::shared_ptr<const OpExp> & op_exp) {
            auto value_left = interpreter->evaluate(op_exp->exp_left);
            if (!value_left) {
                return std::shared_ptr<const Value>();
            }

            if (!std::holds_alternative<IntValue>(*value_left)) {
                return std::shared_ptr<const Value>();
            }

            auto value_right = interpreter->evaluate(op_exp->exp_right);
            if (!value_right) {
                return std::shared_ptr<const Value>();
            }

            if (!std::holds_alternative<IntValue>(*value_right)) {
                return std::shared_ptr<const Value>();
            }

            struct visitor {

                visitor(IntValue int_value_left, IntValue int_value_right)
                    : int_value_left(int_value_left), int_value_right(int_value_right) {
                }

                const IntValue int_value_left;

                const IntValue int_value_right;

                std::shared_ptr<const Value> operator()(const Plus &) {
                    return std::make_shared<const Value>(int_value_left + int_value_right);
                }

                std::shared_ptr<const Value> operator()(const Minus&) {
                    return std::make_shared<const Value>(int_value_left - int_value_right);
                }

                std::shared_ptr<const Value> operator()(const Times &) {
                    return std::make_shared<const Value>(int_value_left * int_value_right);
                }

                std::shared_ptr<const Value> operator()(const Lt &) {
                    return std::make_shared<const Value>(int_value_left < int_value_right);
                }
            };

            auto int_value_left = std::get<IntValue>(*value_left);
            auto int_value_right = std::get<IntValue>(*value_right);
            return std::visit(visitor(int_value_left, int_value_right), op_exp->op);
        }

        std::shared_ptr<const Value> operator()(const std::shared_ptr<const IfExp> & if_exp) {
            auto value_cond = interpreter->evaluate(if_exp->exp_cond);
            if (!value_cond) {
                return std::shared_ptr<const Value>();
            }

            if (!std::holds_alternative<BoolValue>(*value_cond)) {
                return std::shared_ptr<const Value>();
            }

            auto bool_value_cond = std::get<BoolValue>(*value_cond);
            if (bool_value_cond) {
                auto value_true = interpreter->evaluate(if_exp->exp_true);
                if (!value_true) {
                    return std::shared_ptr<const Value>();
                }

                return value_true;
            } else {
                auto value_false = interpreter->evaluate(if_exp->exp_false);
                if (!value_false) {
                    return std::shared_ptr<const Value>();
                }

                return value_false;
            }
        }
    };

    return std::visit(visitor(this), *exp);
}
}
