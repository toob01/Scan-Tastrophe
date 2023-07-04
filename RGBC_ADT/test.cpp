#include "hwlib.hpp"
//#include "../TCS3472/tcs3472.hpp"
//#include "../STEPPER/a4988.hpp"

int main( void ){
    auto led = hwlib::target::pin_out(hwlib::target::pins::d13);
    
    auto sclk = hwlib::target::pin_out(hwlib::target::pins::d4);
    auto mosi = hwlib::target::pin_out(hwlib::target::pins::d5);
    
    auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(sclk, mosi, hwlib::pin_in_dummy);
    
    auto dc = hwlib::target::pin_out(hwlib::target::pins::d7);
    auto rst = hwlib::target::pin_out(hwlib::target::pins::d6);
    auto screen = hwlib::st7789_spi_dc_cs_rst(spi_bus, dc, dc, rst);
    
//    int x_max=20;
//    int y_max=20;
    
    while(true){
        
        led.write(1);
        led.flush();
        hwlib::wait_ms(125);
        led.write(0);
        led.flush();
        hwlib::wait_ms(125);
        led.write(1);
        led.flush();
        hwlib::wait_ms(125);
        led.write(0);
        led.flush();
        hwlib::wait_ms(125);
        
//        for(int x = 0; x < x_max; x++) {
//            for (int y = 0; y < y_max; y++) {
//                hwlib::cout << "x : " << x << " ,y : " << y << "\n";
//                if(x % 2 == 0){
//                    if(y % 2 == 0){
//                        screen.write(hwlib::xy(x, y), hwlib::black);
//                    } else {
//                        screen.write(hwlib::xy(x, y), hwlib::white);
//                    }
//                } else {
//                    if(y % 2 == 0){
//                        screen.write(hwlib::xy(x, y), hwlib::white);
//                    } else {
//                        screen.write(hwlib::xy(x, y), hwlib::black);
//                    }
//                }
//            }
//        }
        screen.write(hwlib::xy(5, 5), hwlib::white);
        hwlib::cout << "done writing to screen" << "\n";
        screen.flush();
        hwlib::cout << "done flushing to screen" << "\n";
        
        led.write(1);
        led.flush();
        hwlib::wait_ms(125);
        led.write(0);
        led.flush();
        hwlib::wait_ms(125);
        led.write(1);
        led.flush();
        hwlib::wait_ms(125);
        led.write(0);
        led.flush();
        hwlib::wait_ms(125);
    }
}
