/*
 * c-chess-cli, a command line interface for UCI chess engines. Copyright 2020 lucasart.
 *
 * c-chess-cli is free software: you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * c-chess-cli is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If
 * not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include <pthread.h>
#include <stdbool.h>

// Job: instruction to play a single game
typedef struct {
    int e1, e2;  // engine[e1] plays engine[e2]
    bool reverse;  // if true, e1 plays second
    char pad[3];
} Job;

// Job Queue: consumed by workers to play tournament (thread safe)
typedef struct {
    pthread_mutex_t mtx;
    Job *jobs;
    size_t idx;
} JobQueue;

JobQueue job_queue_new(int engines, int rounds, int games);
void job_queue_del(JobQueue *jq);

bool job_queue_pop(JobQueue *jq, Job *j, size_t *idx);