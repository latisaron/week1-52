#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void main() {
    struct sockaddr_in server_addr, incomingaddr;
    socklen_t client_length = sizeof(incomingaddr);
    char buffer[1024];
    int n;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("could not create socket");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockfd, (struct sockaddr*)& server_addr, sizeof(server_addr)) < 0) {
        printf("could not bind socket to port");
        close(sockfd);
        return;
    }

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)& incomingaddr, &client_length);
        if (n < 0) {
            printf("could not read form recfrom");
            close(sockfd);
            return;
        }

        buffer[n] = '\0';
        printf("received message from client %s", buffer);

        if (n > 0 ) {
            break;
        }
    }
}