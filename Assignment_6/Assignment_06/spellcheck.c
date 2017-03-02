/*************************************************************
 ** Author: Carlos Carrillo                                  *
 ** Date:   02/29/2016                                       *
 ** Description: This is the main function of a program that *
 *  uses a hash-map implementation to spell check words from *
 *  a table filled with an external file.                    *
 ** Input:  dictionary.txt and a string of characters.       *
 ** Output: Approval or disapproval message.                 *
 ************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "hashMap.h"


/* The getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it. */

char* getWord(FILE *file);

/* Load the contents of file into hashmap ht */
void loadDictionary(FILE* file, struct hashMap* ht);

/* Function to update external file with the changes added by the user */
void updateTable(FILE* file, struct hashMap* ht);

/* Function to ensure all alpha input becomes lower case */
void lowerCase(char* word);

int main (int argc, const char * argv[]) {
    
    const char* filename;
    clock_t timer;
    struct hashMap* hashTable;
    int tableSize = 1597;
    timer = clock();
    
    /* Create a new table */
    hashTable = createMap(tableSize);
  
    FILE* dictionary;

    if(argc == 2)
        filename = argv[1];
    else
        filename = "dictionary.txt"; /*specify your input text file here*/
    
    printf("Opening %s now...\n\n", filename);
    dictionary = fopen(filename, "r"); // open dictionary.txt
  
    loadDictionary(dictionary, hashTable); //load dictionary.txt
    
    fclose(dictionary); //close dictionary.txt
    
    timer = clock() - timer;
	printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    
    //hashTable = createMap(tableSize);
  
    char* word = (char*)malloc(256*sizeof(char));
    char* deleteWord = (char*)malloc(256*sizeof(char));
    char* choice = (char*)malloc(256*sizeof(char));
    int quit=0;
    
    while(!quit){
    
        printf("\nEnter the word you want to check: ");
        scanf("%s", word);
    
        /* Spell checker code starts here */
        
        /*ensure lowercase input*/
        lowerCase(word);
      
        /* Just check if the input word is in the table */
        if(containsKey(hashTable, word))
            printf("\nYou spelled '%s' correctly, congratulations!!\n", word);
        
        else{
            printf("\nThe word '%s' is NOT in your dictionary or it was spelled incorrectly.\n", word);
            /* Prompt user to whether insert the inexistent word or not */
            printf("Would you like to ADD '%s' to the dictionary?? (y/n) ", word);
            scanf("%s", choice);
            lowerCase(choice); //ensure lowercase input
            
            if(*choice == 'y'){
                printf("\nupdating dictionary...\n");
                /* Insert word into the table */
                insertMap(hashTable, word, 1);
                
                /* Update external file with the new entry */
                dictionary = fopen(filename, "w"); // open file
                updateTable(dictionary, hashTable);
                fclose(dictionary);
                
                printf("\nThe word '%s' has been added to your dictionary!\n", word);}}
        
        /* Give user the option to delete the just entered word or any other word */
        printf("\nWould you like to DELETE any word from the dictionary?? (y/n) ");
        scanf("%s", choice);
        lowerCase(choice); //ensure lowercase input
        
        if(*choice == 'y'){
            int key =0;
            do{
                printf("\nEnter the word you want to delete: ");
                scanf("%s", deleteWord);
                
                /*ensure lowercase input*/
                lowerCase(deleteWord);
                
                if(containsKey(hashTable, deleteWord)){
                    key = 1;
                    printf("\nupdating dictionary...\n");
                    
                    /* Remove word from table */
                    removeKey(hashTable, deleteWord);
                    
                    /* Delete word also from the external file */
                    dictionary = fopen(filename, "w"); // open file
                    updateTable(dictionary, hashTable);
                    fclose(dictionary);
                    printf("\nThe word '%s' has been deleted from your dictionary!\n", deleteWord);}
                
                else{
                    printf("\nSorry! The word '%s' is NOT in the dictionary!\n", deleteWord);
                    printf("Do you still want to delete a word?? (y/n) ");
                    scanf("%s", choice);
                    lowerCase(choice);
                    if(*choice == 'n'){key = 1;}}
            
            }while(key == 0);
        }
        
        /* Prompt user to exit the program */
        printf("\nWould you like to check another word?? (y/n) ");
        scanf("%s", choice);
        lowerCase(choice); //ensure lowercase input
        
        if(*choice == 'n'){
            printf("\n");
            break;}
        
        /* Spell checker code finishs here */
        
        /* Don't remove this. It is used for grading*/
        if(strcmp(word,"quit")==0)
            quit=!quit;
    }
    
    /* Free all used memory */
    free(word);
    free(deleteWord);
    free(choice);
    deleteMap(hashTable);
    printf("Deleting table...\n\n");
    
    return 0;
}

void loadDictionary(FILE* file, struct hashMap* ht){
    
    char *input = 0;
    /* Insert all the words from dictionary.txt */
    while((input = getWord(file))){
        insertMap(ht, input, 1);}
}

char* getWord(FILE *file)
{
	int length = 0;
	int maxLength = 16;
	char character;
    
	char* word = (char*)malloc(sizeof(char) * maxLength);
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
		   (character == 39)) /*or is an apostrophy*/
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

/* Function to update external file with the changes added by the user */
void updateTable(FILE* file, struct hashMap* ht){
    
    int i;
    struct hashLink *cur;
    char* word = (char*)malloc(256*sizeof(char));

    /* Simply transfer hashTable keys to dictionary.txt */
    for(i=0; i < capacity(ht); i++){
        cur = ht->table[i];
        while(cur != 0){
            word = cur->key;
            fprintf(file, "%s\n", word);
            cur = cur->next;}
    }
}

/* Function to ensure all alpha input becomes lower case */
void lowerCase(char* word){
    
    char* word2 = (char*)malloc(256*sizeof(char));
    word2 = word;
    
    size_t i;
    for (i = 0; i < strlen(word2); i++)
        word2[i] = tolower(word2[i]);
    word = word2;
}

/* Dummy function, non-useful */
void printValue(ValueType v) {
    printf("Value:%d",v);
}


