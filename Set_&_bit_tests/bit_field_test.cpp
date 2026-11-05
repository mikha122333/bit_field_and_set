#include "pch.h"
#include "bit_field.h"
#include <sstream>

TEST(BitFieldTest, CtorAndSize) {
    bit_field bf(70);
    EXPECT_EQ(bf.size(), size_t(70));
    EXPECT_FALSE(bf.get_bit(0));
    EXPECT_FALSE(bf.get_bit(69));
}

TEST(BitFieldTest, ZeroSizeThrows) {
    EXPECT_THROW(bit_field bf(0), std::logic_error);
}

TEST(BitFieldTest, OutOfRangeThrows) {
    bit_field bf(10);
    EXPECT_THROW(bf.get_bit(10), std::out_of_range);
    EXPECT_THROW(bf.set_bit(10), std::out_of_range);
    EXPECT_THROW(bf.reset_bit(10), std::out_of_range);
}

TEST(BitFieldTest, SetAndReset) {
    bit_field bf(100);
    bf.set_bit(0);
    bf.set_bit(33);
    bf.set_bit(99);

    EXPECT_TRUE(bf.get_bit(0));
    EXPECT_TRUE(bf.get_bit(33));
    EXPECT_TRUE(bf.get_bit(99));
    EXPECT_FALSE(bf.get_bit(1));

    bf.reset_bit(33);
    EXPECT_FALSE(bf.get_bit(33));
}

TEST(BitFieldTest, CopyAndMove) {
    bit_field a(10);
    a.set_bit(5);

    bit_field b(a);
    EXPECT_EQ(a, b);

    bit_field c(std::move(b));
    EXPECT_TRUE(c.get_bit(5));
}

TEST(BitFieldTest, AndOr) {
    bit_field a(10), b(10);
    a.set_bit(1); a.set_bit(2);
    b.set_bit(2); b.set_bit(3);

    bit_field c = a & b;
    EXPECT_FALSE(c.get_bit(1));
    EXPECT_TRUE(c.get_bit(2));
    EXPECT_FALSE(c.get_bit(3));

    bit_field d = a | b;
    EXPECT_TRUE(d.get_bit(1));
    EXPECT_TRUE(d.get_bit(3));
}

TEST(BitFieldTest, DifferentSizesThrow) {
    bit_field a(10), b(11);
    EXPECT_THROW(a & b, std::logic_error);
    EXPECT_THROW(a | b, std::logic_error);
}

TEST(BitFieldTest, NotAndEquality) {
    bit_field a(10);
    a.set_bit(0);

    bit_field b = ~a;
    EXPECT_FALSE(b.get_bit(0));
    EXPECT_TRUE(b.get_bit(1));

    EXPECT_EQ(a, a);
    EXPECT_NE(a, b);
}

TEST(BitFieldTest, Output) {
    bit_field bf(5);
    bf.set_bit(0); bf.set_bit(2); bf.set_bit(4);

    std::ostringstream out;
    out << bf;
    EXPECT_EQ(out.str(), "10101");
}

TEST(BitFieldTest, Input) {
    bit_field bf(5);
    std::stringstream ss("10101");
    ss >> bf;

    EXPECT_TRUE(bf.get_bit(0));
    EXPECT_FALSE(bf.get_bit(1));
    EXPECT_TRUE(bf.get_bit(4));
}