#include "gtest/gtest.h"
#include "utils/HashedString.hpp"

TEST(Utils, HashedStringEquality)
{
    using namespace DeNgine::utils;
    HashedString a("Hello");
    HashedString b("Hello");
    HashedString c("World");
    HashedString d("world");
    EXPECT_EQ(a, b);
    EXPECT_EQ(a.length, b.length);
    EXPECT_NE(a, c);
    EXPECT_NE(c, d);
}
