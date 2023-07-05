#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := ../TCS3472/tcs3472.cpp ../RGBC_ADT/rgbc.cpp ../RGB_ADT/rgb.cpp

# header files in this project
HEADERS := ../TCS3472/tcs3472.hpp ../TCA9548A/mux.hpp ../RGBC_ADT/rgbc.hpp ../RGB_ADT/rgb.hpp

# other places to look for files for this project
SEARCH  := 

SERIAL_PORT   ?= COM8

# set RELATIVE to the next higher directory 
# and defer to the Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due