#include "gtest/gtest.h"
#include "../include/tuple.h"

TEST(TrivTuple, TupleGeneralUse)
{
    triv::tuple<int, double> tuple00{ 100, 100.5 };
    EXPECT_EQ(triv::get<0>(tuple00), 100);
    EXPECT_EQ(triv::get<0>(tuple00) + 100, 100 + 100);
    EXPECT_EQ(triv::get<0>(tuple00) / 2, 100 / 2);
    EXPECT_EQ(triv::get<0>(tuple00) * 2.5f, 100 * 2.5f);

    EXPECT_EQ(triv::get<1>(tuple00), 100.5f);
    EXPECT_EQ(triv::get<1>(tuple00) + 0.5f, 100.5f + 0.5f);
    EXPECT_EQ(triv::get<1>(tuple00) * 3, 100.5f * 3);
    EXPECT_EQ(triv::get<1>(tuple00) / 2, 100.5f / 2);
}

TEST(TrivTuple, TupleDefaultConstruct)
{
    constexpr int DEFAULT_CONSTRUCT_VALUE = 0x7777 * -1;

    struct __TupleDefaultConstruct {
        __TupleDefaultConstruct() : value(DEFAULT_CONSTRUCT_VALUE) { }
        __TupleDefaultConstruct(int __v) : value(__v) { }

        int get(void) const { return value; }
        bool operator==(int rhs) const { return value == rhs; }
    // MEMBER
        int value;
    };
    ASSERT_EQ(__TupleDefaultConstruct(), DEFAULT_CONSTRUCT_VALUE);

    // Fully non-initialized
    triv::tuple<int, __TupleDefaultConstruct> Full;
    EXPECT_EQ(triv::get<0>(Full), int());
    EXPECT_EQ(triv::get<1>(Full), DEFAULT_CONSTRUCT_VALUE);
    EXPECT_EQ(triv::get<1>(Full).get(), __TupleDefaultConstruct().get());

    // Partially non-initialized
    triv::tuple<int, std::string, __TupleDefaultConstruct, float> Partial{ 200.9, "Hello!"/*, third, fourth*/ };
    EXPECT_EQ(triv::get<0>(Partial), (int)200.9);
    EXPECT_EQ(triv::get<1>(Partial), "Hello!");
    EXPECT_EQ(triv::get<2>(Partial), DEFAULT_CONSTRUCT_VALUE);
    EXPECT_EQ(triv::get<3>(Partial), float());

    // Fully initialized
    triv::tuple<int, __TupleDefaultConstruct> None{ 1111, 2222 };
    EXPECT_EQ(triv::get<0>(None), 1111);
    EXPECT_EQ(triv::get<1>(None), 2222);
}
