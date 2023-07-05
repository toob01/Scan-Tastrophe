// =============================================================
//
// File         : rgb.cpp
// Copyright    : tobias.bosch@student.hu.nl 2023
//
// Distributed under the Boost Software License, Version 1.0.
// (See https://www.boost.org/LICENSE_1_0.txt)
//
// =============================================================

/// @file rgb.cpp

#include "rgb.hpp"

rgb::rgb(uint8_t red, uint8_t green, uint8_t blue)
    : red(red), green(green), blue(blue) {};

uint8_t rgb::red_get() const {
    return red;
}

uint8_t rgb::green_get() const {
    return green;
}

uint8_t rgb::blue_get() const {
    return blue;
}

void rgb::red_set(uint8_t new_red) {
    red = new_red;
}

void rgb::green_set(uint8_t new_green) {
    green = new_green;
}

void rgb::blue_set(uint8_t new_blue) {
    blue = new_blue;
}

rgb rgb::operator+(const rgb& rhs) const {
    rgb result(red + rhs.red_get(), green + rhs.green_get(), blue + rhs.blue_get());
    return result;
}

rgb& rgb::operator+=(const rgb& rhs) {
    red += rhs.red_get();
    green += rhs.green_get();
    blue += rhs.blue_get();
    return * this;
}

rgb rgb::operator-(const rgb& rhs) const {
    rgb result(red - rhs.red_get(), green - rhs.green_get(), blue - rhs.blue_get());
    return result;
}

rgb& rgb::operator-=(const rgb& rhs) {
    red -= rhs.red_get();
    green -= rhs.green_get();
    blue -= rhs.blue_get();
    return * this;
}

rgb rgb::operator*(const rgb& rhs) const {
    rgb result(red * rhs.red_get(), green * rhs.green_get(), blue * rhs.blue_get());
    return result;
}

rgb operator*(const rgb& lhs, const int& factor) {
    rgb result(lhs.red_get() * factor, lhs.green_get() * factor, lhs.blue_get() * factor);
    return result;
}

rgb operator*(const int& factor, const rgb& rhs) {
    rgb result(rhs.red_get() * factor, rhs.green_get() * factor, rhs.blue_get() * factor);
    return result;
}

rgb& rgb::operator*=(const rgb& rhs) {
    red *= rhs.red_get();
    green *= rhs.green_get();
    blue *= rhs.blue_get();
    return * this;
}

rgb& rgb::operator*=(const int& factor) {
    red *= factor;
    green *= factor;
    blue *= factor;
    return * this;
}

rgb rgb::operator/(const rgb& rhs) const {
    rgb result(red / rhs.red_get(), green / rhs.green_get(), blue / rhs.blue_get());
    return result;
}

rgb operator/(const rgb& lhs, const int& factor) {
    rgb result(lhs.red_get() / factor, lhs.green_get() / factor, lhs.blue_get() / factor);
    return result;
}

rgb& rgb::operator/=(const rgb& rhs) {
    red /= rhs.red_get();
    green /= rhs.green_get();
    blue /= rhs.blue_get();
    return * this;
}

rgb& rgb::operator/=(const int& factor) {
    red /= factor;
    green /= factor;
    blue /= factor;;
    return * this;
}

rgb rgb::operator|(const rgb& rhs) const {
    rgb result(red | rhs.red_get(), green | rhs.green_get(), blue | rhs.blue_get());
    return result;
}

rgb operator|(rgb lhs, const int& mask) {
    rgb result(lhs.red_get() | mask, lhs.green_get() | mask, lhs.blue_get() | mask);
    return result;
}

rgb operator|(const int& mask, rgb rhs) {
    rgb result(rhs.red_get() | mask, rhs.green_get() | mask, rhs.blue_get() | mask);
    return result;
}

rgb& rgb::operator|=(const rgb& rhs) {
    red |= rhs.red_get();
    green |= rhs.green_get();
    blue |= rhs.blue_get();
    return * this;
}

rgb& rgb::operator|=(const int& mask) {
    red |= mask;
    green |= mask;
    blue |= mask;
    return * this;
}

rgb rgb::operator&(const rgb& rhs) const {
    rgb result(red & rhs.red_get(), green & rhs.green_get(), blue & rhs.blue_get());
    return result;
}

rgb operator&(rgb lhs, const int& mask) {
    rgb result(lhs.red_get() & mask, lhs.green_get() & mask, lhs.blue_get() & mask);
    return result;
}

rgb operator&(const int& mask, rgb rhs) {
    rgb result(rhs.red_get() & mask, rhs.green_get() & mask, rhs.blue_get() & mask);
    return result;
}

rgb& rgb::operator&=(const rgb& rhs) {
    red &= rhs.red_get();
    green &= rhs.green_get();
    blue &= rhs.blue_get();
    return * this;
}

rgb& rgb::operator&=(const int& mask) {
    red &= mask;
    green &= mask;
    blue &= mask;
    return * this;
}

bool rgb::operator==(const rgb& rhs) const {
    return (
        red == rhs.red_get() &&
        green == rhs.green_get() &&
        blue == rhs.blue_get()
    );
}

bool rgb::operator!=(const rgb& rhs) const {
    return (
        red != rhs.red_get() &&
        green != rhs.green_get() &&
        blue != rhs.blue_get()
    );
}

bool rgb::operator<(const rgb & rhs) const {
    return (
        red < rhs.red_get() &&
        green < rhs.green_get() &&
        blue < rhs.blue_get()
    );
}

bool rgb::operator<=(const rgb & rhs) const {
    return (
        red <= rhs.red_get() &&
        green <= rhs.green_get() &&
        blue <= rhs.blue_get()
    );
}

bool rgb::operator>(const rgb & rhs) const {
    return (
        red > rhs.red_get() &&
        green > rhs.green_get() &&
        blue > rhs.blue_get()
    );
}

bool rgb::operator>=(const rgb & rhs) const {
    return (
        red >= rhs.red_get() &&
        green >= rhs.green_get() &&
        blue >= rhs.blue_get()
    );
}

uint8_t& rgb::operator[](int index) {
    static uint8_t null = 0;
    switch(index){
        case 0:
            return red;
        case 1:
            return green;
        case 2:
            return blue;
        default:
            return null;
    }
}

hwlib::ostream& operator<<(hwlib::ostream & lhs, rgb rhs) {
        return lhs
        << rhs.red_get()
        << ";"
        << rhs.green_get()
        << ";"
        << rhs.blue_get();
}