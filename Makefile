CC=gcc
CFLAGS=-I.

all: hellomake.o hellofunc.o
	gcc hellomake.o hellofunc.o -o test
