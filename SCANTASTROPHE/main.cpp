// =============================================================
//
// File         : main.cpp in SCANTASTROPHE/
// Copyright    : tobias.bosch@student.hu.nl 2023
//
// Distributed under the Boost Software License, Version 1.0.
// (See https://www.boost.org/LICENSE_1_0.txt)
//
// =============================================================

#include "hwlib.hpp"
#include "../TCS3472/tcs3472.hpp"
#include "../TCA9548A/tca9548a.hpp"
#include "../RGBC_ADT/rgbc.hpp"
#include "../RGB_ADT/rgb.hpp"

void print_rgb_info(rgb & RGB, int result){
    hwlib::cout << hwlib::hex << result << "\n";
    hwlib::cout << hwlib::dec << "RED: " << RGB[0] << "\n";
    hwlib::cout << hwlib::dec << "GREEN: " << RGB[1] << "\n";
    hwlib::cout << hwlib::dec << "BLUE: " << RGB[2] << "\n\n";
    hwlib::cout << "\x1b[48;2;"<< RGB << "m    " << "\x1b[39;49m\n";
    hwlib::cout << "\x1b[48;2;"<< RGB << "m    " << "\x1b[39;49m\n";
}

void print_grid_colors(std::array<rgb, 8> & RGB){
    hwlib::cout << "\x1b[48;2;" << RGB[3] << "m    \x1b[39;49m\x1b[48;2;" << RGB[7] << "m    \x1b[39;49m\n";
    hwlib::cout << "\x1b[48;2;" << RGB[3] << "m    \x1b[39;49m\x1b[48;2;" << RGB[7] << "m    \x1b[39;49m\n";
    hwlib::cout << "\x1b[48;2;" << RGB[2] << "m    \x1b[39;49m\x1b[48;2;" << RGB[6] << "m    \x1b[39;49m\n";
    hwlib::cout << "\x1b[48;2;" << RGB[2] << "m    \x1b[39;49m\x1b[48;2;" << RGB[6] << "m    \x1b[39;49m\n";
    hwlib::cout << "\x1b[48;2;" << RGB[1] << "m    \x1b[39;49m\x1b[48;2;" << RGB[5] << "m    \x1b[39;49m\n";
    hwlib::cout << "\x1b[48;2;" << RGB[1] << "m    \x1b[39;49m\x1b[48;2;" << RGB[5] << "m    \x1b[39;49m\n";
    hwlib::cout << "\x1b[48;2;" << RGB[0] << "m    \x1b[39;49m\x1b[48;2;" << RGB[4] << "m    \x1b[39;49m\n";
    hwlib::cout << "\x1b[48;2;" << RGB[0] << "m    \x1b[39;49m\x1b[48;2;" << RGB[4] << "m    \x1b[39;49m\n";
    hwlib::cout << "\n";
}

int main(int argc, char **argv){
    
    auto button = hwlib::target::pin_in(hwlib::target::pins::d7);
    auto leds = hwlib::target::pin_out(hwlib::target::pins::d13);
    
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::d2);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::d3);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    
    leds.write(0);
    
    uint8_t mux_address = 0x70;
    
    auto mux = tca9548a(i2c_bus, mux_address);
    mux.select(0);
    auto tcs = tcs3472(i2c_bus, SET_PON|SET_AEN, SET_ATIME_154MS, SET_WTIME_2_4MS, SET_AGAIN_1X);
    
    for(uint8_t t=0; t<8; t++){
        mux.select(t);
        tcs.reload_config();
    }
    
    std::array<rgbc, 8> data;
    int result;
    std::array<rgb, 8> RGB;
    std::array<int, 8> HEX;
    
    while(true){
        if(button.read()){
            leds.write(1);
            for (int t = 0; t < 8; t++){
                mux.select(t);
                tcs.start();
                data[t] = tcs.read_rgbc();
            }
            leds.write(0);
            for (int s = 0; s<8; s++){
                result = tcs.calculate_rgb_integer(data[s]);
                RGB[s] = rgb(((result>>16)&0x0000FF), ((result>>8)&0x0000FF), (result&0x0000FF));
                HEX[s] = result;
            }
            print_grid_colors(RGB);
        }
    }
}