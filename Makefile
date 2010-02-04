# Desdemona Makefile
# Author: Arun Chaganty <arunchaganty@gmail.com>
#

ROOTDIR=./
include Makefile.inc

TARGETS=bin/Desdemona

VERSION=0.1
SRCFILES=include/ misc/ src/ tests/ Doxyfile Makefile README 
DISTFILES=bin/desdemona tests/ doc/ README

OBJS=obj/main.o obj/Othello.o obj/OthelloBoard.o obj/LoggedOthelloGame.o obj/OthelloGame.o obj/OthelloPlayer.o obj/HumanPlayer.o

all: $(TARGETS)

bin/Desdemona: ${OBJS}
	if [ ! -e lib ]; then mkdir lib; fi;
	$(CC) $(LDFLAGS) $^ -o $@

# Pattern to build obj files from src files
${OBJS}: obj/%.o : src/%.cpp 
	if [ ! -e obj ]; then mkdir obj; fi;
	$(CC) $(CFLAGS) -c $^ -o $@

bots:
	${ECHO} Looking into subdir $@ 
	cd $@; ${MAKE}

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

