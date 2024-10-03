#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void main() {
    struct sockaddr_in addr;
    struct sockaddr_in client_addr;
    char buffer[1024];
    int n;
    socklen_t client_length = sizeof(client_addr);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (bind(sockfd, (struct sockaddr*)& addr, sizeof(addr)) < 0) {
        printf(" bind failed ");
        close(sockfd);
        return;
    }

    if (listen(sockfd, 5) < 0) {
        printf("linste faled");
        close(sockfd);
        return;
    }

    int acceptfd = accept(sockfd, (struct sockaddr*)& client_addr, &client_length);
    if (acceptfd < 0) {
        printf("accept failed");
        close(sockfd);
        return;
    }

    memset(buffer, 0, sizeof(buffer));
    n = read(acceptfd, buffer, sizeof(buffer)-1);
    if (n < 0) {
        printf("read failed");
        close(acceptfd);
        close(sockfd);
        return;
    }

    printf("received message from client %s\n", buffer);

    close(sockfd);
    close(acceptfd);

    return;
}