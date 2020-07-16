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
    auto expected_exp = create_plus_op_exp(
        create_int_exp(3),
        create_int_exp(-5)
    );

    std::istringstream is("3 + -5 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseMinusOpExp) {
    auto expected_exp = create_minus_op_exp(
        create_int_exp(2),
        create_int_exp(-11)
    );

    std::istringstream is("2 - -11 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseTimesOpExp) {
    auto expected_exp = create_times_op_exp(
        create_int_exp(3),
        create_int_exp(9)
    );

    std::istringstream is("3 * 9 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseLtOpExp) {
    auto expected_exp = create_lt_op_exp(
        create_int_exp(1),
        create_int_exp(4)
    );

    std::istringstream is("1 < 4 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseIfExp) {
    auto expected_exp = create_if_exp(
        create_bool_exp(false),
        create_int_exp(5),
        create_int_exp(13)
    );

    std::istringstream is("if false then 5 else 13 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, TestParseStrangeFormatExp) {
    auto expected_exp = create_if_exp(
        create_lt_op_exp(
            create_int_exp(-11),
            create_int_exp(0)
        ),
        create_times_op_exp(
            create_int_exp(-3),
            create_int_exp(7)
        ),
        create_int_exp(-3)
    );

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
    auto expected_exp = create_times_op_exp(
        create_plus_op_exp(
            create_int_exp(3),
            create_int_exp(-6)
        ),
        create_int_exp(5)
    );

    std::istringstream is("(3 + -6) * 5 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, Test_Parse_13_LT_LP_17_MINUS_4_RP_IS_FALSE) {
    auto expected_exp = create_lt_op_exp(
        create_int_exp(13),
        create_minus_op_exp(
            create_int_exp(17),
            create_int_exp(4)
        )
    );

    std::istringstream is("13 < (17 - 4) ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, Test_Parse_IF_3_LT_7_THEN_MINUS_7_TIMES_MINUS_4_ELSE_2_IS_28) {
    auto expected_exp = create_if_exp(
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

    std::istringstream is("if 3 < 7 then -7 * -4 else 2 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}

TEST_F(MLDriverTest, Test_Parse_LP_IF_FALSE_THEN_TRUE_ELSE_11_RP_PLUS_MINUS_8_IS_3) {
    auto expected_exp = create_plus_op_exp(
        create_if_exp(
            create_bool_exp(false),
            create_bool_exp(true),
            create_int_exp(11)
        ),
        create_int_exp(-8)
    );

    std::istringstream is("(if false then true else 11) + -8 ;;\n");
    EXPECT_EQ(true, driver.parse(is));

    auto optional_parsed_exp = driver.get_parsed_exp();
    EXPECT_EQ(true, optional_parsed_exp.has_value());

    auto actual_exp = *optional_parsed_exp;
    EXPECT_EQ(exp_to_string(*expected_exp), exp_to_string(*actual_exp));
}
