#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "header.h"

void createGraph(AdjPtr * graph, int r_num)
{
    int c1, c2, len;
    //the input information
    AdjPtr temp_ptr;
    //the temporary pointer for list element
    for (int i = 0; i < r_num; i ++) {
        scanf("%d %d %d", &c1, &c2, &len);
        temp_ptr = (AdjPtr)calloc(1, sizeof(AdjList));
        //create the information for c1
        temp_ptr->edgeLen = len;
        temp_ptr->nextV = c2;
        temp_ptr->Next = graph[c1];
        //we insert at the head of the list to ensure efficiency.
        graph[c1] = temp_ptr;
        temp_ptr = (AdjPtr)calloc(1, sizeof(AdjList));
        //because the road is two-way, here we modify the information for c2.
        temp_ptr->edgeLen = len;
        temp_ptr->nextV = c1;
        temp_ptr->Next = graph[c2];
        //insert at the head, same as what we've done before.
        graph[c2] = temp_ptr;
    }
}

void testTop(AdjPtr * graph, int thres, int testN, int c_num)
{
    int src, dest;
    //the index of the source and the destination
    for (int i = 0; i < testN; i ++)
    {
        scanf("%d %d", &src, &dest);
        findHub(graph, thres, c_num, src, dest);
    }
    scanf(NULL);
}

void findHub(AdjPtr * graph, int thres, int c_num, int src, int dest)
{
    bool * KnownList = (bool *)calloc(c_num, sizeof(bool));
    //used to store whether the shortest route is determined
    int ** PathList = (int **)calloc(c_num, sizeof(int *));
    for (int i = 0; i < c_num; i ++) {
        PathList[i] = (int *)calloc(c_num, sizeof(int));
    }
    //used to store all the possible predecessors of the current city
    int * PathTop = (int *)calloc(c_num, sizeof(int));
    //used to store the top of PathList
    int * DistList = (int *)calloc(c_num, sizeof(int));
    //used to store the distance to the current city
    for (int i = 0; i < c_num; i ++) {
        PathTop[i] = 0;
        KnownList[i] = 0;
        DistList[i] = INT_MAX/2;
    }
    DistList[src] = 0;
    Dijkstra(graph, KnownList, PathList, DistList, PathTop, src, dest, c_num);
    //find the shortest path from src to dest
    reverseCheckHub(src, dest, c_num, PathTop, PathList, thres);
    //check the transportation hubs
}

void Dijkstra(AdjPtr * graph, bool * KnownList, int ** PathList,
    int * DistList, int * PathTop, int src, int dest, int c_num)
{
    int currMin;
    AdjPtr currAdj;
    //the pointer to the adjacent city
    int adjCity;
    //the index of the adjacent city
    int currLen;
    //the current length of the road
    while (1) {
        currMin = findMinUn(KnownList, DistList, c_num);
        //find the minimum unknown city
        if (currMin == -1) {
            break;
            //not found, whole sequence stopped
        }
        KnownList[currMin] = true;
        //flag the current node to be true
        currAdj = graph[currMin];
        //get the current adjacent city
        while (currAdj) //traverse through all the adjacent cities
        {
            adjCity = currAdj->nextV;
            //adjacent city to the current city
            currLen = currAdj->edgeLen;
            //the current length
            if (!KnownList[adjCity]) {
                if (DistList[currMin] + currLen < DistList[adjCity]) {
                    //means that the current route is shorter
                    DistList[adjCity] = DistList[currMin] + currLen;
                    PathTop[adjCity] = 1;
                    //refresh the PathTop
                    PathList[adjCity][0] = currMin;
                    //reset the pathlist
                }
                else if (DistList[currMin] + currLen == DistList[adjCity]) {
                    PathList[adjCity][PathTop[adjCity]] = currMin;
                    //add the current to the path
                    PathTop[adjCity] ++;
                    //path top increment
                }
            }
            currAdj = currAdj->Next;
            //visit the next adjacent city
        }
    }
}

int findMinUn(bool * KnownList, int * DistList, int c_num)
{
    int minDist = INT_MAX/2;
    //the temporary min flag
    int minCity = -1;
    //if not found, then return -1
    for (int i = 0; i < c_num; i ++)
    {
        if (!KnownList[i] && DistList[i] < minDist) {
            //current min
            minDist = DistList[i];
            //refresh minDist
            minCity = i;
            //also mark that the min is found
        }
    }
    return minCity;
}

void reverseCheckHub(int src, int dest, int c_num, int * PathTop, int ** PathList, int thres)
{
    int * cityCntTab = (int *)calloc(c_num, sizeof(int));
    //the table to store the count of all cities, will be used to check hubs.
    int * tempQue = (int *)calloc(10000000, sizeof(int));
    //used to store the path of all cities
    bool flag = false;
    //the flag for whether hub exists
    int currCity;
    //the current city in our traversal
    int queHead = 0;
    int queTail = 1;
    //the head and tail of the queue
    tempQue[0] = dest;
    //initialize the que
    while (queHead != queTail) {
        currCity = tempQue[queHead];
        queHead ++;
        cityCntTab[currCity] ++;
        for (int i = 0; i < PathTop[currCity]; i ++) {
            //traverse through all the predecessor of the 
            tempQue[queTail] = PathList[currCity][i];
            //add the predecessor city into the list
            queTail ++;
        }
    }
    cityCntTab[dest] = 0;
    cityCntTab[src] = 0;
    //make sure the destination and source are not considered
    //next, with the information in the cityCntTab, we can find the hubs.
    for (int i = 0; i < c_num; i ++) {
        if (cityCntTab[i] >= thres) {
            printf("%d ", i);
            flag = true;
        }
    }
    if (!flag) {
        printf("None");
    }
    printf("\n");
}