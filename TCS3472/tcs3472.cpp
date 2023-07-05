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
    int time_ms = 5;
    switch (atime_option) {
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

        case SET_ATIME_200MS:
            time_ms += 201;
            break;

        case SET_ATIME_267MS:
            time_ms += 268;
            break;

        case SET_ATIME_320MS:
            time_ms += 321;
            break;

        case SET_ATIME_385MS:
            time_ms += 386;
            break;

        case SET_ATIME_420MS:
            time_ms += 421;
            break;

        case SET_ATIME_500MS:
            time_ms += 501;
            break;

        case SET_ATIME_532MS:
            time_ms += 533;
            break;

        case SET_ATIME_570MS:
            time_ms += 571;
            break;

        case SET_ATIME_614MS:
            time_ms += 615;
            break;
    }

    
    if((enable_option & SET_WEN) == SET_WEN){
        switch (wtime_option) {
            case SET_WTIME_2_4MS:
                time_ms += 3;
                break;

            case SET_WTIME_24MS:
                time_ms += 25;
                break;

            case SET_WTIME_50MS:
                time_ms += 51;
                break;

            case SET_WTIME_101MS:
                time_ms += 102;
                break;

            case SET_WTIME_154MS:
                time_ms += 155;
                break;

            case SET_WTIME_200MS:
                time_ms += 201;
                break;

            case SET_WTIME_267MS:
                time_ms += 268;
                break;

            case SET_WTIME_320MS:
                time_ms += 321;
                break;

            case SET_WTIME_385MS:
                time_ms += 386;
                break;

            case SET_WTIME_420MS:
                time_ms += 421;
                break;

            case SET_WTIME_500MS:
                time_ms += 501;
                break;

            case SET_WTIME_532MS:
                time_ms += 533;
                break;

            case SET_WTIME_570MS:
                time_ms += 571;
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
    set_active_register_single_byte(TCS_ENABLE);
    {
        auto enable_trans = hwlib::i2c_write_transaction(bus, TCS);
        enable_trans.write(enable_option);
    }
    
    // write atime
    set_active_register_single_byte(TCS_ATIME);
    {
        auto atime_trans = hwlib::i2c_write_transaction(bus, TCS);
        atime_trans.write(atime_option);
    }
    
    // write wtime
    set_active_register_single_byte(TCS_WTIME);
    {
        auto wtime_trans = hwlib::i2c_write_transaction(bus, TCS);
        wtime_trans.write(wtime_option);
    }
    
    // write again
    set_active_register_single_byte(TCS_AGAIN);
    {
        auto again_trans = hwlib::i2c_write_transaction(bus, TCS);
        again_trans.write(again_option);
    }
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
    set_active_register_multi_byte(reg_address);
    { // read 2 bytes from register
        auto trans = hwlib::i2c_read_transaction(bus, 0x29);
        trans.read(data, 2);
    }
    std::array<uint8_t, 2> read_data = {data[1], data[0]};
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


void tcs3472::sleep(){
    {
        set_active_register_single_byte(TCS_ENABLE);
        auto sleep_trans = hwlib::i2c_write_transaction(bus, TCS);
        sleep_trans.write(enable_option & (~SET_PON));
        enable_option &= (~SET_PON);
    }
    hwlib::wait_ms(5);
}


void tcs3472::wake() {
    {
        set_active_register_single_byte(TCS_ENABLE);
        auto wake_trans = hwlib::i2c_write_transaction(bus, TCS);
        wake_trans.write(enable_option | SET_PON);
        enable_option |= SET_PON;
    }
    hwlib::wait_ms(5);
}


void tcs3472::start() {
    set_active_register_single_byte(TCS_ENABLE);
    { // write AEN
        auto trans = hwlib::i2c_write_transaction(bus, TCS);
        trans.write(enable_option | SET_AEN);
        hwlib::wait_ms(3);
    }
    { // start transaction
        auto start = hwlib::i2c_write_transaction(bus, TCS);
    }
        int time = get_wait_time();
        hwlib::wait_ms(time);
}


rgbc tcs3472::read_rgbc() {
    rgbc data_raw(read_red(), read_green(), read_blue(), read_clear());
    return data_raw;
}


rgb tcs3472::calculate_rgb(rgbc & rgbc_data) {
    rgb rgb_data_8bit(0, 0, 0);
    if(rgbc_data.clear_get() == 0) return rgb_data_8bit;
    
    rgb_data_8bit[0] = static_cast<float>(rgbc_data[0]) / static_cast<float>(rgbc_data[3]) * 255;
    rgb_data_8bit[1] = static_cast<float>(rgbc_data[1]) / static_cast<float>(rgbc_data[3]) * 255;
    rgb_data_8bit[2] = static_cast<float>(rgbc_data[2]) / static_cast<float>(rgbc_data[3]) * 255;

    return rgb_data_8bit;
}

rgb tcs3472::calculate_rgb(int red, int green, int blue, int clear) {
    rgb rgb_data_8bit(0, 0, 0);
    if(clear == 0) return rgb_data_8bit;
    
    rgb_data_8bit[0] = static_cast<float>(red) / static_cast<float>(clear) * 255;
    rgb_data_8bit[1] = static_cast<float>(green) / static_cast<float>(clear) * 255;
    rgb_data_8bit[2] = static_cast<float>(blue) / static_cast<float>(clear) * 255;
    return rgb_data_8bit;
}

int tcs3472::calculate_rgb_integer(rgbc & rgbc_data) {
    if(rgbc_data.clear_get() == 0) return 0;
    
    int red = static_cast<float>(rgbc_data[0]) / static_cast<float>(rgbc_data[3]) * 255;
    int green = static_cast<float>(rgbc_data[1]) / static_cast<float>(rgbc_data[3]) * 255;
    int blue =  static_cast<float>(rgbc_data[2]) / static_cast<float>(rgbc_data[3]) * 255;
    
    int rgb_data_24bit = ((red << 16) | (green << 8) | blue);
    return rgb_data_24bit;
}

void tcs3472::reload_config(){
    // write enable
    set_active_register_single_byte(TCS_ENABLE);
    {
        auto enable_trans = hwlib::i2c_write_transaction(bus, TCS);
        enable_trans.write(enable_option);
    }
    
    // write atime
    set_active_register_single_byte(TCS_ATIME);
    {
        auto atime_trans = hwlib::i2c_write_transaction(bus, TCS);
        atime_trans.write(atime_option);
    }
    
    // write wtime
    set_active_register_single_byte(TCS_WTIME);
    {
        auto wtime_trans = hwlib::i2c_write_transaction(bus, TCS);
        wtime_trans.write(wtime_option);
    }
    
    // write again
    set_active_register_single_byte(TCS_AGAIN);
    {
        auto again_trans = hwlib::i2c_write_transaction(bus, TCS);
        again_trans.write(again_option);
    }
}