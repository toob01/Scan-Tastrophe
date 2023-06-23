#include "tcs3472.hpp"

void tcs3472::set_active_register_multi_byte(uint8_t reg_address) {
    auto set_trans = hwlib::i2c_write_transaction(bus, TCS);
    set_trans.write(0xA0 | reg_address);
}

void tcs3472::set_active_register_single_byte(uint8_t reg_address) {
    auto set_trans = hwlib::i2c_write_transaction(bus, TCS);
    set_trans.write(0x80 | reg_address);
}

int tcs3472::get_wait_time() {
    int time_ms = 0;
    switch(atime_option) {
        case SET_ATIME_2_4MS:
            time_ms += 3;
            break;
            
        case SET_ATIME_24MS:
            time_ms += 25;
            break;
            
        case SET_ATIME_50MS:
            time_ms += 51;
            break;
            
        case SET_ATIME_101MS:
            time_ms += 102;
            break;
            
        case SET_ATIME_154MS:
            time_ms += 155;
            break;
            
        case SET_ATIME_614MS:
            time_ms += 615;
            break;
    }
    
    if((enable_option & SET_WEN) == SET_WEN){
        switch(wtime_option){
            case SET_WTIME_2_4MS:
                time_ms += 3;
                break;
            case SET_WTIME_204MS:
                time_ms += 205;
                break;
            case SET_WTIME_614MS:
                time_ms += 615;
                break;
        }
    }
    return time_ms;
}

tcs3472::tcs3472(hwlib::i2c_primitives & c_bus, uint8_t c_enable_option, uint8_t c_atime_option, uint8_t c_wtime_option, uint8_t c_again_option):
    bus(c_bus),
    enable_option(c_enable_option),
    atime_option(c_atime_option),
    wtime_option(c_wtime_option),
    again_option(c_again_option)
{
    // write enable
    set_active_register_single_byte(ENABLE);
    {
        auto enable_trans = hwlib::i2c_write_transaction(bus, TCS);
        enable_trans.write(enable_option);
    }
    
    // write atime
    set_active_register_single_byte(ATIME);
    {
        auto atime_trans = hwlib::i2c_write_transaction(bus, TCS);
        atime_trans.write(atime_option);
    }
    
    // write wtime
    set_active_register_single_byte(WTIME);
    {
        auto wtime_trans = hwlib::i2c_write_transaction(bus, TCS);
        wtime_trans.write(wtime_option);
    }
    
    // write again
    set_active_register_single_byte(AGAIN);
    {
        auto again_trans = hwlib::i2c_write_transaction(bus, TCS);
        again_trans.write(again_option);
    }
}

tcs3472::~tcs3472() {
    
}

int tcs3472::read_register(uint8_t reg_address) {
    uint8_t read_data;
    set_active_register_single_byte(reg_address);
    {
        auto read_trans = hwlib::i2c_read_transaction(bus, TCS);
        read_trans.read(read_data);
    }
    return read_data;
}

std::array<uint8_t, 2> tcs3472::read_color_register(uint8_t reg_address) {
    uint8_t data[2] = {0, 0};
    { // select register in auto-increment mode
        auto fuck = hwlib::i2c_write_transaction(bus, 0x29);
        fuck.write(0b10100000 | reg_address);
    }
    { // read 2 bytes from register
        auto trans = hwlib::i2c_read_transaction(bus, 0x29);
        trans.read(data, 2);
    }
    hwlib::cout << hwlib::bin << ((data[0] << 8) | data[1]);
    std::array<uint8_t, 2> read_data = {data[0], data[1]};
    return read_data;
}

int tcs3472::read_clear() {
    std::array<uint8_t, 2> clear_data;
    clear_data = read_color_register(CDATA);
    return ((clear_data[0] << 8) | clear_data[1]);
}

int tcs3472::read_red() {
    std::array<uint8_t, 2> red_data;
    red_data = read_color_register(RDATA);
    return ((red_data[0] << 8) | red_data[1]);
}

int tcs3472::read_green() {
    std::array<uint8_t, 2> green_data;
    green_data = read_color_register(GDATA);
    return ((green_data[0] << 8) | green_data[1]);
}

int tcs3472::read_blue() {
    std::array<uint8_t, 2> blue_data;
    blue_data = read_color_register(BDATA);
    return ((blue_data[0] << 8) | blue_data[1]);
}

void tcs3472::start() {
//    set_active_register_single_byte(ENABLE);
//    {
//        auto pon_trans = hwlib::i2c_write_transaction(bus, TCS);
//        pon_trans.write(SET_AEN|SET_WEN|SET_PON);
//    }
//    {
//        auto start_trans = hwlib::i2c_write_transaction(bus, TCS);
//        hwlib::wait_ms(get_wait_time());
//    }
    uint8_t current_enable;
    current_enable = read_register(ENABLE);
//    { // select enable register
//        auto trans = hwlib::i2c_write_transaction(bus, 0x29);
//        trans.write(0x80);
//    }
    set_active_register_single_byte(ENABLE);
    { // write AEN | WEN | PON
        auto trans = hwlib::i2c_write_transaction(bus, 0x29);
        trans.write(0x03 | current_enable);
    }
    { // start transaction
        auto start = hwlib::i2c_write_transaction(bus, 0x29);
        hwlib::wait_ms(1000);
    }
}

std::array<int, 4> tcs3472::get_rgb() {
    std::array<int, 4> rgb_data_raw;
    rgb_data_raw[0] = read_clear();
    rgb_data_raw[1] = read_red();
    rgb_data_raw[2] = read_green();
    rgb_data_raw[3] = read_blue();
    return rgb_data_raw;
}

std::array<uint8_t, 4> tcs3472::get_rgb_8bit() {
    std::array<uint8_t, 4> rgb_data_8bit;
    rgb_data_8bit[0] = sqrt(read_clear());
    rgb_data_8bit[1] = sqrt(read_red());
    rgb_data_8bit[2] = sqrt(read_green());
    rgb_data_8bit[3] = sqrt(read_blue());
    return rgb_data_8bit;
}

int tcs3472::selftest() {
    return 0;
}

std::array<uint8_t, 4> tcs3472::read_config() {
    uint8_t enable_data;
    enable_data = read_register(ENABLE);
    uint8_t atime_data;
    atime_data = read_register(ATIME);
    uint8_t wtime_data;
    wtime_data = read_register(WTIME);
    uint8_t again_data;
    again_data = read_register(AGAIN);
    std::array<uint8_t, 4> config = {enable_data, atime_data, wtime_data, again_data};
    return config;
}

void tcs3472::reset_factory_settings() {
    set_active_register_single_byte(ENABLE);
    {
        auto enable_trans = hwlib::i2c_write_transaction(bus, TCS);
        enable_trans.write(SET_PON);
        enable_option = (SET_AEN|SET_WEN);
    }
    
    set_active_register_single_byte(ATIME);
    {
        auto atime_trans = hwlib::i2c_write_transaction(bus, TCS);
        atime_trans.write(SET_ATIME_2_4MS);
        atime_option = SET_ATIME_2_4MS;
    }

    set_active_register_single_byte(WTIME);
    {
        auto wtime_trans = hwlib::i2c_write_transaction(bus, TCS);
        wtime_trans.write(SET_WTIME_2_4MS);
        wtime_option = SET_WTIME_2_4MS;
    }
    
    set_active_register_single_byte(AGAIN);
    {
        auto again_trans = hwlib::i2c_write_transaction(bus, TCS);
        again_trans.write(SET_AGAIN_4X);
        again_option = SET_AGAIN_4X;
    }
}