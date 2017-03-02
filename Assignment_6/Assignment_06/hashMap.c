/************************************************************
 ** Author: Carlos Carrillo                                 *
 ** Date:   02/29/2016                                      *
 ** Description: This program shows the implementation of a *
 *  Hash map-table using Buckets .                          *
 ** Input:  String of characters and integer values.        *
 ** Output: The elements stored in the heap.                *
 ***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "hashMap.h"

/* The first hashing function you can use */
int stringHash1(char * str){
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/* The second hashing function you can use */
int stringHash2(char * str){
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* Initialize the supplied hashMap struct */
void _initMap (struct hashMap * ht, int tableSize) {
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* Allocate memory and initialize a hash map */
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/* Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value. */

void _freeMap (struct hashMap * ht){
    
    int i;
    /* Create temporary pointers */
    struct hashLink *cur, *last;
    
    /* Walk throught the entire map */
    for(i=0; i<ht->tableSize; i++){
        
        cur = ht->table[i];
        while(cur !=0){
            last = cur->next;
            /* Free actual node */
            free(cur);
            cur = last;}
        /* Erase value */
        ht->table[i] = 0;
    }
    /* Reset/free map values */
    ht->tableSize = 0;
    ht->count = 0;
    /* Free up the all memory */
    free(ht->table);
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht){
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* Resizes the hash table to be the size newTableSize */
void _setTableSize(struct hashMap * ht, int newTableSize){
    
    int i;
    int oldSize = ht->tableSize; //Save old size
    
    /* Pointer declarations */
    struct hashLink* cur;
    struct hashMap* newTable;
    
    /* Use createMap() to build a new resized table */
    newTable = createMap(newTableSize);
    
    /* Walk throught the old table and copy elements into newTable */
    for(i=0; i<oldSize; i++){
        /* Set cur to the first position in the old table */
        cur = ht->table[i];
        /* Check every single bucket @ index */
        while(cur != 0){
            insertMap(newTable, cur->key, cur->value); //insert elements to newTable
            cur = cur->next;}} //move forward
    
    /* Use _freeMap() to release old table memory */
    _freeMap(ht);
    
    /* Update pointer values accordingly */
    ht->table = newTable->table;
    ht->tableSize = newTable->tableSize;
    ht->count = newTable->count;
}

/* Insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h). */

void insertMap (struct hashMap * ht, KeyType k, ValueType v){
    
    int hashIndex;
    
    /* Create link to be inserted */
    struct hashLink * newLink = (struct hashLink *) malloc(sizeof(struct hashLink));
    assert(newLink);
    
    /* Find index in terms of HASHING_FUNCTION variable*/
    if(HASHING_FUNCTION == 1)
        hashIndex = stringHash1(k) % ht->tableSize;
    else
        hashIndex = stringHash2(k) % ht->tableSize;
    
    /* Make sure index is NOT a negative value */
    if (hashIndex < 0) hashIndex += ht->tableSize;
    
    /* Remove keys if it already exists in the map */
    if(containsKey(ht, k)) removeKey(ht, k);
    
    newLink->key = k; //fill new link with the new key
    newLink->value = v; //fill new link with the new value
    newLink->next = ht->table[hashIndex]; //move ht->table[hashIndex] to the next link/position
    ht->table[hashIndex] = newLink; //add to bucket/put new values
    ht->count++; //increase size
    
    /* Resize table if λ is too big */
    if ((ht->count / (double)ht->tableSize) > LOAD_FACTOR_THRESHOLD) {
        _setTableSize(ht, (ht->tableSize * 2));}
}

/* This returns the value (which is void*) stored in a hashLink specified by the key k.
 
 If the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 If the supplied key is not in the hashtable return NULL. */

ValueType* atMap (struct hashMap * ht, KeyType k){
    
    int hashIndex;
    
    /* Pointer to be returned with the value member of the key */
    struct hashLink *cur;
    
    /* Find index in terms of HASHING_FUNCTION variable*/
    if(HASHING_FUNCTION == 1)
        hashIndex = stringHash1(k) % ht->tableSize;
    else
        hashIndex = stringHash2(k) % ht->tableSize;
    
    /* Get position in hash table */
    cur = ht->table[hashIndex];
    
    /* Search for the key and return its value member */
    while(cur != 0){
        if(strcmp(k, cur->key) == 0)
            return &cur->value;
        cur = cur->next;}
    
    return NULL;
}

/* A simple yes/no if the key is in the hashtable.
 0 is no, all other values are yes. */

int containsKey (struct hashMap * ht, KeyType k){
    
    int hashIndex;
    struct hashLink *cur;
    
    /* Find index in terms of HASHING_FUNCTION variable*/
    if(HASHING_FUNCTION == 1)
        hashIndex = stringHash1(k) % ht->tableSize;
    else
        hashIndex = stringHash2(k) % ht->tableSize;
    
    /* Make sure index is NOT a negative value */
    if (hashIndex < 0) hashIndex += ht->tableSize;
    
    /* get position in hash table */
    cur = ht->table[hashIndex];
    
    while(cur != 0) {
        /* element is found */
        if(strcmp(k, cur->key) == 0){
            return 1;}
        cur = cur->next;} //move forward
    
    /* element is NOT found */
	return 0;
}

/* Find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program. */

void removeKey (struct hashMap * ht, KeyType k){
    
    int hashIndex;
    /* Temporary pointers */
    struct hashLink *cur = NULL;
    struct hashLink *last;
    
    /* Find index in terms of HASHING_FUNCTION variable */
    if(HASHING_FUNCTION == 1)
        hashIndex = stringHash1(k) % ht->tableSize;
    else
        hashIndex = stringHash2(k) % ht->tableSize;
    
    /* Make sure index is NOT a negative value */
    if (hashIndex < 0) hashIndex += ht->tableSize;
    
    /* Make sure the element is the array */
    if(containsKey (ht, k)){
        cur = ht->table[hashIndex];   //assign temporary pointer
        last = ht->table[hashIndex];}  //assign temporary pointer
       
       while(cur != 0){
           
           if(strcmp(k, cur->key) == 0){
               /* If the key is the firstlink in the linked list stored in the bucket */
               if(cur == ht->table[hashIndex]){
                   ht->table[hashIndex] = cur->next;}
               /* Otherwise */
               else{
                   last->next = cur->next;
                   free(cur);
                   ht->count--; //decrement hashLink counter
                   cur = 0;}}   //jump out of loop.
           else{
               last = cur; 
               cur = cur->next;} //move forward	
       }
}

/* Returns the number of hashLinks in the table */
int size (struct hashMap *ht){
    return ht->count;
}

/* Returns the number of buckets in the table */
int capacity(struct hashMap *ht){
	return ht->tableSize;
}

/* Returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them. */

int emptyBuckets(struct hashMap *ht) {
    
    int i;
    int emptyBucketCount = 0; //counts emptyBuckets
    
    for(i=0; i< ht->tableSize; i++){
        if(ht->table[i] == 0){
            /* Increase counter if an empty bucket is found */
            emptyBucketCount += emptyBucketCount;}
    }
    return emptyBucketCount;
}

/* Returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other) */

float tableLoad(struct hashMap *ht){
    
    /* Float variable to represent the radio */
    float ratioRange = 0.0;
    
    /* Actual computation */
    ratioRange = (float)ht->count / (float)ht->tableSize;
    
    /* Return radio */
    return ratioRange;
}

void printMap (struct hashMap * ht){
	int i;
	struct hashLink *temp;	
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %4d -> ", i);
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
    printf("\n");
}
