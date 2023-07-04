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

/// I2C address of TCS3742 color sensor
#define TCS 0x29

#include "hwlib.hpp"
#include <array>

/// @name Color register (low bit) address definitions.
/// @{
#define RDATA 0x16
#define GDATA 0x18
#define BDATA 0x1A
#define CDATA 0x14
/// @}

/// @name Optional high bit address definitions
/// @{
#define H_CDATA 0x15
#define H_RDATA 0x17
#define H_BDATA 0x19
#define H_GDATA 0x1B
/// @}

/// @name Device configuration register address definitions
/// @{
#define TCS_ENABLE 0x00
#define TCS_ATIME 0x01
#define TCS_WTIME 0x03
#define TCS_AGAIN 0x0F
#define TCS_STATUS 0x13
/// @}

/// @name Enable register options
/// @{
#define SET_WEN 0x08
#define SET_AEN 0x02
#define SET_PON 0x01
/// @}

/// @name Integration time definitions
/// @{
#define SET_ATIME_2_4MS 0xFF
#define SET_ATIME_24MS 0xF6
#define SET_ATIME_50MS 0xEB
#define SET_ATIME_101MS 0xD5
#define SET_ATIME_154MS 0xC0
#define SET_ATIME_200MS 0XAC
#define SET_ATIME_267MS 0X90
#define SET_ATIME_320MS 0X7A
#define SET_ATIME_385MS 0X5F
#define SET_ATIME_420MS 0X50
#define SET_ATIME_500MS 0X2F
#define SET_ATIME_532MS 0X22
#define SET_ATIME_570MS 0X12
#define SET_ATIME_614MS 0x00
/// @}

/// @name Wait time definitions
/// @{
#define SET_WTIME_2_4MS 0xFF
#define SET_WTIME_24MS 0xF6
#define SET_WTIME_50MS 0xEB
#define SET_WTIME_101MS 0xD5
#define SET_WTIME_154MS 0xC0
#define SET_WTIME_200MS 0XAC
#define SET_WTIME_267MS 0X90
#define SET_WTIME_320MS 0X7A
#define SET_WTIME_385MS 0X5F
#define SET_WTIME_420MS 0X50
#define SET_WTIME_500MS 0X2F
#define SET_WTIME_532MS 0X22
#define SET_WTIME_570MS 0X12
#define SET_WTIME_614MS 0x00
/// @}

/// @name Gain definitions
/// @{
#define SET_AGAIN_1X 0x00
#define SET_AGAIN_4X 0x01
#define SET_AGAIN_16X 0x02
#define SET_AGAIN_60X 0x03
/// @}


/// @brief
/// Interface for TCS3472(5) color sensor using (abstractions and functions from) HWLIB
/// @details
/// This class provides an interface for the TCS3472(5) color sensor
/// This implementation only works for sensors with I2C address 0x29, which most of these sensors will have.
/// To use this sensor in amounts more than one or with other devices that have the same address, you have the option to either define multiple I2C busses, or use an I2C multiplexer like the TCA9548A (I recommend the latter).
/// If you happen to have a sensor that has a discrepant address and you haven't been able to figure out how to make it work, feel free to contact me at tobias.bosch@student.hu.nl, I am happy to offer assistance :)
/// Limitations:
///     - no capabilities for the interrupt output that some TCS3472 devices may have.
///     - no capabilities for the WLONG option.
class tcs3472 {
private:

    hwlib::i2c_primitives & bus;
    uint8_t enable_option;
    uint8_t atime_option;
    uint8_t wtime_option;
    uint8_t again_option;
    
    void set_active_register_single_byte(uint8_t reg_address);
    void set_active_register_multi_byte(uint8_t reg_address);
    std::array<uint8_t, 2> read_color_register(uint8_t reg_address);
    int get_wait_time();
    
public:
    /// @brief
    /// Constructor for tcs3472 color sensor 
    /// @details
    /// This constructor creates an interface for the tcs3472 color sensor.
    /// Default values are:
    ///     - TCS_ENABLE    : AEN | PON
    ///     - ATIME         : 2.4 ms
    ///     - WTIME         : 2.4 ms
    ///     - AGAIN         : 1X
    tcs3472(hwlib::i2c_primitives & c_bus, uint8_t c_enable_option=SET_AEN|SET_PON, uint8_t c_atime_option=SET_ATIME_2_4MS, uint8_t c_wtime_option=SET_WTIME_2_4MS, uint8_t c_again_option=SET_AGAIN_1X);
    
    /// Read a register specified by address
    int read_register(uint8_t reg_address);
    
    /// Read 16-bit data from Clear data register
    int read_clear();
    
    /// Read 16-bit data from Red data register
    int read_red();
    
    /// Read 16-bit data from Green data register
    int read_green();
    
    /// Read 16-bit data from Blue data register
    int read_blue();
    
    void sleep();
    
    void wake();
    
    /// Start a sense cycle
    void start();
    
    /// @brief
    /// Read raw data from red, green, blue, and clear registers
    /// @return
    /// Array of integers (0-65535), indeces 0, 1, 2, 3 being R, G, B, and C respectively.
    std::array<int, 4> read_rgbc();
    
    /// @brief
    /// Convert values from RGBC to RGB representation.
    /// @param rgbc
    /// an array of 4 integer values corresponding to R, G, B, and C.
    /// @return
    /// Array of three 8-bit values (0-255), indeces 0, 1, 2 being R, G, and B values
    std::array<uint8_t, 3> calculate_rgb_array(const std::array<int, 4> & rgbc);
    
    /// @brief
    /// Convert values from RGBC to RGB representation, individual parameters per channel.
    /// @param red
    /// (16-bit) integer red channel value
    /// @param green
    /// (16-bit) integer green channel value
    /// @param blue
    /// (16-bit) integer blue channel value
    /// @param clear
    /// (16-bit) integer clear channel value
    /// @return
    /// Array of three 8-bit values (0-255), indeces 0, 1, 2 being R, G, and B values
    std::array<uint8_t, 3> calculate_rgb_array(int red, int green, int blue, int clear);
    
    int calculate_rgb_integer(std::array<int, 4> rgbc);
    
    void reload_config();
};

#endif // TCS3472_HPP
