#include <gtest/gtest.h>

#include "ml_ast.h"

using namespace copl::ml;

namespace {

class MLASTTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        // set up
    }

    virtual void TearDown() {
        // tear down
    }
};
}

TEST_F(MLASTTest, TestIntValueToString) {
    IntValue int_value = 2;
    auto value = std::make_shared<const Value>(int_value);

    auto actual = value_to_string(*value);
    EXPECT_EQ("2", actual);
}

TEST_F(MLASTTest, TestBoolValueToString) {
    BoolValue bool_value = true;
    auto value = std::make_shared<const Value>(bool_value);

    auto actual = value_to_string(*value);
    EXPECT_EQ("true", actual);
}

TEST_F(MLASTTest, TestIntExpToString) {
    IntExp int_exp = -1;
    auto exp = std::make_shared<const Exp>(int_exp);

    auto actual = exp_to_string(*exp);
    EXPECT_EQ("-1", actual);
}

TEST_F(MLASTTest, TestBoolExpToString) {
    BoolExp bool_exp = false;
    auto exp = std::make_shared<const Exp>(bool_exp);

    auto actual = exp_to_string(*exp);
    EXPECT_EQ("false", actual);
}

TEST_F(MLASTTest, TestPlusOpExpToString) {
    IntExp int_exp_left = 8;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = 0;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Plus(), exp_right);
    auto exp = std::make_shared<const Exp>(op_exp);

    auto actual = exp_to_string(*exp);
    EXPECT_EQ("(8 + 0)", actual);
}

TEST_F(MLASTTest, TestMinusOpExpToString) {
    IntExp int_exp_left = 5;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = -3;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Minus(), exp_right);
    auto exp = std::make_shared<const Exp>(op_exp);

    auto actual = exp_to_string(*exp);
    EXPECT_EQ("(5 - -3)", actual);
}

TEST_F(MLASTTest, TestTimesOpExpToString) {
    IntExp int_exp_left = -7;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = 4;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Times(), exp_right);
    auto exp = std::make_shared<const Exp>(op_exp);

    auto actual = exp_to_string(*exp);
    EXPECT_EQ("(-7 * 4)", actual);
}

TEST_F(MLASTTest, TestLtOpExpToString) {
    IntExp int_exp_left = -6;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = -9;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Lt(), exp_right);
    auto exp = std::make_shared<const Exp>(op_exp);

    auto actual = exp_to_string(*exp);
    EXPECT_EQ("(-6 < -9)", actual);
}

TEST_F(MLASTTest, TestIfExpToString) {
    BoolExp bool_exp_cond = true;
    auto exp_cond = std::make_shared<const Exp>(bool_exp_cond);

    IntExp int_exp_true = -11;
    auto exp_true = std::make_shared<const Exp>(int_exp_true);

    IntExp int_exp_false = 13;
    auto exp_false = std::make_shared<const Exp>(int_exp_false);

    auto if_exp = std::make_shared<const IfExp>(exp_cond, exp_true, exp_false);
    auto exp = std::make_shared<const Exp>(if_exp);

    auto actual = exp_to_string(*exp);
    EXPECT_EQ("(if true then -11 else 13)", actual);
}
