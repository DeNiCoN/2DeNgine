#include "utils/LRUCache.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <string>
using namespace std::literals;

class NoHash
{

};

class LRUCacheTest : public ::testing::Test
{
protected:
    LRUCache<int, int> empty;
    LRUCache<std::string, std::string> i1;
    LRUCache<std::string, std::string> i2;
    LRUCache<std::string, std::string> i3;

    void SetUp() override
    {
        i1.insert("a", "_a");
        i2.insert("a", "_a");
        i2.insert("b", "_b");
        i3.insert("a", "_a");
        i3.insert("b", "_b");
        i3.insert("c", "_c");
    }

    template<typename K, typename V>
    bool equal(LRUCache<K, V> c, std::initializer_list<V> l)
    {
        return std::equal(c.begin(), c.end(), l.begin(),
        [](const auto& a, const auto& b)
        {
            return a.second == b;
        });
    }

};

TEST_F(LRUCacheTest, Empty)
{
    EXPECT_TRUE(empty.empty());
    EXPECT_TRUE(empty.size() == 0);
}

TEST_F(LRUCacheTest, Add)
{
    unsigned int initial_size = empty.size();
    empty.insert(2, 1);
    EXPECT_EQ(empty.back().first, 2);
    EXPECT_EQ(empty.back().second, 1);
    EXPECT_FALSE(empty.empty());
    EXPECT_EQ(empty.size(), initial_size + 1);

    empty.insert(3, 2);
    EXPECT_EQ(empty.begin()->first, 3);
    EXPECT_EQ(empty.begin()->second, 2);
    EXPECT_EQ(empty.size(), initial_size + 2);

    empty.insert(1, 1);
    EXPECT_EQ(empty.begin()->first, 1);
    EXPECT_EQ(empty.begin()->second, 1);
    EXPECT_EQ(empty.size(), initial_size + 3);
}

TEST_F(LRUCacheTest, Find)
{
    ASSERT_TRUE(equal(i1, {"_a"s}));
    EXPECT_EQ(i1.find("a")->second, "_a"s);
    EXPECT_TRUE(equal(i1, {"_a"s}));

    EXPECT_EQ(i3.find("a")->second, "_a"s);
    EXPECT_EQ(i3.begin()->second, "_a"s);
}
