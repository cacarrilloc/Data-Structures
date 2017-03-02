/************************************************************
 ** Author: Carlos Carrillo                                 *
 ** Date:   03/10/2016                                      *
 ** Description: This program shows am implementation of    *
 *  the implementation of the depth-first search (DFS) and  *
 *  breadth-first search (BFS) algorithm.                   *
 ** Input:  Undirected graphs.                              *
 ** Output: A boolean (encoded as an int) indicating        *
 *          whether or not a path exists between the        *
 *          argument vertices.                              *
 ***********************************************************/

#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "cirListDeque.h"

void createGraph1(Graph* g){
	Vertex* firstVert;
	Vertex* secondVert;
	int i;
	srand(3);
		
	g->numVertices = 3;
	setupVertices(g);
	
	g->numEdges = 3;
	for(i = 0; i < g->numEdges; ++i){
		firstVert = &g->vertexSet[i];
		secondVert = &g->vertexSet[(i+1) % g->numVertices];
		setupEdge(g, firstVert, secondVert);
	}
}

void createGraph2(Graph* g){
	Vertex* firstVert;
	Vertex* secondVert;
	int i;
	srand(57);
		
	g->numVertices = 8;
	setupVertices(g);
	
	g->numEdges = 10;
	for(i = 0; i < g->numEdges; ++i){
		firstVert = &g->vertexSet[rand() % g->numVertices];
		secondVert = firstVert;
		while(firstVert == secondVert || isAdjacent(firstVert, secondVert))
			secondVert = &g->vertexSet[rand() % g->numVertices];
			
		setupEdge(g, firstVert, secondVert);
	}
}

void createGraph3(Graph* g){
	Vertex* firstVert;
	Vertex* secondVert;
	int i;
	srand(33);
		
	g->numVertices = 26;
	setupVertices(g);
	
	g->numEdges = 10;
	for(i = 0; i < g->numEdges; ++i){
		firstVert = &g->vertexSet[rand() % g->numVertices];
		secondVert = firstVert;
		while(firstVert == secondVert || isAdjacent(firstVert, secondVert))
			secondVert = &g->vertexSet[rand() % g->numVertices];
			
		setupEdge(g, firstVert, secondVert);
	}
}

void createGraph4(Graph* g){
	Vertex* firstVert;
	Vertex* secondVert;
	int i;
	srand(9875);
		
	g->numVertices = 26;
	setupVertices(g);
	
	g->numEdges = 100;
	for(i = 0; i < g->numEdges; ++i){
		firstVert = &g->vertexSet[rand() % g->numVertices];
		secondVert = firstVert;
		while(firstVert == secondVert || isAdjacent(firstVert, secondVert))
			secondVert = &g->vertexSet[rand() % g->numVertices];
			
		setupEdge(g, firstVert, secondVert);
	}
}

void createGraph5(Graph* g){
	int i, j;
	srand(9875);
		
	g->numVertices = 20;
	setupVertices(g);
	
	g->numEdges = 400;
	for(i = 0; i < g->numVertices; ++i)
		for(j = i + 1; j < g->numVertices; ++j)
			setupEdge(g, &g->vertexSet[i], &g->vertexSet[j]);
}

/* Initializes all information for the vertices in the graph
 * param: g		Graph whose vertices will be initialized
 * pre: numVertices has been initialized
 */
void setupVertices(Graph* g){
	int i;
	g->vertexSet = (Vertex*) malloc(g->numVertices * sizeof(Vertex));
	for(i = 0; i < g->numVertices; ++i)
	{
		g->vertexSet[i].label = 'A' + i;
		g->vertexSet[i].isVisited = 0;
		g->vertexSet[i].neighbors = (Vertex**)malloc(sizeof(Vertex*));
		g->vertexSet[i].numNeighbors = 0;
	}
}

/* Creates all the links necessary to form an edge between the two argument vertices.
 * param: g		Graph in which the vertices reside
 * param: first	Vertex from which the edge will originate
 * param: second	Vertex at which the edge terminates
 * post: all links necessary to form an edge between first and second have been completed.
 */
void setupEdge(Graph* g, Vertex* first, Vertex* second){
	first->numNeighbors++;
	second->numNeighbors++;
	first->neighbors = (Vertex**)realloc(first->neighbors, first->numNeighbors * sizeof(Vertex*));
	second->neighbors = (Vertex**)realloc(second->neighbors, second->numNeighbors * sizeof(Vertex*));
	
	first->neighbors[first->numNeighbors - 1] = second;
	second->neighbors[second->numNeighbors - 1] = first;
}

/* This function prints the graph
 * param: g		Graph to print
 */
void printGraph(Graph* g){
	int i, j;
	Vertex* currVert;
	printf("*****\t\t This graph has %d Vertices and %d Edges\n", g->numVertices, g->numEdges);

	/* print the vertex set */
	for(i = 0; i < g->numVertices; ++i)
	{
		currVert = &g->vertexSet[i];
		printf("%c: ", currVert->label);
		for(j = 0; j < currVert->numNeighbors - 1; ++j)
			printf("%c, ", currVert->neighbors[j]->label);
		if(currVert->numNeighbors > 0)
			printf("%c\n", currVert->neighbors[j]->label);
		else printf("\n");
	}
}

/* This function can be used to determine if two vertices are adjacent
 * param: firstVert		Vertex to check neighbors from
 * param: secondVert	Vertex to check neighbors to
 * ret:	boolean (encoded as int) indicating whether or not the vertices
 *		are adjacent (an edge exists between them)
 */
int isAdjacent(Vertex* firstVert, Vertex* secondVert){
	int i;
	for(i = 0; i < firstVert->numNeighbors; ++i)
		if(	firstVert->neighbors[i] == secondVert)
			return 1;
	return 0;
}

/* This function clears all the search flags in the graph
 * param: g		Graph to have its flags cleared
 * post: All vertices in the graph should have their search flags turned off
 */
void clearVisited(Graph* g){
	int i;
	for(i = 0; i < g->numVertices; ++i)
		g->vertexSet[i].isVisited = 0;
}

/* these two functions provide a recursive version of the depth first search.
 * feel free to use this to check your answers
 * param: g			Graph to perform the search in
 * param: source	Vertex to originate the search from
 * param: destination Vertex to stop the search from (if it is found)
 * ret: boolean indicating whether or not a path exists
 */
int DFSRecursiveHelper(Graph* g, Vertex* currVert, Vertex* destination){
	int i;
	
	currVert->isVisited = 1;
	if(currVert == destination)
		return 1;
	for(i = 0; i < currVert->numNeighbors; ++i)
		if(!currVert->neighbors[i]->isVisited)
			if(DFSRecursiveHelper(g, currVert->neighbors[i], destination))
				return 1;
	return 0;
}

int DFSRecursive(Graph* g, Vertex* source, Vertex* destination){
	clearVisited(g);
	return DFSRecursiveHelper(g, source, destination);
}


/* This function should return a boolean (encoded as an int) indicating
 * whether or not a path exists between the argument vertices.
 * param: g			Graph to perform the search in
 * param: source	Vertex to originate the search from
 * param: destination Vertex to stop the search from (if it is found)
 * ret: boolean indicating whether or not a path exists
 */
int DFS(Graph* g, Vertex* source, Vertex* destination){
    
    int i;
    
    /* Clear all the search flags in the graph */
    clearVisited(g);
    
    /* Create a container for vertices known to be reachable */
    struct cirListDeque * stackContainer = malloc(sizeof(struct cirListDeque));
    initCirListDeque(stackContainer);
    
    /* Create temp pointer to array of Vertex */
    Vertex * curVertex = source;
    
    /* Create a set of reachable vertices, initially empty. */
    for(i=0; i < curVertex->numNeighbors; i++){
        addBackCirListDeque(stackContainer, curVertex->neighbors[i]);}
 
    /* Set boolean reminder */
    curVertex->isVisited = 1;
    
    while(!isEmptyCirListDeque(stackContainer)){
        
        /* Assign TOP element from the STACK to curVertex */
        curVertex = backCirListDeque(stackContainer);
        /* Remove TOP element from the STACK container */
        removeBackCirListDeque(stackContainer);
        
        /* Check if source and destination are connected */
        if(EQ(curVertex, destination)){
            return 1;}
    
        /* Set boolean reminder again */
        curVertex->isVisited = 1;
    
        /* Traverse container to check if curVertex is reachable already */
        for(i=0; i<curVertex->numNeighbors; i++){
        
            /* If curVertex is NOT already in the set of reachable vertices */
            if(!curVertex->neighbors[i]->isVisited){
            
            /* Add curVertex's neighbors to the container */
            addBackCirListDeque(stackContainer, curVertex->neighbors[i]);}}
    }
    return 0;
}

/* This function should return a boolean (encoded as an int) indicating
 * whether or not a path exists between the argument vertices.
 * param: g			Graph to perform the search in
 * param: source	Vertex to originate the search from
 * param: destination Vertex to stop the search from (if it is found)
 * ret: boolean indicating whether or not a path exists
 */

int BFS(Graph* g, Vertex* source, Vertex* destination){
    
    int i;
    
    /* Clear all the search flags in the graph */
    clearVisited(g);
    
    /* Create a container for vertices known to be reachable */
    struct cirListDeque * QueueContainer = malloc(sizeof(struct cirListDeque));
    initCirListDeque(QueueContainer);
    
    /* Create temp pointer to array of Vertex */
    Vertex * curVertex = source;
    
    /* Create a set of reachable vertices, initially empty. */
    for(i=0; i < curVertex->numNeighbors; i++){
        addBackCirListDeque(QueueContainer, curVertex->neighbors[i]);}
    
    /* Set boolean reminder */
    curVertex->isVisited = 1;
    
    while(!isEmptyCirListDeque(QueueContainer)){
        
        /* Assign FRONT element from the QUEUE to curVertex */
        curVertex = frontCirListDeque(QueueContainer);
        /* Remove FRONT element from the QUEUE container */
        removeFrontCirListDeque(QueueContainer);
        
        /* Check if source and destination are connected */
        if(EQ(curVertex, destination)){
            return 1;}
        
        /* Set boolean reminder again */
        curVertex->isVisited = 1;
        
        /* Traverse container to check if curVertex is reachable already */
        for(i=0; i<curVertex->numNeighbors; i++){
            
            /* If curVertex is NOT already in the set of reachable vertices */
            if(!curVertex->neighbors[i]->isVisited){
                
                /* Add curVertex's neighbors to the container */
                addBackCirListDeque(QueueContainer, curVertex->neighbors[i]);}}
    }
	return 0;
}

