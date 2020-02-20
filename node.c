#include "node.h"
#include <stdio.h>
#include <stdlib.h>

//Node "objects" for a linked list, trying to imitate object oriented programming
Node nodeGen(char* setName, int setNum){
    Node node = malloc(sizeof(node_struct));

    node->name = setName;
    node->btime = setNum;
    node->next = NULL;
    node->turnaround = -1;

    return node;
}

//Free the memory used by a node
void nodeFree(Node node){
    free(node);
}

//Set the next node in the linked list
void setNext(Node current, Node nextn){
    current->next = nextn;
}

//Get the name of the node
char* getName(Node node){
    return node->name;
}

//Get the remaining burst time for the node
int getTime(Node node){
    return node->btime;
}

//Retrieve when the node started execution in RR
int getTtime(Node node){
    return node->turnaround;
}

//Set when the node started execution in RR
void setTtime(Node node, int num){
    node->turnaround = num;
}


//Decrement the node's remaining burst time
void decrement(Node node){
    node->btime = node->btime -1;
}

//Get the next node in the linked list
Node getNext(Node node){
    return node->next;
}
