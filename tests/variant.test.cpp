#include "../include/variant.h"
#include "gtest/gtest.h"

#include <iostream>
#include <string>

using namespace triv;
using namespace triv::__detail;

TEST(triv, variant) {
    static_assert(__exact_match_idx<int, int, short, float&, short, const char> == 0, "");
    static_assert(__exact_match_idx<int*, short, int, short, const char, int*> == 4, "");
    
    variant<int, float, const char*, size_t> v = (size_t)10;
    EXPECT_EQ(triv::get<size_t>(v), 10);

    bool Thrown = false;
    try {
        // float member is currently inactive, throw bad access variant
        triv::get<float>(v);
    } catch (const bad_access_variant& e) {
        Thrown = true;
    }
    EXPECT_TRUE(Thrown);

    variant<int, float, const char*, size_t> v2 = 10.5f;
    EXPECT_EQ(triv::get<float>(v2), 10.5f);
    EXPECT_EQ(triv::get<1>(v2), 10.5f);

    Thrown = false;
    try {
        // first member (int) is currently inactive, throw bad access variant
        triv::get<0>(v2);
    } catch (const bad_access_variant& e) {
        Thrown = true;
    }
    EXPECT_TRUE(Thrown);
}