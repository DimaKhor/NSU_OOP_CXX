#include "gtest/gtest.h"
#include "bigint.h"

TEST (constructor_tests, empty_constructor) {
    BigInt a;
    EXPECT_EQ(a.getString(), "");
}

TEST (constructor_tests, int_constructor) {
    EXPECT_EQ(BigInt(2111111111).getString(), "2111111111");
    EXPECT_EQ(BigInt(0).getString(), "0");
    EXPECT_EQ(BigInt(-3).getString(), "-3");
}

TEST (constructor_tests, string_constructor) {
    EXPECT_EQ(BigInt("99999999999999").getString(), "99999999999999");
    EXPECT_EQ(BigInt("0").getString(), "0");
    EXPECT_EQ(BigInt("-200").getString(), "-200");

    try
    {
        BigInt b("dima.khoroshev");
    }
    catch (const std::logic_error &e)
    {
        EXPECT_STREQ(e.what(), "invalid_argument");
    }
}

TEST (constructor_tests, copy_constructor) {
    BigInt a("99999999999999");
    BigInt b(a);
    EXPECT_EQ(a.getString(), b.getString());
}

TEST (operators_tests, assignment_operator) {
    BigInt a("-3");
    BigInt b = a;
    b = b;
    EXPECT_EQ(a.getString(), b.getString());
}

TEST (binary_operators_tests, not_operator) {
    BigInt a(4);
    a = ~a;
    EXPECT_EQ(a.getString(), "-3");
}

TEST (operators_tests, increment_operator) {
    BigInt a("111111111111111111");
    a++;
    ++a;
    EXPECT_EQ(a.getString(), "111111111111111113");
}

TEST (operators_tests, decrement_operator) {
    BigInt a("333333333333333333");
    --a;
    a--;
    EXPECT_EQ(a.getString(), "333333333333333331");
}

TEST (aritmetic_assignment_tests, addition) {
    BigInt a("333333333");
    a += BigInt("666666666");
    EXPECT_EQ(a.getString(), "999999999");

    BigInt e("666666666");
    e += BigInt("-333333333");
    EXPECT_EQ(e.getString(), "333333333");

    BigInt b("-666666666");
    b += BigInt("333333333");
    EXPECT_EQ(b.getString(), "-333333333");

    BigInt c("-333333333");
    c += BigInt("-333333333");
    EXPECT_EQ(c.getString(), "-666666666");

    BigInt d("0");
    d += BigInt("999999999");
    EXPECT_EQ(d.getString(), "999999999");
}

TEST (aritmetic_assignment_tests, multiplication) {
    BigInt a("999999999");
    a *= BigInt("999999999");
    EXPECT_EQ(a.getString(), "999999998000000001");

    BigInt b("-999999999");
    b *= BigInt("-999999999");
    EXPECT_EQ(b.getString(), "999999998000000001");

    BigInt c("-999999999");
    c *= BigInt("999999999");
    EXPECT_EQ(c.getString(), "-999999998000000001");

    BigInt d("999999999");
    d *= BigInt("0");
    EXPECT_EQ(d.getString(), "0");
}

TEST (aritmetic_assignment_tests, subtraction) {
    BigInt a("666666666666666666");
    a -= BigInt("333333333333333333");
    EXPECT_EQ(a.getString(), "333333333333333333");

    BigInt b("-666666666666");
    b -= BigInt("333333333333");
    EXPECT_EQ(b.getString(), "-999999999999");

    BigInt c("-666666666666");
    c -= BigInt("-333333333333");
    EXPECT_EQ(c.getString(), "-333333333333");

    BigInt d("0");
    d -= BigInt("66666666666666666");
    EXPECT_EQ(d.getString(), "-66666666666666666");
}

TEST (aritmetic_assignment_tests, division) {
    BigInt a(999999999);
    a /= BigInt(666);
    EXPECT_EQ(a.getString(), "1501501");

    BigInt b(999999999);
    b /= BigInt(-666);
    EXPECT_EQ(b.getString(), "-1501501");

    BigInt c(-999999999);
    c /= BigInt(666);
    EXPECT_EQ(c.getString(), "-1501501");

    try
    {
        BigInt d("66");
        BigInt e("0");
        d /= e;

    }
    catch (const std::logic_error &e)
    {
        EXPECT_STREQ(e.what(), "division by zero");
    }
}

TEST (aritmetic_assignment_tests, degree) {
    BigInt a("999999999");
    a ^= BigInt("2");
    EXPECT_EQ(a.getString(), "999999998000000001");
}

TEST (aritmetic_assignment_tests, remainder_division) {
    BigInt a(999999997);
    a %= BigInt(666);
    EXPECT_EQ(a.getString(), "331");

    BigInt b(666);
    b %= BigInt(999);
    EXPECT_EQ(b.getString(), "666");
}

TEST (binary_operators_tests, and_operator) {
    BigInt a(66);
    a &= BigInt(99);
    EXPECT_EQ(a.getString(), "66");
}

TEST (binary_operators_tests, or_operator) {
    BigInt a(66);
    a |= BigInt(99);
    EXPECT_EQ(a.getString(), "99");
}

TEST (unary_operation, unary_operation) {
    BigInt a("123456789123456789");
    +a;
    EXPECT_EQ(a.getString(), "123456789123456789");

    BigInt b("2");
    BigInt c = -b;
    EXPECT_EQ(c.getString(), "-2");
}

TEST (comparison_tests, assignment) {
    EXPECT_TRUE(BigInt(6666666666) == BigInt(6666666666));
    EXPECT_FALSE(BigInt("-99999999999999") == BigInt("99999999999999"));
}

TEST (comparison_tests, not_assignment) {
    EXPECT_FALSE(BigInt(6666666666) != BigInt(6666666666));
    EXPECT_TRUE(BigInt("-99999999999999") != BigInt("99999999999999"));
}

TEST (comparison_tests, less) {
    EXPECT_FALSE(BigInt(6666666666) < BigInt(6666666666));
    EXPECT_TRUE(BigInt("-99999999999999") < BigInt("99999999999999"));
}

TEST (comparison_tests, bigger) {
    EXPECT_FALSE(BigInt(6666666666) > BigInt("999999999999"));
    EXPECT_TRUE(BigInt("6666666666") > BigInt("-6666666666"));
}

TEST (comparison_tests, less_assignment) {
    EXPECT_TRUE(BigInt(6666666666) <= BigInt(6666666666));
    EXPECT_FALSE(BigInt("999999999999") <= BigInt("-999999999999"));
}

TEST (comparison_tests, bigger_assignment) {
    EXPECT_FALSE(BigInt(66666666666) >= BigInt("999999999999"));
    EXPECT_TRUE(BigInt("999999999999") >= BigInt("999999999999"));
}

TEST (aritmetic_tests, addition) {
    BigInt a("333333333");
    BigInt a1("666666666");
    BigInt aResult = a + a1;
    EXPECT_EQ(aResult.getString(), "999999999");

    BigInt b("-666666666");
    BigInt b1("333333333");
    BigInt bResult  = b + b1;
    EXPECT_EQ(bResult.getString(), "-333333333");

    BigInt c("-333333333");
    BigInt c1("-333333333");
    BigInt cResult = c + c1;
    EXPECT_EQ(cResult.getString(), "-666666666");

    BigInt d("0");
    BigInt d1("999999999");
    BigInt dResult = d + d1;
    EXPECT_EQ(dResult.getString(), "999999999");
}

TEST (aritmetic_tests, multiplication) {
    BigInt a("999999999");
    BigInt a1 ("999999999");
    BigInt aResult = a * a1;
    EXPECT_EQ(aResult.getString(), "999999998000000001");

    BigInt b("-999999999");
    BigInt b1("-999999999");
    BigInt bResult = b * b1;
    EXPECT_EQ(bResult.getString(), "999999998000000001");

    BigInt c("-999999999");
    BigInt c1("999999999");
    BigInt cResult = c * c1;
    EXPECT_EQ(cResult.getString(), "-999999998000000001");

    BigInt d("999999999");
    BigInt d1("0");
    BigInt dResult = d * d1;
    EXPECT_EQ(dResult.getString(), "0");
}

TEST (aritmetic_tests, subtraction) {
    BigInt a("666666666666666666");
    BigInt a1("333333333333333333");
    BigInt aResult = a - a1;
    EXPECT_EQ(aResult.getString(), "333333333333333333");

    BigInt b("-666666666666");
    BigInt b1("333333333333");
    BigInt bResult = b - b1;
    EXPECT_EQ(bResult.getString(), "-999999999999");

    BigInt c("-666666666666");
    BigInt c1("-333333333333");
    BigInt cResult = c - c1;
    EXPECT_EQ(cResult.getString(), "-333333333333");


    BigInt d("0");
    BigInt d1("66666666666666666");
    BigInt dResult = d - d1;
    EXPECT_EQ(dResult.getString(), "-66666666666666666");
}

TEST (aritmetic_tests, division) {
    BigInt a(999999999);
    BigInt a1(666);
    BigInt aResult = a / a1;
    EXPECT_EQ(aResult.getString(), "1501501");

    BigInt b(999999999);
    BigInt b1(-666);
    BigInt bResult = b / b1;
    EXPECT_EQ(bResult.getString(), "-1501501");

    BigInt c(-999999999);
    BigInt c1(666);
    BigInt cResult = c / c1;
    EXPECT_EQ(cResult.getString(), "-1501501");

    try
    {
        BigInt d("66");
        BigInt e("0");
        d = d / e;

    }
    catch (const std::logic_error &e)
    {
        EXPECT_STREQ(e.what(), "division by zero");
    }
}

TEST (aritmetic_tests, degree) {
    BigInt a("999999999");
    BigInt a1 ("2");
    BigInt aResult = a ^ a1;
    EXPECT_EQ(aResult.getString(), "999999998000000001");
}

TEST (aritmetic_tests, remainder_division) {
    BigInt a(999999997);
    BigInt a1(666);
    BigInt aResult = a % a1;
    EXPECT_EQ(aResult.getString(), "331");

    BigInt b(666);
    BigInt b1(999);
    BigInt bResult = b % b1;
    EXPECT_EQ(bResult.getString(), "666");
}

TEST (binary_tests, and_operator) {
    BigInt a(66);
    BigInt a1(99);
    BigInt aResult = a & a1;
    EXPECT_EQ(aResult.getString(),"66");
}

TEST (binary_tests, or_operator) {
    BigInt a(66);
    BigInt a1(99);
    BigInt aResult = a | a1;
    EXPECT_EQ(aResult.getString(),"99");
}

TEST(test_type_conversion_operators, int_conversion)
{
    try
    {
        BigInt num = BigInt("9999999999999");
    }
    catch(const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), "int overflow");
    }
}

TEST(test_input_output_operators, output)
{
    std::ostringstream out;
    out << BigInt("-9999999999999");
    EXPECT_STREQ(out.str().data(), "-9999999999999");
}

TEST(size_test, operator_size) {
    EXPECT_TRUE(BigInt("999999999999999999999999").size() == 3);
    EXPECT_TRUE(BigInt("0").size() == 1);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
