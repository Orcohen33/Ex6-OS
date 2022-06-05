#include <stdio.h>
#include "SafeQueue.h"
/*--------------------------------- Question 1 -------------------------------------*/

struct Queue *createQ()
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->head = q->tail = NULL;
    q->size = 0;
    pthread_cond_init(&q->cond, NULL);
    pthread_mutex_init(&q->mutex, NULL);
    return q;
}
void destroyQ(struct Queue *q)
{
    pthread_mutex_destroy(&q->mutex);
    pthread_cond_destroy(&q->cond);
    free(q);
}
void enQ(struct Queue *q, void *data)
{
    pthread_mutex_lock(&q->mutex);
    struct Node *node = (struct Node *)data;
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = node->data;
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->sock_fd = node->sock_fd;
    if (q->head == NULL)
    {
        q->head = q->tail = node;
        pthread_cond_signal(&q->cond);
    }
    else
    {
        q->tail->next = node;
        node->prev = q->tail;
        q->tail = node;
    }
    q->size++;
    pthread_mutex_unlock(&q->mutex);
}
void *deQ(struct Queue *q)
{
    pthread_mutex_lock(&q->mutex);
    while (q->head == NULL)
    {
        pthread_cond_wait(&q->cond, &q->mutex);
    }
    struct Node *temp = q->head;
    q->head = q->head->next;
    if (q->head == NULL)
    {
        q->tail = NULL;
    }
    else
    {
        q->head->prev = NULL;
    }
    q->size--;
    pthread_mutex_unlock(&q->mutex);
    return temp;
}