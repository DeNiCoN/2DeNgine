#include "gtest/gtest.h"
#include "utils/HashedString.hpp"

using namespace DeNgine::utils;

TEST(Utils, Murmurhash)
{
    EXPECT_EQ(hash("s"), hash("s"));
    EXPECT_NE(hash("a"), hash("s"));
    EXPECT_EQ(hash("such a big string. I'm need more characters."),
              hash("such a big string. I'm need more characters."));
    EXPECT_NE(hash("such a bug string. I'm need more characters."),
              hash("such a big string. I'm need more characters."));
    EXPECT_EQ(hash("such a big string. I'm need more characters.", 4),
              hash("such a big string. I'm need more characters.", 4));
    EXPECT_NE(hash("such a big string. I'm need more characters.", 4),
              hash("such a big string. I'm need more characters.", 5));
}

TEST(Utils, HashedStringEquality)
{
    HashedString a("Hello");
    HashedString b("Hello");
    HashedString c("World");
    HashedString d("world");
    EXPECT_EQ(a, b);
    EXPECT_EQ(a.length, b.length);
    EXPECT_NE(a, c);
    EXPECT_NE(c, d);
}
