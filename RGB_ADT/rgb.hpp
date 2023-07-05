// =============================================================
//
// File         : rgb.hpp
// Copyright    : tobias.bosch@student.hu.nl 2023
//
// Distributed under the Boost Software License, Version 1.0.
// (See https://www.boost.org/LICENSE_1_0.txt)
//
// =============================================================

// this file contains Doxygen comments

#ifndef RGB_HPP
#define RGB_HPP

#include <stdint.h>
#include "hwlib.hpp"

/// @file rgb.hpp

/// @brief
/// RGB value Abstract DataType
/// @details
/* This is an ADT that represents red, green, and clear colour values in 8-bit unsigned integers.
 * It is primarily expected to be used in combination with the TCS3472 line of colours sensors.
 * Operators included are: +, +=, -, -=, *, *=, /, /=, <<, |, |=, &, &=, <, <=, >, >=, ==, !=, []
 * One constructor is included: (uint8_t, uint8_t, uint8_t), with default values (0, 0, 0)
 * Internal variables red, green, blue are private. Getters and setters are provided. 
 * Dependencies: stdint.h, hwlib.hpp */
class rgb {
private:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
public:
    /// @brief 
    /// Constructor from unsigned 8-bit integer values
    /// @details
    /* This constructor initializes an RGB value collection.
     * The constructor has default values (0, 0, 0), thus allowing for empty initialization.
     * Be mindful when using the empty constructor, as the values (0, 0, 0) are plausible results from your colour sensor. */
    rgb(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0);

    /// @brief
    /// Getter for red colour value
    uint8_t red_get() const;

    /// @brief 
    /// Getter for green colour value
    uint8_t green_get() const;
    
    /// @brief 
    /// Getter for blue colour value
    uint8_t blue_get() const;

    /// @brief 
    /// Setter for red colour value
    void red_set(uint8_t new_red);

    /// @brief 
    /// Setter for green colour value 
    void green_set(uint8_t new_green);
    
    /// @brief 
    /// Setter for blue colour value 
    void blue_set(uint8_t new_blue);

    /// @brief 
    /// Add two rgb values together
    /// @details
    /// This operator+ adds one rgb value to another, by taking the sum of each corresponding r, g, b value.
    /// e.g. rgb(1, 2, 3) + rgb(1, 2, 3) = rgb(2, 4, 6)
    /// @return 
    /// New rgb object with summed contents
    rgb operator+(const rgb & rhs) const;

    /// @brief 
    /// Add one rgb value into another
    /// @details
    /// This operator+= adds the contents of one rgb value to another, modifying the original contents of the rgb value.
    /// @return
    /// Modified rgb value object by reference
    rgb& operator+=(const rgb & rhs);

    /// @brief 
    /// Subract two rgb values
    /// @details
    /// This operator- subtracts the contents of one rgb value from another, by taking the difference of each corresponding r, g, b value.
    /// @return
    /// New rgb object with subtracted contents
    rgb operator-(const rgb & rhs) const;

    /// @brief 
    /// Subtract an rgb value from another
    /// @details
    /// This operator-= subtracts the contents of one rgb value from another, modifying the original contents of the rgb value.
    /// @return 
    /// Modified rgb value object by reference
    rgb& operator-=(const rgb & rhs);

    /// @brief 
    /// Multiply two rgb values
    /// @details
    /// This operator* multiplies the contents of one rgb value by another, by taking the product of each corresponding r, g, b value.
    /// e.g. rgb(1, 2, 3) * rgb(1, 2, 3) = rgb(1, 4, 9)
    /// @return 
    /// New rgb object with multiplied contents
    rgb operator*(const rgb & rhs) const;

    /// @brief 
    /// Multiply an rgb value by a factor
    /// @details
    /// This operator* multiplies the contents of an rgb value by a given factor, by taking the product of the contents and the factor.
    /// e.g. rgb(1, 2, 3) * 2 = rgb(2, 4, 6)
    /// @return   
    /// New rgb object with multiplied contents
    friend rgb operator*(const rgb & lhs, const int & factor);

    /// @brief 
    /// Multiply an rgb value by a factor : ivnerted parameters
    friend rgb operator*(const int & factor, const rgb & rhs);

    /// @brief
    /// Mutiply an rgb value by another
    /// @details
    /// This operator*= multiplies the contents of one rgb value by another, modifying the original contents of the rgb value.
    /// @return
    /// Modified rgb value object by reference
    rgb& operator*=(const rgb & rhs);
    
    /// @brief 
    /// Multiply an rgb value by a factor, modifying the original
    /// @return   
    /// Modified rgb value object by reference
    rgb& operator*=(const int & factor);

    /// @brief 
    /// Divide two rgb values
    /// @details
    /// This operator/ divides the contents of an rgb value by another, by taking the quotient of each corresponding r, g, b value.
    /// @return   
    /// New rgb value with divided contents
    rgb operator/(const rgb & rhs) const;

    /// @brief 
    /// Divide an rgb value by a factor
    /// @details
    /// This operator/ divides the contents of an rgb value by a given factor, by taking the quotient of the contents and the factor.
    /// e.g. rgb(2, 4, 6) / 2 = rgb(1, 2, 3)
    /// @return   
    /// New rgb object with divided contents
    friend rgb operator/(const rgb & lhs, const int & factor);

    /// @brief 
    /// Divide an rgb value by another
    /// @details
    /// This operator/= divides the contents of one rgb value by another, modifying the original contents of the rgb value.
    /// @return   
    /// Modified rgb value object by reference
    rgb& operator/=(const rgb & rhs);

    /// @brief 
    /// Divide an rgb value by a factor, modifying the original
    /// @return   
    /// Modified rgb value object by refernce
    rgb& operator/=(const int & factor);

    /// @brief 
    /// Bitwise OR two rgb values
    /// @details
    /// This operator| performs a Bitwise OR operation on the contents of an rgb value with another's.
    /// e.g. rgb(1, 0, 1) | rgb(0, 1, 0) = rgb(1, 1, 1)
    /// @return   
    /// New rgb object with result of Bitwise OR operation
    rgb operator|(const rgb & rhs) const;

    /// @brief 
    /// Bitwise OR an rgb value with an integer mask
    /// @details
    /// This operator| performs a Bitwise OR operation on the contents of an rgb value with a given mask.
    /// e.g. rgb(0, 0, 0) | 0b1 = rgb(1, 1, 1)
    /// @return   
    /// New rgb object with result of Bitwise OR operation
    friend rgb operator|(rgb rhs, const int & mask);

    /// @brief 
    /// Bitwise OR an rgb value with an integer mask : inverted parameters
    friend rgb operator|(const int & mask, rgb rhs);

    /// @brief 
    /// Bitwise OR two rgb values, modifying the original
    /// @return   
    /// Modified rgb value object by reference
    rgb& operator|=(const rgb & rhs);

    /// @brief 
    /// Bitwise OR an rgb value with a integer mask, modifying the original
    /// @return   
    /// Modified rgb value object by reference
    rgb& operator|=(const int & mask);

    /// @brief 
    /// Bitwise AND two rgb values
    /// @details
    /// This operator& performs a bitwise AND operation on the contents of an rgb value with another's.
    /// e.g. rgb(1, 0, 1) & rgb(0, 1, 0) = rgb(0, 0, 0)
    /// @return   
    /// New rgb object with result of Bitwise AND operation
    rgb operator&(const rgb & rhs) const;

    /// @brief 
    /// Bitwise AND an rgb value with an integer mask
    /// @details
    /// This operator& performs a Bitwise AND operation on the contents of an rgb value with a given mask.
    /// e.g. rgb(1, 0, 1, 0) & 0b1 = rgb(1, 0, 1)
    /// @return   
    /// New rgb object with result of Bitwise AND operation
    friend rgb operator&(rgb rhs, const int & mask);
    
    /// @brief 
    /// Bitwise AND an rgb value with an integer mask : inverted parameters
    friend rgb operator&(const int & mask, rgb rhs);

    /// @brief 
    /// Bitwise AND two rgb values, modifying the original
    /// @return   
    /// Modified rgb value object by reference
    rgb& operator&=(const rgb & rhs);

    /// @brief 
    /// Bitwise AND an rgb value with a integer mask, modifying the original
    /// @return   
    /// Modified rgb value object by reference
    rgb& operator&=(const int & mask);

    /// @brief 
    /// Compare two rgb values for equality
    /// @details
    /// This operator== tests for equality between two rgb values.
    /// If, and only if all corresponding contents are equal, this operator returns true, else it returns false.
    bool operator==(const rgb & rhs) const;

    /// @brief 
    /// Compare two rgb values for inequality
    /// @details
    /// This operator!= tests for inequality between two rgb values.
    /// If, and only if none of the corresponding contents are equal, this operator returns true, else it returns false.
    bool operator!=(const rgb & rhs) const;

    /// @brief 
    /// Compare two rgb values for less than
    /// @details
    /// This operator< tests if all contents of an rgb value are less than the contents of a given rgb value.
    /// If, and only if all corresponding contents are less than the given contents, this operator returns true, else it returns false.
    bool operator<(const rgb & rhs) const;

    /// @brief 
    /// Compare two rgb values for less or equal than
    /// @details
    /// This operator<= tests if all contents of an rgb value are less than or equal to the contents of a given rgb value.
    /// If, and only if all corresponding contents are less than or equal to the given contents, this operator returns true, else it returns false.
    bool operator<=(const rgb & rhs) const;

    /// @brief 
    /// Compare two rgb values for more than
    /// @details
    /// This operator> tests if all contents of an rgb value are more than the contents of a given rgb value.
    /// If, and only if all correspondig contents are more than the given contents, this operator returns true, else it returns false.
    bool operator>(const rgb & rhs) const;

    /// @brief 
    /// Compare two rgb values for more or equal than
    /// @details
    /// This operator>= tests if all contents of an rgb value are more or equal to the contents of a given rgb value.
    /// If, and only if all corresponding contents are less than or equal to the given contents, this operator returns true, else it returns false.
    bool operator>=(const rgb & rhs) const;

    /// @brief 
    /// Indexing operator for rgb value
    /// @details
    /// This operator[] allows for the capability of addressing the contents of an rgb value by index in order R, G, B.
    /// Thus, to address the red, green, and blue values, we can use rgb[0], rgb[1], and rgb[2] respectively.
    /// NOTE : operator[] does not check if the index you've entered is out of range because bmptk-make does not allow for throwing exceptions by default, instead it will return 0.
    /// @return
    /// Reference to the addressed colour value, or 0 on index out of range
    uint8_t& operator[](int index);

    /// @brief 
    /// Insertion operator for rgb values, using hwlib::ostream
    /// @details
    /// This operator<< adds the contents of an rgb value as formatted string to a hwlib::ostream object.
    /// e.g. hwlib::cout << "values : " << rgb(1, 2, 3); would result in string : "values : 1;2;3"
    /// @return   
    /// hwlib::ostream object with added string
    friend hwlib::ostream& operator<<(hwlib::ostream & lhs, rgb rhs);
};
#endif // RGB_HPP