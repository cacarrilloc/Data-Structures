/*************************************************************
 ** Author: Carlos Carrillo                                  *
 ** Date:   02/09/2016                                       *
 ** Description: This program is an implementation of a      *
 *  compare function which test two values of a node to      *
 *  determine if one is less than, greater than, or equal to *
 *  the other; anf the print_type function which prints the  *
 *  type of values used in the main program.                 *
 ** Input:  Two node values.                                 *
 ** Output: if left < right return -1;                       *
 *          if left > right return 1;                        *
 *          if left = right return 0.                        *
 ************************************************************/

#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"

/*----------------------------------------------------------------------------
 Very similar to the compareTo method in java or the strcmp function in c. it
 returns an integer to tell you if the left value is greater than, less than, or
 equal to the right value. You are comparing the number variable, letter is not
 used in the comparison.

 if left < right return -1
 if left > right return 1
 if left = right return 0
 */

 /*Define this function, type casting the value of void * to the desired type.
  The current definition of TYPE in bst.h is void*, which means that left and
  right are void pointers. To compare left and right, you should first cast
  left and right to the corresponding pointer type (struct data *), and then
  compare the values pointed by the casted pointers.

  DO NOT compare the addresses pointed by left and right, i.e. "if (left < right)",
  which is really wrong.
 */
int compare(TYPE left, TYPE right){
    
    /* Create struct data pointers */
    struct data *leftPointer;
    struct data *rightPointer;
    
    /* Cast left and right to (struct data *)*/
    leftPointer = (struct data *) left;
    rightPointer = (struct data *) right;
    
    if(leftPointer->number < rightPointer->number){
        return -1;}
    
    else if(leftPointer->number > rightPointer->number){
        return 1;}
    
    else
        return 0;
}

/*Define this function, type casting the value of void * to the desired type*/
void print_type(TYPE curval){
    
    /* Create struct data pointer */
    struct data *curvalPointer;
    
    /* Cast pointer to (struct data *) */
    curvalPointer = (struct data *) curval;
    
    /* Print node values and names */
    printf("Node Value = %.3d, Node Description: %s\n", curvalPointer->number, curvalPointer->name);
}


