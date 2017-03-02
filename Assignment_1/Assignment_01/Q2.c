/* CS261- Assignment 1 - Q.2*/
/* Name: Carlos Carrillo
 * Date: 01/11/2016
 * Solution description: This program contains:
 * 1) A function that performs the following computations:
 *   a. Sets the value of a to twice its original value.
 *   b. Sets the value of b to half of its original value.
 *   c. Assigns a + b to c.
 *   d. Returns the value of c.
 * 2) A Main function that:
 *   a. Prints the values of x, y, and z.
 *   b. Calls foo(...) appropriately passing x, y, and z as
 *      arguments and print the returned value. 
 *   c. Prints out the values of x, y, and z after the function call*/
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a * 2;
    
    /*Set b to half its original value*/
    *b = *b / 2;
    
    /*Assign a+b to c*/
    c = *a + *b;
    
    /*Return c*/
    return c;
}

int main(int argc, const char * argv[]){
    
    printf("\nWELCOME TO Q2.c PROGRAM:\n");
    
    /*Declare three integers x, y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    
    /*Print the values of x, y and z*/
    printf("\nINITIAL VALUES:\n");
    printf("Initial value of 'x' = %d\n", x);
    printf("Initial value of 'y' = %d\n", y);
    printf("Initial value of 'z' = %d\n", z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    int storeFoo = foo(&x, &y, z);
    
    /*Print the value returned by foo*/
    printf("\nThe value returned by foo is: %d\n", storeFoo);
    
    /*Print the values of x, y and z again*/
    printf("\nFINAL VALUES:\n");
    printf("Final value of 'x' = %d\n", x);
    printf("Final value of 'y' = %d\n", y);
    printf("Final value of 'z' = %d\n\n", z);
 
    /*Is the return value different than the value of z? Why? YES! 
     'z' was never modified since foo() only takes a copy of its value.
     Also, 'c' is not a pointer within foo(), so there is not access 
     to the location of 'z'. Consequently, it cannot be modified*/
    return 0;
}

