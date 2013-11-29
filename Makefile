#################################################################
##
## FILE:	Makefile
## AUTHOR:	Ankit Pasi || Alex Wong
## PROJECT:	CS 3251 Project 2 - Professor Traynor
## DESCRIPTION: Compile Project 2 Server
##
#################################################################

CC=gcc
LDFLAGS=-lssl -lcrypto -w -v

OS := $(shell uname -s)

# Extra LDFLAGS if Solaris
ifeq ($(OS), SunOS)
	LDFLAGS=-lsocket -lnsl
    endif

all: server
	
server: serverthread.o networking.o
	$(CC) -lcrypto -lpthread serverthread.o networking.o sorter.o -o musicServer $(LDFLAGS)
	
serverthread.o: serverthread.c parser.h
	$(CC) -c serverthread.c -w
	
parser.o: parser.c parser.h
	$(CC) -c parser.c -w

sorter.o: sorter.c sorter.h
	$(CC) -c sorter.c

networking.o: networking.c networking.h sorter.h
	$(CC) -c networking.c  -w




clean:
	rm -f serverthread parser *.o