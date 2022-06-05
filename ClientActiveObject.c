#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <memory.h>
#include <netinet/in.h>
#include <sys/types.h>
static int sock1 = -1;
void *receiveMsg(void *arg)
{
    char *my_buffer = (char *)calloc(256, 1);

    int bytes = 0, numOfMessages = 0;

    while ((bytes = recv(sock1, my_buffer, 2000, 0)) != -1 || numOfMessages < 3)
    {
        if (bytes == 0)
        {
            break;
        }
        else
        {
            printf("[RECIEVED BACK]: %s\n", my_buffer);
            numOfMessages++;
        }
        bzero(my_buffer, 256);
    }
    printf("Finished receiving\n");
    free(my_buffer);
    return NULL;
}

void *sendMsg(void *arg)
{
    char str1[256] = {'\0'};
    int numOfMessages = 0;
    printf("You can send 3 messages to server:\n");
    while (numOfMessages < 3)
    {
        printf("Enter message: ");
        scanf("%s", str1);
        send(sock1, str1, strlen(str1), 0);
        printf("%d messages sent\n", (numOfMessages + 1));
        numOfMessages++;
        sleep(1);
        bzero(str1, 256);
    }
    return NULL;
}

int main()
{
    sock1 = socket(AF_INET, SOCK_STREAM, 0);
    if (sock1 == -1)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    // init client
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(8080);
    printf("Ready to login\n");
    int clientSocket = connect(sock1, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (clientSocket == -1)
    {
        perror("socket");
        printf("listen failed");
        close(sock1);
        return -1;
    }
    printf("Login successfuly\n");
    //------------

    pthread_t t1, t2;

    // exec rcv, send operations threads
    pthread_create(&t1, NULL, receiveMsg, NULL);
    pthread_create(&t2, NULL, sendMsg, NULL);
    // join both threads
    pthread_join(t2, NULL);
    pthread_join(t1, NULL);
    printf("finish send and received\n");
    close(sock1); // close socket
    return 0;
}
/*
    How to run:
    1. Open cmd and write "make all"
    2. Then write "./main1" to run the server.
    3. Then open another cmd and write "./client" to run the client .(Can be done several times at the same time)
        - You have 3 messages to send for each client.
        - The process by which a message passes:
            1. The server receives the message and inserts it into the first queue.
            2. The first active object activates the function on the message and activates an Caeser cipher on it,
            Then forwards the message to the second queue.
            3.The second active object takes the message from the second queue and runs a function on it that resizes the letters,
            Then forwards the message to the third queue.
            4. The third active object takes the message from the third queue and sends the new message back to the client.

*/