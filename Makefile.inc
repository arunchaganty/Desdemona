# vim: ft=make

# put common definitions in here
CC		 = g++
DEBUG    = -O2 # Uncomment for debug options -O0 -ggdb -pg
CFLAGS	 = $(DEBUG) -Wall -I$(ROOTDIR)include/ -fPIC
CXXFLAGS = $(CFLAGS)
LDFLAGS	 = -g

