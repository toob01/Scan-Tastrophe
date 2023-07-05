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

void print_grid_colors(std::array<rgb, 16> & RGB){
    hwlib::cout << "======================" << hwlib::endl << hwlib::endl;
    hwlib::cout << "||  \x1b[48;2;" << RGB[3] << "m    \x1b[48;2;" << RGB[7] << "m    \x1b[48;2;" << RGB[11] << "m    \x1b[48;2;" << RGB[15] << "m    \x1b[39;49m  ||\n";
    hwlib::cout << "||  \x1b[48;2;" << RGB[3] << "m    \x1b[48;2;" << RGB[7] << "m    \x1b[48;2;" << RGB[11] << "m    \x1b[48;2;" << RGB[15] << "m    \x1b[39;49m  ||\n";
    hwlib::cout << "||  \x1b[48;2;" << RGB[2] << "m    \x1b[48;2;" << RGB[6] << "m    \x1b[48;2;" << RGB[10] << "m    \x1b[48;2;" << RGB[14] << "m    \x1b[39;49m  ||\n";
    hwlib::cout << "||  \x1b[48;2;" << RGB[2] << "m    \x1b[48;2;" << RGB[6] << "m    \x1b[48;2;" << RGB[10] << "m    \x1b[48;2;" << RGB[14] << "m    \x1b[39;49m  ||\n";
    hwlib::cout << "||  \x1b[48;2;" << RGB[1] << "m    \x1b[48;2;" << RGB[5] << "m    \x1b[48;2;" << RGB[9] << "m    \x1b[48;2;" << RGB[13] << "m    \x1b[39;49m  ||\n";
    hwlib::cout << "||  \x1b[48;2;" << RGB[1] << "m    \x1b[48;2;" << RGB[5] << "m    \x1b[48;2;" << RGB[9] << "m    \x1b[48;2;" << RGB[13] << "m    \x1b[39;49m  ||\n";
    hwlib::cout << "||  \x1b[48;2;" << RGB[0] << "m    \x1b[48;2;" << RGB[4] << "m    \x1b[48;2;" << RGB[8] << "m    \x1b[48;2;" << RGB[12] << "m    \x1b[39;49m  ||\n";
    hwlib::cout << "||  \x1b[48;2;" << RGB[0] << "m    \x1b[48;2;" << RGB[4] << "m    \x1b[48;2;" << RGB[8] << "m    \x1b[48;2;" << RGB[12] << "m    \x1b[39;49m  ||\n\n";
    hwlib::cout << "======================" << hwlib::endl;
    hwlib::cout << "\n";
    hwlib::cout << "What a nice picture! :)" << hwlib::endl;
}

int main(int argc, char **argv){
    hwlib::cout << "\x1b[31m Setting up...\x1b[39m" << hwlib::endl;
    
    auto button = hwlib::target::pin_in(hwlib::target::pins::d7);
    auto leds = hwlib::target::pin_out(hwlib::target::pins::d13);
    
    auto scl1 = hwlib::target::pin_oc(hwlib::target::pins::d2);
    auto sda1 = hwlib::target::pin_oc(hwlib::target::pins::d3);
    auto scl2 = hwlib::target::pin_oc(hwlib::target::pins::d4);
    auto sda2 = hwlib::target::pin_oc(hwlib::target::pins::d5);
    
    auto i2c_bus1 = hwlib::i2c_bus_bit_banged_scl_sda(scl1, sda1);
    auto i2c_bus2 = hwlib::i2c_bus_bit_banged_scl_sda(scl2, sda2);
    
    leds.write(0);
    
    uint8_t mux_address1 = 0x70;
    uint8_t mux_address2 = 0x71;
    
    auto mux1 = tca9548a(i2c_bus1, mux_address1);
    auto mux2 = tca9548a(i2c_bus2, mux_address2);
    mux1.select(0);
    mux2.select(0);
    auto tcs1 = tcs3472(i2c_bus1, SET_PON|SET_AEN, SET_ATIME_154MS, SET_WTIME_2_4MS, SET_AGAIN_1X);
    auto tcs2 = tcs3472(i2c_bus2, SET_PON|SET_AEN, SET_ATIME_154MS, SET_WTIME_2_4MS, SET_AGAIN_1X);
    
    for(uint8_t t=0; t<8; t++){
        mux1.select(t);
        mux2.select(t);
        tcs1.reload_config();
        tcs2.reload_config();
    }
    
    int result;
    std::array<rgbc, 16> data;
    std::array<rgb, 16> RGB;
    std::array<int, 16> HEX;
    
    while(true){
        hwlib::cout << "\x1b[32m Setup Complete! \x1b[39m" << hwlib::endl << hwlib::endl << hwlib::endl;
        hwlib::cout << "=============================================================================" << hwlib::endl
                    << "                   Hello! Welcome to the Scan-Tastrophe.                     " << hwlib::endl << hwlib::endl
                    << "                    Everything is ready to go for you!                       " << hwlib::endl
                    << "  Simply place something on top of the sensors, and press the green button.  " << hwlib::endl
                    << "=============================================================================" << hwlib::endl << hwlib::endl;
        break;
    }

    while(true){
        hwlib::cout << "Waiting on button input..." << hwlib::endl<< hwlib::endl;
        if(button.read()){
            hwlib::cout << "Button input read, starting scan!" << hwlib::endl<< hwlib::endl;
            leds.write(1);
            for (int t = 0; t < 8; t++){
                mux1.select(t);
                mux2.select(t);
                tcs1.start();
                tcs2.start();
                data[t] = tcs1.read_rgbc();
                data[t+8] = tcs2.read_rgbc();
            }
            leds.write(0);
            for (int s = 0; s<16; s++){
                result = tcs1.calculate_rgb_integer(data[s]);
                RGB[s] = rgb(((result>>16)&0x0000FF), ((result>>8)&0x0000FF), (result&0x0000FF));
                HEX[s] = result;
            }
            print_grid_colors(RGB);
        }
    }
}