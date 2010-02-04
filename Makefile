# Desdemona Makefile
# Author: Arun Chaganty <arunchaganty@gmail.com>
#

ROOTDIR=./
include Makefile.inc

TARGETS=bin/Desdemona lib/libOthello.so

VERSION=0.1
SRCFILES=include/ misc/ src/ tests/ Doxyfile Makefile README 
DISTFILES=bin/desdemona tests/ doc/ README

LDFLAGS += -ldl

OTHELLO_LIB_OBJS=obj/Othello.o obj/OthelloBoard.o obj/LoggedOthelloGame.o obj/OthelloGame.o obj/OthelloPlayer.o
OBJS=obj/main.o $(OTHELLO_LIB_OBJS)

all: $(TARGETS)

bin/Desdemona: ${OBJS}
	if [ ! -e lib ]; then mkdir lib; fi;
	$(CC) $(LDFLAGS) $^ -o $@

lib/libOthello.so: $(OTHELLO_LIB_OBJS)
	if [ ! -e lib ]; then mkdir lib; fi;
	$(CC) $(LDFLAGS) -shared -Wl,-soname,$@.1 -o $@ $^ -lc

# Pattern to build obj files from src files
${OBJS}: obj/%.o : src/%.cpp 
	if [ ! -e obj ]; then mkdir obj; fi;
	$(CC) $(CFLAGS) -c $^ -o $@

bots:
	echo Looking into subdir $@ 
	cd $@; make

src-dist: 
	rm -rf Desdemona-src-$(VERSION)
	mkdir Desdemona-src-$(VERSION)
	cp -rf $(SRCFILES) Desdemona-src-$(VERSION)/
	tar -czf Desdemona-src-$(VERSION).tar.gz Desdemona-src-$(VERSION)/
	rm -rf Desdemona-src-$(VERSION)

bin-dist: all
	rm -rf Desdemona-$(VERSION)
	mkdir Desdemona-$(VERSION)
	cp -rf $(DISTFILES) Desdemona-$(VERSION)/
	tar -czf Desdemona-$(VERSION).tar.gz Desdemona-$(VERSION)/
	rm -r Desdemona-$(VERSION)

.PHONY: clean doc bots

doc: 
	doxygen

clean:
	rm -rf bin/*
	rm -rf lib/*
	rm -rf obj/*

