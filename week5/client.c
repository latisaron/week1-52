#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

unsigned short checksum(void *buffer, int len) {
    // this should do a classic checksum stuff but i can't figure it out right now
    return 1;
}

void main(int argc, char* argv[]) {
    struct sockaddr_in server_addr, client_addr;
    int n;
    int one = 1;

    // AF_INET represents the domain family ipv4
    // SOCK_RAW basically means it's a raw socket, not tcp/udp - means raw packets will be coming in
    // IPPROTO_UDP basically means the socket should only look for UDP packets - but i need to create my own UDP headers
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0) {
        printf(" could not create socket"); 
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    void* packet = malloc(1024);

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

    // printf("sizeof(*packet) is %d\n", sizeof(*packet));
    // printf("sizeof(*packet) is %d\n", sizeof(*ihl));
    // printf("sizeof(*packet) is %d\n", sizeof(*saddr));

    char* data = packet + sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id) + sizeof(*frag_off) + sizeof(*ttl) + sizeof(*protocol) + sizeof(*check_ip) + sizeof(*saddr) + sizeof(*daddr) + sizeof(*source) + sizeof(*dest) + sizeof(*len) + sizeof(*check_udp);
    strncpy(data, argv[1], 1024 - sizeof(uint8_t) - sizeof(*tos) - sizeof(*tot_len) - sizeof(*id) - sizeof(*frag_off) - sizeof(*ttl) - sizeof(*protocol) - sizeof(*check_ip) - sizeof(*saddr) - sizeof(*daddr) - sizeof(*source) - sizeof(*dest) - sizeof(*len) - sizeof(*check_udp) - 1);
    data[sizeof(*packet) - sizeof(uint8_t) - sizeof(*tos) - sizeof(*tot_len) - sizeof(*id) - sizeof(*frag_off) - sizeof(*ttl) - sizeof(*protocol) - sizeof(*check_ip) - sizeof(*saddr) - sizeof(*daddr) - sizeof(*source) - sizeof(*dest) - sizeof(*len) - sizeof(*check_udp) - 1] = '\0';


    unsigned int tmpihl = 4;
    unsigned int tmpversion = 5;
    *((char*)packet) = ((uint8_t) tmpihl << 4 | ((uint8_t) tmpversion & 0x0F) );
    *tos = 0;
    *tot_len = htons(sizeof(uint8_t) + sizeof(*tos) + sizeof(*tot_len) + sizeof(*id) + sizeof(*frag_off) + sizeof(*ttl) + sizeof(*protocol) + sizeof(*check_ip) + sizeof(*saddr) + sizeof(*daddr) + sizeof(*source) + sizeof(*dest) + sizeof(*len) + sizeof(*check_udp) + strlen(data));
    *id = htons(54321);
    *frag_off = 0;
    *ttl = 64;
    *protocol = IPPROTO_UDP;
    *check_ip = 0;
    *saddr = inet_addr("127.0.0.2");
    *daddr = server_addr.sin_addr.s_addr;
    *check_ip = 0; 

    *source = htons(12345);
    *dest = htons(8080);
    *len = htons(sizeof(*source) + sizeof(*dest) + sizeof(*len) + sizeof(*check_udp) + strlen(data));
    *check_udp = 0;


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

    unsigned char* byte_ptr = (unsigned char*)packet;

    // Iterate through each byte and print it
    for (size_t i = 0; i < 1024; i++) {
        printf("%02x ", byte_ptr[i]); // Print in hexadecimal format
    }

    if (sendto(sockfd, packet, ntohs(*tot_len), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("send failed");
        close(sockfd);
        return;
    }

    close(sockfd);
    free(packet);
    return;
}