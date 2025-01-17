#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest/doctest.h"
#include <vector>
#include <string>

#include "BigInt.hpp"

using namespace std;

TEST_CASE("Default constructor")
{
    BigInt x;
    ostringstream sout;
    sout << x;
    REQUIRE(sout.str() == "0");
}

TEST_CASE("Default constructor with a string parameter")
{
    SUBCASE("correct parameter #1")
    {
        BigInt x("123");
        REQUIRE(x == 123);
    }
    SUBCASE("correct parameter #2")
    {
        BigInt x("     123");
        REQUIRE(x == 123);
    }
    SUBCASE("correct parameter #3")
    {
        BigInt x("123x123");
        REQUIRE(x == 123);
    }
    SUBCASE("correct parameter #4")
    {
        BigInt x("   -123");
        REQUIRE(x == -123);
    }
    SUBCASE("correct parameter #5")
    {
        BigInt x("   +123");
        REQUIRE(x == 123);
    }
    SUBCASE("incorrect input #1")
    {
        REQUIRE_THROWS_AS(BigInt("+ 123"), runtime_error);
    }
    SUBCASE("incorrect input #2")
    {
        REQUIRE_THROWS_AS(BigInt("++123"), runtime_error);
    }
    SUBCASE("incorrect input #3")
    {
        REQUIRE_THROWS_AS(BigInt("hello"), runtime_error);
    }
    SUBCASE("incorrect input #4")
    {
        REQUIRE_THROWS_AS(BigInt(""), runtime_error);
    }
}

TEST_CASE("Default constructor with an integer parameter")
{
    ostringstream sout;

    SUBCASE("positive integer")
    {
        BigInt x(123456789);
        sout << x;
        REQUIRE(sout.str() == "123456789");
    }

    SUBCASE("negative integer")
    {
        BigInt x(-123456789);
        sout << x;
        REQUIRE(sout.str() == "-123456789");
    }
}

TEST_CASE("Input operator")
{
    ostringstream sout;
    SUBCASE("correct input #1")
    {
        istringstream sinp("123");
        BigInt x;
        sinp >> x;
        REQUIRE(sinp.eof());
        REQUIRE(x == 123);
    }
    SUBCASE("correct input #2")
    {
        istringstream sinp("  123");
        BigInt x;
        sinp >> x;
        REQUIRE(sinp.eof());
        REQUIRE(x == 123);
    }
    SUBCASE("correct input #3")
    {
        istringstream sinp("123x123");
        BigInt x;
        sinp >> x;
        REQUIRE(sinp.good());
        REQUIRE(x == 123);
        char ch;
        sinp >> ch;
        REQUIRE(ch == 'x');
    }
    SUBCASE("correct input #4")
    {
        istringstream sinp("   -123");
        BigInt x;
        sinp >> x;
        REQUIRE(sinp.eof());
        REQUIRE(x == -123);
    }
    SUBCASE("correct input #5")
    {
        istringstream sinp("   +123");
        BigInt x;
        sinp >> x;
        REQUIRE(sinp.eof());
        REQUIRE(x == 123);
    }
    SUBCASE("incorrect input #1")
    {
        istringstream sinp("+ 123");
        BigInt x;
        sinp >> x;
        REQUIRE(sinp.fail());
        REQUIRE(x == 0);
    }
    SUBCASE("incorrect input #2")
    {
        istringstream sinp("++123");
        BigInt x;
        sinp >> x;
        REQUIRE(sinp.fail());
        REQUIRE(x == 0);
    }
    SUBCASE("incorrect input #3")
    {
        istringstream sinp("hello");
        BigInt x;
        char ch;
        sinp >> x;
        REQUIRE(sinp.fail());
        REQUIRE(x == 0);
        sinp.clear();
        sinp >> ch;
        REQUIRE(ch == 'h');
    }
    SUBCASE("incorrect input #4")
    {
        istringstream sinp("");
        BigInt x;
        sinp >> x;
        REQUIRE(sinp.fail());
        REQUIRE(sinp.eof());
        REQUIRE(x == 0);
    }
}

TEST_CASE("Addition operator")
{
    ostringstream sout;

    SUBCASE("positive + positive #1")
    {
        BigInt a("193");
        BigInt b("52");
        sout << a + b;
        REQUIRE(sout.str() == "245");
    }

    SUBCASE("positive + positive #2")
    {
        BigInt a("999");
        BigInt b("1");
        sout << a + b;
        REQUIRE(sout.str() == "1000");
    }

    SUBCASE("positive + positive #3")
    {
        // for (int x = 0; x <= 1000; x++)
        // {
        //     for (int y = 0; y <= 1000; y++)
        //     {
        //         BigInt a(std::to_string(x));
        //         BigInt b(std::to_string(y));
        //         sout << a + b;
        //         REQUIRE(sout.str() == std::to_string(x + y));
        //         sout.str("");
        //     }
        // }
    }

    SUBCASE("negative + positive #1")
    {
        BigInt a("-100");
        BigInt b("200");
        sout << a + b;
        REQUIRE(sout.str() == "100");
    }

    SUBCASE("negative + positive #2")
    {
        BigInt a("-300");
        BigInt b("200");
        sout << a + b;
        REQUIRE(sout.str() == "-100");
    }

    SUBCASE("positive + negative #1")
    {
        BigInt a("300");
        BigInt b("-200");
        sout << a + b;
        REQUIRE(sout.str() == "100");
    }

    SUBCASE("positive + negative #2")
    {
        BigInt a("200");
        BigInt b("-400");
        sout << a + b;
        REQUIRE(sout.str() == "-200");
    }

    SUBCASE("negative + negative #1")
    {
        BigInt a("-1");
        BigInt b("-999");
        sout << a + b;
        REQUIRE(sout.str() == "-1000");
    }

    SUBCASE("negative + negative #2")
    {
        BigInt a("-193");
        BigInt b("-52");
        sout << a + b;
        REQUIRE(sout.str() == "-245");
    }
}

TEST_CASE("Equality operators")
{
    ostringstream sout;

    SUBCASE("equality operator #1")
    {
        BigInt a("193");
        BigInt b("193");
        REQUIRE(a == b);
    }

    SUBCASE("equality operator #2")
    {
        BigInt a("-193");
        BigInt b("-193");
        REQUIRE(a == b);
    }

    SUBCASE("non-equality operator #1")
    {
        BigInt a("193");
        BigInt b("-193");
        REQUIRE(a != b);
    }

    SUBCASE("non-equality operator #2")
    {
        BigInt a("19333");
        BigInt b("193");
        REQUIRE(a != b);
    }
}

TEST_CASE("Comparison operators")
{
    ostringstream sout;

    SUBCASE("less than operator #1")
    {
        BigInt a("19");
        BigInt b("193");
        REQUIRE(a < b);
    }

    SUBCASE("less than operator #2")
    {
        BigInt a("-194");
        BigInt b("-193");
        REQUIRE(a < b);
    }

    SUBCASE("less than operator #3")
    {
        BigInt a("-192");
        BigInt b("-193");
        REQUIRE_FALSE(a < b);
    }

    SUBCASE("less than operator #4")
    {
        for (int i = -100; i <= 100; i++)
        {
            for (int j = -100; j <= 100; j++)
            {
                if (i < j)
                {
                    BigInt a(std::to_string(i));
                    BigInt b(std::to_string(j));
                    REQUIRE(a < b);
                }
            }
        }
    }

    SUBCASE("greater than operator #1")
    {
        BigInt a("193");
        BigInt b("19");
        REQUIRE(a > b);
    }

    SUBCASE("greater than operator #2")
    {
        BigInt a("-99");
        BigInt b("-100");
        REQUIRE(a > b);
    }

    SUBCASE("greater than operator #3")
    {
        for (int i = -100; i <= 100; i++)
        {
            for (int j = -100; j <= 100; j++)
            {
                if (i >= j)
                {
                    BigInt a(std::to_string(i));
                    BigInt b(std::to_string(j));
                    REQUIRE(a >= b);
                }
            }
        }
    }

    SUBCASE("less than or equal operator #1")
    {
        BigInt a("19");
        BigInt b("193");
        REQUIRE(a <= b);
    }

    SUBCASE("less than or equal operator #2")
    {
        BigInt a("-100");
        BigInt b("-100");
        REQUIRE(a <= b);
    }

    SUBCASE("greater than or equal operator #1")
    {
        BigInt a("200");
        BigInt b("200");
        REQUIRE(a >= b);
    }

    SUBCASE("greater than or equal operator #2")
    {
        BigInt a("-199");
        BigInt b("-200");
        REQUIRE(a >= b);
    }
}

TEST_CASE("Abs() function")
{
    ostringstream sout;

    SUBCASE("abs(positive)")
    {
        istringstream sinp("123");
        BigInt x;
        sinp >> x;
        BigInt r = BigInt::abs(x);
        REQUIRE(r == 123);
    }

    SUBCASE("abs(negative)")
    {
        istringstream sinp("-123");
        BigInt x;
        sinp >> x;
        BigInt r = BigInt::abs(x);
        REQUIRE(r == 123);
    }
}

TEST_CASE("Subtraction operator")
{
    ostringstream sout;

    SUBCASE("positive - positive #1")
    {
        BigInt a("193");
        BigInt b("52");
        sout << a - b;
        REQUIRE(sout.str() == "141");
    }

    SUBCASE("positive - positive #2")
    {
        BigInt a("88");
        BigInt b("88");
        sout << a - b;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("positive - positive #3")
    {
        BigInt a("100");
        BigInt b("2");
        sout << a - b;
        REQUIRE(sout.str() == "98");
    }

    SUBCASE("positive - positive #4")
    {
        BigInt a("2");
        BigInt b("100");
        sout << a - b;
        REQUIRE(sout.str() == "-98");
    }

    SUBCASE("negative - negative #1")
    {
        BigInt a("-100");
        BigInt b("-100");
        sout << a - b;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("negative - negative #2")
    {
        BigInt a("-100");
        BigInt b("-1");
        sout << a - b;
        REQUIRE(sout.str() == "-99");
    }

    SUBCASE("negative - negative #3")
    {
        BigInt a("-1");
        BigInt b("-100");
        sout << a - b;
        REQUIRE(sout.str() == "99");
    }

    SUBCASE("negative - positive #1")
    {
        BigInt a("-100");
        BigInt b("23");
        sout << a - b;
        REQUIRE(sout.str() == "-123");
    }

    SUBCASE("positive - negative #1")
    {
        BigInt a("100");
        BigInt b("-23");
        sout << a - b;
        REQUIRE(sout.str() == "123");
    }
}

TEST_CASE("Prefix and postfix increment and decrement")
{
    ostringstream sout;

    SUBCASE("Postfix increment")
    {
        BigInt a("-3");
        a++;
        a++;
        sout << a;
        REQUIRE(sout.str() == "-1");
    }

    SUBCASE("Prefix increment")
    {
        BigInt a("101");
        ++a;
        sout << a;
        REQUIRE(sout.str() == "102");
    }

    SUBCASE("Postfix decrement")
    {
        BigInt a("0");
        a--;
        a--;
        a--;
        sout << a;
        REQUIRE(sout.str() == "-3");
    }

    SUBCASE("Prefix decrement")
    {
        BigInt a("0");
        --a;
        --a;
        --a;
        --a;
        sout << a;
        REQUIRE(sout.str() == "-4");
    }
}

TEST_CASE("Add and assignment")
{
    ostringstream sout;

    SUBCASE("positive += positive #1")
    {
        BigInt a("1");
        BigInt b("99");
        a += b;
        sout << a;
        REQUIRE(sout.str() == "100");
    }

    SUBCASE("positive += positive #1")
    {
        BigInt a("1");
        BigInt b("99");
        a += b;
        sout << a;
        REQUIRE(sout.str() == "100");
    }

    SUBCASE("positive += positive #2")
    {
        BigInt a("999");
        BigInt b("1");
        a += b;
        sout << a;
        REQUIRE(sout.str() == "1000");
    }

    SUBCASE("positive += positive #3")
    {
        // for (int x = 0; x <= 1000; x++)
        // {
        //     for (int y = 0; y <= 1000; y++)
        //     {
        //         BigInt a(std::to_string(x));
        //         BigInt b(std::to_string(y));
        //         sout << a + b;
        //         REQUIRE(sout.str() == std::to_string(x + y));
        //         sout.str("");
        //     }
        // }
    }

    SUBCASE("negative += positive #1")
    {
        BigInt a("-100");
        BigInt b("200");
        a += b;
        sout << a;
        REQUIRE(sout.str() == "100");
    }

    SUBCASE("negative += positive #2")
    {
        BigInt a("-300");
        BigInt b("200");
        a += b;
        sout << a;
        REQUIRE(sout.str() == "-100");
    }

    SUBCASE("positive += negative #1")
    {
        BigInt a("300");
        BigInt b("-200");
        a += b;
        sout << a;
        REQUIRE(sout.str() == "100");
    }

    SUBCASE("positive += negative #2")
    {
        BigInt a("200");
        BigInt b("-400");
        a += b;
        sout << a;
        REQUIRE(sout.str() == "-200");
    }

    SUBCASE("negative += negative #1")
    {
        BigInt a("-1");
        BigInt b("-999");
        a += b;
        sout << a;
        REQUIRE(sout.str() == "-1000");
    }

    SUBCASE("negative += negative #2")
    {
        BigInt a("-193");
        BigInt b("-52");
        a += b;
        sout << a;
        REQUIRE(sout.str() == "-245");
    }
}

TEST_CASE("Subtract and assignment")
{
    ostringstream sout;

    SUBCASE("positive -= positive #1")
    {
        BigInt a("193");
        BigInt b("52");
        a -= b;
        sout << a;
        REQUIRE(sout.str() == "141");
    }

    SUBCASE("positive -= positive #2")
    {
        BigInt a("88");
        BigInt b("88");
        a -= b;
        sout << a;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("positive -= positive #3")
    {
        BigInt a("100");
        BigInt b("2");
        a -= b;
        sout << a;
        REQUIRE(sout.str() == "98");
    }

    SUBCASE("positive -= positive #4")
    {
        BigInt a("2");
        BigInt b("100");
        a -= b;
        sout << a;
        REQUIRE(sout.str() == "-98");
    }

    SUBCASE("negative -= negative #1")
    {
        BigInt a("-100");
        BigInt b("-100");
        a -= b;
        sout << a;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("negative -= negative #2")
    {
        BigInt a("-100");
        BigInt b("-1");
        a -= b;
        sout << a;
        REQUIRE(sout.str() == "-99");
    }

    SUBCASE("negative -= negative #3")
    {
        BigInt a("-1");
        BigInt b("-100");
        a -= b;
        sout << a;
        REQUIRE(sout.str() == "99");
    }

    SUBCASE("negative -= positive #1")
    {
        BigInt a("-100");
        BigInt b("23");
        a -= b;
        sout << a;
        REQUIRE(sout.str() == "-123");
    }

    SUBCASE("positive -= negative #1")
    {
        BigInt a("100");
        BigInt b("-23");
        a -= b;
        sout << a;
        REQUIRE(sout.str() == "123");
    }
}

TEST_CASE("Multpiplication operator")
{
    ostringstream sout;

    SUBCASE("positive * positive #1")
    {
        BigInt a("999");
        BigInt b("2");
        sout << a * b;
        REQUIRE(sout.str() == "1998");
    }

    SUBCASE("positive * positive #2")
    {
        BigInt a("989");
        BigInt b("21");
        sout << a * b;
        REQUIRE(sout.str() == "20769");
    }

    SUBCASE("positive * positive #3")
    {
        BigInt a("21");
        BigInt b("98900");
        sout << a * b;
        REQUIRE(sout.str() == "2076900");
    }

    SUBCASE("positive * positive #4")
    {
        BigInt a("13");
        BigInt b("12");
        sout << a * b;
        REQUIRE(sout.str() == "156");
    }

    SUBCASE("positive * positive #5")
    {
        BigInt a("1");
        BigInt b("134563");
        sout << a * b;
        REQUIRE(sout.str() == "134563");
    }

    SUBCASE("zero * positive #6")
    {
        BigInt a("0");
        BigInt b("134563");
        sout << a * b;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("negative * negative #6")
    {
        BigInt a("-234");
        BigInt b("-12");
        sout << a * b;
        REQUIRE(sout.str() == "2808");
    }

    SUBCASE("negative * negative #7")
    {
        BigInt a("-12");
        BigInt b("-234");
        sout << a * b;
        REQUIRE(sout.str() == "2808");
    }

    SUBCASE("negative * positive #8")
    {
        BigInt a("-12");
        BigInt b("234");
        sout << a * b;
        REQUIRE(sout.str() == "-2808");
    }

    SUBCASE("negative * positive #9")
    {
        BigInt a("12");
        BigInt b("-234");
        sout << a * b;
        REQUIRE(sout.str() == "-2808");
    }

    SUBCASE("zero * positive #10")
    {
        BigInt a("0");
        BigInt b("-234");
        sout << a * b;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("zero * zero #11")
    {
        BigInt a("0");
        BigInt b("0");
        sout << a * b;
        REQUIRE(sout.str() == "0");
    }
}

TEST_CASE("Multpiply and assignment operator")
{
    ostringstream sout;

    SUBCASE("positive *= positive #1")
    {
        BigInt a("999");
        BigInt b("2");
        a *= b;
        sout << a;
        REQUIRE(sout.str() == "1998");
    }

    SUBCASE("positive *= positive #2")
    {
        BigInt a("989");
        BigInt b("21");
        a *= b;
        sout << a;
        REQUIRE(sout.str() == "20769");
    }

    SUBCASE("positive *= positive #3")
    {
        BigInt a("21");
        BigInt b("98900");
        a *= b;
        sout << a;
        REQUIRE(sout.str() == "2076900");
    }

    SUBCASE("positive *= positive #4")
    {
        BigInt a("13");
        BigInt b("12");
        a *= b;
        sout << a;
        REQUIRE(sout.str() == "156");
    }

    SUBCASE("positive *= positive #5")
    {
        BigInt a("1");
        BigInt b("134563");
        a *= b;
        sout << a;
        REQUIRE(sout.str() == "134563");
    }

    SUBCASE("zero *= positive #6")
    {
        BigInt a("0");
        BigInt b("134563");
        a *= b;
        sout << a;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("negative *= negative #6")
    {
        BigInt a("-234");
        BigInt b("-12");
        a *= b;
        sout << a;
        REQUIRE(sout.str() == "2808");
    }

    SUBCASE("negative *= negative #7")
    {
        BigInt a("-12");
        BigInt b("-234");
        a *= b;
        sout << a;
        REQUIRE(sout.str() == "2808");
    }

    SUBCASE("negative *= positive #8")
    {
        BigInt a("-12");
        BigInt b("234");
        a *= b;
        sout << a;
        REQUIRE(sout.str() == "-2808");
    }

    SUBCASE("negative *= positive #9")
    {
        BigInt a("12");
        BigInt b("-234");
        a *= b;
        sout << a;
        REQUIRE(sout.str() == "-2808");
    }

    SUBCASE("zero *= positive #10")
    {
        BigInt a("0");
        BigInt b("-234");
        a *= b;
        sout << a;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("zero *= zero #11")
    {
        BigInt a("0");
        BigInt b("0");
        a *= b;
        sout << a;
        REQUIRE(sout.str() == "0");
    }
}

TEST_CASE("Division operator")
{
    ostringstream sout;

    SUBCASE("positive / positive #1")
    {
        BigInt a("1481481468");
        BigInt b("12");
        sout << a / b;
        REQUIRE(sout.str() == "123456789");
    }

    SUBCASE("positive / positive #2")
    {
        BigInt a("12345");
        BigInt b("13");
        sout << a / b;
        REQUIRE(sout.str() == "949");
    }

    SUBCASE("positive / positive #3")
    {
        BigInt a("3600");
        BigInt b("12");
        sout << a / b;
        REQUIRE(sout.str() == "300");
    }

    SUBCASE("positive / positive #4")
    {
        BigInt a("360036");
        BigInt b("12");
        sout << a / b;
        REQUIRE(sout.str() == "30003");
    }

    SUBCASE("positive / positive #5")
    {
        BigInt a("9210965");
        BigInt b("339");
        sout << a / b;
        REQUIRE(sout.str() == "27170");
    }

    SUBCASE("positive / positive #6")
    {
        BigInt a("921");
        BigInt b("678");
        sout << a / b;
        REQUIRE(sout.str() == "1");
    }

    SUBCASE("0 / value #1")
    {
        BigInt a("0");
        BigInt b("123456789");
        sout << a / b;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("value / 0 #2")
    {
        BigInt a("123456789");
        BigInt b("0");
        REQUIRE_THROWS_AS(a / b, runtime_error);
    }

    SUBCASE("0 / -value #3")
    {
        BigInt a("0");
        BigInt b("-123456789");
        sout << a / b;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("-value / 0 #4")
    {
        BigInt a("-123456789");
        BigInt b("0");
        REQUIRE_THROWS_AS(a / b, runtime_error);
    }

    SUBCASE("0 / 0 #5")
    {
        BigInt a("0");
        BigInt b("0");
        REQUIRE_THROWS_AS(a / b, runtime_error);
    }

    SUBCASE("negative / negative #1")
    {
        BigInt a("-1481481468");
        BigInt b("-12");
        sout << a / b;
        REQUIRE(sout.str() == "123456789");
    }

    SUBCASE("negative / positive #2")
    {
        BigInt a("-12345");
        BigInt b("13");
        sout << a / b;
        REQUIRE(sout.str() == "-949");
    }

    SUBCASE("positive / negative #3")
    {
        BigInt a("3600");
        BigInt b("-12");
        sout << a / b;
        REQUIRE(sout.str() == "-300");
    }

    SUBCASE("positive / negative #4")
    {
        BigInt a("3");
        BigInt b("-2");
        sout << a / b;
        REQUIRE(sout.str() == "-1");
    }

    SUBCASE("negative / positive #5")
    {
        BigInt a("-2");
        BigInt b("3");
        sout << a / b;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("negative / positive #6")
    {
        BigInt a("-921");
        BigInt b("678");
        sout << a / b;
        REQUIRE(sout.str() == "-1");
    }
}

TEST_CASE("Divide and assignment operator")
{
    ostringstream sout;

    SUBCASE("positive /= positive #1")
    {
        BigInt a("1481481468");
        BigInt b("12");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "123456789");
    }

    SUBCASE("positive /= positive #2")
    {
        BigInt a("12345");
        BigInt b("13");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "949");
    }

    SUBCASE("positive /= positive #3")
    {
        BigInt a("3600");
        BigInt b("12");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "300");
    }

    SUBCASE("positive /= positive #4")
    {
        BigInt a("360036");
        BigInt b("12");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "30003");
    }

    SUBCASE("positive /= positive #5")
    {
        BigInt a("9210965");
        BigInt b("339");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "27170");
    }

    SUBCASE("positive /= positive #6")
    {
        BigInt a("921");
        BigInt b("678");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "1");
    }

    SUBCASE("0 /= value #1")
    {
        BigInt a("0");
        BigInt b("123456789");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("0 /= -value #3")
    {
        BigInt a("0");
        BigInt b("-123456789");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("negative /= negative #1")
    {
        BigInt a("-1481481468");
        BigInt b("-12");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "123456789");
    }

    SUBCASE("negative /= positive #2")
    {
        BigInt a("-12345");
        BigInt b("13");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "-949");
    }

    SUBCASE("positive /= negative #3")
    {
        BigInt a("3600");
        BigInt b("-12");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "-300");
    }

    SUBCASE("positive /= negative #4")
    {
        BigInt a("3");
        BigInt b("-2");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "-1");
    }

    SUBCASE("negative /= positive #5")
    {
        BigInt a("-2");
        BigInt b("3");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "0");
    }

    SUBCASE("negative /= positive #6")
    {
        BigInt a("-921");
        BigInt b("678");
        a /= b;
        sout << a;
        REQUIRE(sout.str() == "-1");
    }
}

TEST_CASE("Modular division operator")
{
    ostringstream sout;

    SUBCASE("positive % positive #1")
    {
        BigInt a("1");
        BigInt b("99");
        sout << a % b;
        REQUIRE(sout.str() == "1");
    }

    SUBCASE("positive % positive #2")
    {
        BigInt a("864964064048640964086450968409864509684096840986409640986480964806409864086480468094680946098456890468456830394304234");
        BigInt b("9747634534537423975347875479534955345935349555394559353");
        sout << a % b;
        REQUIRE(sout.str() == "5908537950814752622129236752714503969358368360439630375");
    }

    SUBCASE("negative % positive #1")
    {
        BigInt a("-5");
        BigInt b("10");
        sout << a % b;
        REQUIRE(sout.str() == "-5");
    }

    SUBCASE("negative % negative #1")
    {
        BigInt a("-5");
        BigInt b("-10");
        REQUIRE_THROWS_AS(a % b, runtime_error);
    }
}

TEST_CASE("Modular division and assignment operator")
{
    ostringstream sout;

    SUBCASE("positive %= positive #1")
    {
        BigInt a("1");
        BigInt b("99");
        a %= b;
        sout << a;
        REQUIRE(sout.str() == "1");
    }

    SUBCASE("positive %= positive #2")
    {
        BigInt a("864964064048640964086450968409864509684096840986409640986480964806409864086480468094680946098456890468456830394304234");
        BigInt b("9747634534537423975347875479534955345935349555394559353");
        a %= b;
        sout << a;
        REQUIRE(sout.str() == "5908537950814752622129236752714503969358368360439630375");
    }

    SUBCASE("negative %= positive #1")
    {
        BigInt a("-5");
        BigInt b("10");
        a %= b;
        sout << a;
        REQUIRE(sout.str() == "-5");
    }
}

TEST_CASE("Unary minus and plus")
{
    ostringstream sout;

    SUBCASE("-positive #1")
    {
        BigInt a("144");
        BigInt b = -a;
        sout << b;
        REQUIRE(sout.str() == "-144");
        REQUIRE(a == 144);
    }

    SUBCASE("-negative #2")
    {
        BigInt a("-144");
        BigInt b = -a;
        sout << b;
        REQUIRE(sout.str() == "144");
        REQUIRE(a == -144);
    }

    SUBCASE("+positive #1")
    {
        BigInt a("144");
        BigInt b = +a;
        sout << b;
        REQUIRE(sout.str() == "144");
        REQUIRE(a == 144);
    }

    SUBCASE("+negative #2")
    {
        BigInt a("-144");
        BigInt b = +a;
        sout << b;
        REQUIRE(sout.str() == "-144");
        REQUIRE(a == -144);
    }
}