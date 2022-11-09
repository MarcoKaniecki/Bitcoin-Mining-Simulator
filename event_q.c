//
// Created by Marco Kaniecki on 2022-07-29.
//

#include "event_q.h"
#include <pthread.h>

// create new event to be added to queue
extern EVENT_TYPE * event_new()
{
    return calloc(1, sizeof(EVENT_TYPE));
}

// create new queue
extern EVENT_QUEUE * event_q_init()
{
    return calloc(1, sizeof(EVENT_QUEUE));
}

void event_q_add(EVENT_TYPE *e)
{
    // used to protect queue
    pthread_mutex_lock(&monitor);

    if (eq->head) {
        eq->tail->next = e;

    } else {
        eq->head = e;
    }
    eq->tail = e;
    e->next = NULL;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&monitor);
}

EVENT_TYPE * event_q_remove()
{
    // used to protect queue
    pthread_mutex_lock(&monitor);
    if (!eq->head)  // stop consumer when queue is empty
        pthread_cond_wait(&cond, &monitor);

    EVENT_TYPE * e = eq->head;

    if (e)  // makes sure that head is not NULL before assigning to next
        eq->head = e->next;

    pthread_mutex_unlock(&monitor);
    return e;
}