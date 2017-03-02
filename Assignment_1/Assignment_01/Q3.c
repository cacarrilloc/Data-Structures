/* CS261- Assignment 1 - Q.3*/
/* Name: Carlos Carrillo
 * Date: 01/12/2016
 * Solution description: This program contains:
 * 1) A function that sorts a given array of n integers in ascending order.
 * 2) A main function that:
 *      a. Declares an integer n and assign it a value of 20.
 *      b. Allocates memory for an array of n integers using malloc. 
 *      c. Fills the array with random numbers, 
 *      d. Prints the sorted contents of the array.*/
 
#include <stdio.h>
#include <stdlib.h>

/*#include <time.h> //for future/possible use*/

void sort(int* number, int n){
    
    /*Sort the given array number of length n*/
    /*Sorting algorithm borrowed from www.sanfoundry.com/
     c-program-sort-array-ascending-order/ */
    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j){
            if (number[i] > number[j]){
                int temp =  number[i];
                number[i] = number[j];
                number[j] = temp;}}
    }
}

int main(int argc, const char * argv[]){
    
    printf("\nWELCOME TO Q3.c PROGRAM:\n");
    
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
    int *intArray = (int *)malloc(sizeof(int)*n);
    
    /*Fill this array with random numbers, using rand().*/
    /*srand(time(NULL)); //for future/possible use.*/
    for(int i=0; i < n; i++){
        intArray[i] = (rand() % 100) + 1;}
    
    /*Print the contents of the array.*/
    printf("\nUNSORTED ARRAY: \n");
    
    for(int i=0; i < n; i++){
        printf("Value = %.2d\n", intArray[i]);}

    /*Pass this array along with n to the sort() function of part a.*/
    sort(intArray, n);
    
    /*Print the contents of the array.*/
    printf("\nSORTED ARRAY (ascending order):\n");
    
    for(int i=0; i < n; i++){
        printf("Value = %.2d\n", intArray[i]);}
    
    printf("\n");
    
    return 0;
}
