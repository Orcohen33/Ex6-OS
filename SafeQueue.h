#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <sys/types.h>

#pragma once

struct Node
{
    void *data;
    struct Node *next, *prev;
    int sock_fd;
} * Node;

typedef struct Queue
{
    struct Node *head, *tail;
    int size;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
} * Queue;

struct Queue *createQ();
void destroyQ(struct Queue *q);
void enQ(struct Queue *q, void *data);
void *deQ(struct Queue *q);