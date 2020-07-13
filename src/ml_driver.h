#ifndef ML_DRIVER_H
#define ML_DRIVER_H

#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

#include "ml_parser.tab.hpp"

#include "ml_interpreter.h"
#include "ml_scanner.h"

namespace copl::ml {

std::shared_ptr<const Exp> create_int_exp(IntExp int_exp);

std::shared_ptr<const Exp> create_bool_exp(BoolExp bool_exp);

std::shared_ptr<const Exp> create_plus_op_exp(
    const std::shared_ptr<const Exp> & exp_left,
    const std::shared_ptr<const Exp> & exp_right
);

std::shared_ptr<const Exp> create_minus_op_exp(
    const std::shared_ptr<const Exp> & exp_left,
    const std::shared_ptr<const Exp> & exp_right
);

std::shared_ptr<const Exp> create_times_op_exp(
    const std::shared_ptr<const Exp> & exp_left,
    const std::shared_ptr<const Exp> & exp_right
);

std::shared_ptr<const Exp> create_lt_op_exp(
    const std::shared_ptr<const Exp> & exp_left,
    const std::shared_ptr<const Exp> & exp_right
);

std::shared_ptr<const Exp> create_if_exp(
    const std::shared_ptr<const Exp> & exp_cond,
    const std::shared_ptr<const Exp> & exp_true,
    const std::shared_ptr<const Exp> & exp_false
);

class MLDriver {
public:
    void set_parsed_exp(const std::shared_ptr<const Exp> & exp);

    void clear_parsed_exp();

    std::optional<std::shared_ptr<const Exp>> get_parsed_exp() const;

    bool parse(std::istream & is);

    bool parse(const std::string & filename);

    std::optional<std::shared_ptr<const Result>> evaluate();

    bool eof_found = false;

private:
    MLInterpreter interpreter;

    std::optional<std::shared_ptr<const Exp>> parsed_exp = std::nullopt;
};
}
#endif // ML_DRIVER_H
