# 
# Author: Arun Tejasvi Chaganty <arunchaganty@gmail.com>
# Date:   2010-02-04
#

ROOTDIR  = ../../
include $(ROOTDIR)Makefile.inc

BOT	= MyBot
OUT = bot.so

OBJS = $(BOT).o

all: $(OUT)

$(OUT): $(BOT).o $(ROOTDIR)lib/libOthello.so
	$(CC) $(LDFLAGS) -shared $^ -o $@

${OBJS}: %.o : %.cpp 
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean submission

submission: clean
	zip submission.zip *

clean:
	rm -rf $(OUT)
	rm -rf *.o
