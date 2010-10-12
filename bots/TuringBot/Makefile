# 
# Author: Arun Tejasvi Chaganty <arunchaganty@gmail.com>
# Date:   2010-02-04
#

ROOTDIR  = ../../
include $(ROOTDIR)Makefile.inc

BOT	= TuringBot

all: $(BOT).so

$(BOT).so: $(BOT).cpp $(ROOTDIR)lib/libOthello.so
	$(CC) $(LDFLAGS) $(CFLAGS) -shared $^ -o $@

.PHONY: clean 

clean:
	rm -rf $(BOT).so
