/* CS261- Assignment 1 - Q.0*/
/* Name: Carlos Carrillo
 * Date: 01/11/2016
 * Solution description: This program prints
 * the address of x (using the address of operator);
 * pass x as an argument to a function. In the function,
 * it prints the value of the integer pointed to by 
 * iptr, the address pointed to by iptr, and the 
 * address of iptr itself. In the main function,
 * following the call to fooA(...), it prints the 
 * value of x. */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
    
    /*Print the value pointed to by iptr*/
    printf("2) Value pointed to by 'iptr' = %d\n", *iptr);
     
    /*Print the address pointed to by iptr*/
    printf("3) Address pointed to by 'iptr' = %p\n", iptr);
    
    /*Print the address of iptr itself*/
    printf("4) Address of 'iptr' itself = %p\n", &iptr);
}

int main(int argc, const char * argv[]){
    
    printf("\nWELCOME TO Q0.c PROGRAM:\n\n");
    
    /*declare an integer x*/
    int x = 4;
    
    /*print the address of x*/
    int *tempPtr = &x;
    printf("1) Address of 'x' = %p\n", tempPtr);
    
    /*Call fooA() with the address of x*/
    fooA(&x);
    
    /*print the value of x*/
    printf("5) Value of 'x' = %d\n\n", x);
    
    return 0;
}
