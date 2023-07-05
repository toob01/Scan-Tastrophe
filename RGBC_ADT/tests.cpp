// =============================================================
//
// File         : tests.cpp in RGBC_ADT/
// Copyright    : tobias.bosch@student.hu.nl 2023
//
// Distributed under the Boost Software License, Version 1.0.
// (See https://www.boost.org/LICENSE_1_0.txt)
//
// =============================================================

#include "catch.hpp"
#include "rgbc.hpp"

TEST_CASE("red getter"){
    rgbc x(1111, 2222, 3333, 4444);
    REQUIRE(x.red_get() == 1111);
}

TEST_CASE("green getter"){
    rgbc x(1111, 2222, 3333, 4444);
    REQUIRE(x.green_get() == 2222);
}

TEST_CASE("blue getter"){
    rgbc x(1111, 2222, 3333, 4444);
    REQUIRE(x.blue_get() == 3333);
}

TEST_CASE("clear getter"){
    rgbc x(1111, 2222, 3333, 4444);
    REQUIRE(x.clear_get() == 4444);
}

TEST_CASE("red setter"){
    rgbc x(0, 0, 0, 0);
    x.red_set(1111);
    REQUIRE(x.red_get() == 1111);
}

TEST_CASE("green setter"){
    rgbc x(0, 0, 0, 0);
    x.green_set(2222);
    REQUIRE(x.green_get() == 2222);
}

TEST_CASE("blue setter"){
    rgbc x(0, 0, 0, 0);
    x.blue_set(3333);
    REQUIRE(x.blue_get() == 3333);
}

TEST_CASE("clear setter"){
    rgbc x(0, 0, 0, 0);
    x.clear_set(4444);
    REQUIRE(x.clear_get() == 4444);
}

TEST_CASE("constructor"){
    rgbc x(1111, 2222, 3333, 4444);
    REQUIRE((x.red_get() == 1111 &&
            x.green_get() == 2222 &&
            x.blue_get() == 3333 &&
            x.clear_get() == 4444));
}

TEST_CASE("constructor, empty"){
    rgbc x;
    REQUIRE((x.red_get() == 0 &&
            x.green_get() == 0 &&
            x.blue_get() == 0));
}

TEST_CASE("constructor, partial"){
    rgbc x(1111, 2222);
    REQUIRE((x.red_get() == 1111 &&
            x.green_get() == 2222 &&
            x.blue_get() == 0));
}


TEST_CASE("equality, equal"){
    rgbc x(1111, 2222, 3333, 4444);
    rgbc y(1111, 2222, 3333, 4444);
    REQUIRE(x == y);
}

TEST_CASE("equality, not equal"){
    rgbc x(1111, 2222, 3333, 4444);
    rgbc y(2222, 3333, 4444, 5555);
    REQUIRE_FALSE(x == y);
}

TEST_CASE("add rgbc to rgbc, result == rgbc()"){
    rgbc x(1111, 2222, 3333, 4444);
    rgbc y(2222, 3333, 4444, 5555);
    REQUIRE((x + y) == rgbc(3333, 5555, 7777, 9999));
}

TEST_CASE("add rgbc to rgbc, result == x + y"){
    rgbc x(1111, 2222, 3333, 4444);
    rgbc y(2222, 3333, 4444, 5555);
    rgbc z = x + y;
    REQUIRE(z == rgbc(3333, 5555, 7777, 9999));
}

TEST_CASE("add rgbc into other rgbc (+=)"){
    rgbc x(1111, 2222, 3333, 4444);
    rgbc y(2222, 3333, 4444, 5555);
    x += y;
    REQUIRE(x == rgbc(3333, 5555, 7777, 9999));
}

TEST_CASE("subract rgbc from rgbc, result == rgbc()"){
    rgbc x(2222, 3333, 4444, 5555);
    rgbc y(1111, 2222, 3333, 4444);
    REQUIRE((x - y) == rgbc(1111, 1111, 1111, 1111));
}

TEST_CASE("subtract rgbc from rgbc, result == x + y"){
    rgbc x(2222, 3333, 4444, 5555);
    rgbc y(1111, 2222, 3333, 4444);
    rgbc z = x - y;
    REQUIRE(z == rgbc(1111, 1111, 1111, 1111));
}

TEST_CASE("subtract rgbc from rgbc (-=)"){
    rgbc x(2222, 3333, 4444, 5555);
    rgbc y(1111, 2222, 3333, 4444);
    x -= y;
    REQUIRE(x == rgbc(1111, 1111, 1111, 1111));
}

TEST_CASE("multiply two rgbc values, member"){
    rgbc x(1, 2, 3, 4);
    rgbc y(1, 2, 3, 4);
    rgbc z = x * y;
    REQUIRE(z == rgbc(1, 4, 9, 16));
}

TEST_CASE("multiply rgbc by factor, friend lhs"){
    rgbc x(1, 2, 3, 4);
    rgbc z = x * 2;
    REQUIRE(z == rgbc(2, 4, 6, 8));
}

TEST_CASE("multiply rgbc by factor, friend rhs"){
    rgbc x(1, 2, 3, 4);
    rgbc z = 2 * x;
    REQUIRE(z == rgbc(2, 4, 6, 8));
}

TEST_CASE("multiply rgbc into rgbc (*=)"){
    rgbc x(1, 2, 3, 4);
    rgbc y(1, 2, 3, 4);
    x *= y;
    REQUIRE(x == rgbc(1, 4, 9, 16));
}

TEST_CASE("multiply rgbc by factor (*=)"){
    rgbc x(1, 2, 3, 4);
    x *= 2;
    REQUIRE(x == rgbc(2, 4, 6, 8));
}

TEST_CASE("divide two rgbc values, member"){
    rgbc x(1, 4, 9, 16);
    rgbc y(1, 2, 3, 4);
    rgbc z = x / y;
    REQUIRE(z == rgbc(1, 2, 3, 4));
}

TEST_CASE("divide rgbc by factor, friend lhs"){
    rgbc x(2, 4, 6, 8);
    rgbc z = x / 2;
    REQUIRE(z == rgbc(1, 2, 3, 4));
}

TEST_CASE("divide rgbc into rgbc (/=)"){
    rgbc x(1, 4, 9, 16);
    rgbc y(1, 2, 3, 4);
    x /= y;
    REQUIRE(x == rgbc(1, 2, 3, 4));
}

TEST_CASE("divide rgbc by factor (/=)"){
    rgbc x(2, 4, 6, 8);
    x /= 2;
    REQUIRE(x == rgbc(1, 2, 3, 4));
}

TEST_CASE("bitwise OR rgbc with rgbc"){
    rgbc x(0, 1, 0, 1);
    rgbc y(1, 0, 1, 0);
    rgbc z = x | y;
    REQUIRE(z == rgbc(1, 1, 1, 1));
}

TEST_CASE("bitwise OR rgbc with mask, friend lhs"){
    rgbc x(0, 0, 0, 0);
    rgbc z = x | 0b1;
    REQUIRE(z == rgbc(1, 1, 1, 1));
}

TEST_CASE("bitwise OR rgbc with mask, friend rhs"){
    rgbc x(0, 0, 0, 0);
    rgbc z = 0b1 | x;
    REQUIRE(z == rgbc(1, 1, 1, 1));
}

TEST_CASE("bitwise OR rgbc into rgbc (|=)"){
    rgbc x(0, 1, 0, 1);
    rgbc y(1, 0, 1, 0);
    x |= y;
    REQUIRE(x == rgbc(1, 1, 1, 1));
}

TEST_CASE("bitwise OR mask into rgbc (|=)"){
    rgbc x(0, 0, 0, 0);
    x |= 0b1;
    REQUIRE(x == rgbc(1, 1, 1, 1));
}

TEST_CASE("bitwise AND rgbc with rgbc"){
    rgbc x(0, 1, 0, 1);
    rgbc y(1, 0, 1, 0);
    rgbc z = x & y;
    REQUIRE(z == rgbc(0, 0, 0, 0));
}

TEST_CASE("bitwise AND rgbc with mask, friend lhs"){
    rgbc x(0, 1, 0, 1);
    rgbc z = x & 0b1;
    REQUIRE(z == rgbc(0, 1, 0, 1));
}

TEST_CASE("bitwise AND rgbc with mask, friend rhs"){
    rgbc x(0, 1, 0, 1);
    rgbc z = 0b1010 & x;
    REQUIRE(z == rgbc(0, 0, 0, 0));
}

TEST_CASE("bitwise AND rgbc into rgbc (&=)"){
    rgbc x(0, 1, 0, 1);
    rgbc y(1, 0, 1, 0);
    x &= y;
    REQUIRE(x == rgbc(0, 0, 0, 0));
}

TEST_CASE("bitwise AND mask into rgbc (&=)"){
    rgbc x(0, 1, 0, 1);
    x &= 0b1;
    REQUIRE(x == rgbc(0, 1, 0, 1));
}

TEST_CASE("less than, true"){
    rgbc x(1, 1, 1, 1);
    rgbc y(2, 2, 2, 2);
    REQUIRE(x < y);
}

TEST_CASE("less than, false"){
    rgbc x(1, 1, 1, 1);
    rgbc y(2, 2, 2, 2);
    REQUIRE_FALSE(y < x);
}

TEST_CASE("less or equal to, less than, true"){
    rgbc x(1, 1, 1, 1);
    rgbc y(2, 2, 2, 2);
    REQUIRE(x <= y);
}

TEST_CASE("less or equal to, all equal to, true"){
    rgbc x(1, 1, 1, 1);
    rgbc y(1, 1, 1, 1);
    REQUIRE(x <= y);
}

TEST_CASE("less or equal to, some equal to, true"){
    rgbc x(1, 1, 1, 1);
    rgbc y(2, 1, 2, 1);
    REQUIRE(x <= y);
}

TEST_CASE("less or equal to, less than, false"){
    rgbc x(1, 1, 1, 1);
    rgbc y(2, 2, 2, 2);
    REQUIRE_FALSE(y <= x);
}

TEST_CASE("less or equal to, all equal to, false"){
    rgbc x(1, 1, 1, 1);
    rgbc y(2, 2, 2, 2);
    REQUIRE_FALSE(y <= x);
}

TEST_CASE("less or equal to, some equal to, false"){
    rgbc x(1, 1, 1, 1);
    rgbc y(2, 1, 2, 1);
    REQUIRE_FALSE(y <= x);
}

TEST_CASE("index operator, read"){
    rgbc x(0, 1, 2, 3);
    REQUIRE (x[0] == 0);
    REQUIRE (x[1] == 1);
    REQUIRE (x[2] == 2);
    REQUIRE (x[3] == 3);
}

TEST_CASE("index operator, write"){
    rgbc x(0, 1, 2, 3);
    x[0] = 10;
    x[1] = 20;
    x[2] = 30;
    x[3] = 40;
    REQUIRE (x[0] == 10);
    REQUIRE (x[1] == 20);
    REQUIRE (x[2] == 30);
    REQUIRE (x[3] == 40);
}

TEST_CASE("index operator, out of range"){
    rgbc x(0, 1, 2, 3);
    REQUIRE (x[0] == 0);
    REQUIRE (x[1] == 1);
    REQUIRE (x[2] == 2);
    REQUIRE (x[3] == 3);
    REQUIRE(x[4] == 0);
}

TEST_CASE("insertion operator hwlib::ostream"){
    rgbc x(1, 2, 3, 4);
    hwlib::cout << "\x1b[37;41m MANUAL TEST CASE BECAUSE HWLIB DOESN'T HAVE STRINGSTREAM, PLEASE REVIEW: \x1b[39;49m" << hwlib::endl;
    hwlib::cout << "\x1b[32m" << x << "\x1b[39;49m" << hwlib::endl;
    hwlib::cout << "If you just saw a terminal output \x1b[32m'1;2;3;4' \x1b[39;49m then the << operator is working \x1b[32m correctly! \x1b[39;49m" << hwlib::endl;
    REQUIRE(true);
}