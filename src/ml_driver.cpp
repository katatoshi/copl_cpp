#include "ml_driver.h"

using namespace copl::ml;

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
