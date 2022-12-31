//
// Created by 19023 on 2022-07-29.
//

#ifndef MAIN_C_EVENT_Q_H
#define MAIN_C_EVENT_Q_H
#define buffersize 255

typedef struct event{
    struct event *next;
    char event_stdin[buffersize];
    char event[buffersize];
}event_t;

typedef struct event_list{
    event_t *head;
    event_t *tail;
} event_list_t;

//add to the list
void event_q_add(event_t *t);
//dequeue from the list
event_t *event_q_remove();
//new list
extern event_list_t * event_list();
//new node
extern event_t *event_new();

#endif //MAIN_C_EVENT_Q_H
