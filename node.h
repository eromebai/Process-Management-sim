//
// Created by pi on 28/10/19.
//

#ifndef ASSIGNMENT2_NODE_H
#define ASSIGNMENT2_NODE_H

typedef struct {
    char * name;
    int btime;
    int turnaround;
    struct node_struct* next;
}node_struct;

typedef node_struct* Node;

Node nodeGen(char*, int);

void nodeFree(Node);

char* getName(Node);

int getTime(Node);

int getTtime(Node);

void setTtime(Node, int);

void decrement(Node);

Node getNext(Node);

void setNext(Node,Node);

#endif //ASSIGNMENT2_NODE_H
