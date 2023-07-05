#############################################################################
#
# Project Makefile
#
# (c) Tobias Bosch 2023
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := ../RGBC_ADT/rgbc.cpp ../RGB_ADT/rgb.cpp tcs3472.cpp

# header files in this project
HEADERS := ../RGBC_ADT/rgbc.hpp ../RGB_ADT/rgb.hpp tcs3472.hpp

# other places to look for files for this project
SEARCH  := 

SERIAL_PORT ?= COM8

# set RELATIVE to the next higher directory 
# and defer to the Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
