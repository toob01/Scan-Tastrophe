#include "hwlib.hpp"
#include "tcs3472.hpp"
#include "../TCA9548A/mux.hpp"


int main(int argc, char **argv){
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
    mux.select(0);
    while(true){
        if(button.read()){
            leds.write(1);
            tcs.start();
            leds.write(0);
            data[0] = tcs.read_rgbc();
            int result = tcs.calculate_rgb_integer(data[0]);
            hwlib::cout << hwlib::bin << hwlib::setw(24) << hwlib::setfill('0') << result << "\n";
            hwlib::cout << hwlib::hex << result << "\n";
        }
    }
}