#include "ActiveObject.h"

/*--------------------------------- Question 2 -------------------------------------*/

activeObject *newAO(struct Queue *q, void *(*func1)(void *), void *(*func2)(void *))
{
    activeObject *ao = (activeObject *)malloc(sizeof(activeObject));
    ao->q = q;
    ao->func1 = func1;
    ao->func2 = func2;
    ao->thread = (pthread_t *)malloc(sizeof(pthread_t));
    ao->thread_status = 0;
    pthread_create(ao->thread, NULL, startActiveObject, ao);
    return ao;
}

void *startActiveObject(void *arg)
{
    activeObject *ao = (activeObject *)arg;
    while (1)
    {
        void *data = ao->func1(deQ(ao->q));
        if (data == NULL)
        {
            break;
        }
        /*void *res = */ ao->func2(data);
    }
    ao->thread_status = 1;
    pthread_exit(NULL);
}
void destroyAO(activeObject *ao)
{
    if (ao->thread_status == 0)
    {
        pthread_cancel(*ao->thread);
    }
    destroyQ(ao->q);
    free(ao->thread);
    free(ao);
}