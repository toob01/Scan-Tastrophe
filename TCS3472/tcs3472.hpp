// =============================================================
//
// File         : tca3472.hpp
// Copyright    : tobias.bosch@student.hu.nl 2023
//
// Distributed under the Boost Software License, Version 1.0.
// (See https://www.boost.org/LICENSE_1_0.txt)
//
// =============================================================

// this file contains Doxygen comments
/// @file

#ifndef TCS3472_HPP 
#define TCS3472_HPP

/// includes
#include "hwlib.hpp"

/// Color register (low bit) address definitions
#define RDATA 0x16
#define BDATA 0x18
#define GDATA 0x1A
#define CDATA 0x14

/// Optional high bit address definitions
#define H_CDATA 0x15
#define H_RDATA 0x17
#define H_BDATA 0x19
#define H_GDATA 0x1B

/// Device configuration register address definitions
#define ENABLE 0x00
#define ATIME 0x01
#define WTIME 0x03
#define WLONG 0x0D
#define AGAIN 0x0F
#define STATUS 0x13

/// Enable register options
#define SET_WEN 0x08
#define SET_AEN 0x02
#define SET_PON 0x01

/// integration time definitions
#define SET_ATIME_2_4MS 0xFF
#define SET_ATIME_24MS 0xF6
#define SET_ATIME_50MS 0xEB
#define SET_ATIME_101MS 0xD5
#define SET_ATIME_154MS 0xC0
#define SET_ATIME_700MS 0x00

/// wait time definitions
#define SET_WTIME_2_4MS 0xFF
#define SET_WTIME_204MS 0xAB
#define SET_WTIME_614MS 0x00

/// wlong setting definition
#define SET_WLONG 0x02

/// gain definitions
#define SET_AGAIN_1X 0x00
#define SET_AGAIN_4X 0x01
#define SET_AGAIN_16X 0x02
#define SET_AGAIN_60X 0x03


/// \brief
/// Interface for TCS3472(5) color sensor using (abstractions and functions from) HWLIB
/// \details
/// This class provides an interface for the TCS3472(5) color sensor
/// This implementation only works for sensors with I2C address 0x29, which most of these sensors will have.
/// To use this sensor in amounts more than one or with other devices that have the same address, you have the option to either define multiple I2C busses, or use an I2C multiplexer like the TCA9548A (I recommend the latter).
/// If you happen to have a sensor that has a discrepant address, please contact me at tobias.bosch@student.hu.nl, I am happy to offer assistance :)
/// This library provides no capabilities for the interrupt output that some TCS3472 devices may have.

class tcs3472 {
private:
    hwlib::i2c_bus & bus;
    const uint8_t tcs = 0x29;
public:
    /// \brief
    /// Constructor for tcs3472 color sensor 
    /// \details
    /// This constructor creates an interface for the tcs3472 color sensor IC.
    /// Default values are:
    ///     - ENABLE    : AEN | WEN
    ///     - ATIME     : 2.4 ms
    ///     - WTIME     : 2.4 ms
    ///     - AGAIN     : 4X
    tcs3472(hwlib::i2c_bus & bus, uint8_t enable_option=SET_AEN|SET_WEN, uint8_t atime_option=SET_ATIME_2_4MS, uint8_t wtime_option=SET_WTIME_2_4MS, uint8_t again_option=SET_AGAIN_4X);
    
    /// Destructor for tcs3472 color sensor, resets all configurations to factory values.
    ~tcs3472();
    
    /// Start a sense cycle
    void start();
    
    /// Read a register specified by address
    int read_register(uint8_t reg_address, uint8_t );
    
    /// Read 16-bit data from Clear data register
    int read_clear();
    
    /// Read 16-bit data from Red data register
    int read_red();
    
    /// Read 16-bit data from Green data register
    int read_green();
    
    /// Read 16-bit data from Blue data register
    int read_blue();
    
    /// \brief
    /// Read raw data from clear, red, green, and blue registers
    /// \return
    /// Returns an array of integers, indeces 0, 1, 2, 3 being C, R, G, and B respectively.
    int[] get_rgb();
    
    /// \brief
    /// Read data fron clear, red, green, and blue registers converted to explicit 8-bit values.
    /// \return
    /// Returns an array of 8-bit values, indeces 0, 1, 2, 3 being C, R, G, and B respectively.
    uint8_t[] get_rgb_8bit();
    
    /// \brief
    /// Test if color sensor is available on I2C bus and functional.
    /// \details
    /// Execute a self-test program that reads the Device ID, tries to set certain configuration values and reads if said values are actually stored in the corresponding registers,
    /// and tests if the color sensor functions by executing two cycles and checking if values change between cycles
    /// Execution is terminated immediately if an error occurs, error codes correspond to:
    ///     - 0 : no errors
    ///     - 1 : problem with I2C communication
    ///     - 2 : unknown device ID
    ///     - 3 : error with enable register
    ///     - 4 : error with ATIME register
    ///     - 5 : error with WTIME register
    ///     - 6 : error with CONTROL register
    ///     - 7 : no change between cycles
    /// \return
    /// 0 on successful test, corresponding error code on failed test.
    int selftest();
    
};

#endif // TCS3472_HPP
