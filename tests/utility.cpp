#include "gtest/gtest.h"
#include "../include/utility.h"

TEST(TrivUtility, _And)
{
    constexpr bool AndTrueExpected00 = triv::_And<true, true, true>::value;
    constexpr bool AndTrueExpected01 = triv::_And_v<true, true, true>;
    EXPECT_TRUE(AndTrueExpected00);
    EXPECT_TRUE(AndTrueExpected01);

    constexpr bool AndFalseExpected00 = triv::_And<true, false, true>::value;
    constexpr bool AndFalseExpected01 = triv::_And_v<false, false, true>;
    constexpr bool AndFalseExpected02 = triv::_And_v<true, 1, 0>;
    EXPECT_FALSE(AndFalseExpected00);
    EXPECT_FALSE(AndFalseExpected01);
    EXPECT_FALSE(AndFalseExpected02);
}

TEST(TrivUtility, _Or)
{
    constexpr bool OrTrueExpected00 = triv::_Or<false, false, false, true>::value;
    constexpr bool OrTrueExpected01 = triv::_Or_v<true, false, true, false, true>;
    EXPECT_TRUE(OrTrueExpected00);
    EXPECT_TRUE(OrTrueExpected01);

    constexpr bool OrFalseExpected00 = triv::_Or<false, false, false>::value;
    constexpr bool OrFalseExpected01 = triv::_Or_v<false>;
    constexpr bool OrFalseExpected02 = triv::_Or_v<0, false, 0, 0>;
    EXPECT_FALSE(OrFalseExpected00);
    EXPECT_FALSE(OrFalseExpected01);
    EXPECT_FALSE(OrFalseExpected02);
}