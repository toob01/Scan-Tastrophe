// =============================================================
//
// File         : main.cpp in TCA9548A/
// Copyright    : tobias.bosch@student.hu.nl 2023
//
// Distributed under the Boost Software License, Version 1.0.
// (See https://www.boost.org/LICENSE_1_0.txt)
//
// =============================================================

#include "hwlib.hpp"
#include "tca9548a.hpp"
#include <array>
#include <iomanip>

void write_start_stop(hwlib::pin_oc & scl, hwlib::pin_oc & sda){
    scl.write(1);
    sda.write(1);
    sda.write(0);
    hwlib::wait_us(1);
    sda.write(1);
}

int main(void){
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::d2);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::d3);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    
    uint8_t mux_address = 0x70;
    
    auto mux = tca9548a(i2c_bus, mux_address);
    uint8_t data[2] = {0, 0};
    mux.select(0);
    { // select enable register
        auto trans = hwlib::i2c_write_transaction(i2c_bus, 0x29);
        trans.write(0x80);
    }
    { // write AEN | WEN | PON
        auto trans = hwlib::i2c_write_transaction(i2c_bus, 0x29);
        trans.write(0x0B);
    }
    { // start transaction
        auto start = hwlib::i2c_write_transaction(i2c_bus, 0x29);
        hwlib::wait_ms(1000);
    }
    { // select clear register in two byte thingy mode
        auto fuck = hwlib::i2c_write_transaction(i2c_bus, 0x29);
        fuck.write(0b10110100);
    }
    { // read 2 bytes from clear register
        auto trans = hwlib::i2c_read_transaction(i2c_bus, 0x29);
        trans.read(data, 2);
    }
    hwlib::cout << hwlib::bin << ((data[0] << 8) | data[1]);
}
