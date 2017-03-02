/*************************************************************
 ** Author: Carlos Carrillo                                  *
 ** Date:   02/19/2016                                       *
 ** Description: This is the main function of a program that *
 *  shows a heap implementation using a dynamic array, a     *
 *  stack, and a bag.                                        *
 ** Input:  String of characters and integer values.         *
 ** Output: The elements stored in the heap.                 *
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"

int main (int argc, const char * argv[])
{
    /* Global variables */
    FILE *filePointer;
    char desc[TASK_DESC_SIZE];
    char filename[128];
    char *nlptr;
    int priority;
    struct Task* newTask;
    struct Task* firstTask;
    /* Input validation variables */
    int status;
    int temp;
    
    char cmd = ' ';
    DynArr* mainList = createDynArr(10);
    
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    
    do{
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n");
        /* get input command (from the keyboard) */
        cmd = getchar();
        /* clear the trailing newline character */
        while (getchar() != '\n');
        
        switch (cmd){
                
            case 'l': /* load to-do list from a file */
                printf("\nPlease enter the name of the file you want to upload: ");
                scanf("%s", filename);
                
                /* Clear the trailing newline character */
                while (getchar() != '\n');
                filePointer = fopen(filename, "r");
                
                /* Copy list into array */
                loadList(mainList, filePointer);
                
                /* Close file */
                fclose(filePointer);
                printf("\nThe file has been successfully loaded!\n\n");
                break;
                
            case 's': /* save to-do list to a file */
                printf("\nPlease enter the filename in which you want to save the list: ");
                scanf("%s", filename);
                
                /* clear the trailing newline character */
                while (getchar() != '\n');
                filePointer = fopen(filename, "w");
                
                /* Save list into file */
                saveList(mainList, filePointer);
                
                /* Close file */
                fclose(filePointer);
                printf("\nThe file has been successfully saved!\n\n");
                break;
                
            case 'a': /* add a new task */
                printf("\nPlease enter the task description: ");
                
                /* Routine to allow spaces between words in task description */
                if (fgets(desc, sizeof(desc), stdin) != NULL){
                    /* remove trailing newline character */
                    nlptr = strchr(desc, '\n');
                    if (nlptr) {*nlptr = '\0';}}
                
                /* Loop to validate priority input */
                do {
                    printf("\nPlease enter the task priority in the range of [0-999]: ");
                    
                    /* Input validation: Reject if it's not a numeric value */
                    status = scanf("%d", &priority);
                    while(status!=1){
                        while((temp=getchar()) != EOF && temp != '\n');
                        printf("Invalid input... please enter ONLY a number: ");
                        status = scanf("%d", &priority);}

                    /* Input validation: Reject if value is out of range */
                    if(priority < 0||priority > 999){
                       printf("\nYour input is out of range! Please try again!\n");}
            
                } while(!(priority >= 0 && priority <= 999));
                
                /* clear the trailing newline character */
                while (getchar() != '\n');
                
                /* Create task */
                newTask = createTask(priority, desc);
                
                /* Add the task to the heap */
                addHeap(mainList, newTask, compare);
                printf("\nThe task '%s' has been added to your to-do list.\n\n", desc);
                break;
                
            case 'g': /* get the first task */
                
                /* Make sure heap is not empty */
                if (sizeDynArr(mainList) > 0){
                    firstTask = (struct Task*)getMinHeap(mainList);
                    printf("\nYour first task is: %s\n\n", firstTask->description);}
                else
                    printf("\nYour to-do list is empty!\n\n");

                break;
                
            case 'r': /* remove the first task */
                
                /* Make sure heap is not empty */
                if (sizeDynArr(mainList) > 0){
                    
                    /* Get first element to be displayed and freed */
                    firstTask = (struct Task*)getMinHeap(mainList);
                    
                    /* Call remove function */
                    removeMinHeap(mainList, compare);
                    printf("\nThe first task '%s' has been removed.\n\n", firstTask->description);
                    
                    /* Free first-task memory */
                    free(firstTask);}
                else
                    printf("\nYour to-do list is empty!\n\n");

                break;
                
            case 'p': /* print the list */
                
                /* Make sure heap is not empty */
                if (sizeDynArr(mainList) > 0){
                    printList(mainList);}
                else
                    printf("\nYour to-do list is empty!\n\n");
                
                break;
                
            case 'e': /* exit the program */
                
                printf("\nHasta la vista, baby!!!\n\n");
                break;
                
            default: 
                printf("Please choose a valid option\n\n" );
                break;
        }
    }
    while(cmd != 'e');
    /* delete the list */
    deleteDynArr(mainList);
    
    return 0;
}


