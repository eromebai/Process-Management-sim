#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//A string copying function for creating names for my node "Objects"
char* StringCopy(char* s){
    char* ptr = malloc(((strlen(s) +1) * sizeof(char)));
    char* traverse = s;
    int i = 0;
    while(*traverse != '\0'){
        ptr[i] = *traverse;
        i++;
        traverse++;
    }
    ptr[i] = '\0';

    return ptr;
}

int main(){
    FILE* inputfp = fopen("cpu_scheduling_input_file.txt", "r");
    FILE* outputfp = fopen("cpu_scheduling_output_file.txt", "w");

    //A list holding my Queue "Objects" in the order that they are created. Only up to 100 queues can be read
    Queue ListOfQ[100];
    int qCount = 0;

    int queueNum = 0;
    int timeQ = 0;
    int c;

    //Outer loop reads one line at a time, ending when the end of the file is detected
    while((c =getc(inputfp)) != EOF) {
        ungetc(c, inputfp);

        //Taking queue name and time quantum
        fscanf(inputfp, "%*s %d %*s %d", &queueNum, &timeQ);

        char name[20];
        int time = 0;

        //Taking the first process in the queue and storing it in a node
        fscanf(inputfp, "%s %d", name, &time);

        Node n = nodeGen(StringCopy(name), time);

        //Creating a queue beginning with the first created node
        ListOfQ[qCount] = queueGen(queueNum, timeQ, n, outputfp);
        qCount++;

        Node m;

        //Reading all subsequent nodes in the queue and linking them
        while ((c = getc(inputfp)) != '\n') {
            ungetc(c, inputfp);
            if((c = getc(inputfp)) == EOF){
                break;
            }
            ungetc(c, inputfp);
            fscanf(inputfp, "%s %d", name, &time);
            m = nodeGen(StringCopy(name), time);
            setNext(n, m);
            n = m;
        }
    }

    //After all the linked lists have been created, this outputs the queues in the correct order
    int count = 1;

    for(count; count < qCount + 1; count++){
        int tracker = 0;
        for(;;){
            if(getQname(ListOfQ[tracker]) == count){
                runFCFS(ListOfQ[tracker]);
                runSJF(ListOfQ[tracker]);
                runRR(ListOfQ[tracker]);
                queueFree(ListOfQ[tracker]);
                break;
            }
            tracker++;
        }
    }

    fclose(inputfp);
    fclose(outputfp);

    return 0;
}