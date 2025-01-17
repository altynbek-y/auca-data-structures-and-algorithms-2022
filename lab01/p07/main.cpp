#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest/doctest.h"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

TEST_CASE("default constructor")
{
    string s;

    REQUIRE(s == "");
    REQUIRE(s.size() == 0);
}

TEST_CASE("constructor with size and initial value")
{
    string s("test", 4);

    REQUIRE(s.size() == 4);
    REQUIRE(s == "test");
}

TEST_CASE("copy constructor (value semantics)")
{
    string s1("test");
    string s2(s1); // copy constructor

    REQUIRE(s2 == "test");
}

TEST_CASE("assignment operator (value semantics)")
{
    string s("test1");

    s = "test2";

    REQUIRE(s == "test2");
}

TEST_CASE("move constructor")
{
    string s1 = "test";
    string s2(move(s1));

    REQUIRE(s1 == "");
    REQUIRE(s2 == "test");
}

TEST_CASE("move assignment")
{
    string s1 = "test";
    string s2 = move(s1);

    REQUIRE(s1 == "");
    REQUIRE(s2 == "test");
}

TEST_CASE("subscript operator")
{
    string s("test");

    REQUIRE(s[0] == 't');

    s[0] = 'l';

    REQUIRE(s[0] == 'l');
}

TEST_CASE("method at(index), exception")
{
    string s("test");

    REQUIRE_THROWS(s.at(5));
    REQUIRE_THROWS_AS(s.at(5), out_of_range);
}

TEST_CASE("push_back method")
{
    string s("test");

    s.push_back('i');
    s.push_back('n');
    s.push_back('g');

    REQUIRE(s.size() == 7);
    REQUIRE(s == "testing");
}

TEST_CASE("pop_back method")
{
    string s("test");

    s.pop_back();
    s.pop_back();
    s.pop_back();

    REQUIRE(s.size() == 1);
    REQUIRE(s == "t");
}

TEST_CASE("+, += operators")
{
    string s("test");

    SUBCASE("+")
    {
        s += "ing";

        REQUIRE(s.size() == 7);
        REQUIRE(s == "testing");
    }

    SUBCASE("+=")
    {
        s = s + "s";

        REQUIRE(s.size() == 5);
        REQUIRE(s == "tests");
    }
}

TEST_CASE("==, !=, < and other comparison operators, method compare")
{
    string s("test");

    SUBCASE("==")
    {
        REQUIRE(s == "test");
    }

    SUBCASE("!=")
    {
        REQUIRE(s != "tesa");
    }

    SUBCASE(">")
    {
        REQUIRE(s > "sest");
    }

    SUBCASE("<")
    {
        REQUIRE(s < "zest");
    }

    SUBCASE(">=")
    {
        REQUIRE(s >= "test");
    }

    SUBCASE("<=")
    {
        REQUIRE(s <= "test");
    }
}

TEST_CASE("the work of for (auto &c : str) statement with std::string")
{
    string s("test");
    string copy = "";

    for (auto &c : s)
    {
        copy += c;
    }

    REQUIRE(copy == "test");
}

TEST_CASE("methods front(), back()")
{
    string s("test");

    SUBCASE("front()")
    {
        REQUIRE(s.front() == 't');

        s.front() = 'l';

        REQUIRE(s.front() == 'l');
    }

    SUBCASE("back()")
    {
        REQUIRE(s.back() == 't');

        s.back() = 'm';

        REQUIRE(s.back() == 'm');
    }
}

TEST_CASE("methods substr(index, length), find(char ch)")
{
    string s1("test");

    SUBCASE("substr(index, length)")
    {
        string s2 = s1.substr(0, 2);

        REQUIRE(s2 == "te");
    }

    SUBCASE("find(char ch)")
    {
        int pos = s1.find('e');

        REQUIRE(pos == 1);

        pos = s1.find('l');

        REQUIRE(pos == string::npos);
    }
}

TEST_CASE("type std::string::iterator, operators: *it, it->field , ++it, --it, it += n, it-=n, it2 – it1")
{
    string s1("test");
    vector<string> vs = {"test1", "test2", "test3"};

    string::iterator it1 = s1.begin();
    string::iterator it2 = s1.end();
    vector<string>::iterator it = vs.begin();

    SUBCASE("*it")
    {
        REQUIRE(*it1 == 't');
    }

    SUBCASE("std::string::iterator")
    {
        REQUIRE(it->size() == 5);
    }

    SUBCASE("++it")
    {
        ++it1;
        REQUIRE(*it1 == 'e');
    }

    SUBCASE("--it")
    {
        --it2;
        REQUIRE(*it2 == 't');
    }

    SUBCASE("it += n")
    {
        it1 += 3;
        REQUIRE(*it1 == 't');
    }

    SUBCASE("it -= n")
    {
        it2 -= 3;
        REQUIRE(*it2 == 'e');
    }

    SUBCASE("it2 – it1")
    {
        REQUIRE(it2 - it1 == 4);
    }
}

TEST_CASE("method insert(index, length, char)")
{
    string s("test");

    s.insert(0, 2, 'h');

    REQUIRE(s == "hhtest");
}

TEST_CASE("methods erase(index, length)")
{
    string s("test");

    s.erase(0, 1);

    REQUIRE(s == "est");

    s.erase(1, 1);

    REQUIRE(s == "et");
}

TEST_CASE("constructor string(beg, end);")
{
    string s1("test");

    string s2(s1.begin(), s1.end());

    REQUIRE(s2 == "test");
}

TEST_CASE("the work of std::reverse algorithm with std::string")
{
    string s("test");

    reverse(s.begin(), s.end());

    REQUIRE(s == "tset");
}

TEST_CASE("the work of std::sort algorithm with std::string")
{
    string s("test");

    sort(s.begin(), s.end());

    REQUIRE(s == "estt");
}

TEST_CASE("the work of std::binary_search algorithm with std::string")
{
    string s("estt");

    REQUIRE(binary_search(s.begin(), s.end(), 'e'));

    REQUIRE(!binary_search(s.begin(), s.end(), 'a'));
}

TEST_CASE("the work of std::min_element algorithm with std::string")
{
    string s("test");
    char c = *min_element(s.begin(), s.end());

    REQUIRE(c == 'e');

    s = "";
    REQUIRE(min_element(s.begin(), s.end()) == s.end());
}

TEST_CASE("the work of std::max_element algorithm with std::string")
{
    string s("test");

    char c = *max_element(s.begin(), s.end());

    REQUIRE(c == 't');

    s = "";
    REQUIRE(max_element(s.begin(), s.end()) == s.end());
}
