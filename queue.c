#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

//A Queue "object" immitating object oriented design
Queue queueGen(int gname, int gtime, Node nstart, FILE* fp){
    Queue q = malloc(sizeof(queue));

    q->qname = gname;
    q->timeq = gtime;
    q->start = nstart;
    q->output = fp;

    return q;
}

//Frees a queue along with the linked list it points to
void queueFree(Queue Gqueue){
    Node n = getStart(Gqueue);
    while(n != NULL){
        Node m = getNext(n);
        nodeFree(n);
        n = m;
    }

    free(Gqueue);
}

//Retrieve the queue name(number)
int getQname(Queue q){
    return q->qname;
}

//Retrieve the time quantum set fot the queue
int getTimeQ(Queue q){
    return q->timeq;
}

//Get the starting node for the linked list this queue points to
Node getStart(Queue q){
    return q->start;
}

//Get the output file pointer this queue is set to output to
FILE* getFP(Queue q){
    return q->output;
}

//Method which runs first come first serve
void runFCFS(Queue q){
    fprintf(getFP(q), "Ready Queue %d Applying FCFS Scheduling: \n\nOrder of selection by CPU:\n", getQname(q));
    printf("Ready Queue %d Applying FCFS Scheduling: \n\nOrder of selection by CPU:\n", getQname(q));

    Node n = getStart(q);
    while(n != NULL){
        fprintf(getFP(q), "%s ", getName(n));
        n = getNext(n);
    }

    fprintf(getFP(q), "\n\nIndividual waiting times for each process:\n");
    printf("\n\nIndividual waiting times for each process:\n");

    int wait = 0;
    int total = 0;
    int count = 0;
    Node m = getStart(q);

    while(m != NULL){
        fprintf(getFP(q), "%s = %d\n", getName(m), wait);
        printf("%s = %d\n", getName(m), wait);
        total = total + wait;
        wait = wait + getTime(m);
        m = getNext(m);
        count++;
    }

    fprintf(getFP(q), "\nAverage waiting time = %d\n\n", total/count);
    printf("\nAverage waiting time = %d\n\n", total/count);
}

//Method which runs shortest job first
void runSJF(Queue q){
    Node n = getStart(q);
    Node nstart = NULL;

    //Creating a clone of the list ordered by cpu burst time
    while(n != NULL){
        if(nstart == NULL){
            nstart = nodeGen(getName(n),getTime(n));
        }
        else{
            Node r = nstart;
            Node prev = NULL;

            while (r != NULL) {

                if (getTime(n) < getTime(r)) {
                    if(prev != NULL) {
                        Node p = nodeGen(getName(n), getTime(n));
                        setNext(p, getNext(prev));
                        setNext(prev, p);
                        break;
                    }
                    else{
                        Node NewStart = nodeGen(getName(n), getTime(n));
                        setNext(NewStart, nstart);
                        nstart = NewStart;
                        break;
                    }
                }
                prev = r;
                r = getNext(r);
            }

            if(r == NULL){
                setNext(prev, nodeGen(getName(n), getTime(n)));
            }

        }
        n = getNext(n);
    }

    fprintf(getFP(q), "Ready Queue %d Applying SJF Scheduling: \n\nOrder of selection by CPU:\n", getQname(q));
    printf("Ready Queue %d Applying SJF Scheduling: \n\nOrder of selection by CPU:\n", getQname(q));

    Node t = nstart;

    while(t != NULL){
        fprintf(getFP(q), "%s ", getName(t));
        t = getNext(t);
    }

    fprintf(getFP(q), "\n\nIndividual waiting times for each process:\n");
    printf("\n\nIndividual waiting times for each process:\n");

    t = nstart;
    int wait = 0;
    int total = 0;
    int count = 0;

    while(t != NULL){
        fprintf(getFP(q), "%s = %d\n", getName(t), wait);
        printf("%s = %d\n", getName(t), wait);
        total = total + wait;
        wait = wait + getTime(t);
        t = getNext(t);
        count++;
    }
    fprintf(getFP(q), "\nAverage waiting time = %d\n\n", total/count);
    printf("\nAverage waiting time = %d\n\n", total/count);

    n = nstart;
    while(n != NULL){
        Node m = getNext(n);
        nodeFree(n);
        n = m;
    }
}

//Method which runs round robin
void runRR(Queue q){

    fprintf(getFP(q), "Ready Queue %d Applying RR Scheduling: \n\nOrder of selection by CPU:\n", getQname(q));
    printf("Ready Queue %d Applying RR Scheduling: \n\nOrder of selection by CPU:\n", getQname(q));

    Node nstart = nodeGen(getName(getStart(q)), getTime(getStart(q)));

    Node n = nstart;
    Node m = getNext(getStart(q));

    while(m != NULL){
        Node t = nodeGen(getName(m), getTime(m));
        setNext(n, t);
        n = t;
        m = getNext(m);
    }

    n = nstart;
    Node last = NULL;

    while(n != NULL){
        last = n;
        n = getNext(n);
    }

    setNext(last, nstart);

    n = nstart;
    int count = 0;

    while(n != NULL){
        count = getTimeQ(q);
        fprintf(getFP(q), "%s ", getName(n));
        printf("%s ", getName(n));
        while(getTime(n) != 0 && count != 0){
            decrement(n);
            count--;
        }
        if(getTime(n) == 0 && getName(last) == getName(n)){
            free(n);
            break;
        }
        else if(getTime(n) == 0){
            setNext(last, getNext(n));
            Node m = n;
            n = getNext(n);
            free(m);
        }
        else{
            last = n;
            n = getNext(n);
        }
    }

    nstart = nodeGen(getName(getStart(q)), getTime(getStart(q)));

    n = nstart;
    m = getNext(getStart(q));

    while(m != NULL){
        Node t = nodeGen(getName(m), getTime(m));
        setNext(n, t);
        n = t;
        m = getNext(m);
    }

    n = nstart;
    last = NULL;

    while(n != NULL){
        last = n;
        n = getNext(n);
    }

    setNext(last, nstart);

    fprintf(getFP(q), "\n\nTurnaround times for each process: \n");
    printf("\n\nTurnaround times for each process: \n");

    n = nstart;
    int total = 0;

    while(n != NULL){
        count = getTimeQ(q);
        if(getTtime(n) == -1){
            setTtime(n, total);
        }

        while(getTime(n) != 0 && count != 0){
            decrement(n);
            count--;
            total++;
        }

        if(getTime(n) == 0){
            fprintf(getFP(q), "%s = %d\n", getName(n), total - getTtime(n));
            printf("%s = %d\n", getName(n), total - getTtime(n));
            setNext(last, getNext(n));
            if(getName(last) != getName(n)) {
                m = n;
                nodeFree(n);
                n = getNext(m);
            }

        }
        else{
            last = n;
            n = getNext(n);
        }

        if(getTime(n) == 0 && getName(last) == getName(n)){
            free(n);
            fprintf(getFP(q), "\n");
            printf("\n");
            break;
        }
    }
}