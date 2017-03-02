/************************************************************
 ** Author: Carlos Carrillo                                 *
 ** Date:   01/26/2016                                      *
 ** Description: This program shows some implementations of *
 *  a deque and bag ADTs                                    *
 ** Input: String of integers.                              *
 ** Output: Some or all the elements stored in the ADTs.    *
 ***********************************************************/

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* Double Link*/
struct DLink {
    
    TYPE value;
    struct DLink * next;
    struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
    int size;
    struct DLink *firstLink;
    struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
 */

void _initList (struct linkedList *lst) {
    
    /* Allocate memory for firstLink */
    lst->firstLink = malloc(sizeof(struct DLink));
   	assert(lst->firstLink != 0);
    
    /* Allocate memory for lastLink */
    lst->lastLink = malloc(sizeof(struct DLink));
   	assert(lst->lastLink);
    
    /* Initialize lastLink and firstLink when size = 0 */
    lst->firstLink->next = lst->lastLink;
    lst->lastLink->prev = lst->firstLink;
    lst->size = 0;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
    struct linkedList *newList = malloc(sizeof(struct linkedList));
    _initList(newList);
    return(newList);
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
 */

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v){
    
    /* Allocate memory for the link to be added */
    struct DLink *addedLink = (struct DLink*) malloc(sizeof(struct DLink));
    assert(addedLink != 0);
    
    /* Create link to perform the adLink operation */
    struct DLink *prevLink = l->prev;
    
    /* Assign attributes to the new link */
    addedLink->value = v;
    addedLink->next = l;
    addedLink->prev = prevLink;
    
    /* Reassign l and previousLink attributes */
    l->prev = addedLink;
    prevLink->next = addedLink;
    
    /* Increase size */
    lst->size++;
}

/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
 */

void addFrontList(struct linkedList *lst, TYPE e){

    /* Just call addBefore */
    _addLinkBefore(lst, lst->firstLink->next, e);
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
 */

void addBackList(struct linkedList *lst, TYPE e) {
    
    /* Just call addBefore */
    _addLinkBefore(lst, lst->lastLink, e);
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
 */

TYPE frontList (struct linkedList *lst) {
    
    /* make sure it's NOT and empty collection */
    assert(!isEmptyList(lst));
    
    /* Return first/front element from the collection */
    return lst->firstLink->next->value;
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
 */

TYPE backList (struct linkedList *lst){
    
    /* make sure it's NOT and empty collection */
    assert(!isEmptyList(lst));
    
    /* Return first/front element from the collection */
    return lst->lastLink->prev->value;
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
 */

void _removeLink(struct linkedList *lst, struct DLink *l)
{
    /* make sure it's NOT and empty collection */
    assert(!isEmptyList(lst));
    
    /* reassign prev and next link */
    l->prev->next = l->next;
    l->next->prev = l->prev;
    
    /* Deallocate memory */
    free(l);
    
    /* decrease size */
    lst->size--;
}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
 */

void removeFrontList(struct linkedList *lst){
    
    /* make sure it's NOT and empty collection */
    assert(!isEmptyList(lst));
    
    /* Use _removeLink to remove the first link in front */
    _removeLink (lst, lst->firstLink->next);
}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
 */

void removeBackList(struct linkedList *lst){
    
    /* Make sure it's NOT and empty collection */
    assert(!isEmptyList(lst));
    
    /* Use _removeLink to remove the first link in front */
    _removeLink (lst, lst->lastLink->prev);
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
 */

int isEmptyList(struct linkedList *lst){
    
    assert(lst);
    return lst->size == 0;
}

/* Function to print list
 Pre: lst is not null
 */
void printList(struct linkedList* lst){
    
    /* make sure it's NOT and empty collection */
    assert(!isEmptyList(lst));
    
    /* Create a link to keep current value to be printed */
    struct DLink *currentLink = lst->firstLink;
    
    /* Print all elements between the 2 sentinels */
    while(currentLink->next != lst->lastLink){
        currentLink = currentLink->next;
        printf("%d\n", currentLink->value);}
}

/*
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v){
    
    /* Just call addFrontList() to add the element */
    addFrontList(lst, v);
}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0
 
	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
 */
int containsList (struct linkedList *lst, TYPE e){
    
    /* make sure it's NOT and empty collection */
    assert(!isEmptyList(lst));
    
    /* Create a new link to represent the current */
    /* link to be compared within the loop */
    struct DLink *currentLink = lst->firstLink->next;
    
    /* Transverse the collection to find the element wanted */
    while(currentLink != lst->lastLink){
        
        /* Return 1 if the element is found */
        if(EQ(currentLink->value, e)){
            return 1;}
        
        /* set the pointer to the next element */
        currentLink = currentLink->next;}
    
    /* Return 0 if the element is NOT found */
    return 0;
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs
 
	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
 */
void removeList (struct linkedList *lst, TYPE e){
    
    /* make sure it's NOT and empty collection */
    assert(!isEmptyList(lst));
    
    /* Create a new link to represent the current */
    /* link to be removed within loop */
    struct DLink *currentLink = lst->firstLink->next;
    
    /* Transverse the collection to find the element wanted */
    while(currentLink != lst->lastLink){
        
        /* Remove the element if it's found */
        if(EQ(currentLink->value, e)){
            _removeLink(lst, currentLink);
            
            /* Since the desired element may be more than once */
            /* within the collection, make sure only ONE copy  */
            /* of the element is removed. */
            break;}
        
        currentLink = currentLink->next;
    }
}
