#Author: Carlos Carrillo
#Date:   01/19/2016
#Description: This is the makefile for Assignment_2

all: prog testda

prog: dynamicArray.o stackapp.o
	gcc -g -Wall -std=c99 -o prog dynamicArray.o stackapp.o -lm

testda: dynamicArray.o testDynArray.o
	gcc -g -Wall -std=c99 -o testda dynamicArray.o testDynArray.o

stackapp.o: stackapp.c dynArray.h
	gcc -g -Wall -std=c99 -c stackapp.c

testDynArray.o: testDynArray.c dynArray.h
	gcc -g -Wall -std=c99 -c testDynArray.c

dynamicArray.o: dynamicArray.c dynArray.h
	gcc -g -Wall -std=c99 -c dynamicArray.c

clean:
	rm dynamicArray.o
	rm stackapp.o
	rm testDynArray.o
	rm stackapp
	rm testda