/************************************************************
 ** Author: Carlos Carrillo                                 *
 ** Date:   01/27/2016                                      *
 ** Description: This program is an implementation of the   *
 *  deque ADT using a circularly linked list.               *
 ** Input: String of integers.                              *
 ** Output: All of the elements stored in the container.    *
 ***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
    TYPE value;/* value of the link */
    struct DLink * next;/* pointer to the next link */
    struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
    int size;/* number of links in the deque */
    struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
 ************************************************************************ */

/* Initialize deque.
 
	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
 */
void _initCirListDeque (struct cirListDeque *q){
    
    /* Allocate memory for Sentinel */
    q->Sentinel = (struct DLink *) malloc(sizeof(struct DLink));
    assert(q->Sentinel != 0);
    
    /* Set all initial links to be equal to Sentinel */
    q->Sentinel->prev = q->Sentinel;
    q->Sentinel->next = q->Sentinel;
    
    /* Initialize size = 0 */
    q->size = 0;
}

/*
 create a new circular list deque
 
 */

struct cirListDeque *createCirListDeque(){
    struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
    _initCirListDeque(newCL);
    return(newCL);
}


/* Create a link for a value.
 
	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
 */
struct DLink * _createLink (TYPE val){
    
    /* Create a link dinamically allocated */
    struct DLink* newLink = (struct DLink *) malloc(sizeof(struct DLink));
    assert(newLink != 0); /* Double check if it was properly created */
    
    /* Pass the value to the link just created */
    newLink->value = val;
    
    /*Return the value of the link just created */
    return newLink;
}

/* Adds a link after another link
 
	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque
	post:	the new link is added into the deque after the existing link
 */
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v){
    
    /* Make sure that q and lnk exist */
    assert(q != 0);
    assert(lnk != 0);
    
    /* Use/call '_createLink' to create the link to be added */
    struct DLink* addLink = _createLink(v);
    
    /* Replace/assign pointers to add the new link */
    addLink->prev = lnk;
    addLink->next = lnk->next;
    lnk->next->prev = addLink;
    lnk->next = addLink;
    
    /* Increment collection size */
    q->size++;

}

/* Adds a link to the back of the deque
 
	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
 */
void addBackCirListDeque (struct cirListDeque *q, TYPE val){
    
    /* Make sure that q exist */
    assert(q != 0);
    
    /* Use/call '_addLinkAfter' to add the new link */
    _addLinkAfter(q, q->Sentinel->prev, val);
}

/* Adds a link to the front of the deque
 
	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
 */
void addFrontCirListDeque(struct cirListDeque *q, TYPE val){
    
    /* Make sure that q exist */
    assert(q != 0);
    
    /* Use/call '_addLinkAfter' to add the new link */
    _addLinkAfter(q, q->Sentinel, val);
}

/* Get the value of the front of the deque
 
	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
 */
TYPE frontCirListDeque(struct cirListDeque *q){
    
    /* Make sure that q exist and size != 0 */
    assert(q != 0);
    assert(q->size != 0);
    
    /* Return front link */
    return q->Sentinel->next->value;
}

/* Get the value of the back of the deque
 
	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
 */
TYPE backCirListDeque(struct cirListDeque *q){
    
    /* Make sure that q exist and size != 0 */
    assert(q != 0);
    assert(q->size != 0);
    
    /* Return front link */
    return q->Sentinel->prev->value;
}

/* Remove a link from the deque
 
	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
 */
void _removeLink(struct cirListDeque *q, struct DLink *lnk){
    
    /* Make sure that q exist and size != 0 */
    assert(q != 0);
    assert(q->size != 0);
    
    /* Use/call '_createLink' to create the link to be added */
    struct DLink * removeLink = lnk->prev;
    
    /* Reassign links accordingly */
    removeLink->next = lnk->next;
    removeLink = lnk->next;
    removeLink->prev = lnk->prev;
    
    /* Deallocate memory for lnk */
    free(lnk);
    
    /* Decrease collection size */
    q->size--;
}

/* Remove the front of the deque
 
	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
 */
void removeFrontCirListDeque (struct cirListDeque *q){
    
    /* Make sure that q exist and size != 0 */
    assert(q != 0);
    assert(q->size != 0);
    
    /* Use/call '_removeLink' to remove link from the front */
    _removeLink(q, q->Sentinel->next);
}


/* Remove the back of the deque
 
	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
 */
void removeBackCirListDeque(struct cirListDeque *q){
    
    /* Make sure that q exist and size != 0 */
    assert(q != 0);
    assert(q->size != 0);
    
    /* Use/call '_removeLink' to remove link from the front */
    _removeLink(q, q->Sentinel->prev);
    printf("\n"); //just to better visualize testing
}

/* De-allocate all links of the deque
 
	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
 */
void freeCirListDeque(struct cirListDeque *q){
    
    /* Free/delete all the links in the collection */
    while(q->Sentinel->next != q->Sentinel){
        /* Print deleting process for testing purposes */
        printf("Deleting link = %g\n", frontCirListDeque(q));
        removeFrontCirListDeque(q);}
    
    /* Also free the Sentinel */
    free(q->Sentinel);
    
    /* Make Sentinel = 0 just in case */
    q->Sentinel = 0;
    
    printf("\n"); //just to better visualize the testing process
}

/* Check whether the deque is empty
 
	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
 */
int isEmptyCirListDeque(struct cirListDeque *q){
    
    /* Make sure 'q' exist */
    assert(q != 0);
    
    /* Return appropriate values depending on size */
    if(q->size == 0){
        return 1;}
    else{
        return 0;}
}

/* Print the links in the deque from front to back
 
	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
 */
void printCirListDeque(struct cirListDeque *q){
    
    /* Make sure 'q' exist and size != 0 */
    assert(q != 0);
    assert(q->size != 0);
    
    /* create a link to represent the Sentinel */
    struct DLink * tempSentinel = q->Sentinel;
    //assert(tempSentinel != 0); // make sure the new link was properly created
    
    /* Print the values starting from the link next to Sentinel */
    while(tempSentinel->next != q->Sentinel){
        tempSentinel = tempSentinel->next;
        printf("%.2lf\n", tempSentinel->value);} //print double with only 2 decimal digits
    
    printf("\n"); //just to better visualize the testing process
}

/* Reverse the deque
 
	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
 */
void reverseCirListDeque(struct cirListDeque *q){
    
    /* Make sure 'q' exist and size != 0 */
    assert(q != 0);
    assert(q->size != 0);
    
    /* Create 2 pointers for the swap operation */
    struct DLink *currentLink = q->Sentinel;
    assert(currentLink != 0); //make sure the link was properly created
    struct DLink *tempLink = q->Sentinel->prev;
    assert(tempLink != 0); //make sure the link was properly created
    
    // Swap prev and next for each link
    do{
        tempLink = currentLink->next;
        currentLink->next = currentLink->prev;
        currentLink->prev = tempLink;
        currentLink = tempLink;
    } while(currentLink != q->Sentinel);
}



