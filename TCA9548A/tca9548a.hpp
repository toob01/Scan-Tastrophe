// =============================================================
//
// File         : tca9458a.hpp
// Copyright    : tobias.bosch@student.hu.nl 2023
//
// Distributed under the Boost Software License, Version 1.0.
// (See https://www.boost.org/LICENSE_1_0.txt)
//
// =============================================================

// this file contains Doxygen comments

#ifndef TCA9458A_HPP
#define TCA9458A_HPP
#include "hwlib.hpp"

/// @file tca9458a.hpp

/// @brief 
/// Simple class to use tca9548a 8-output I2C multiplexer
/// @details
/// Very simple implementation of communication with the tca9548a I2C multiplexer
/// Provides one constructor: (hwlib::i2c_bus, uint8_t)
/// Address of device can be specified
class tca9548a {
private:
    hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus;
    const uint8_t address;
public:
    /// @brief
    /// Construct from hwlib i2c bus object and 8-bit i2c address
    tca9548a(hwlib::i2c_bus_bit_banged_scl_sda & c_i2c_bus, uint8_t c_address):
        i2c_bus(c_i2c_bus),
        address(c_address)
        {};
    
    /// @brief 
    /// Select multiplexer output 0 through 7
    /// @return
    /// -1 on invalid selection, selected output on success
    int select(int output){
        if (output > 7) return -1;
        
        auto trans = hwlib::i2c_write_transaction(i2c_bus, address);
        trans.write(1 << output);
        return output;
    };
}; // class tca9548a
#endif // TCA9458A_HPP
