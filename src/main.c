#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include "raw_socket.h"
#include "packet_parser.h"
#define BUFFER_SIZE 65536

int main() {
    int raw_sock = create_raw_socket();
    unsigned char *buffer = (unsigned char *) malloc(BUFFER_SIZE);
    
    struct sockaddr saddr;
    socklen_t saddr_size = sizeof(saddr);

    printf("[+] Sniffer started. Listening...\n");

    while(1) {
        int data_size = recvfrom(raw_sock, buffer, BUFFER_SIZE, 0, &saddr, &saddr_size);
        if(data_size < 0) {
            perror("Recvfrom error");
            return 1;
        }
        process_packet(buffer, data_size);
    }

    free(buffer);
    close(raw_sock);
    return 0;
}