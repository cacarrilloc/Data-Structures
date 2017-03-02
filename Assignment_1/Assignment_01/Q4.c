/* CS261- Assignment 1 - Q.4*/
/* Name: Carlos Carrillo
 * Date: 01/12/2016
 * Solution description: This program contains afunction
 * that sorts an array of n students based on their scores
 * in ascending order.The IDs and scores of the students 
 * are to be generated randomly. */
 
#include <stdio.h>
#include <stdlib.h>

/*#include <time.h> //for future/possible use.*/

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
    
    /*Sort the n students based on their score*/
    /*Sorting algorithm borrowed from www.sanfoundry.com/
     c-program-sort-array-ascending-order/ */
    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j){
            if (students[i].score > students[j].score){
                int temp1 = students[i].score;
                int temp2 = students[i].id;
                students[i].score = students[j].score;
                students[j].score = temp1;
                students[i].id = students[j].id;
                students[j].id = temp2;}}
    }
}

int main(int argc, const char * argv[]){
    
    printf("\nWELCOME TO Q4.c PROGRAM:\n");
    
    /*Declare an integer n and assign it a value.*/
    int n = 5;
    
    /*Allocate memory for n students using malloc.*/
    struct student* myStu = malloc(n * sizeof(struct student));
    
    /*Generate random IDs and scores for the n students, using rand().*/
    
    /* Seed srand */
    /* srand(time(NULL)); //for future/possible use.*/
    
    for(int i=0; i<n; i++){
        /*fill up ID array with random numbers from 1 to 20*/
        myStu[i].id = (rand() % 20) + 1;
        
        /*fill up score array with random numbers from 1 to 100*/
        myStu[i].score = (rand() % 100) + 1;}
    
    /*Print the contents of the array of n students.*/
    printf("\nUNSORTED VALUES:\n");
    
    for(int i=0; i<n; i++){
        int stuId = myStu[i].id;
        int stuScore = myStu[i].score;
        printf("Student ID = %.2d;  SCORE = %.2d\n", stuId, stuScore);}

    /*Pass this array along with n to the sort() function*/
    sort(myStu, n);
    
    /*Print the contents of the array of n students.*/
    printf("\nSORTED SCORES (ascending order):\n");
    
    for(int i=0; i<n; i++){
        int stuId = myStu[i].id;
        int stuScore = myStu[i].score;
        printf("Student ID = %.2d;  SCORE = %.2d\n", stuId, stuScore);}
    
    printf("\n");
    
    return 0;
}
