// =============================================================
//
// File         : rgbc.hpp
// Copyright    : tobias.bosch@student.hu.nl 2023
//
// Distributed under the Boost Software License, Version 1.0.
// (See https://www.boost.org/LICENSE_1_0.txt)
//
// =============================================================

// this file contains Doxygen comments

#ifndef RGBC_HPP
#define RGBC_HPP

#include <stdint.h>
#include "hwlib.hpp"

/// @file rgbc.hpp

/// @brief
/// RGBC value Abstract DataType
/// @details
/* This is an ADT that represents red, green, blue, and clear colour values in 16-bit unsigned integers.
 * It is primarily expected to be used in combination with the TCS3472 line of colours sensors.
 * Operators included are: +, +=, -, -=, *, *=, /, /=, <<, |, |=, &, &=, <, <=, >, >=, ==, !=, []
 * One constructor is included: (uint16_t, uint16_t, uint16_t, uint16_t), with default values (0, 0, 0, 0)
 * Internal variables red, green, blue, clear are private. Getters and setters are provided. 
 * Dependencies: stdint.h, hwlib.hpp */
class rgbc {
private:
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    uint16_t clear;
public:
    /// @brief 
    /// Constructor from unsigned 8-bit integer values
    /// @details
    /* This constructor initializes an RGBC value collection.
     * The constructor has default values (0, 0, 0, 0), thus allowing for empty initialization.
     * Be mindful when using the empty constructor, as the values (0, 0, 0, 0) are plausible results from your colour sensor. */
    rgbc(uint16_t red = 0, uint16_t green = 0, uint16_t blue = 0, uint16_t clear = 0);

    /// @brief
    /// Getter for red colour value
    uint16_t red_get() const;

    /// @brief 
    /// Getter for green colour value
    uint16_t green_get() const;
    
    /// @brief 
    /// Getter for blue colour value
    uint16_t blue_get() const;
    
    /// @brief 
    /// Getter for clear brightness / combined colour value
    uint16_t clear_get() const;

    /// @brief 
    /// Setter for red colour value
    void red_set(uint16_t new_red);

    /// @brief 
    /// Setter for green colour value 
    void green_set(uint16_t new_green);
    
    /// @brief 
    /// Setter for blue colour value 
    void blue_set(uint16_t new_blue);
    
    /// @brief 
    /// Setter for clear brightness / combined colour value 
    void clear_set(uint16_t new_clear);

    /// @brief 
    /// Add two rgbc values together
    /// @details
    /// This operator+ adds one rgbc value to another, by taking the sum of each corresponding r, g, b, c value.
    /// e.g. rgbc(1, 2, 3, 4) + rgbc(1, 2, 3, 4) = rgbc(2, 4, 6, 8)
    /// @return 
    /// New rgbc object with summed contents
    rgbc operator+(const rgbc & rhs) const;

    /// @brief 
    /// Add one rgbc value into another
    /// @details
    /// This operator+= adds the contents of one rgbc value to another, modifying the original contents of the rgbc value.
    /// @return
    /// Modified rgbc value object by reference
    rgbc& operator+=(const rgbc & rhs);

    /// @brief 
    /// Subract two rgbc values
    /// @details
    /// This operator- subtracts the contents of one rgbc value from another, by taking the difference of each corresponding r, g, b, c value.
    /// @return
    /// New rgbc object with subtracted contents
    rgbc operator-(const rgbc & rhs) const;

    /// @brief 
    /// Subtract an rgbc value from another
    /// @details
    /// This operator-= subtracts the contents of one rgbc value from another, modifying the original contents of the rgbc value.
    /// @return 
    /// Modified rgbc value object by reference
    rgbc& operator-=(const rgbc & rhs);

    /// @brief 
    /// Multiply two rgbc values
    /// @details
    /// This operator* multiplies the contents of one rgbc value by another, by taking the product of each corresponding r, g, b, c value.
    /// e.g. rgbc(1, 2, 3, 4) * rgbc(1, 2, 3, 4) = rgbc(1, 4, 9, 16)
    /// @return 
    /// New rgbc object with multiplied contents
    rgbc operator*(const rgbc & rhs) const;

    /// @brief 
    /// Multiply an rgbc value by a factor
    /// @details
    /// This operator* multiplies the contents of an rgbc value by a given factor, by taking the product of the contents and the factor.
    /// e.g. rgbc(1, 2, 3, 4) * 2 = rgbc(2, 4, 6, 8)
    /// @return   
    /// New rgbc object with multiplied contents
    friend rgbc operator*(const rgbc & lhs, const int & factor);

    /// @brief 
    /// Multiply an rgbc value by a factor : ivnerted parameters
    friend rgbc operator*(const int & factor, const rgbc & rhs);

    /// @brief
    /// Mutiply an rgbc value by another
    /// @details
    /// This operator*= multiplies the contents of one rgbc value by another, modifying the original contents of the rgbc value.
    /// @return
    /// Modified rgbc value object by reference
    rgbc& operator*=(const rgbc & rhs);
    
    /// @brief 
    /// Multiply an rgbc value by a factor, modifying the original
    /// @return   
    /// Modified rgbc value object by reference
    rgbc& operator*=(const int & factor);

    /// @brief 
    /// Divide two rgbc values
    /// @details
    /// This operator/ divides the contents of an rgbc value by another, by taking the quotient of each corresponding r, g, b, c value.
    /// @return   
    /// New rgbc value with divided contents
    rgbc operator/(const rgbc & rhs) const;

    /// @brief 
    /// Divide an rgbc value by a factor
    /// @details
    /// This operator/ divides the contents of an rgbc value by a given factor, by taking the quotient of the contents and the factor.
    /// e.g. rgbc(2, 4, 6, 8) / 2 = rgbc(1, 2, 3, 4)
    /// @return   
    /// New rgbc object with divided contents
    friend rgbc operator/(const rgbc & lhs, const int & factor);

    /// @brief 
    /// Divide an rgbc value by another
    /// @details
    /// This operator/= divides the contents of one rgbc value by another, modifying the original contents of the rgbc value.
    /// @return   
    /// Modified rgbc value object by reference
    rgbc& operator/=(const rgbc & rhs);

    /// @brief 
    /// Divide an rgbc value by a factor, modifying the original
    /// @return   
    /// Modified rgbc value object by refernce
    rgbc& operator/=(const int & factor);

    /// @brief 
    /// Bitwise OR two rgbc values
    /// @details
    /// This operator| performs a Bitwise OR operation on the contents of an rgbc value with another's.
    /// e.g. rgbc(1, 0, 1, 0) | rgbc(0, 1, 0, 1) = rgbc(1, 1, 1, 1)
    /// @return   
    /// New rgbc object with result of Bitwise OR operation
    rgbc operator|(const rgbc & rhs) const;

    /// @brief 
    /// Bitwise OR an rgbc value with an integer mask
    /// @details
    /// This operator| performs a Bitwise OR operation on the contents of an rgbc value with a given mask.
    /// e.g. rgbc(0, 0, 0, 0) | 0b1 = rgbc(1, 1, 1, 1)
    /// @return   
    /// New rgbc object with result of Bitwise OR operation
    friend rgbc operator|(rgbc rhs, const int & mask);

    /// @brief 
    /// Bitwise OR an rgbc value with an integer mask : inverted parameters
    friend rgbc operator|(const int & mask, rgbc rhs);

    /// @brief 
    /// Bitwise OR two rgbc values, modifying the original
    /// @return   
    /// Modified rgbc value object by reference
    rgbc& operator|=(const rgbc & rhs);

    /// @brief 
    /// Bitwise OR an rgbc value with a integer mask, modifying the original
    /// @return   
    /// Modified rgbc value object by reference
    rgbc& operator|=(const int & mask);

    /// @brief 
    /// Bitwise AND two rgbc values
    /// @details
    /// This operator& performs a bitwise AND operation on the contents of an rgbc value with another's.
    /// e.g. rgbc(1, 0, 1, 0) & rgbc(0, 1, 0, 1) = rgbc(0, 0, 0, 0)
    /// @return   
    /// New rgbc object with result of Bitwise AND operation
    rgbc operator&(const rgbc & rhs) const;

    /// @brief 
    /// Bitwise AND an rgbc value with an integer mask
    /// @details
    /// This operator& performs a Bitwise AND operation on the contents of an rgbc value with a given mask.
    /// e.g. rgbc(1, 0, 1, 0) & 0b1 = rgbc(1, 0, 1, 0)
    /// @return   
    /// New rgbc object with result of Bitwise AND operation
    friend rgbc operator&(rgbc rhs, const int & mask);
    
    /// @brief 
    /// Bitwise AND an rgbc value with an integer mask : inverted parameters
    friend rgbc operator&(const int & mask, rgbc rhs);

    /// @brief 
    /// Bitwise AND two rgbc values, modifying the original
    /// @return   
    /// Modified rgbc value object by reference
    rgbc& operator&=(const rgbc & rhs);

    /// @brief 
    /// Bitwise AND an rgbc value with a integer mask, modifying the original
    /// @return   
    /// Modified rgbc value object by reference
    rgbc& operator&=(const int & mask);

    /// @brief 
    /// Compare two rgbc values for equality
    /// @details
    /// This operator== tests for equality between two rgbc values.
    /// If, and only if all corresponding contents are equal, this operator returns true, else it returns false.
    bool operator==(const rgbc & rhs) const;

    /// @brief 
    /// Compare two rgbc values for inequality
    /// @details
    /// This operator!= tests for inequality between two rgbc values.
    /// If, and only if none of the corresponding contents are equal, this operator returns true, else it returns false.
    bool operator!=(const rgbc & rhs) const;

    /// @brief 
    /// Compare two rgbc values for less than
    /// @details
    /// This operator< tests if all contents of an rgbc value are less than the contents of a given rgbc value.
    /// If, and only if all corresponding contents are less than the given contents, this operator returns true, else it returns false.
    bool operator<(const rgbc & rhs) const;

    /// @brief 
    /// Compare two rgbc values for less or equal than
    /// @details
    /// This operator<= tests if all contents of an rgbc value are less than or equal to the contents of a given rgbc value.
    /// If, and only if all corresponding contents are less than or equal to the given contents, this operator returns true, else it returns false.
    bool operator<=(const rgbc & rhs) const;

    /// @brief 
    /// Compare two rgbc values for more than
    /// @details
    /// This operator> tests if all contents of an rgbc value are more than the contents of a given rgbc value.
    /// If, and only if all correspondig contents are more than the given contents, this operator returns true, else it returns false.
    bool operator>(const rgbc & rhs) const;

    /// @brief 
    /// Compare two rgbc values for more or equal than
    /// @details
    /// This operator>= tests if all contents of an rgbc value are more or equal to the contents of a given rgbc value.
    /// If, and only if all corresponding contents are less than or equal to the given contents, this operator returns true, else it returns false.
    bool operator>=(const rgbc & rhs) const;

    /// @brief 
    /// Indexing operator for rgbc value
    /// @details
    /// This operator[] allows for the capability of addressing the contents of an rgbc value by index in order R, G, B, C.
    /// Thus, to address the red, green, blue, and clear values, we can use rgbc[0], rgbc[1], rgbc[2], and rgbc[3] respectively.
    /// NOTE : operator[] does not check if the index you've entered is out of range because bmptk-make does not allow for throwing exceptions by default, instead it will return 0.
    /// @return
    /// Reference to the addressed colour value, or 0 on index out of range
    uint16_t& operator[](int index);

    /// @brief 
    /// Insertion operator for rgbc values, using hwlib::ostream
    /// @details
    /// This operator<< adds the contents of an rgbc value as formatted string to a hwlib::ostream object.
    /// e.g. hwlib::cout << "values : " << rgbc(1, 2, 3, 4) would result in string : "values : 1;2;3;4"
    /// @return   
    /// hwlib::ostream object with added string
    friend hwlib::ostream& operator<<(hwlib::ostream & lhs, rgbc rhs);
};
#endif // RGBC_HPP