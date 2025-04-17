#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "header.h"

int main()
//the main function, for tackling user input and giving the correct output.
{
    int cityCnt, roadCnt, hubThres;
    //respectively the number of cities, roads and the threshold for hubs.
    int testCnt;
    //the number of all the testcases
    printf("Input the number of cities, roads and the threshold for hubs.");
    scanf("%d %d %d", &cityCnt, &roadCnt, &hubThres);
    AdjPtr * graph = (AdjPtr *)calloc(cityCnt, sizeof(AdjPtr));
    createGraph(graph, roadCnt);
    //create an adjacency list with createGraph()
    scanf("%d", &testCnt);
    testTop(graph, hubThres, testCnt, cityCnt);
    //the top module for the testing
    return 0;
}