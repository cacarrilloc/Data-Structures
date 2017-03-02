/* CS261- Assignment 1 - Q.5*/
/* Name: Carlos Carrillo
 * Date: 01/12/2016
 * Solution description: This program contains:
 * 1) A function void sticky(char* word) where word is a single word 
 *    that is modified appear with “sticky caps” For example, “sticky” 
 *    becomes “StIcKy” and “RANDOM” becomes “RaNdOm”. 
 * 2) An toUpperCase() and toLowerCase() functions that change the 
 *    case of the characters. */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
    
    return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
    
    return ch-'A'+'a';
}

void sticky(char* word){
    
    /*Convert to sticky caps*/
    int length = 0;
    
    while(word[length] != '\0'){
        length++;}
    
    /*Algorithm borrowed from stackoverflow.com/
     questions/15648531/pointer-and-array-in-c */
    for(int i = 0; i < length; i++ ){
        
        /* even character */
        if( i % 2 == 0){
            if(word[i] >= 'a' && word[i] <= 'z'){
                /* transform into upper case */
                word[i] = toUpperCase(word[i]);}
            
        /* odd character */
        } else {
            if(word[i] >= 'A' && word[i] <= 'Z'){
                /* transform into lower case */
                word[i] = toLowerCase(word[i]);}}
    }
}

int main(int argc, const char * argv[]){
    
    printf("\nWELCOME TO Q5.c PROGRAM:\n");
    
    /*Read a word from the keyboard using scanf*/
    char input[256];
    
    printf("\nTransform a word into StIcKy Caps!!!");
    printf("\nType your word: ");
    scanf("%s", input);
  
    /*Call sticky*/
    sticky(input);
    
    /*Print the new word*/
    printf("\nStIcKy Output: %s\n\n", input);
    printf("Bye!!!\n\n");
    
    return 0;
}
