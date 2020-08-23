#pragma once
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include "str.h"

typedef struct {
    pthread_mutex_t mtx;
    FILE *file;
    str_t lastFen;
    int next;
    bool repeat;
    char pad[3];
} Openings;

Openings openings_new(const str_t *fileName, bool random, int repeat, int threadId);
void openings_delete(Openings *openings, int threadId);

int openings_next(Openings *o, str_t *fen, int threadId);