//
// Created by 19023 on 2022-07-29.
//

#include "reader.h"
#include "event_q.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define END_EVENT "END"
#define MINE_EVENT "MINE"
#define TRX_EVENT "TRX"
#define BLK_EVENT "BLK"
#define EPOCH_EVENT "EPOCH"

#define TRUNCATE(name) name[strlen(name)-1] = '\0' //Macro to remove a linefeed

pthread_t reader_thread;
event_list_t *queue;

extern pthread_mutex_t lock;
extern pthread_cond_t condition;

// Producer
static void * runner(){
    // read in all events from stdin
    // no scanf in main.c
    char buffer[buffersize];
    int id;
    char eventbuffer[buffersize];

    for(;;){ //while there is no end event
        //reading input
        event_t * e = event_new();
        fgets(e->event_stdin, buffersize, stdin);
        //we can extract the event name bys using sscanf
        //check for the event
        sscanf(e->event_stdin, "%s" ,eventbuffer);
        if(strcmp(eventbuffer, TRX_EVENT) == 0  || strcmp(eventbuffer, BLK_EVENT) == 0){
            sscanf(e->event_stdin, "%s %d" ,eventbuffer, &id);
            strcpy(e->event, eventbuffer);
            printf("Received event %s with ID %d\n", eventbuffer, id);
        }
        else if(strcmp(eventbuffer, END_EVENT) == 0 || strcmp(eventbuffer, EPOCH_EVENT) == 0  || strcmp(eventbuffer, MINE_EVENT) == 0){
            //TRUNCATE(e->event_stdin);
            strcpy(e->event, eventbuffer);
            printf("Received event %s\n", eventbuffer);
        }
        event_q_add(e); // epoch mine, blk

        if(strcmp(eventbuffer, END_EVENT) == 0){
            break;
        }
    }
    return 0;
}

extern void start_reader(){
    // start the thread
    pthread_cond_init(&condition, NULL);
    pthread_mutex_init(&lock, NULL);
    queue = event_list();
    pthread_create(&reader_thread, NULL, &runner, NULL);
}

extern void stop_reader(){
    // join thread
    if(pthread_join(reader_thread, NULL) != 0){
        perror("fail to join thread");
    }
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&condition);
}