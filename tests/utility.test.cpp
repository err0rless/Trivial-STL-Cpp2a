#include "gtest/gtest.h"
#include "../include/utility.h"

#include <type_traits>

TEST(triv, utility) {}

TEST(triv, __utility_And) {
    constexpr bool AndTrueExpected00 = triv::And<true, true, true>;
    constexpr bool AndTrueExpected01 = triv::And<true, true, true>;
    EXPECT_TRUE(AndTrueExpected00);
    EXPECT_TRUE(AndTrueExpected01);

    constexpr bool AndFalseExpected00 = triv::And<true, false, true>;
    constexpr bool AndFalseExpected01 = triv::And<false, false, true>;
    constexpr bool AndFalseExpected02 = triv::And<true, 1, 0>;
    EXPECT_FALSE(AndFalseExpected00);
    EXPECT_FALSE(AndFalseExpected01);
    EXPECT_FALSE(AndFalseExpected02);
}

TEST(triv, __utility_Or) {
    constexpr bool OrTrueExpected00 = triv::Or<false, false, false, true>;
    constexpr bool OrTrueExpected01 = triv::Or<true, false, true, false, true>;
    EXPECT_TRUE(OrTrueExpected00);
    EXPECT_TRUE(OrTrueExpected01);

    constexpr bool OrFalseExpected00 = triv::Or<false, false, false>;
    constexpr bool OrFalseExpected01 = triv::Or<false>;
    constexpr bool OrFalseExpected02 = triv::Or<0, false, 0, 0>;
    EXPECT_FALSE(OrFalseExpected00);
    EXPECT_FALSE(OrFalseExpected01);
    EXPECT_FALSE(OrFalseExpected02);
}

TEST(triv, __utility_indexing) {
    using FirstOfType00 = triv::first_of_t<int, char, short>;
    using FirstOfType01 = triv::first_of_t<double, char, short>;
    constexpr bool FirstOfTrueExpected00 = std::is_same_v<FirstOfType00, int>;
    constexpr bool FirstOfTrueExpected01 = std::is_same_v<FirstOfType01, double>;
    EXPECT_TRUE(FirstOfTrueExpected00);
    EXPECT_TRUE(FirstOfTrueExpected01);

    using IndexOfType00 = triv::index_of_t<0, volatile int, char, short>;
    using IndexOfType01 = triv::index_of_t<2, int, char, const short>;
    constexpr bool IndexOfTrueExpected00 = std::is_same_v<IndexOfType00, volatile int>;
    constexpr bool IndexOfTrueExpected01 = std::is_same_v<IndexOfType01, const short>;
    EXPECT_TRUE(IndexOfTrueExpected00);
    EXPECT_TRUE(IndexOfTrueExpected01);
}