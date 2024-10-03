#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void main(int argc, char* argv[]) {
    struct sockaddr_in server_addr;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    printf("in here");
    
    if (sockfd < 0) {
        printf(" could not create socket");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ssize_t n = sendto(sockfd, argv[1], strlen(argv[1]), 0, (struct sockaddr*)& server_addr, sizeof(server_addr));

    if (n < 0) {
        printf("could not send to udp server");
        close(sockfd);
        return;
    }

    close(sockfd);
    return;
}