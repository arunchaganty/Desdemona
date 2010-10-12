# 
# Author: Arun Tejasvi Chaganty <arunchaganty@gmail.com>
# Date:   2010-02-04
#

ROOTDIR  = ../../
include $(ROOTDIR)Makefile.inc

BOT	= MyBot
OUT = bot.so

all: $(OUT)

$(OUT): $(BOT).cpp $(ROOTDIR)lib/libOthello.so
	$(CC) $(LDFLAGS) $(CFLAGS) -shared $^ -o $@

.PHONY: clean submission

submission: clean
	zip submission.zip *

clean:
	rm -rf $(OUT)
