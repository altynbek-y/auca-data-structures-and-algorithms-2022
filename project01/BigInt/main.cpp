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
    BigInt x("-12765876876764764876764648484864848746448764787864");
    ostringstream sout;
    sout << x;
    REQUIRE(sout.str() == "-12765876876764764876764648484864848746448764787864");

    SUBCASE("throw runtime_error")
    {
        REQUIRE_THROWS_AS(BigInt("-123a"), runtime_error);
    }
}

TEST_CASE("Input-output operators")
{
    BigInt x;
    istringstream sin("-1045549757534953498539820483");
    sin >> x;

    ostringstream sout;
    sout << x;
    REQUIRE(sout.str() == "-1045549757534953498539820483");
}

TEST_CASE("Operators: +, -, *, /, %, += , -=, *=, /=, %=, prefix and postfix ++ and --, unary -, unary +")
{
    BigInt a("123456789");
    BigInt b("123456789");

    SUBCASE("+")
    {
        BigInt res = a + b;
        ostringstream sout;
        sout << res;
        REQUIRE(sout.str() == "246913578");
    }
}