#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

unsigned short checksum(void *buffer, int len) {
    // this should do a classic checksum stuff but i can't figure it out right now
    return 1;
}

void main(int argc, char* argv[]) {
    struct sockaddr_in server_addr, client_addr;
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
    char packet[1024];
    int one = 1;

    // AF_INET represents the domain family ipv4
    // SOCK_RAW basically means it's a raw socket, not tcp/udp - means raw packets will be coming in
    // IPPROTO_UDP basically means the socket should only look for UDP packets - but i need to create my own UDP headers
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sockfd < 0) {
        printf(" could not create socket"); 
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    struct iphdr* packet_iphdr = (struct iphdr*) packet;
    struct udphdr* packet_udphdr = (struct udphdr*)(packet + sizeof(struct iphdr));

    char* data = packet + sizeof(struct iphdr) + sizeof(struct udphdr);
    strncpy(data, argv[1], sizeof(packet) - sizeof(struct iphdr) - sizeof(struct udphdr) - 1);
    data[sizeof(packet) - sizeof(struct iphdr) - sizeof(struct udphdr) - 1] = '\0';

    packet_iphdr->ihl = 5;
    packet_iphdr->version = 4;
    packet_iphdr->tos = 0;
    packet_iphdr->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + strlen(data));
    packet_iphdr->id = htons(54321);
    packet_iphdr->frag_off = 0;
    packet_iphdr->ttl = 64;
    packet_iphdr->protocol = IPPROTO_UDP;
    packet_iphdr->check = 0;
    packet_iphdr->saddr = inet_addr("127.0.0.2");
    packet_iphdr->daddr = server_addr.sin_addr.s_addr;

    // packet_iphdr->check = checksum((unsigned short*)packet, packet_iphdr->tot_len);

    packet_udphdr->source = htons(12345);
    packet_udphdr->dest = htons(8000);
    packet_udphdr->len = htons(sizeof(struct udphdr) + strlen(data));
    packet_udphdr->check = 0;

    printf("ihl is %d \n", packet_iphdr->ihl);
    printf(" version is %d \n ", packet_iphdr->version);
    printf(" tos is %d \n ", packet_iphdr->tos);
    printf(" totlen is %d \n ", htons(packet_iphdr->tot_len));
    printf(" id is %d \n ", packet_iphdr->id);
    printf(" fragoff is %d \n ", packet_iphdr->frag_off);
    printf(" ttl is %d \n ", packet_iphdr->ttl);
    printf(" protocl is %d \n ", packet_iphdr->protocol);
    printf(" check is %d \n ", packet_iphdr->check);
    printf(" saddr is %d \n ", packet_iphdr->saddr);
    printf(" daddr is %d \n ", packet_iphdr->daddr);

    printf("udpsrc is %d \n", packet_udphdr->source);
    printf("udpdest is %d\n", packet_udphdr->dest);
    printf("udplen is %d\n", packet_udphdr->len);
    printf("udpcheck is %d\n", packet_udphdr->check);

    if (sendto(sockfd, packet, ntohs(packet_iphdr->tot_len), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("send failed");
        close(sockfd);
        return;
    }

    close(sockfd);
    return;
}