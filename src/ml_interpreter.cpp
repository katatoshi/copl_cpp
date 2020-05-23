#include "ml_interpreter.h"

namespace copl::ml {

std::shared_ptr<const Result> MLInterpreter::evaluate(const std::shared_ptr<const Exp> & exp) {
    struct visitor {

        visitor(MLInterpreter * interpreter)
            : interpreter(interpreter) {
        }

        MLInterpreter * interpreter;

        std::shared_ptr<const Result> operator()(IntExp int_exp) {
            IntValue int_value = int_exp;
            return std::make_shared<const Result>(int_value);
        }

        std::shared_ptr<const Result> operator()(BoolExp bool_exp) {
            BoolValue bool_value = bool_exp;
            return std::make_shared<const Result>(bool_value);
        }

        std::shared_ptr<const Result> operator()(const std::shared_ptr<const OpExp> & op_exp) {
            auto result_left = interpreter->evaluate(op_exp->exp_left);
            if (!std::holds_alternative<Value>(*result_left)) {
                return std::make_shared<const Result>(Error());
            }

            auto value_left = std::get<Value>(*result_left);
            if (!std::holds_alternative<IntValue>(value_left)) {
                return std::make_shared<const Result>(Error());
            }

            auto result_right = interpreter->evaluate(op_exp->exp_right);
            if (!std::holds_alternative<Value>(*result_right)) {
                return std::make_shared<const Result>(Error());
            }

            auto value_right = std::get<Value>(*result_right);
            if (!std::holds_alternative<IntValue>(value_right)) {
                return std::make_shared<const Result>(Error());
            }

            struct visitor {

                visitor(IntValue int_value_left, IntValue int_value_right)
                    : int_value_left(int_value_left), int_value_right(int_value_right) {
                }

                const IntValue int_value_left;

                const IntValue int_value_right;

                std::shared_ptr<const Result> operator()(const Plus &) {
                    Value value = int_value_left + int_value_right;
                    return std::make_shared<const Result>(value);
//                     return std::make_shared<const Result>(int_value_left + int_value_right);
                }

                std::shared_ptr<const Result> operator()(const Minus&) {
                    Value value = int_value_left - int_value_right;
                    return std::make_shared<const Result>(value);
//                     return std::make_shared<const Result>(int_value_left - int_value_right);
                }

                std::shared_ptr<const Result> operator()(const Times &) {
                    Value value = int_value_left * int_value_right;
                    return std::make_shared<const Result>(value);
//                     return std::make_shared<const Result>(int_value_left * int_value_right);
                }

                std::shared_ptr<const Result> operator()(const Lt &) {
                    Value value = int_value_left < int_value_right;
                    return std::make_shared<const Result>(value);
//                     return std::make_shared<const Result>(int_value_left < int_value_right);
                }
            };

            auto int_value_left = std::get<IntValue>(value_left);
            auto int_value_right = std::get<IntValue>(value_right);
            return std::visit(visitor(int_value_left, int_value_right), op_exp->op);
        }

        std::shared_ptr<const Result> operator()(const std::shared_ptr<const IfExp> & if_exp) {
            auto result_cond = interpreter->evaluate(if_exp->exp_cond);
            if (!std::holds_alternative<Value>(*result_cond)) {
                return std::make_shared<const Result>(Error());
            }

            auto value_cond = std::get<Value>(*result_cond);
            if (!std::holds_alternative<BoolValue>(value_cond)) {
                return std::make_shared<const Result>(Error());
            }

            auto bool_value_cond = std::get<BoolValue>(value_cond);
            if (bool_value_cond) {
                auto result_true = interpreter->evaluate(if_exp->exp_true);
                if (!std::holds_alternative<Value>(*result_true)) {
                    return std::make_shared<const Result>(Error());
                }

                return result_true;
            } else {
                auto result_false = interpreter->evaluate(if_exp->exp_false);
                if (!std::holds_alternative<Value>(*result_false)) {
                    return std::make_shared<const Result>(Error());
                }

                return result_false;
            }
        }
    };

    return std::visit(visitor(this), *exp);
}
}
