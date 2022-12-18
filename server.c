#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

int main( int argc, char* argv[]){
    if(argc != 3){
        printf("Missing arguments! \n");
        printf("Usage: %s <file> <port> \n", argv[0]);
        exit(0);
    }

    char *exportFileName = argv[1];
    int port = atoi(argv[2]);
    printf("Server started! \n");
    printf("Export file name: %s \n", exportFileName);
    printf("Port: %i \n", port);

    printf("Setting up socket... \n");
    int sockfd;
    struct sockaddr_in6 serverAddr, newAddr;
    char buffer[1024];
    socklen_t addr_size;

    sockfd = socket(AF_INET6, SOCK_DGRAM, 0);

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin6_family = AF_INET6;
    serverAddr.sin6_flowinfo = 0;
    serverAddr.sin6_port = htons(port);
    serverAddr.sin6_addr = in6addr_loopback;

    bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    addr_size = sizeof(newAddr);

    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&newAddr, &addr_size);

    printf("Data received: %s \n", buffer);
}