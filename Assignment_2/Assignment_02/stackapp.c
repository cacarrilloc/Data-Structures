/************************************************************
 ** Author: Carlos Carrillo                                 *
 ** Date:   01/20/2016                                      *
 ** Description: This program is an application of a stack  *
 *  to check balanced parentheses, braces, and brackets.    *
 ** Input: String of parentheses characters.                *
 ** Output: Balanced = 1 and Not balanced = 0.              *
 ***********************************************************/

/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"

/****************************************************************
Using stack to check for unbalanced parentheses.
*****************************************************************/

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null	*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre:    s is not null
	post:	*/

int isBalanced(char* s)
{
    /* Variable to temporarily store every char from the string */
    char tempChar;
    
    /* Declare, allocate, and create a dynamic array to represent a stack */
    struct DynArr *stack = newDynArr(5);
    
    /* Loop to check the parentheses balance. */
    /* The particular case '{ ( } )' will be considered as NOT BALANCED */
    /* Algorithm borrowed from www.geeksforgeeks.org/check-for- */
    /* balanced-parentheses-in-an-expression/ */
    do{
        /* Use nextChar() to read through the string */
        tempChar = nextChar(s);
        
        switch(tempChar)
        {
            /* Only store open parentheses in the stack */
            case '(':
                pushDynArr(stack, tempChar);
                break;
            case '{':
                pushDynArr(stack, tempChar);
                break;
            case '[':
                pushDynArr(stack, tempChar);
                break;
                
            /* Check if the top of the stack matches with tempChar. */
            /* If it doesn't, the string is unbalanced. */
            case ')':
                if(!isEmptyDynArr(stack) && topDynArr(stack) == '('){
                    popDynArr(stack);}
                else{
                    return 0;} /* Not balanced */
                break;
                
            case '}':
                if(!isEmptyDynArr(stack) && topDynArr(stack) == '{'){
                    popDynArr(stack);}
                else{
                    return 0;} /* Not balanced */
                break;
                
            case ']':
                if(!isEmptyDynArr(stack) && topDynArr(stack) == '['){
                    popDynArr(stack);}
                else{
                    return 0;} /* Not balanced */
                break;
                
            default:
                break; /* if it's not a bracket, do nothing */
        }
        
    }while(tempChar != '\0');
    
    /* The stack should be empty at this point */
    if(!isEmptyDynArr(stack)){
        return 0;}
    
    /* deallocate stack memory */
    deleteDynArr(stack);
    
    /* return when the string is balanced */
    return 1;
}

int main(int argc, char* argv[]){
    
    char* s=argv[1];
    int res;
    
    printf("Assignment 2\n");
    
    /*Read input from the keyboard using scanf*/
    char input[256];
    
    /* prompt the user */
    printf("\nType a string of parentheses in any order: ");
    scanf("%s", input);
    
    s = input;
    
    /* Check precondition 's != NULL'. */
    if(s == NULL){
        printf("No input detected.\n");}
    
    /* Pass value to isBalanced() */
    else{
        res = isBalanced(s);
        
        if(res)
            printf("\nThe string %s is balanced\n\n",s);
        else
            printf("\nThe string %s is not balanced\n\n",s);
    }
    
    return 0;
}


