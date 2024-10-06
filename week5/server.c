#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void main() {
    struct sockaddr_in server_addr, client_addr;
    int n;
    void* packet = malloc(1024);
    char* buffer = (char*) packet;
    // AF_INET represents the domain family ipv4
    // SOCK_RAW basically means it's a raw socket, not tcp/udp - means raw packets will be coming in
    // IPPROTO_UDP basically means the socket should only look for UDP packets - but i need to create my own UDP headers
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sockfd < 0) {
        printf(" could not create socket");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr*)& server_addr, sizeof(server_addr)) < 0) {
        printf("could not fucking bind the socket");
        close(sockfd);
        return;
    }


    socklen_t client_len = sizeof(client_addr);
    
    while (1) {
        n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)& client_addr, &client_len);
        if (n < 0) {
            printf("could not receive");
            close(sockfd);
            return;
        }

        unsigned char* byte_ptr = (unsigned char*)packet;

        // Iterate through each byte and print it
        for (size_t i = 0; i < 1024; i++) {
            printf("%02x ", byte_ptr[i]); // Print in hexadecimal format
        }
        printf("\n");

        uint8_t* combined = (uint8_t*)(packet);
        uint8_t* tos = (uint8_t*) (packet + sizeof(uint8_t)); // type of service - priority and quality of the service for each packet
        uint16_t* tot_len = (uint16_t*) (packet + sizeof(uint8_t) + sizeof(*tos)); // total length (ip header + data) - the data itself is also UDP header + data etc
        uint16_t* id = (uint16_t*) (packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len)); // id - basically used for when the packet needs to be fragmented
        uint16_t* frag_off = (uint16_t*) (packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id)); // fragment offset - used in packet fragmentation so it knows the order
        uint8_t* ttl = (uint8_t*) (packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id) + sizeof(*frag_off)); // time to live how many router hops a packet can do before it gets dropped
        uint8_t* protocol = (uint8_t*) (packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id) + sizeof(*frag_off) + sizeof(*ttl)); // protocol (UDP = 17) 6 is TCP 17 is UDP
        u_int16_t* check_ip = (uint16_t*) (packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id) + sizeof(*frag_off) + sizeof(*ttl) + sizeof(*protocol)); // IP checksum - the checksum is computed for error checking the IP header
        uint32_t* saddr = (uint32_t*) (packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id) + sizeof(*frag_off) + sizeof(*ttl) + sizeof(*protocol) + sizeof(*check_ip)); // source ip address
        uint32_t* daddr = (uint32_t*) (packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id) + sizeof(*frag_off) + sizeof(*ttl) + sizeof(*protocol) + sizeof(*check_ip) + sizeof(*saddr)); // destination ip address

        uint16_t* source = (uint16_t*) (packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id) + sizeof(*frag_off) + sizeof(*ttl) + sizeof(*protocol) + sizeof(*check_ip) + sizeof(*saddr) + sizeof(*daddr)); // source port - port number on sending device
        uint16_t* dest = (uint16_t*) (packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id) + sizeof(*frag_off) + sizeof(*ttl) + sizeof(*protocol) + sizeof(*check_ip) + sizeof(*saddr) + sizeof(*daddr) + sizeof(*source)); // destination port - port number on the receiving device
        uint16_t* len = (uint16_t*) (packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id) + sizeof(*frag_off) + sizeof(*ttl) + sizeof(*protocol) + sizeof(*check_ip) + sizeof(*saddr) + sizeof(*daddr) + sizeof(*source) + sizeof(*dest)); // length of udp header + data - length of udp header + payload
        uint16_t* check_udp = (uint16_t*) (packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id) + sizeof(*frag_off) + sizeof(*ttl) + sizeof(*protocol) + sizeof(*check_ip) + sizeof(*saddr) + sizeof(*daddr) + sizeof(*source) + sizeof(*dest) + sizeof(*len)); // udp checksum (optional) - checksum as above
        
        char* data = packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id) + sizeof(*frag_off) + sizeof(*ttl) + sizeof(*protocol) + sizeof(*check_ip) + sizeof(*saddr) + sizeof(*daddr) + sizeof(*source) + sizeof(*dest) + sizeof(*len) + sizeof(*check_udp);

        // printf("ihl is %d \n", *ihl);
        // printf(" version is %d \n ", *version);
        // printf(" tos is %d \n ", *tos);
        // printf(" totlen is %d \n ", htons(*tot_len));
        // printf(" id is %d \n ", *id);
        // printf(" fragoff is %d \n ", *frag_off);
        // printf(" ttl is %d \n ", *ttl);
        // printf(" protocl is %d \n ", *protocol);
        // printf(" check is %d \n ", *check_ip);
        // printf(" saddr is %d \n ", *saddr);
        // printf(" daddr is %d \n ", *daddr);

        // printf("udpsrc is %d \n", *source);
        // printf("udpdest is %d\n", ntohs(*dest));
        // printf("udplen is %d\n", ntohs(*len));
        // printf("udpcheck is %d\n", *check_udp);

        buffer[n] = '\0';

        printf("got string from user %s \n", data);
        // printf("data len is %d \n", strlen(data));
        // printf("buff len is %d \n", strlen(buffer));

        // printf("--------------------------\n");
        memset(buffer, 0, 1024);
        if (ntohs(*dest) == 8080) {
            break;   
        } else {
            continue;
        }
    }
    close(sockfd);
    free(packet);
    return;
}