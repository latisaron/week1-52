#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void main() {
    void* packet = malloc(1024);  // Allocates 1024 bytes of memory
    unsigned int* ihl = (unsigned int*) packet;
    uint32_t* saddr = (uint32_t*) (packet + sizeof(*ihl));  // Note this

    // Output sizes of types
    printf("Size of *ihl (unsigned int): %lu\n", sizeof(*ihl));   // unsigned int is 4 bytes
    printf("Size of *saddr (uint32_t): %lu\n", sizeof(*saddr));   // uint32_t is 4 bytes
    printf("Size of pointer ihl: %lu\n", sizeof(ihl));            // pointer itself, 8 bytes
    printf("Size of pointer saddr: %lu\n", sizeof(saddr));        // pointer itself, 8 bytes

    // Size of the packet (the memory block is 1024 bytes, but sizeof only applies to types, not malloc sizes)
    printf("Size of the memory pointed by packet: %lu\n", sizeof(packet));  // pointer size, 8 bytes

}