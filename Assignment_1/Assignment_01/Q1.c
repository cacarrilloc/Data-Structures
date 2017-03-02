/* CS261- Assignment 1 - Q.1*/
/* Name: Carlos Carrillo
 * Date: 01/11/2016
 * Solution description: This program contains:
 * 1) A function that allocates memory for ten students and returns a pointer.
 * 2) A function that generates and stores random IDs and scores for ten students
 * 3) A function that prints the ids and scores of all the students.
 * 4) A function that prints the minimum, maximum, and average scores of the students.*/
 
#include <stdio.h>
#include <stdlib.h>

/*#include <time.h> //for future or possible use*/

struct student{
    int id;
    int score;
};

struct student* allocate(){
    
    /*Allocate memory for ten students*/
    int numStu = 10;
    struct student* myStu = malloc(numStu * sizeof(struct student));
    //assert(myStu != 0);
    
    /*return the pointer*/
    return myStu;
}

void generate(struct student* students){
    
    /*Generate random ID and scores for ten students, ID
     being between 1 and 10, scores between 0 and 100*/
    
    /* Seed srand */
    /* srand(time(NULL)); //for future or possible use*/
    for(int i=0; i<10; i++){
        /*fill up ID array with ordered numbers from 1 to 10*/
        students[i].id = i+1;
        
        /*fill up score array with random numbers from 1 to 100*/
        students[i].score = (rand() % 100) + 1;}
    
    /*Shuffle ID array values aleatory. Algorithm borrowed from 
     www.dispersiondesign.com/articles/algorithms/shuffle_array_order*/
    for(int x=0; x<10; x++){
        int y = rand() % (x + 1);
        int temp = students[x].id;
        students[x].id = students[y].id;
        students[y].id = temp;}
}

void output(struct student* students){
    
    /*Output information about the ten students in the format: ID1 Score1*/
    printf("\nTABLE OF VALUES:\n");
    for(int i=0; i<10; i++){
        int stuId = students[i].id;
        int stuScore = students[i].score;
        printf("Student ID = %.2d;  SCORE = %.2d\n", stuId, stuScore);}
}

void summary(struct student* students){
    
    /*Compute and print the minimum, maximum and average scores of the ten students*/
    int maxScore = 0;
    int minScore = 100;
    int average = 0;
    int accumulator = 0;
    
    /*Maximum Score*/
    for(int j=0; j<10; j++){
        if(students[j].score > maxScore)
            maxScore = students[j].score;}
    
    /*Minimum Score*/
    for(int k=0; k<10; k++){
        if(students[k].score < minScore)
            minScore = students[k].score;}

    /*Avg*/
    for(int x=0; x<10; x++){
        accumulator = accumulator + students[x].score;}
    
    average = accumulator/10;
    
    printf("\nMAXIMUM Score = %d \n", maxScore);
    printf("MINIMUM Score = %.2d \n", minScore);
    printf("AVERAGE Score = %d \n\n", average);
}

void deallocate(struct student* stud){
    
    /* check if the pointer is NULL */
    if(stud != NULL){
        /*Deallocate memory from stud*/
        free(stud);
    }
}

int main(int argc, const char * argv[]){
    
    printf("\nWELCOME TO Q1.c PROGRAM:\n");
    
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    
    /*call generate*/
    generate(stud);
    
    /*call output*/
    output(stud);
    
    /*call summary*/
    summary(stud);
    
    /*call deallocate*/
    deallocate(stud);
    
    return 0;
}
