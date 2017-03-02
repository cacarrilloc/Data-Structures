/*************************************************************
 ** Author: Carlos Carrillo                                  *
 ** Date:   02/29/2016                                       *
 ** Description: This is the main function of a program that *
 *  uses a hash-map implementation to create a concordance   *
 *  program, which counts the number of occurrences of each  *
 *  word in a document.                                      *
 ** Input:  String of characters.                            *
 ** Output: Number of occurrences of each word in a document.*
 ************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/* The getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it. */

char* getWord(FILE *file);

/* Function to print table as requested by the assignment */
void printConcordance (struct hashMap * ht);

int main (int argc, const char * argv[]) {
	const char* filename;
	struct hashMap *hashTable;	
	int tableSize = 10;
    char* word;
	clock_t timer;
	FILE *fileptr;
    
    /* Concordance code variables */
    int* occurrence;
    int firstOccurrence;
    
    /* This part is using command line arguments, you can use them if you wish
     but it is not required. DO NOT remove this code though, we will use it for
     testing your program.
     
     if you wish not to use command line arguments manually type in your
     filename and path in the else case. */
    
    if(argc == 2)
        filename = argv[1];
    else
        filename = "input1.txt"; /*specify your input text file here*/
    
	timer = clock();
	
	hashTable = createMap(tableSize);
	
    /*... concordance code goes here ...*/
    
    printf("Opening %s now...\n\n", filename);
    fileptr = fopen(filename, "r"); // open file
    
    /* Transfer input */
    word = getWord(fileptr);
    
    while (word != NULL){
        
        /* Increment occurrence variable if it is already in the table */
        if (containsKey(hashTable, word)){
            occurrence = atMap(hashTable, word);
            *occurrence += 1;}
        
        /* Otherwise create a new entry with a value equals to 1 */
        else{
            firstOccurrence = 1;
            insertMap(hashTable, word, firstOccurrence);}
        
        /* move to the next word */
        word = getWord(fileptr);
    }
    
    /* Print the words from the table as requested */
    printConcordance (hashTable);

    /* Close file procedure */
    if(fclose(fileptr))
        printf("Error closing file: %s\n", filename);
    else
        printf("Closing %s now...\n", filename);

	/*... concordance code ends here ...*/
    
	printMap(hashTable);
	timer = clock() - timer;
	printf("\nconcordance ran in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	printf("Table emptyBuckets = %d\n", emptyBuckets(hashTable));
    printf("Table count = %d\n", size(hashTable));
	printf("Table capacity = %d\n", capacity(hashTable));
	printf("Table load = %f\n", tableLoad(hashTable));
	
	printf("Deleting keys\n");
	
	removeKey(hashTable, "and");
	removeKey(hashTable, "me");
	removeKey(hashTable, "the");
	printMap(hashTable);
		
	deleteMap(hashTable);
	printf("\nDeleting table...\n\n");

	return 0;
}

void printValue(ValueType v){
	printf("Value:%d",v);
}

char* getWord(FILE *file){
    
	int length = 0;
	int maxLength = 16;
	char character;
    
	char* word = malloc(sizeof(char) * maxLength);
	assert(word != NULL);
    
	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   character == 39) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}
    
	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

void printConcordance (struct hashMap * ht){
    
    printf("*** CONCORDANCE RESULTS ***\n\n");
    int i;
    struct hashLink *tempPrint;
    for(i = 0;i < capacity(ht); i++){
        tempPrint = ht->table[i];
        while(tempPrint != 0){
            printf("  %-14s: ", tempPrint->key);
            printf("%3d", tempPrint->value);
            printf("\n");
            tempPrint=tempPrint->next;}
    }
    printf("\n");
}
