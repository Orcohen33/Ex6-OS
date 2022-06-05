#include <iostream>
#include <pthread.h>

typedef struct reactor{
    int fd;
    pthread_t tid;
    void*(*func)(void*);
}reactor , *p_reactor;

typedef struct reqests{
    int fd;
    p_reactor ptr;
}request, *p_requests;

p_reactor reactor_init()
{
    p_reactor p = (p_reactor)malloc(sizeof(reactor));
    return p;
}

void install_handler(p_reactor p, void*(*func)(void*) , int fd)
{
    p->func = func;
    p->fd = fd;
    pthread_create(&p->tid, NULL, func, p); // not finished
}

void remove_handler(p_reactor p , int fd)
{
    pthread_cancel(p->tid);
    pthread_join(p->tid, NULL);
    p->fd = -1;
    p->func = NULL;
}