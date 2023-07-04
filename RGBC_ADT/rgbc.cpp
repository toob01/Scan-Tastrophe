#include "rgbc.hpp"

rgbc::rgbc(uint16_t red, uint16_t green, uint16_t blue, uint16_t clear)
    : red(red), green(green), blue(blue), clear(clear) {};

uint16_t rgbc::red_get() const {
    return red;
}

uint16_t rgbc::green_get() const {
    return green;
}

uint16_t rgbc::blue_get() const {
    return blue;
}

uint16_t rgbc::clear_get() const {
    return clear;
}

void rgbc::red_set(uint16_t new_red) {
    red = new_red;
}

void rgbc::green_set(uint16_t new_green) {
    green = new_green;
}

void rgbc::blue_set(uint16_t new_blue) {
    blue = new_blue;
}

void rgbc::clear_set(uint16_t new_clear) {
    clear = new_clear;
}

rgbc rgbc::operator+(const rgbc& rhs) const {
    rgbc result(red + rhs.red_get(), green + rhs.green_get(), blue + rhs.blue_get(), clear + rhs.clear_get());
    return result;
}

rgbc& rgbc::operator+=(const rgbc& rhs) {
    red += rhs.red_get();
    green += rhs.green_get();
    blue += rhs.blue_get();
    clear += rhs.clear_get();
    return * this;
}

rgbc rgbc::operator-(const rgbc& rhs) const {
    rgbc result(red - rhs.red_get(), green - rhs.green_get(), blue - rhs.blue_get(), clear - rhs.clear_get());
    return result;
}

rgbc& rgbc::operator-=(const rgbc& rhs) {
    red -= rhs.red_get();
    green -= rhs.green_get();
    blue -= rhs.blue_get();
    clear -= rhs.clear_get();
    return * this;
}

rgbc rgbc::operator*(const rgbc& rhs) const {
    rgbc result(red * rhs.red_get(), green * rhs.green_get(), blue * rhs.blue_get(), clear * rhs.clear_get());
    return result;
}

rgbc operator*(const rgbc& lhs, const int& factor) {
    rgbc result(lhs.red_get() * factor, lhs.green_get() * factor, lhs.blue_get() * factor, lhs.clear_get() * factor);
    return result;
}

rgbc operator*(const int& factor, const rgbc& rhs) {
    rgbc result(rhs.red_get() * factor, rhs.green_get() * factor, rhs.blue_get() * factor, rhs.clear_get() * factor);
    return result;
}

rgbc& rgbc::operator*=(const rgbc& rhs) {
    red *= rhs.red_get();
    green *= rhs.green_get();
    blue *= rhs.blue_get();
    clear *= rhs.clear_get();
    return * this;
}

rgbc& rgbc::operator*=(const int& factor) {
    red *= factor;
    green *= factor;
    blue *= factor;
    clear *= factor;
    return * this;
}

rgbc rgbc::operator/(const rgbc& rhs) const {
    rgbc result(red / rhs.red_get(), green / rhs.green_get(), blue / rhs.blue_get(), clear / rhs.clear_get());
    return result;
}

rgbc operator/(const rgbc& lhs, const int& factor) {
    rgbc result(lhs.red_get() / factor, lhs.green_get() / factor, lhs.blue_get() / factor, lhs.clear_get() / factor);
    return result;
}

rgbc operator/(const int& factor, const rgbc& rhs) {
    rgbc result(rhs.red_get() / factor, rhs.green_get() / factor, rhs.blue_get() / factor, rhs.clear_get() / factor);
    return result;
}

rgbc& rgbc::operator/=(const rgbc& rhs) {
    red /= rhs.red_get();
    green /= rhs.green_get();
    blue /= rhs.blue_get();
    clear /= rhs.clear_get();
    return * this;
}

rgbc& rgbc::operator/=(const int& factor) {
    red /= factor;
    green /= factor;
    blue /= factor;
    clear /= factor;
    return * this;
}

rgbc rgbc::operator|(const rgbc& rhs) const {
    rgbc result(red | rhs.red_get(), green | rhs.green_get(), blue | rhs.blue_get(), clear | rhs.clear_get());
    return result;
}

rgbc operator|(rgbc lhs, const int& mask) {
    rgbc result(lhs.red_get() | mask, lhs.green_get() | mask, lhs.blue_get() | mask, lhs.clear_get() | mask);
    return result;
}

rgbc operator|(const int& mask, rgbc rhs) {
    rgbc result(rhs.red_get() | mask, rhs.green_get() | mask, rhs.blue_get() | mask, rhs.clear_get() | mask);
    return result;
}

rgbc& rgbc::operator|=(const rgbc& rhs) {
    red |= rhs.red_get();
    green |= rhs.green_get();
    blue |= rhs.blue_get();
    clear |= rhs.clear_get();
    return * this;
}

rgbc& rgbc::operator|=(const int& mask) {
    red |= mask;
    green |= mask;
    blue |= mask;
    clear |= mask;
    return * this;
}

rgbc rgbc::operator&(const rgbc& rhs) const {
    rgbc result(red & rhs.red_get(), green & rhs.green_get(), blue & rhs.blue_get(), clear & rhs.clear_get());
    return result;
}

rgbc operator&(rgbc lhs, const int& mask) {
    rgbc result(lhs.red_get() & mask, lhs.green_get() & mask, lhs.blue_get() & mask, lhs.clear_get() & mask);
    return result;
}

rgbc operator&(const int& mask, rgbc rhs) {
    rgbc result(rhs.red_get() & mask, rhs.green_get() & mask, rhs.blue_get() & mask, rhs.clear_get() & mask);
    return result;
}

rgbc& rgbc::operator&=(const rgbc& rhs) {
    red &= rhs.red_get();
    green &= rhs.green_get();
    blue &= rhs.blue_get();
    clear &= rhs.clear_get();
    return * this;
}

rgbc& rgbc::operator&=(const int& mask) {
    red &= mask;
    green &= mask;
    blue &= mask;
    clear &= mask;
    return * this;
}

bool rgbc::operator==(const rgbc& rhs) const {
    return (
        red == rhs.red_get() &&
        green == rhs.green_get() &&
        blue == rhs.blue_get() &&
        clear == rhs.clear_get()
    );
}

bool rgbc::operator!=(const rgbc& rhs) const {
    return (
        red != rhs.red_get() &&
        green != rhs.green_get() &&
        blue != rhs.blue_get() &&
        clear != rhs.clear_get()
    );
}

bool rgbc::operator<(const rgbc & rhs) const {
    return (
        red < rhs.red_get() &&
        green < rhs.green_get() &&
        blue < rhs.blue_get() &&
        clear < rhs.clear_get()
    );
}

bool rgbc::operator<=(const rgbc & rhs) const {
    return (
        red <= rhs.red_get() &&
        green <= rhs.green_get() &&
        blue <= rhs.blue_get() &&
        clear <= rhs.clear_get()
    );
}

bool rgbc::operator>(const rgbc & rhs) const {
    return (
        red > rhs.red_get() &&
        green > rhs.green_get() &&
        blue > rhs.blue_get() &&
        clear > rhs.clear_get()
    );
}

bool rgbc::operator>=(const rgbc & rhs) const {
    return (
        red >= rhs.red_get() &&
        green >= rhs.green_get() &&
        blue >= rhs.blue_get() &&
        clear >= rhs.clear_get()
    );
}

uint16_t& rgbc::operator[](int index) {
    switch(index){
        case 0:
            return red;
        case 1:
            return green;
        case 2:
            return blue;
        case 3:
            return clear;
        default:
            throw std::out_of_range("Invalid index to rgbc value");
    }
}

std::ostream& operator<<(std::ostream& lhs, const rgbc rhs) {
    return lhs
        << "{ r:"
        << rhs.red_get()
        << ", g:"
        << rhs.green_get()
        << ", b:"
        << rhs.blue_get()
        << ", c:"
        << rhs.clear_get()
        << " }";
}

hwlib::ostream& operator<<(hwlib::ostream & lhs, rgbc rhs) {
        return lhs
        << "{ r:"
        << rhs.red_get()
        << ", g:"
        << rhs.green_get()
        << ", b:"
        << rhs.blue_get()
        << ", c:"
        << rhs.clear_get()
        << " }";
}