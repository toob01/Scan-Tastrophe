#ifndef MUX_HPP
#define MUX_HPP
#include "hwlib.hpp"

class i2c_mux {
private:
    hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus;
    const uint8_t address;
public:
    i2c_mux(hwlib::i2c_bus_bit_banged_scl_sda & c_i2c_bus, uint8_t c_address):
        i2c_bus(c_i2c_bus),
        address(c_address)
        {};
    
    int select(int output){
        if (output > 7) return -1;
        
        auto trans = hwlib::i2c_write_transaction(i2c_bus, address);
        trans.write(1 << output);
        return output;
    };
    
//    void select_write(int output, uint8_t data){
//        select(output);
//        auto trans = hwlib::i2c_write_transaction(i2c_bus, address);
//        trans.write(data);
//    }
}; // class i2c_mux
#endif // MUX_HPP
