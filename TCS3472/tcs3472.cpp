#include "tcs3472.hpp"

void tcs3472::set_active_register_new_trans(uint8_t reg_address) {
    auto set_trans = hwlib::i2c_write_transaction(bus, TCS);
    set_trans.write(0xA0 | reg_address);
}

void tcs3472::set_active_register_existing_trans(hwlib::i2c_write_transaction & set_trans, uint8_t reg_address) {
    set_trans.write(0xA0 | reg_address);
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
            
        case SET_ATIME_700MS:
            time_ms += 701;
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

// QUESTION : MOETEN DEFAULT VALUES IN CPP EN HPP, OF ALLEEN 1 VAN DE TWEE ?
tcs3472::tcs3472(hwlib::i2c_primitives & c_bus, uint8_t c_enable_option=SET_AEN|SET_WEN, uint8_t c_atime_option=SET_ATIME_2_4MS, uint8_t c_wtime_option=SET_WTIME_2_4MS, uint8_t c_again_option=SET_AGAIN_4X):
    bus(c_bus),
    enable_option(c_enable_option),
    atime_option(c_atime_option),
    wtime_option(c_wtime_option),
    again_option(c_again_option)
{
    auto options_trans = hwlib::i2c_write_transaction(bus, TCS);
    // write enable
    set_active_register_existing_trans(options_trans, ENABLE);
    options_trans.write(enable_option);
    
    // write atime if AEN enabled
    if((enable_option & SET_AEN) == SET_AEN){
        set_active_register_existing_trans(options_trans, ATIME);
        options_trans.write(atime_option);
    }
    
    // write wtime if WEN enabled
    if((enable_option & SET_WEN) == SET_WEN){
        set_active_register_existing_trans(options_trans, WTIME);
        options_trans.write(wtime_option);
    }
    
    // write again
    set_active_register_existing_trans(options_trans, AGAIN);
    options_trans.write(again_option);
}

tcs3472::~tcs3472() {
    reset_factory_settings();
}

int tcs3472::read_register(uint8_t reg_address) {
    uint8_t read_data;
    set_active_register_new_trans(reg_address);
    {
        auto read_trans = hwlib::i2c_read_transaction(bus, TCS);
        read_trans.read(read_data);
    }
    return read_data;
}

uint8_t* tcs3472::read_color_register(uint8_t reg_address) {
    static uint8_t read_data[2];
    {
        auto read_trans = hwlib::i2c_read_transaction(bus, TCS);
        read_trans.read(read_data, 2);
    }
    return read_data;
}

int tcs3472::read_clear() {
    uint8_t* clear_data;
    set_active_register_new_trans(CDATA);
    clear_data = read_color_register(CDATA);
    return ((clear_data[0] << 8) | clear_data[1]);
}

int tcs3472::read_red() {
    uint8_t* red_data;
    set_active_register_new_trans(RDATA);
    red_data = read_color_register(RDATA);
    return ((red_data[0] << 8) | red_data[1]);
}

int tcs3472::read_green() {
    uint8_t* green_data;
    set_active_register_new_trans(GDATA);
    green_data = read_color_register(GDATA);
    return ((green_data[0] << 8) | green_data[1]);
}

int tcs3472::read_blue() {
    uint8_t* blue_data;
    set_active_register_new_trans(BDATA);
    blue_data = read_color_register(BDATA);
    return ((blue_data[0] << 8) | blue_data[1]);
}

void tcs3472::start() {
    uint8_t current_enable = read_register(ENABLE);
    {
        auto pon_trans = hwlib::i2c_write_transaction(bus, TCS);
        set_active_register_existing_trans(pon_trans, ENABLE);
        pon_trans.write(current_enable | SET_PON);
        current_enable |= SET_PON;
    }
    {
        auto start_trans = hwlib::i2c_write_transaction(bus, TCS);
        hwlib::wait_ms(get_wait_time());
    }
    {
        auto poff_trans = hwlib::i2c_write_transaction(bus, TCS);
        poff_trans.write(current_enable & (~SET_PON));
        current_enable &= ~SET_PON;
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

void tcs3472::reset_factory_settings() {
    auto options_trans = hwlib::i2c_write_transaction(bus, TCS);
    set_active_register_existing_trans(options_trans, ENABLE);
    options_trans.write(enable_option);
    set_active_register_existing_trans(options_trans, ATIME);
    options_trans.write(atime_option);
    set_active_register_existing_trans(options_trans, WTIME);
    options_trans.write(wtime_option);
    set_active_register_existing_trans(options_trans, AGAIN);
    options_trans.write(again_option);
}