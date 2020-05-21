#include <gtest/gtest.h>

#include "ml_interpreter.h"

using namespace copl::ml;

namespace {

class MLInterpreterTest : public ::testing::Test {
protected:
    MLInterpreter interpreter;

    virtual void SetUp() {
        // set up
    }

    virtual void TearDown() {
        // tear down
    }
};
}

TEST_F(MLInterpreterTest, TestEvaluateIntExp) {
    IntExp int_exp = -1;
    auto exp = std::make_shared<const Exp>(int_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(*value));

    auto actual = std::get<IntValue>(*value);
    EXPECT_EQ(-1, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateBoolExp) {
    BoolExp bool_exp = false;
    auto exp = std::make_shared<const Exp>(bool_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<BoolValue>(*value));

    auto actual = std::get<BoolValue>(*value);
    EXPECT_EQ(false, actual);
}

TEST_F(MLInterpreterTest, TestEvaluatePlusOpExp) {
    IntExp int_exp_left = 3;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = -5;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Plus(), exp_right);
    auto exp = std::make_shared<const Exp>(op_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(*value));

    auto actual = std::get<IntValue>(*value);
    EXPECT_EQ(-2, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateMinusOpExp) {
    IntExp int_exp_left = 2;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = -11;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Minus(), exp_right);
    auto exp = std::make_shared<const Exp>(op_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(*value));

    auto actual = std::get<IntValue>(*value);
    EXPECT_EQ(13, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateTimesOpExp) {
    IntExp int_exp_left = 3;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = 9;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Times(), exp_right);
    auto exp = std::make_shared<const Exp>(op_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(*value));

    auto actual = std::get<IntValue>(*value);
    EXPECT_EQ(27, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateLtOpExpTrue) {
    IntExp int_exp_left = 1;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = 4;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Lt(), exp_right);
    auto exp = std::make_shared<const Exp>(op_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<BoolValue>(*value));

    auto actual = std::get<BoolValue>(*value);
    EXPECT_EQ(true, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateLtOpExpFalse) {
    IntExp int_exp_left = -7;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = -11;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Lt(), exp_right);
    auto exp = std::make_shared<const Exp>(op_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<BoolValue>(*value));

    auto actual = std::get<BoolValue>(*value);
    EXPECT_EQ(false, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateIfExpTrue) {
    BoolExp bool_exp_cond = true;
    auto exp_cond = std::make_shared<const Exp>(bool_exp_cond);

    IntExp int_exp_true = 9;
    auto exp_true = std::make_shared<const Exp>(int_exp_true);

    IntExp int_exp_false = 3;
    auto exp_false = std::make_shared<const Exp>(int_exp_false);

    auto if_exp = std::make_shared<const IfExp>(exp_cond, exp_true, exp_false);
    auto exp = std::make_shared<const Exp>(if_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(*value));

    auto actual = std::get<IntValue>(*value);
    EXPECT_EQ(9, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateIfExpFalse) {
    BoolExp bool_exp_cond = false;
    auto exp_cond = std::make_shared<const Exp>(bool_exp_cond);

    IntExp int_exp_true = 5;
    auto exp_true = std::make_shared<const Exp>(int_exp_true);

    IntExp int_exp_false = 13;
    auto exp_false = std::make_shared<const Exp>(int_exp_false);

    auto if_exp = std::make_shared<const IfExp>(exp_cond, exp_true, exp_false);
    auto exp = std::make_shared<const Exp>(if_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(*value));

    auto actual = std::get<IntValue>(*value);
    EXPECT_EQ(13, actual);
}

TEST_F(MLInterpreterTest, Test_Evaluate_LP_3_PLUS_MINUS_6_RP_TIMES_5_IS_MINUS_15) {
    IntExp int_exp_left_left = 3;
    auto exp_left_left = std::make_shared<const Exp>(int_exp_left_left);

    IntExp int_exp_left_right = -6;
    auto exp_left_right = std::make_shared<const Exp>(int_exp_left_right);

    auto op_exp_left = std::make_shared<const OpExp>(exp_left_left, Plus(), exp_left_right);
    auto exp_left = std::make_shared<const Exp>(op_exp_left);

    IntExp int_exp_right = 5;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Times(), exp_right);
    auto exp = std::make_shared<const Exp>(op_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(*value));

    auto actual = std::get<IntValue>(*value);
    EXPECT_EQ(-15, actual);
}

TEST_F(MLInterpreterTest, Test_Evaluate_13_LT_LP_17_MINUS_4_RP_IS_FALSE) {
    IntExp int_exp_left = 13;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right_left = 17;
    auto exp_right_left = std::make_shared<const Exp>(int_exp_right_left);

    IntExp int_exp_right_right = 4;
    auto exp_right_right = std::make_shared<const Exp>(int_exp_right_right);

    auto op_exp_right = std::make_shared<const OpExp>(exp_right_left, Minus(), exp_right_right);
    auto exp_right = std::make_shared<const Exp>(op_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Lt(), exp_right);
    auto exp = std::make_shared<const Exp>(op_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<BoolValue>(*value));

    auto actual = std::get<BoolValue>(*value);
    EXPECT_EQ(false, actual);
}

TEST_F(MLInterpreterTest, Test_Evaluate_IF_3_LT_7_THEN_MINUS_7_TIMES_MINUS_4_ELSE_2_IS_28) {
    IntExp int_exp_cond_left = 3;
    auto exp_cond_left = std::make_shared<const Exp>(int_exp_cond_left);

    IntExp int_exp_cond_right = 7;
    auto exp_cond_right = std::make_shared<const Exp>(int_exp_cond_right);

    auto op_exp_cond = std::make_shared<const OpExp>(exp_cond_left, Lt(), exp_cond_right);
    auto exp_cond = std::make_shared<const Exp>(op_exp_cond);

    IntExp int_exp_true_left = -7;
    auto exp_true_left = std::make_shared<const Exp>(int_exp_true_left);

    IntExp int_exp_true_right = -4;
    auto exp_true_right = std::make_shared<const Exp>(int_exp_true_right);

    auto op_exp_true = std::make_shared<const OpExp>(exp_true_left, Times(), exp_true_right);
    auto exp_true = std::make_shared<const Exp>(op_exp_true);

    IntExp int_exp_false = 2;
    auto exp_false = std::make_shared<const Exp>(int_exp_false);

    auto if_exp = std::make_shared<const IfExp>(exp_cond, exp_true, exp_false);
    auto exp = std::make_shared<const Exp>(if_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(*value));

    auto actual = std::get<IntValue>(*value);
    EXPECT_EQ(28, actual);
}

TEST_F(MLInterpreterTest, Test_Evaluate_LP_IF_FALSE_THEN_TRUE_ELSE_11_RP_PLUS_MINUS_8_IS_3) {
    BoolExp bool_exp_left_cond = false;
    auto exp_left_cond = std::make_shared<const Exp>(bool_exp_left_cond);

    BoolExp bool_exp_left_true = true;
    auto exp_left_true = std::make_shared<const Exp>(bool_exp_left_true);

    IntExp int_exp_left_false = 11;
    auto exp_left_false = std::make_shared<const Exp>(int_exp_left_false);

    auto if_exp_left = std::make_shared<const IfExp>(
        exp_left_cond,
        exp_left_true,
        exp_left_false
    );
    auto exp_left = std::make_shared<const Exp>(if_exp_left);

    IntExp int_exp_right = -8;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Plus(), exp_right);
    auto exp = std::make_shared<const Exp>(op_exp);

    auto value = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(*value));

    auto actual = std::get<IntValue>(*value);
    EXPECT_EQ(3, actual);
}
