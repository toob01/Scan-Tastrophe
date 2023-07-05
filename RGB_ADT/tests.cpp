#include "catch.hpp"
#include "rgb.hpp"

TEST_CASE("red getter"){
    rgb x(1, 2, 3);
    REQUIRE(x.red_get() == 1);
}

TEST_CASE("green getter"){
    rgb x(1, 2, 3);
    REQUIRE(x.green_get() == 2);
}

TEST_CASE("blue getter"){
    rgb x(1, 2, 3);
    REQUIRE(x.blue_get() == 3);
}

TEST_CASE("red setter"){
    rgb x(0, 0, 0);
    x.red_set(1);
    REQUIRE(x.red_get() == 1);
}

TEST_CASE("green setter"){
    rgb x(0, 0, 0);
    x.green_set(2);
    REQUIRE(x.green_get() == 2);
}

TEST_CASE("blue setter"){
    rgb x(0, 0, 0);
    x.blue_set(3);
    REQUIRE(x.blue_get() == 3);
}

TEST_CASE("constructor, explicit values"){
    rgb x(1, 2, 3);
    REQUIRE((x.red_get() == 1 &&
            x.green_get() == 2 &&
            x.blue_get() == 3));
}

TEST_CASE("constructor, empty"){
    rgb x;
    REQUIRE((x.red_get() == 0 &&
            x.green_get() == 0 &&
            x.blue_get() == 0));
}

TEST_CASE("constructor, partial"){
    rgb x(1, 2);
    REQUIRE((x.red_get() == 1 &&
            x.green_get() == 2 &&
            x.blue_get() == 0));
}

TEST_CASE("equality, equal"){
    rgb x(1, 2, 3);
    rgb y(1, 2, 3);
    REQUIRE(x == y);
}

TEST_CASE("equality, not equal"){
    rgb x(1, 2, 3);
    rgb y(2, 3, 4);
    REQUIRE_FALSE(x == y);
}

TEST_CASE("add rgb to rgb, result == rgb()"){
    rgb x(1, 2, 3);
    rgb y(2, 3, 4);
    REQUIRE((x + y) == rgb(3, 5, 7));
}

TEST_CASE("add rgb to rgb, result == x + y"){
    rgb x(1, 2, 3);
    rgb y(2, 3, 4);
    rgb z = x + y;
    REQUIRE(z == rgb(3, 5, 7));
}

TEST_CASE("add rgb into other rgb (+=)"){
    rgb x(1, 2, 3);
    rgb y(2, 3, 4);
    x += y;
    REQUIRE(x == rgb(3, 5, 7));
}

TEST_CASE("subract rgb from rgb, result == rgb()"){
    rgb x(2, 3, 4);
    rgb y(1, 2, 3);
    REQUIRE((x - y) == rgb(1, 1, 1));
}

TEST_CASE("subtract rgb from rgb, result == x + y"){
    rgb x(2, 3, 4);
    rgb y(1, 2, 3);
    rgb z = x - y;
    REQUIRE(z == rgb(1, 1, 1));
}

TEST_CASE("subtract rgb from rgb (-=)"){
    rgb x(2, 3, 4);
    rgb y(1, 2, 3);
    x -= y;
    REQUIRE(x == rgb(1, 1, 1));
}

TEST_CASE("multiply two rgb values, member"){
    rgb x(1, 2, 3);
    rgb y(1, 2, 3);
    rgb z = x * y;
    REQUIRE(z == rgb(1, 4, 9));
}

TEST_CASE("multiply rgb by factor, friend lhs"){
    rgb x(1, 2, 3);
    rgb z = x * 2;
    REQUIRE(z == rgb(2, 4, 6));
}

TEST_CASE("multiply rgb by factor, friend rhs"){
    rgb x(1, 2, 3);
    rgb z = 2 * x;
    REQUIRE(z == rgb(2, 4, 6));
}

TEST_CASE("multiply rgb into rgb (*=)"){
    rgb x(1, 2, 3);
    rgb y(1, 2, 3);
    x *= y;
    REQUIRE(x == rgb(1, 4, 9));
}

TEST_CASE("multiply rgb by factor (*=)"){
    rgb x(1, 2, 3);
    x *= 2;
    REQUIRE(x == rgb(2, 4, 6));
}

TEST_CASE("divide two rgb values, member"){
    rgb x(1, 4, 9);
    rgb y(1, 2, 3);
    rgb z = x / y;
    REQUIRE(z == rgb(1, 2, 3));
}

TEST_CASE("divide rgb by factor, friend lhs"){
    rgb x(2, 4, 6);
    rgb z = x / 2;
    REQUIRE(z == rgb(1, 2, 3));
}

TEST_CASE("divide rgb into rgb (/=)"){
    rgb x(1, 4, 9);
    rgb y(1, 2, 3);
    x /= y;
    REQUIRE(x == rgb(1, 2, 3));
}

TEST_CASE("divide rgb by factor (/=)"){
    rgb x(2, 4, 6);
    x /= 2;
    REQUIRE(x == rgb(1, 2, 3));
}

TEST_CASE("bitwise OR rgb with rgb"){
    rgb x(0, 1, 0);
    rgb y(1, 0, 1);
    rgb z = x | y;
    REQUIRE(z == rgb(1, 1, 1));
}

TEST_CASE("bitwise OR rgb with mask, friend lhs"){
    rgb x(0, 0, 0);
    rgb z = x | 0b1;
    REQUIRE(z == rgb(1, 1, 1));
}

TEST_CASE("bitwise OR rgb with mask, friend rhs"){
    rgb x(0, 0, 0);
    rgb z = 0b1 | x;
    REQUIRE(z == rgb(1, 1, 1));
}

TEST_CASE("bitwise OR rgb into rgb (|=)"){
    rgb x(0, 1, 0);
    rgb y(1, 0, 1);
    x |= y;
    REQUIRE(x == rgb(1, 1, 1));
}

TEST_CASE("bitwise OR mask into rgb (|=)"){
    rgb x(0, 0, 0);
    x |= 0b1;
    REQUIRE(x == rgb(1, 1, 1));
}

TEST_CASE("bitwise AND rgb with rgb"){
    rgb x(0, 1, 0);
    rgb y(1, 0, 1);
    rgb z = x & y;
    REQUIRE(z == rgb(0, 0, 0));
}

TEST_CASE("bitwise AND rgb with mask, friend lhs"){
    rgb x(0, 1, 0);
    rgb z = x & 0b1;
    REQUIRE(z == rgb(0, 1, 0));
}

TEST_CASE("bitwise AND rgb with mask, friend rhs"){
    rgb x(0, 1, 0);
    rgb z = 0b1010 & x;
    REQUIRE(z == rgb(0, 0, 0));
}

TEST_CASE("bitwise AND rgb into rgb (&=)"){
    rgb x(0, 1, 0);
    rgb y(1, 0, 1);
    x &= y;
    REQUIRE(x == rgb(0, 0, 0));
}

TEST_CASE("bitwise AND mask into rgb (&=)"){
    rgb x(0, 1, 0);
    x &= 0b1;
    REQUIRE(x == rgb(0, 1, 0));
}

TEST_CASE("less than, true"){
    rgb x(1, 1, 1);
    rgb y(2, 2, 2);
    REQUIRE(x < y);
}

TEST_CASE("less than, false"){
    rgb x(1, 1, 1);
    rgb y(2, 2, 2);
    REQUIRE_FALSE(y < x);
}

TEST_CASE("less or equal to, less than, true"){
    rgb x(1, 1, 1);
    rgb y(2, 2, 2);
    REQUIRE(x <= y);
}

TEST_CASE("less or equal to, all equal to, true"){
    rgb x(1, 1, 1);
    rgb y(1, 1, 1);
    REQUIRE(x <= y);
}

TEST_CASE("less or equal to, some equal to, true"){
    rgb x(1, 1, 1);
    rgb y(2, 1, 2);
    REQUIRE(x <= y);
}

TEST_CASE("less or equal to, less than, false"){
    rgb x(1, 1, 1);
    rgb y(2, 2, 2);
    REQUIRE_FALSE(y <= x);
}

TEST_CASE("less or equal to, all equal to, false"){
    rgb x(1, 1, 1);
    rgb y(2, 2, 2);
    REQUIRE_FALSE(y <= x);
}

TEST_CASE("less or equal to, some equal to, false"){
    rgb x(1, 1, 1);
    rgb y(2, 1, 2);
    REQUIRE_FALSE(y <= x);
}

TEST_CASE("index operator, read"){
    rgb x(0, 1, 2);
    REQUIRE (x[0] == 0);
    REQUIRE (x[1] == 1);
    REQUIRE (x[2] == 2);
}

TEST_CASE("index operator, write"){
    rgb x(0, 1, 2);
    x[0] = 10;
    x[1] = 20;
    x[2] = 30;
    REQUIRE (x[0] == 10);
    REQUIRE (x[1] == 20);
    REQUIRE (x[2] == 30);
}

TEST_CASE("index operator, out of range"){
    rgb x(0, 1, 2);
    REQUIRE (x[0] == 0);
    REQUIRE (x[1] == 1);
    REQUIRE (x[2] == 2);
    REQUIRE(x[3] == 0);
}

TEST_CASE("insertion operator hwlib::ostream"){
    rgb x(1, 2, 3);
    hwlib::cout << "\x1b[37;41m MANUAL TEST CASE BECAUSE HWLIB DOESN'T HAVE STRINGSTREAM, PLEASE REVIEW: \x1b[39;49m" << hwlib::endl;
    hwlib::cout << "\x1b[32m" << x << "\x1b[39;49m" << hwlib::endl;
    hwlib::cout << "If you just saw a terminal output \x1b[32m'1;2;3' \x1b[39;49m then the << operator is working \x1b[32m correctly! \x1b[39;49m" << hwlib::endl;
    REQUIRE(true);
}