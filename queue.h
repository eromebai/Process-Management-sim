#include "node.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef ASSIGNMENT2_QUEUE_H
#define ASSIGNMENT2_QUEUE_H

typedef struct {
    int qname;
    int timeq;
    Node start;
    FILE* output;
}queue;

typedef queue* Queue;

Queue queueGen(int, int, Node, FILE*);

int getQname(Queue);

int getTimeQ(Queue);

Node getStart(Queue);

FILE* getFP(Queue);

void queueFree(Queue);

void runFCFS(Queue);

void runSJF(Queue);

void runRR(Queue);

#endif //ASSIGNMENT2_QUEUE_H
