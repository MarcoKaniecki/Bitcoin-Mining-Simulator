//
// Created by Marco Kaniecki on 2022-07-29.
//

#ifndef MINER_READER_H
#define MINER_READER_H

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "event_q.h"

#define END_EVENT "END"
#define MINE_EVENT "MINE"
#define TRX_EVENT "TRX"
#define BLK_EVENT "BLK"
#define EPOCH_EVENT "EPOCH"

extern void start_reader();
extern void stop_reader();

#endif //MINER_READER_H
