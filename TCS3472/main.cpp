#include "hwlib.hpp"
#include "tcs3472.hpp"
#include "../TCA9548A/mux.hpp"


int main(int argc, char **argv){
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::d2);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::d3);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    
    uint8_t mux_address = 0x70;
    
    auto mux = i2c_mux(i2c_bus, mux_address);
    mux.select(0);
    auto tcs0 = tcs3472(i2c_bus, SET_AEN|SET_WEN, SET_ATIME_2_4MS, SET_WTIME_2_4MS, SET_AGAIN_60X);

    tcs0.start();
    auto data_clear = tcs0.read_clear();
    hwlib::cout << "\n" << data_clear << "\n";
    auto data_red = tcs0.read_red();
    hwlib::cout << "\n" << data_red << "\n";
    
//    std::array<int, 4> rgb_data = tcs0.get_rgb();
//    hwlib::cout << "TCS 0 data : \n";
//    hwlib::cout << rgb_data[0] << "\n";
//    hwlib::cout << rgb_data[1] << "\n";
//    hwlib::cout << rgb_data[2] << "\n";
//    hwlib::cout << rgb_data[3] << "\n";
//    auto config = tcs0.read_config();
//    hwlib::cout << hwlib::hex << config[0] << "\n";
//    hwlib::cout << hwlib::hex << config[1] << "\n";
//    hwlib::cout << hwlib::hex << config[2] << "\n";
//    hwlib::cout << hwlib::hex << config[3] << "\n";
//    tcs0.reset_factory_settings();
//    auto config2 = tcs0.read_config();
//    hwlib::cout << hwlib::hex << config2[0] << "\n";
//    hwlib::cout << hwlib::hex << config2[1] << "\n";
//    hwlib::cout << hwlib::hex << config2[2] << "\n";
//    hwlib::cout << hwlib::hex << config2[3] << "\n";
}
