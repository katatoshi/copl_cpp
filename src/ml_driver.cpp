#include "ml_driver.h"

using namespace copl::ml;

std::shared_ptr<const Exp> copl::ml::create_int_exp(IntExp int_exp) {
    return std::make_shared<const Exp>(int_exp);
}

std::shared_ptr<const Exp> copl::ml::create_bool_exp(BoolExp bool_exp) {
    return std::make_shared<const Exp>(bool_exp);
}

std::shared_ptr<const Exp> copl::ml::create_plus_op_exp(
    const std::shared_ptr<const Exp> & exp_left,
    const std::shared_ptr<const Exp> & exp_right
) {
    auto op_exp = std::make_shared<const OpExp>(exp_left, Plus(), exp_right);
    return std::make_shared<const Exp>(op_exp);
}

std::shared_ptr<const Exp> copl::ml::create_minus_op_exp(
    const std::shared_ptr<const Exp> & exp_left,
    const std::shared_ptr<const Exp> & exp_right
) {
    auto op_exp = std::make_shared<const OpExp>(exp_left, Minus(), exp_right);
    return std::make_shared<const Exp>(op_exp);
}

std::shared_ptr<const Exp> copl::ml::create_times_op_exp(
    const std::shared_ptr<const Exp> & exp_left,
    const std::shared_ptr<const Exp> & exp_right
) {
    auto op_exp = std::make_shared<const OpExp>(exp_left, Times(), exp_right);
    return std::make_shared<const Exp>(op_exp);
}

std::shared_ptr<const Exp> copl::ml::create_lt_op_exp(
    const std::shared_ptr<const Exp> & exp_left,
    const std::shared_ptr<const Exp> & exp_right
) {
    auto op_exp = std::make_shared<const OpExp>(exp_left, Lt(), exp_right);
    return std::make_shared<const Exp>(op_exp);
}

std::shared_ptr<const Exp> copl::ml::create_if_exp(
    const std::shared_ptr<const Exp> & exp_cond,
    const std::shared_ptr<const Exp> & exp_true,
    const std::shared_ptr<const Exp> & exp_false
) {
    auto if_exp = std::make_shared<const IfExp>(exp_cond, exp_true, exp_false);
    return std::make_shared<const Exp>(if_exp);
}

void MLDriver::set_parsed_exp(const std::shared_ptr<const Exp> & exp) {
    parsed_exp = std::make_optional(exp);
}

void MLDriver::clear_parsed_exp() {
    parsed_exp = std::nullopt;
}

std::optional<std::shared_ptr<const Exp>> MLDriver::get_parsed_exp() const {
    return parsed_exp;
}

bool MLDriver::parse(std::istream & is) {
    MLScanner scanner(&is);
    MLParser parser(scanner, *this);

    clear_parsed_exp();

    auto result = parser.parse();

    return result == 0;
}

bool MLDriver::parse(const std::string & filename) {
    std::ifstream ifs(filename);

    return parse(ifs);
}

std::optional<std::shared_ptr<const Result>> MLDriver::evaluate() {
    if (!parsed_exp) {
        return std::nullopt;
    }

    auto result = interpreter.evaluate(*parsed_exp);

    return std::make_optional(result);
}
