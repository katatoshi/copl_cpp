#include <gtest/gtest.h>

#include <sstream>

#include "ml_driver.h"

using namespace copl::ml;

namespace {

class MLDriverTest : public ::testing::Test {
protected:
    MLDriver driver;

    virtual void SetUp() {
        // set up
    }

    virtual void TearDown() {
        // tear down
    }
};
}

TEST_F(MLDriverTest, TestParseIntExp) {
    IntExp int_exp = -1;
    auto expected_exp = std::make_shared<const Exp>(int_exp);

    std::istringstream is("-1 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseBoolExp) {
    BoolExp bool_exp = false;
    auto expected_exp = std::make_shared<const Exp>(bool_exp);

    std::istringstream is("false ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParsePlusOpExp) {
    IntExp int_exp_left = 3;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = -5;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Plus(), exp_right);
    auto expected_exp = std::make_shared<const Exp>(op_exp);

    std::istringstream is("3 + -5 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseMinusOpExp) {
    IntExp int_exp_left = 2;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = -11;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Minus(), exp_right);
    auto expected_exp = std::make_shared<const Exp>(op_exp);

    std::istringstream is("2 - -11 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseTimesOpExp) {
    IntExp int_exp_left = 3;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = 9;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Times(), exp_right);
    auto expected_exp = std::make_shared<const Exp>(op_exp);

    std::istringstream is("3 * 9 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseLtOpExpTrue) {
    IntExp int_exp_left = 1;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = 4;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Lt(), exp_right);
    auto expected_exp = std::make_shared<const Exp>(op_exp);

    std::istringstream is("1 < 4 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseLtOpExpFalse) {
    IntExp int_exp_left = -7;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right = -11;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Lt(), exp_right);
    auto expected_exp = std::make_shared<const Exp>(op_exp);

    std::istringstream is("-7 < -11 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseIfExpTrue) {
    BoolExp bool_exp_cond = true;
    auto exp_cond = std::make_shared<const Exp>(bool_exp_cond);

    IntExp int_exp_true = 9;
    auto exp_true = std::make_shared<const Exp>(int_exp_true);

    IntExp int_exp_false = 3;
    auto exp_false = std::make_shared<const Exp>(int_exp_false);

    auto if_exp = std::make_shared<const IfExp>(exp_cond, exp_true, exp_false);
    auto expected_exp = std::make_shared<const Exp>(if_exp);

    std::istringstream is("if true then 9 else 3 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseIfExpFalse) {
    BoolExp bool_exp_cond = false;
    auto exp_cond = std::make_shared<const Exp>(bool_exp_cond);

    IntExp int_exp_true = 5;
    auto exp_true = std::make_shared<const Exp>(int_exp_true);

    IntExp int_exp_false = 13;
    auto exp_false = std::make_shared<const Exp>(int_exp_false);

    auto if_exp = std::make_shared<const IfExp>(exp_cond, exp_true, exp_false);
    auto expected_exp = std::make_shared<const Exp>(if_exp);

    std::istringstream is("if false then 5 else 13 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseStrangeFormatExp) {
    IntExp int_exp_cond_left = -11;
    auto exp_cond_left = std::make_shared<const Exp>(int_exp_cond_left);

    IntExp int_exp_cond_right = 0;
    auto exp_cond_right = std::make_shared<const Exp>(int_exp_cond_right);

    auto op_exp_cond = std::make_shared<const OpExp>(exp_cond_left, Lt(), exp_cond_right);
    auto exp_cond = std::make_shared<const Exp>(op_exp_cond);

    IntExp int_exp_true_left = -3;
    auto exp_true_left = std::make_shared<const Exp>(int_exp_true_left);

    IntExp int_exp_true_right = 7;
    auto exp_true_right = std::make_shared<const Exp>(int_exp_true_right);

    auto op_exp_true = std::make_shared<const OpExp>(exp_true_left, Times(), exp_true_right);
    auto exp_true = std::make_shared<const Exp>(op_exp_true);

    IntExp int_exp_false = -3;
    auto exp_false = std::make_shared<const Exp>(int_exp_false);

    auto if_exp = std::make_shared<const IfExp>(exp_cond, exp_true, exp_false);
    auto expected_exp = std::make_shared<const Exp>(if_exp);

    std::istringstream is(
R"((
if((-11)<0)
  then  (  -3  *  7  )
    else((-3 ) )
);;
)"
    );
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, Test_Parse_LP_3_PLUS_MINUS_6_RP_TIMES_5_IS_MINUS_15) {
    IntExp int_exp_left_left = 3;
    auto exp_left_left = std::make_shared<const Exp>(int_exp_left_left);

    IntExp int_exp_left_right = -6;
    auto exp_left_right = std::make_shared<const Exp>(int_exp_left_right);

    auto op_exp_left = std::make_shared<const OpExp>(exp_left_left, Plus(), exp_left_right);
    auto exp_left = std::make_shared<const Exp>(op_exp_left);

    IntExp int_exp_right = 5;
    auto exp_right = std::make_shared<const Exp>(int_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Times(), exp_right);
    auto expected_exp = std::make_shared<const Exp>(op_exp);

    std::istringstream is("(3 + -6) * 5 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, Test_Parse_13_LT_LP_17_MINUS_4_RP_IS_FALSE) {
    IntExp int_exp_left = 13;
    auto exp_left = std::make_shared<const Exp>(int_exp_left);

    IntExp int_exp_right_left = 17;
    auto exp_right_left = std::make_shared<const Exp>(int_exp_right_left);

    IntExp int_exp_right_right = 4;
    auto exp_right_right = std::make_shared<const Exp>(int_exp_right_right);

    auto op_exp_right = std::make_shared<const OpExp>(exp_right_left, Minus(), exp_right_right);
    auto exp_right = std::make_shared<const Exp>(op_exp_right);

    auto op_exp = std::make_shared<const OpExp>(exp_left, Lt(), exp_right);
    auto expected_exp = std::make_shared<const Exp>(op_exp);

    std::istringstream is("13 < (17 - 4) ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, Test_Parse_IF_3_LT_7_THEN_MINUS_7_TIMES_MINUS_4_ELSE_2_IS_28) {
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
    auto expected_exp = std::make_shared<const Exp>(if_exp);

    std::istringstream is("if 3 < 7 then -7 * -4 else 2 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, Test_Parse_LP_IF_FALSE_THEN_TRUE_ELSE_11_RP_PLUS_MINUS_8_IS_3) {
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
    auto expected_exp = std::make_shared<const Exp>(op_exp);

    std::istringstream is("(if false then true else 11) + -8 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}
