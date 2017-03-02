/*************************************************************
 ** Author: Carlos Carrillo                                  *
 ** Date:   02/19/2016                                       *
 ** Description: This program is an implementation of a      *
 *  compare function which test two values of a node to      *
 *  determine if one is less than, greater than, or equal to *
 *  the other; and the printList function which prints the   *
 *  list of tasks entered by the user.                       *
 ** Input:  Two node values.                                 *
 ** Output: if left < right return -1;                       *
 *          if left > right return 1;                        *
 *          if left = right return 0.                        *
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"

/*----------------------------------------------------------------------------
 very similar to the compareTo method in java or the strcmp function in c. it
 returns an integer to tell you if the left value is greater then, less then, or
 equal to the right value. you are comparing the number variable, letter is not
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
int compare(TYPE left, TYPE right)
{
    /* Create struct data pointers */
    struct Task *leftElement;
    struct Task *rightElement;
    
    /* Cast left and right to (struct data *)*/
    leftElement = (struct Task *) left;
    rightElement = (struct Task *) right;
    
    if(leftElement->priority < rightElement->priority){
        return -1;}
    
    else if(leftElement->priority > rightElement->priority){
        return 1;}
    
    else
        return 0;
}

/***************************************************************
Print type function defined by user to print their specific type
****************************************************************/


void print_type(TYPE val){
    
    struct Task *v = (struct Task*) val;
    printf("Priority: %.3d   Task: %s  \n", v->priority, v->description);
}

/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
TaskP createTask (int priority, char *desc){
    
    /* create an allocate memory for a new task */
    TaskP newTask = (TaskP) malloc(sizeof(struct Task));
    
    newTask->priority = priority;
    strcpy(newTask->description, desc);
    
    return newTask;
}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the
			task priority, followed by a tab character (\t), and
			the task description.

			The tasks are not necessarily stored in the file in
			priority order.

*/

/* This function has been modified in order to save the items in order on the external file */
void saveList(DynArr *heap, FILE *filePtr)
{
    int i;
	TaskP task;
	assert(sizeDynArr(heap) > 0);
    
    /* Pre-sort list to save the list in order */
    sortHeap(heap, compare);
    
	/* Inversed loop to save list in the right order */
    for(i = sizeDynArr(heap)-1; i >= 0; i--){
	  task = getDynArr(heap, i);
	  fprintf(filePtr, "%d\t%s\n", task->priority, task->description);}
}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
			Refer to the saveList() function for the format of tasks in the file
*/
void loadList(DynArr *heap, FILE *filePtr)
{
  TaskP task;
  char line[100];  /* Assume lines < 100 */
  char desc[TASK_DESC_SIZE];
  int priority;

  /* Read the priority first, then the description.
   * fgets() is used to read string with spaces
   */

  while(fgets(line, sizeof(line), filePtr) != 0)
    {
      sscanf(line, "%d\t%[^\n]", &priority, desc);
      task = createTask(priority, desc);
      addHeap(heap, task, compare);
    } /* should use feof to make sure it found eof and not error*/

}

/*  Print the list in priority order.  This requires that either we sort it...or make a copy and pull
off the smallest element one at a time.  That's what we've done here.

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
			The tasks are not removed from the list.
*/

/* I have modified this function to make it work for my own design */
void printList(DynArr *heap)
{
    int currIndx = sizeDynArr(heap) - 1;
    TYPE temp;
    
    /* Check the list is not empty */
    assert(sizeDynArr(heap) > 0);
    
    /* Sort into descending priority */
    sortHeap(heap, compare);
    
    /* Call print_type to print all the list elements */
    printf("\n");
    while(currIndx >= 0){
        print_type(getDynArr(heap, currIndx));
        currIndx--;}
    printf("\n");
    
    /* Re-accomadate first element after printing */
    temp = getMinHeap(heap);
    removeMinHeap(heap, compare);
    addHeap(heap, temp, compare);
}