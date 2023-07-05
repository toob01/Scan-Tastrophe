# Scan-Tastrophe: the miniature photoscanner

The Scan-Tastrophe is a rudimentary photoscanner with 4 x 4 pixel resolution, making use of the TCS3472 colour sensor.
The codebase makes extensive use of [hwlib](https://github.com/wovo/hwlib) to address an Arduino Due microcontroller.
With use of [bmptk](https://github.com/wovo/bmptk) it's possible to compile the program for other microcontrollers as well.

The codebase is documented with Doxygen comments, and generated documentation can be found in the DOCS folder.

# Repository Contents
Scan-Tastrophe includes one library for use with the TCS34725/7 range of colour sensors in combination with [hwlib](https://github.com/wovo/hwlib).

Additionally it includes two Abstract datatypes that the TCS34725/7 library makes use of:
  - RGBC (red, green, blue, clear) stored in 16-bit unsigned integers
  - RGB (red, green, blue) stored in 8-bit unsigned integers

Both ADTs are provided with tests using the [Catch2 testing framework](https://github.com/catchorg/Catch2)
> Note: there is no implication nor warranty for the functionality of any software in this repository, see License for details.

# Features

## TCS34725/7 library

The TCS34725/7 library provides the following functionality:
- Configuration Macros for registers and their values
- Reading from specific registers
- Reading colour data from corresponding registers
- Explicitly put device in sleep and idle state
- Explicitely starting an RGBC cycle
- Reading and returning all colour data
- Converting raw colour data to 8-bit RGB values or 24-bit integer (hex) value

## RGBC and RGB ADTs

The RGBC and RGB abstract datatypes are to store the data one might receive from the TCS3472x colour sensor
RGBC stores four 16-bit unsigned integers, one for each of the Red, Green, Blue, and Clear colour channels.
RGB stores three 8-bit unsigned integers, one for each 8-bit representation of the values as described in the RGBC datatype.

Both provide a range of operators to make it easy to interact with and modify colour data.

Operators included are: +, +=, -, -=, *, *=, /, /=, |, |=, &, &=, ==, !=, <, <=, >, >=, [], <<

See DOCS for implementation details.

# Author

[Tobias Bosch](https://github.com/toob01)

# License

Copyright (c) 2023, Tobias Bosch
Scan-Tastrophe is distributed under the Boost Software License, Version 1.0. 
(See accompanying file `LICENSE` or copy at http://www.boost.org/LICENSE_1_0.txt)
