#include "rgbc.hpp"

rgbc::rgbc(uint16_t red, uint16_t green, uint16_t blue, uint16_t clear)
    : red(red), green(green), blue(blue), clear(clear) {};

uint16_t rgbc::red_get() const {
    
}

uint16_t rgbc::green_get() const {
    
}

uint16_t rgbc::blue_get() const {
    
}

uint16_t rgbc::clear_get() const {
    
}

void rgbc::red_set(uint16_t new_red) {
    
}

void rgbc::green_set(uint16_t new_green) {
    
}

void rgbc::blue_set(uint16_t new_blue) {
    
}

void rgbc::clear_set(uint16_t new_clear) {
    
}

rgbc rgbc::operator+(const rgbc& rhs) const {
    
}

rgbc& rgbc::operator+=(const rgbc& rhs) {
    
}

rgbc rgbc::operator-(const rgbc& rhs) const {
    
}

rgbc& rgbc::operator-=(const rgbc& rhs) {
    
}

rgbc rgbc::operator*(const rgbc& rhs) const {
    
}

rgbc operator*(const rgbc& lhs, const int& factor) {
    
}

rgbc operator*(const int& factor, const rgbc& rhs) {
    
}

rgbc& rgbc::operator*=(const rgbc& rhs) {
    
}

rgbc& operator*=(const int& factor, const rgbc& rhs) {
    
}

rgbc rgbc::operator/(const rgbc& rhs) const {
    
}

rgbc& operator/(const rgbc& lhs, const int& factor) {
    
}

rgbc& operator/(const int& factor, const rgbc& rhs) {
    
}

rgbc& rgbc::operator/=(const rgbc& rhs) {
    
}

rgbc& operator/=(const int& factor, const rgbc& rhs) {
    
}

rgbc rgbc::operator|(const rgbc& rhs) const {
    
}

rgbc operator|(rgbc lhs, const int& mask) {
    
}

rgbc operator|(const int& mask, rgbc rhs) {
    
}

rgbc& rgbc::operator|=(const rgbc& rhs) {
    
}

rgbc& operator|=(rgbc& lhs, const int& mask) {
    
}

rgbc rgbc::operator&(const rgbc& rhs) const {
    
}

rgbc operator&(rgbc lhs, const int& mask) {
    
}

rgbc operator&(const int& mask, rgbc rhs) {
    
}

rgbc& rgbc::operator&=(const rgbc& rhs) {
    
}

rgbc& operator&=(rgbc& lhs, const int& mask) {
    
}

bool rgbc::operator==(const rgbc& rhs) const {
    
}

bool rgbc::operator!=(const rgbc& rhs) const {
    
}

std::ostream& operator<<(std::ostream& os, const rgbc& color) {
    
}