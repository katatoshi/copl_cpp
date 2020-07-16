#include <iostream>
#include <variant>

#include "ml_driver.h"

using namespace copl::ml;

struct ResultVisitor {
    ResultVisitor() {
    }

    void operator()(Error) {
        std::cout << "Error" << std::endl;
    }

    void operator()(Value value) {
        std::cout << "- = " << value_to_string(value) << std::endl;
    }
};

int main() {
    ResultVisitor result_visitor;

    MLDriver driver;
    std::cout << "# ";
    while (driver.parse(std::cin)) {
        if (driver.eof_found) {
            std::cout << std::endl;
            break;
        }

        auto optional_result = driver.evaluate();
        if (optional_result) {
            std::visit(result_visitor, **optional_result);
        }

        std::cout << "# ";
    }
}
