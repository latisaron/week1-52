#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


void main() {
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    memset(buffer, 0, 1024);
    int n;
    struct iphdr {
        unsigned int ihl:4; // internet header length - 4 means 4 bytes - 32 bits
        unsigned int version:4; // ipv4
        uint8_t tos; // type of service - priority and quality of the service for each packet
        uint16_t tot_len; // total length (ip header + data) - the data itself is also UDP header + data etc
        uint16_t id; // id - basically used for when the packet needs to be fragmented
        uint16_t frag_off; // fragment offset - used in packet fragmentation so it knows the order
        uint8_t ttl; // time to live how many router hops a packet can do before it gets dropped
        uint8_t protocol; // protocol (UDP = 17) 6 is TCP 17 is UDP
        u_int16_t check; // IP checksum - the checksum is computed for error checking the IP header
        uint32_t saddr; // source ip address
        uint32_t daddr; // destination ip address
    };

    struct udphdr {
        uint16_t source; // source port - port number on sending device
        uint16_t dest; // destination port - port number on the receiving device
        uint16_t len; // length of udp header + data - length of udp header + payload
        uint16_t check; // udp checksum (optional) - checksum as above
    };

    int one = 1;
    

    // AF_INET represents the domain family ipv4
    // SOCK_RAW basically means it's a raw socket, not tcp/udp - means raw packets will be coming in
    // IPPROTO_UDP basically means the socket should only look for UDP packets - but i need to create my own UDP headers
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sockfd < 0) {
        printf(" could not create socket");
        return;
    }

    // IP_HDRINCL - tells the kernel you are constructing the IP headers by myself
    setsockopt(sockfd, IPPROTO_UDP, IP_HDRINCL, &one, sizeof(one));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockfd, (struct sockaddr*)& server_addr, sizeof(server_addr));

    struct iphdr* package_iphdr = (struct iphdr*)buffer;
    struct udphdr* package_udphdr = (struct udphdr*)(buffer + sizeof(struct iphdr));
    char* data = (buffer + sizeof(struct iphdr) + sizeof(struct udphdr));

    socklen_t client_len = sizeof(client_addr);

    n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)& client_addr, &client_len);
    if (n < 0) {
        printf("could not receive");
        close(sockfd);
        return;
    }
    buffer[n] = '\0';

    printf("got string from user %s", data);
    printf("data len is %d", strlen(data));
    printf("buff len is %d", strlen(buffer));

    close(sockfd);
    return;
}