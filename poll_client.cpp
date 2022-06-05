#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <pthread.h>
#include <iostream>
#include <stdio.h>

#define PORT "9034" // Port we're listening on
#define IP_ADDR "127.0.0.1"

using namespace std;

int sockfd = -1;
bool is_connected = false;

void *send_to_server(void *args)
{
    char buf[1024] = {0};
    while (is_connected)
    {
        cin >> buf;
        if (strcmp(buf, "exit") == 0)
        {
            send(sockfd, buf, strlen(buf), 0);
            is_connected = false;
            break;
        }
        if (send(sockfd, buf, strlen(buf), 0) == -1)
        {
            cout << "Error sending message" << endl;
            break;
        }
        bzero(buf, 1024);
    }
    return NULL;
}

void *receive_from_server(void *args)
{
    char buf[1024];
    while (is_connected)
    {
        if (recv(sockfd, buf, 1024, 0) == -1)
        {
            cout << "Error receiving message" << endl;
            break;
        }
        cout << "Server: " << buf << endl;
        bzero(buf, 1024);
    }
    return NULL;
}

int main(){
    cout << "Connected to server" << endl;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        cout << "Error creating socket" << endl;
        return 1;
    }
    struct sockaddr_in serv_addr;
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(PORT));
    serv_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        cout << "Error connecting to server" << endl;
        close(sockfd);
        return 1;
    }
    is_connected = true;
    pthread_t send_thread, receive_thread;
    pthread_create(&send_thread, NULL, send_to_server, NULL);
    pthread_create(&receive_thread, NULL, receive_from_server, NULL);
    pthread_join(send_thread, NULL);
    // pthread_kill(send_thread, 0);
    cout << "Disconnected from server" << endl;
    return 0;

}