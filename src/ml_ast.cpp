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

std::shared_ptr<const Exp> create_int_exp(IntExp int_exp) {
    return std::make_shared<const Exp>(int_exp);
}

std::shared_ptr<const Exp> create_bool_exp(BoolExp bool_exp) {
    return std::make_shared<const Exp>(bool_exp);
}

std::shared_ptr<const Exp> create_plus_op_exp(
    const std::shared_ptr<const Exp> & exp_left,
    const std::shared_ptr<const Exp> & exp_right
) {
    auto op_exp = std::make_shared<const OpExp>(exp_left, Plus(), exp_right);
    return std::make_shared<const Exp>(op_exp);
}

std::shared_ptr<const Exp> create_minus_op_exp(
    const std::shared_ptr<const Exp> & exp_left,
    const std::shared_ptr<const Exp> & exp_right
) {
    auto op_exp = std::make_shared<const OpExp>(exp_left, Minus(), exp_right);
    return std::make_shared<const Exp>(op_exp);
}

std::shared_ptr<const Exp> create_times_op_exp(
    const std::shared_ptr<const Exp> & exp_left,
    const std::shared_ptr<const Exp> & exp_right
) {
    auto op_exp = std::make_shared<const OpExp>(exp_left, Times(), exp_right);
    return std::make_shared<const Exp>(op_exp);
}

std::shared_ptr<const Exp> create_lt_op_exp(
    const std::shared_ptr<const Exp> & exp_left,
    const std::shared_ptr<const Exp> & exp_right
) {
    auto op_exp = std::make_shared<const OpExp>(exp_left, Lt(), exp_right);
    return std::make_shared<const Exp>(op_exp);
}

std::shared_ptr<const Exp> create_if_exp(
    const std::shared_ptr<const Exp> & exp_cond,
    const std::shared_ptr<const Exp> & exp_true,
    const std::shared_ptr<const Exp> & exp_false
) {
    auto if_exp = std::make_shared<const IfExp>(exp_cond, exp_true, exp_false);
    return std::make_shared<const Exp>(if_exp);
}
}
