#include "gtest/gtest.h"
#include "../include/utility.h"

TEST(TrivUtility, _And)
{
    constexpr bool AndTrueExpected00 = triv::_And<true, true, true>::value;
    constexpr bool AndTrueExpected01 = triv::_And_v<true, true, true>;
    EXPECT_EQ(AndTrueExpected00, true);
    EXPECT_EQ(AndTrueExpected01, true);

    constexpr bool AndFalseExpected00 = triv::_And<true, false, true>::value;
    constexpr bool AndFalseExpected01 = triv::_And_v<false, false, true>;
    constexpr bool AndFalseExpected02 = triv::_And_v<true, 1, 0>;
    EXPECT_EQ(AndFalseExpected00, false);
    EXPECT_EQ(AndFalseExpected01, false);
    EXPECT_EQ(AndFalseExpected02, false);
}

TEST(TrivUtility, _Or)
{
    constexpr bool OrTrueExpected00 = triv::_Or<false, false, false, true>::value;
    constexpr bool OrTrueExpected01 = triv::_Or_v<true, false, true, false, true>;
    EXPECT_EQ(OrTrueExpected00, true);
    EXPECT_EQ(OrTrueExpected01, true);

    constexpr bool OrFalseExpected00 = triv::_Or<false, false, false>::value;
    constexpr bool OrFalseExpected01 = triv::_Or_v<false>;
    constexpr bool OrFalseExpected02 = triv::_Or_v<0, false, 0, 0>;
    EXPECT_EQ(OrFalseExpected00, false);
    EXPECT_EQ(OrFalseExpected01, false);
    EXPECT_EQ(OrFalseExpected02, false);
}