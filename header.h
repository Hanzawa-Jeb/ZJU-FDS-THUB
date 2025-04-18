#ifndef HEADER_H
#define HEADER_H
//include guard

typedef struct AdjList{
    //used to store the adjacency list
    int nextV;
    //the city that the edge is pointing to
    int edgeLen;
    //the length of the current edge
    struct AdjList * Next;
    //the next adjacent element of the current city
} AdjList;
typedef AdjList * AdjPtr;

void createGraph(AdjPtr * graph, int r_num);
//used to create the graph with adjacency list
void testTop(AdjPtr * graph, int thres, int testN, int c_num);
//the top module for the testing
void findHub(AdjPtr * graph, int thres, int c_num, int src, int dest);
//used to find all the hubs in the graph
void Dijkstra(AdjPtr * graph, bool * KnownList, int ** PathList, 
    int * DistList, int * PathTop, int src, int dest, int c_num);
//used in findHub(), to calculate the 
int findMinUn(bool * KnownList, int * DistList, int c_num);
//used to find the unknown city with the minimum distance
void reverseCheckHub(int src, int dest, int c_num, int * PathTop, int ** PathList, int thres);
//used to check the transportation hubs in the shortest path

#endif