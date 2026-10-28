#include "pch.h"
#include "set.h"
#include <sstream>

TEST(SetTest, CtorAndSize) {
    set s(10);
    EXPECT_EQ(s.size(), size_t(10));

    set def;
    EXPECT_EQ(def.size(), size_t(1));
}

TEST(SetTest, InsertEraseIsExist) {
    set s(10);
    EXPECT_FALSE(s.is_exist(3));

    s.insert(3);
    EXPECT_TRUE(s.is_exist(3));

    s.erase(3);
    EXPECT_FALSE(s.is_exist(3));
}

TEST(SetTest, OutOfRange) {
    set s(5);
    EXPECT_FALSE(s.is_exist(5));
    EXPECT_THROW(s.insert(5), std::out_of_range);
    EXPECT_THROW(s.erase(5), std::out_of_range);
}

TEST(SetTest, UnionIntersectionDifference) {
    set a(10), b(10);
    a += 1; a += 2; a += 3;
    b += 2; b += 3; b += 4;

    set u = a + b;
    EXPECT_TRUE(u.is_exist(1));
    EXPECT_TRUE(u.is_exist(4));

    set i = a * b;
    EXPECT_FALSE(i.is_exist(1));
    EXPECT_TRUE(i.is_exist(2));
    EXPECT_FALSE(i.is_exist(4));

    set d = a - b;
    EXPECT_TRUE(d.is_exist(1));
    EXPECT_FALSE(d.is_exist(2));
}

TEST(SetTest, Equality) {
    set a(10), b(10);
    EXPECT_EQ(a, b);

    a.insert(1);
    EXPECT_NE(a, b);

    b.insert(1);
    EXPECT_EQ(a, b);
}

TEST(SetTest, Output) {
    set s(10);
    s.insert(0); s.insert(2); s.insert(5);

    std::ostringstream out;
    out << s;
    EXPECT_EQ(out.str(), "{ 0, 2, 5 }");
}

TEST(SetTest, Input) {
    set s(10);
    std::stringstream ss("{ 1, 3, 5 }");
    ss >> s;

    EXPECT_TRUE(s.is_exist(1));
    EXPECT_TRUE(s.is_exist(3));
    EXPECT_TRUE(s.is_exist(5));
    EXPECT_FALSE(s.is_exist(2));
}

TEST(SetTest, SimpleNumbersSmall) {
    set p = simple_numbers(10);

    EXPECT_FALSE(p.is_exist(0));
    EXPECT_FALSE(p.is_exist(1));
    EXPECT_TRUE(p.is_exist(2));
    EXPECT_TRUE(p.is_exist(3));
    EXPECT_TRUE(p.is_exist(5));
    EXPECT_TRUE(p.is_exist(7));
    EXPECT_FALSE(p.is_exist(4));
    EXPECT_FALSE(p.is_exist(6));
    EXPECT_FALSE(p.is_exist(8));
    EXPECT_FALSE(p.is_exist(9));
}

TEST(SetTest, SimpleNumbersUpTo30) {
    set p = simple_numbers(30);

    EXPECT_TRUE(p.is_exist(2));
    EXPECT_TRUE(p.is_exist(5));
    EXPECT_TRUE(p.is_exist(29));

    EXPECT_FALSE(p.is_exist(0));
    EXPECT_FALSE(p.is_exist(1));
    EXPECT_FALSE(p.is_exist(4));
    EXPECT_FALSE(p.is_exist(25));
    EXPECT_FALSE(p.is_exist(28));
}