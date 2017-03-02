#Author: Carlos Carrillo
#Date:   09/24/2015
#Description: This is the makefile for Assignment_0

#This target will compile the entire program

default: prog 

assignment0.o: assignment0.c
	gcc -Wall -std=c99 -c assignment0.c

prog: assignment0.o
	gcc -Wall -std=c99 -o prog assignment0.o

clean:
	rm assignment0.o

cleanall: clean 
	rm prog