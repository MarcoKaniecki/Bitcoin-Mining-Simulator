//
// Created by Marco Kaniecki on 2022-07-29.
//

#include "reader.h"
#include "event_q.h"

EVENT_QUEUE *eq;
pthread_t thread_id;

// producer
static void *runner(void *arg)
{
    // read in all events from stdin
    char event_type[MAX_BUFFER_SIZE];
    unsigned int block_id;

    for (;;)
    {
        EVENT_TYPE * e = event_new();

        // reads whatever is in stdin line by line
        fgets(e->event, sizeof(e->event), stdin);

        // extract first variable ie. EPOCH, MINE, BLK, TRX ...
        sscanf(e->event, "%s", event_type);

        if (!strcmp(event_type, BLK_EVENT) || !strcmp(event_type, TRX_EVENT))
        {
            // %*s to ignore the event_type
            sscanf(e->event, "%*s %d", &block_id);
            printf("Received event %s with ID %d\n", event_type, block_id);
        }
        else if (!strcmp(event_type, EPOCH_EVENT) || !strcmp(event_type, MINE_EVENT) || !strcmp(event_type, END_EVENT))
            printf("Received event %s\n", event_type);

        event_q_add(e);

        if (!strcmp(event_type, END_EVENT))
            break;
    }
}

// init monitor, condition, queue and create a thread solely for reading inputs from stdin
void start_reader()
{
    pthread_mutex_init(&monitor, NULL);
    pthread_cond_init(&cond, NULL);
    eq = event_q_init();  // initialize event queue
    pthread_create(&thread_id, NULL, &runner, NULL);
}


void stop_reader()
{
    pthread_join(thread_id, NULL);
    pthread_mutex_destroy(&monitor);
    pthread_cond_destroy(&cond);
}
