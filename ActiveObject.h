#include <stdio.h>
#include <pthread.h>

#include "SafeQueue.h"

typedef struct activeObject
{
    struct Queue *q;
    void *(*func1)(void *);
    void *(*func2)(void *);
    pthread_t *thread;
    int thread_id;
    int thread_status;
} activeObject;

activeObject *newAO(struct Queue *q, void *(*func1)(void *), void *(*func2)(void *));
void *startActiveObject(void *arg);
void destroyAO(activeObject *ao);