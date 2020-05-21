#include "ml_ast.h"

namespace copl::ml {

std::string value_to_string(const Value & value) {
    struct visitor {

        std::string operator()(IntValue int_value) {
            return std::to_string(int_value);
        }

        std::string operator()(BoolValue bool_value) {
            return bool_value ? "true" : "false";
        }
    };

    return std::visit(visitor(), value);
}

std::string prim_to_string(const Prim & prim) {
    struct visitor {

        std::string operator()(const Plus &) {
            return "+";
        }

        std::string operator()(const Minus &) {
            return "-";
        }

        std::string operator()(const Times &) {
            return "*";
        }

        std::string operator()(const Lt &) {
            return "<";
        }
    };

    return std::visit(visitor(), prim);
}

std::string OpExp::to_string() const {
    return "("
        + exp_to_string(*exp_left)
        + " "
        + prim_to_string(op)
        + " "
        + exp_to_string(*exp_right)
        + ")";
}

std::string IfExp::to_string() const {
    return "(if "
        + exp_to_string(*exp_cond)
        + " then "
        + exp_to_string(*exp_true)
        + " else "
        + exp_to_string(*exp_false)
        + ")";
}

std::string exp_to_string(const Exp & exp) {
    struct visitor {

        std::string operator()(IntExp int_exp) {
            return std::to_string(int_exp);
        }

        std::string operator()(BoolExp bool_exp) {
            return bool_exp ? "true" : "false";
        }

        std::string operator()(const std::shared_ptr<const OpExp> & op_exp) {
            return op_exp->to_string();
        }

        std::string operator()(const std::shared_ptr<const IfExp> & if_exp) {
            return if_exp->to_string();
        }
    };

    return std::visit(visitor(), exp);
}
}
