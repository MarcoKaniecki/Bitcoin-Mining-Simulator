//
// Created by Marco Kaniecki on 2022-07-29.
//

#ifndef MINER_EVENT_Q_H
#define MINER_EVENT_Q_H

#define MAX_BUFFER_SIZE 256

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

typedef struct event_type
{
    struct event_type *next;
    char event[MAX_BUFFER_SIZE];
} EVENT_TYPE;

typedef struct event_queue
{
    EVENT_TYPE *head;
    EVENT_TYPE *tail;
} EVENT_QUEUE;

pthread_mutex_t monitor;
pthread_cond_t cond;
extern EVENT_QUEUE *eq;

extern EVENT_TYPE *event_new();
extern EVENT_QUEUE * event_q_init();
extern void event_q_add(EVENT_TYPE *event);
extern EVENT_TYPE * event_q_remove();

#endif //MINER_EVENT_Q_H
