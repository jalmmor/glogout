# Example Makefile script
# Purpose: Demonstrate usage of pkg-config with MRPT libraries
# By: Jose Luis Blanco, 2010.
#
#   ========================= *IMPORTANT* ================================
#   For this method to work MRPT must be installed in your
#   system in a path accesible to pkg-config. To check if pkg-config
#   sees MRPT config files, execute:
#      pkg-config --list-all | grep mrpt
#   If no package appears, MRPT is not installed or something else is wrong.
#   ======================================================================
#

# Set up basic variables:
CC         = gcc
CFLAGS     = -Wall
LDFLAGS    =

# List of sources:
SOURCES    = glogout.c
OBJECTS    = $(SOURCES:.c=.o)

# Name of executable target:
EXECUTABLE = glogout

# MRPT specific flags:
#  Here we invoke "pkg-config" passing it as argument the list of the
#  MRPT libraries needed by our program (see available libs
#   with "pkg-config --list-all | grep mrpt").
#
CFLAGS     += ` pkg-config --libs --cflags gtk+-3.0`
#LDFLAGS    += `pkg-config --libs --cflags gtk+-3.0`


all:  
	$(CC) $(CFLAGS) glogout.c -o glogout

clean:
	rm  glogout

