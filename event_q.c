//
// Created by 19023 on 2022-07-29.
//
#include <stdlib.h>
#include "event_q.h"
#include "pthread.h"


pthread_mutex_t lock;
pthread_cond_t condition;

extern event_list_t *queue;

extern event_list_t * event_list() {
    return calloc(1, sizeof(event_list_t));
}

extern event_t *event_new() {
    return calloc(1, sizeof(event_t));
}

void event_q_add(event_t *t){
    pthread_mutex_lock(&lock); // used to protect the queue
    if (queue->head) {
        queue->tail->next = t;
    } else {
        queue->head = t;
    }
    queue->tail = t;
    t->next = NULL;
    pthread_cond_signal(&condition);
    pthread_mutex_unlock(&lock);
}

event_t *event_q_remove(){
    //critical section
    //producer does not have to wait
    pthread_mutex_lock(&lock);

    if (!queue->head) {
        pthread_cond_wait(&condition, &lock);
    }
    event_t * t = queue->head;
    queue->head = t->next;
    pthread_mutex_unlock(&lock);
    return t;
}