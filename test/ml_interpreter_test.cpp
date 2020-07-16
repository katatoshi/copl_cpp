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
    auto exp = create_int_exp(-1);

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(value));

    auto actual = std::get<IntValue>(value);
    EXPECT_EQ(-1, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateBoolExp) {
    auto exp = create_bool_exp(false);

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<BoolValue>(value));

    auto actual = std::get<BoolValue>(value);
    EXPECT_EQ(false, actual);
}

TEST_F(MLInterpreterTest, TestEvaluatePlusOpExp) {
    auto exp = create_plus_op_exp(
        create_int_exp(3),
        create_int_exp(-5)
    );

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(value));

    auto actual = std::get<IntValue>(value);
    EXPECT_EQ(-2, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateMinusOpExp) {
    auto exp = create_minus_op_exp(
        create_int_exp(2),
        create_int_exp(-11)
    );

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(value));

    auto actual = std::get<IntValue>(value);
    EXPECT_EQ(13, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateTimesOpExp) {
    auto exp = create_times_op_exp(
        create_int_exp(3),
        create_int_exp(9)
    );

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(value));

    auto actual = std::get<IntValue>(value);
    EXPECT_EQ(27, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateLtOpExpTrue) {
    auto exp = create_lt_op_exp(
        create_int_exp(1),
        create_int_exp(4)
    );

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<BoolValue>(value));

    auto actual = std::get<BoolValue>(value);
    EXPECT_EQ(true, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateLtOpExpFalse) {
    auto exp = create_lt_op_exp(
        create_int_exp(-7),
        create_int_exp(-11)
    );

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<BoolValue>(value));

    auto actual = std::get<BoolValue>(value);
    EXPECT_EQ(false, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateIfExpTrue) {
    auto exp = create_if_exp(
        create_bool_exp(true),
        create_int_exp(9),
        create_int_exp(3)
    );

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(value));

    auto actual = std::get<IntValue>(value);
    EXPECT_EQ(9, actual);
}

TEST_F(MLInterpreterTest, TestEvaluateIfExpFalse) {
    auto exp = create_if_exp(
        create_bool_exp(false),
        create_int_exp(5),
        create_int_exp(13)
    );

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(value));

    auto actual = std::get<IntValue>(value);
    EXPECT_EQ(13, actual);
}

TEST_F(MLInterpreterTest, Test_Evaluate_LP_3_PLUS_MINUS_6_RP_TIMES_5_IS_MINUS_15) {
    auto exp = create_times_op_exp(
        create_plus_op_exp(
            create_int_exp(3),
            create_int_exp(-6)
        ),
        create_int_exp(5)
    );

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(value));

    auto actual = std::get<IntValue>(value);
    EXPECT_EQ(-15, actual);
}

TEST_F(MLInterpreterTest, Test_Evaluate_13_LT_LP_17_MINUS_4_RP_IS_FALSE) {
    auto exp = create_lt_op_exp(
        create_int_exp(13),
        create_minus_op_exp(
            create_int_exp(17),
            create_int_exp(4)
        )
    );

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<BoolValue>(value));

    auto actual = std::get<BoolValue>(value);
    EXPECT_EQ(false, actual);
}

TEST_F(MLInterpreterTest, Test_Evaluate_IF_3_LT_7_THEN_MINUS_7_TIMES_MINUS_4_ELSE_2_IS_28) {
    auto exp = create_if_exp(
        create_lt_op_exp(
            create_int_exp(3),
            create_int_exp(7)
        ),
        create_times_op_exp(
            create_int_exp(-7),
            create_int_exp(-4)
        ),
        create_int_exp(2)
    );

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(value));

    auto actual = std::get<IntValue>(value);
    EXPECT_EQ(28, actual);
}

TEST_F(MLInterpreterTest, Test_Evaluate_LP_IF_FALSE_THEN_TRUE_ELSE_11_RP_PLUS_MINUS_8_IS_3) {
    auto exp = create_plus_op_exp(
        create_if_exp(
            create_bool_exp(false),
            create_bool_exp(true),
            create_int_exp(11)
        ),
        create_int_exp(-8)
    );

    auto result = interpreter.evaluate(exp);
    EXPECT_EQ(true, std::holds_alternative<Value>(*result));

    auto value = std::get<Value>(*result);
    EXPECT_EQ(true, std::holds_alternative<IntValue>(value));

    auto actual = std::get<IntValue>(value);
    EXPECT_EQ(3, actual);
}
