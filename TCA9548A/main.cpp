#include "hwlib.hpp"
#include "mux.hpp"
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
    
    auto mux = i2c_mux(i2c_bus, mux_address);
    
    int red_data[8] = {};
    
    for(uint8_t t=0; t<7; t++){
        uint8_t data[2] = {0, 0};
        mux.select(t);
        { // TODO: PLEASE FUCKING COMMENT WHY YOU'RE USING IF TRUE OR CURLY BRACES
            auto trans = hwlib::i2c_write_transaction(i2c_bus, 0x29);
            trans.write(0b10000000);
            trans.write(0b00000011);
        }
        {
            auto start = hwlib::i2c_write_transaction(i2c_bus, 0x29);
            hwlib::wait_ms(150);
            start.write(0b10110100);
        }
        {
            auto trans = hwlib::i2c_read_transaction(i2c_bus, 0x29);
            trans.read(data, 2);
        }
    red_data[t] = (data[0] << 8) | data[1];
        
    }
    hwlib::cout << "| " << hwlib::setfill(' ') << hwlib::setw(5) << red_data[4] << " | " << hwlib::setfill(' ') << hwlib::setw(5) << red_data[0] << " |" << "\n";
    hwlib::cout << "| " << hwlib::setfill(' ') << hwlib::setw(5) << red_data[5] << " | " << hwlib::setfill(' ') << hwlib::setw(5) << red_data[1] << " |" << "\n";
    hwlib::cout << "| " << hwlib::setfill(' ') << hwlib::setw(5) << red_data[6] << " | " << hwlib::setfill(' ') << hwlib::setw(5) << red_data[2] << " |" << "\n";
    hwlib::cout << "| " << hwlib::setfill(' ') << hwlib::setw(5) << red_data[7] << " | " << hwlib::setfill(' ') << hwlib::setw(5) << red_data[3] << " |" << "\n";
    hwlib::cout << "\n";
}
