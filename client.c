#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

// create a main function and print hello world
int main( int argc, char* argv[]){
    if(argc != 4){
        printf("Missing arguments! \n");
        printf("Usage: %s <file> <ipv6-adress> <port> \n", argv[0]);
        exit(0);
    }

    char *importFileName = argv[1];
    char *serverAdress = argv[2];
    int port = atoi(argv[3]);
    printf("Client started! \n");
    printf("Import file name: %s \n", importFileName);
    printf("Server IPv6 address: %s \n", serverAdress);
    printf("Server port: %i \n", port);


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
    serverAddr.sin6_addr = in6addr_any;

    strcpy(buffer, "Hello Server!\n");
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
}