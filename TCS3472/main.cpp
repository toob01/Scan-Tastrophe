#include "hwlib.hpp"
#include "tcs3472.hpp"
#include "../TCA9548A/mux.hpp"

void print_rgb_info(int result){
    hwlib::cout << hwlib::bin << hwlib::setw(24) << hwlib::setfill('0') << result << "\n";
        hwlib::cout << hwlib::hex << result << "\n";
        hwlib::cout << hwlib::dec << "RED: " << ((result>>16)&0x0000FF) << "\n";
        hwlib::cout << hwlib::dec << "GREEN: " << ((result>>8)&0x0000FF) << "\n";
        hwlib::cout << hwlib::dec << "BLUE: " << (result&0x0000FF) << "\n\n";
        hwlib::cout << "\x1b[48;2;"<< ((result>>16)&0x0000FF) << ";" << ((result>>8)&0x0000FF) << ";" << (result&0x0000FF) << "m    " << "\x1b[39;49m\n";
        hwlib::cout << "\x1b[48;2;"<< ((result>>16)&0x0000FF) << ";" << ((result>>8)&0x0000FF) << ";" << (result&0x0000FF) << "m    " << "\x1b[39;49m\n";
}

int main(int argc, char **argv){
//    auto screen_scl = hwlib::target::pin_out(hwlib::target::pins::d9);
//    auto screen_sda = hwlib::target::pin_out(hwlib::target::pins::d10);
//    auto screen_dc = hwlib::target::pin_out(hwlib::target::pins::d11);
//    auto screen_res = hwlib::target::pin_out(hwlib::target::pins::d12);
//    
//    auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(screen_scl, screen_sda, hwlib::pin_in_dummy);
//    auto screen = hwlib::st7789_spi_dc_cs_rst(spi_bus, screen_dc, hwlib::pin_out_dummy, screen_res);
    
    auto button = hwlib::target::pin_in(hwlib::target::pins::d7);
    auto leds = hwlib::target::pin_out(hwlib::target::pins::d13);
    
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::d2);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::d3);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    
    uint8_t mux_address = 0x70;
    
    auto mux = i2c_mux(i2c_bus, mux_address);
    mux.select(0);
    auto tcs = tcs3472(i2c_bus, SET_PON|SET_AEN|SET_WEN, SET_ATIME_267MS, SET_WTIME_267MS, SET_AGAIN_1X);
    
    leds.write(0);
    
    for(uint8_t t=0; t<8; t++){
        mux.select(t);
        tcs.reload_config();
    }
    
    std::array<int, 4> data[8] = {};
    int result;
    mux.select(0);
    while(true){
        if(button.read()){
            leds.write(1);
            tcs.start();
            leds.write(0);
            data[0] = tcs.read_rgbc();
            result = tcs.calculate_rgb_integer(data[0]);
            print_rgb_info(result);
        }
    }
}