#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "packet_parser.h"
void print_payload(unsigned char* data, int size) {
    printf("   |-Payload (%d bytes) :\n   ", size);
    for (int i = 0; i < size; i++) {
        if (data[i] >= 32 && data[i] <= 126) {
            printf("%c", data[i]);
        } else {
            printf(".");
        }
    }
    printf("\n");
}

void process_packet(unsigned char* buffer, int size) {
    struct ethhdr *eth = (struct ethhdr *)buffer;

    // Filtre IPv4 (0x0800)
    if (eth->h_proto == htons(ETH_P_IP)) {
        struct iphdr *iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));
        unsigned short iphdrlen = iph->ihl * 4;

        // Préparation des adresses
        struct sockaddr_in source, dest;
        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = iph->saddr;
        memset(&dest, 0, sizeof(dest));
        dest.sin_addr.s_addr = iph->daddr;

        // Filtre TCP (6)
        if (iph->protocol == 6) {
            struct tcphdr *tcph = (struct tcphdr*)(buffer + sizeof(struct ethhdr) + iphdrlen);
            
            // Calcul de la position des données
            int header_size = sizeof(struct ethhdr) + iphdrlen + (tcph->doff * 4);
            int payload_size = size - header_size;

            // Affichage si données présentes
            if (payload_size > 0) {
                printf("[TCP] %s:%d -> %s:%d\n", 
                    inet_ntoa(source.sin_addr), ntohs(tcph->source),
                    inet_ntoa(dest.sin_addr), ntohs(tcph->dest));
                
                print_payload(buffer + header_size, payload_size);
            }
        }
    }
}