#include "hwlib.hpp"
#include "mux.hpp"

int main(void){
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::d2);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::d3);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    
    uint8_t mux_address = 0x70;
    
    auto mux = i2c_mux(i2c_bus, mux_address);
    uint8_t data;
    
    for(uint8_t t=0; t<8; t++){
        mux.select(t);
        auto trans = hwlib::i2c_write_transaction(i2c_bus, mux_address);
        trans.write(0b10010110);
    }
    
    for(uint8_t t=0; t<8; t++){
        mux.select(t);
        auto trans2 = hwlib::i2c_read_transaction(i2c_bus, mux_address);
        trans2.read(data);
        hwlib::cout << "Sensor " << t << " red read : " << data << "\n";
    }
}
