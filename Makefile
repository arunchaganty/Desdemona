# Desdemona Makefile
# Author: Arun Chaganty <arunchaganty@gmail.com>
#

CC=g++
CFLAGS=-Wall -g -Iinclude/
CXXFLAGS=$(CFLAGS)
LDFLAGS=-g
TARGETS=bin/Desdemona

VERSION=0.1

SRCFILES=include/ misc/ src/ tests/ Doxyfile Makefile README 
DISTFILES=bin/desdemona tests/ doc/ README

all: $(TARGETS)

bin/Desdemona: obj/main.o obj/Othello.o obj/OthelloBoard.o obj/LoggedOthelloGame.o obj/OthelloGame.o obj/OthelloPlayer.o obj/HumanPlayer.o obj/RandomPlayer.o
	if [ ! -e lib ]; then mkdir lib; fi;
	$(CC) $(LDFLAGS) $^ -o $@

obj/main.o: src/main.cpp
	if [ ! -e obj ]; then mkdir obj; fi;
	$(CC) $(CFLAGS) -c $^ -o $@

obj/Othello.o: src/Othello.cpp
	if [ ! -e obj ]; then mkdir obj; fi;
	$(CC) $(CFLAGS) -c $^ -o $@

obj/OthelloBoard.o: src/OthelloBoard.cpp
	if [ ! -e obj ]; then mkdir obj; fi;
	$(CC) $(CFLAGS) -c $^ -o $@

obj/OthelloPlayer.o: src/OthelloPlayer.cpp
	if [ ! -e obj ]; then mkdir obj; fi;
	$(CC) $(CFLAGS) -c $^ -o $@

obj/OthelloGame.o: src/OthelloGame.cpp
	if [ ! -e obj ]; then mkdir obj; fi;
	$(CC) $(CFLAGS) -c $^ -o $@

obj/LoggedOthelloGame.o: src/LoggedOthelloGame.cpp
	if [ ! -e obj ]; then mkdir obj; fi;
	$(CC) $(CFLAGS) -c $^ -o $@

obj/HumanPlayer.o: src/HumanPlayer.cpp
	if [ ! -e obj ]; then mkdir obj; fi;
	$(CC) $(CFLAGS) -c $^ -o $@

obj/RandomPlayer.o: src/RandomPlayer.cpp
	if [ ! -e obj ]; then mkdir obj; fi;
	$(CC) $(CFLAGS) -c $^ -o $@


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

.PHONY: clean doc

doc: 
	doxygen

clean:
	rm -rf bin/*
	rm -rf lib/*
	rm -rf obj/*

