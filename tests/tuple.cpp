#include "gtest/gtest.h"
#include "../include/tuple.h"

TEST(triv_tuple, tuple)
{
    triv::tuple<int, double> tuple00{ 100, 100.5 };
    EXPECT_EQ(triv::get<0>(tuple00), 100);
    EXPECT_EQ(triv::get<1>(tuple00), 100.5f);
}