#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ActiveObject.h"
#include "SafeQueue.h"

static pthread_t *clients;

// ------------------------------------- Q1 -------------------------------------
struct Queue *q1;
struct Queue *q2;
struct Queue *q3;
// ------------------------------------------------------------------------------
// ------------------------------------- Q2 -------------------------------------
struct activeObject *ao1;
struct activeObject *ao2;
struct activeObject *ao3;
// ------------------------------------------------------------------------------
// ------------------------------------- Q3 -------------------------------------

void *toQ1(void *data)
{
    enQ(q1, data);
    return data;
}
void *toQ2(void *data)
{
    enQ(q2, data);
    return data;
}
void *toQ3(void *data)
{
    enQ(q3, data);
    return data;
}
void *toQ4(void *data)
{
    free(data);
    return NULL;
}

void *func1(void *data)
{
    struct Node *node = (struct Node *)data; // toPrint data

    if (!node)
    {
        printf("Error: temp is NULL\n");
        return NULL;
    }
    char *str = (char *)node->data;
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'z')
        {
            str[i] = 'a';
        }
        else if (str[i] == 'Z')
        {
            str[i] = 'A';
        }
        else
        {
            str[i]++;
        }
    }
    node->data = str;
    return node;
}

void *func2(void *data)
{
    struct Node *node = (struct Node *)data; // toPrint data
    char *str = (char *)node->data;
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 'a' + 'A';
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] - 'A' + 'a';
        }
    }
    node->data = str;
    return node;
}

// -----------------------------------------------------------------------------------
// ---------------------------------- SERVER -----------------------------------------
void *receiveMessage(void *sock_fd)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->sock_fd = *(int *)sock_fd;
    printf("[RECEIVE_MESSAGE] sock_fd: %d\n", node->sock_fd);
    char buffer[1024] = {'\0'};
    int n;
    int countMessages = 0;
    while (countMessages < 3)
    {
        bzero(buffer, 1024);
        n = recv(node->sock_fd, buffer, 1024, 0);
        if (n < 0)
        {
            perror("ERROR reading from socket");
            exit(1);
        }
        if (n == 0)
        {
            printf("Client disconnected\n");
            break;
        }
        if (strlen(buffer) > 0)
        {

            node->data = (void *)malloc(strlen(buffer) + 1);
            strcpy((char *)node->data, buffer);
            node->next = NULL;
            toQ1(node);

            countMessages++;
        }
    }
    sleep(3);
    printf("[FINISH RECEIVE]\n");
    close(node->sock_fd);
    return sock_fd;
}
void *sendBackAnswerToClient(void *data)
{
    struct Node *n = (struct Node *)data;
    printf("Sending back to client: %s\n", (char *)n->data);
    if (n->sock_fd == -1)
    {
        printf("Error: sock_fd is -1\n");
        return NULL;
    }
    send(n->sock_fd, n->data, strlen((char *)n->data), 0);
    return data;
}
void *runServer()
{
    int sock_fd, new_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size;
    int port = 8080;
    clients = (pthread_t *)malloc(sizeof(pthread_t) * 10);
    // Creating socket file descriptor
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    // Zeroing the structure
    memset(&server_addr, 0, sizeof(server_addr));
    // Filling the structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // Binding the socket
    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Error: bind");
        exit(1);
    }
    printf("Binded\n");
    // Listening for connections
    if (listen(sock_fd, 5) == -1)
    {
        perror("listen");
        exit(1);
    }
    printf("Listening ..\n");
    // Accepting connections
    while (1)
    {
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size)) == -1)
        {
            perror("Accept error");
            exit(1);
        }
        printf("New connection :\n");
        pthread_create(&clients[new_fd], NULL, receiveMessage, &new_fd);
    }
}
// -----------------------------------------------------------------------------------

/* --------------------------------- MAIN -----------------------------------*/
int main()
{
    q1 = createQ();
    q2 = createQ();
    q3 = createQ();
    ao1 = newAO(q1, func1, toQ2);
    sleep(1);
    ao2 = newAO(q2, func2, toQ3);
    sleep(1);
    ao3 = newAO(q3, sendBackAnswerToClient, toQ4);

    runServer();

    return 0;
}