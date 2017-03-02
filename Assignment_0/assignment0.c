/************************************************************
 ** Author: Carlos Carrillo                                 *
 ** Date:   01/06/2016                                      *
 ** Description: This program converts a value from inches  *
 *  to centimeters and vice versa.                          *
 ** Input: A float and String of characters variables       *
 ** Output: The input values converted into the target unit.*
 ***********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    double cmts;    //input variable
    double inch;    //input variable
    
    /* get the number of centimeter from the user */
    printf("\nEnter the number of inches to be converted: ");
    scanf_s("%lf", &inch);
    
    /* print the input */
    printf("\n%.2f inch is equal to ", inch);
    
    /* do the conversion */
    cmts = inch * 2.54;
    
    /* print the result */
    printf("%.2f cm.\n\n", cmts);
    
    /* get the number of centimeter from the user */
    printf("Enter the number of centimeters to be converted: ");
    scanf_s("%lf", &cmts);
    
    /* print the input */
    printf("\n%.2f cm is equal to ", cmts);
    
    /* do the conversion */
    inch = cmts * 0.39370;
    
    /* print the result */
    printf("%.2f inch.\n\n", inch);
    
    return(0);    
}