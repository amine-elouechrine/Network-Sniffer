#include <stdio.h>
#include <string.h>
#include "../include/packet_parser.h"

// Un faux paquet capturé (Hex dump d'un paquet HTTP simple)
unsigned char mock_packet[] = {
    // Ethernet Header (14 bytes)
    0x00, 0x0c, 0x29, 0x4f, 0x8e, 0x35, // Dest MAC
    0x00, 0x50, 0x56, 0xc0, 0x00, 0x08, // Source MAC
    0x08, 0x00,                         // IPv4 Type
    // IP Header (20 bytes)
    0x45, 0x00, 0x00, 0x28, 0x1c, 0x46, 0x40, 0x00, 0x40, 0x06, 0x00, 0x00, 
    0xc0, 0xa8, 0x01, 0x0a, // Source IP: 192.168.1.10
    0xc0, 0xa8, 0x01, 0x14, // Dest IP: 192.168.1.20
    // TCP Header (20 bytes)
    0x00, 0x50,             // Source Port: 80
    0x30, 0x39,             // Dest Port: 12345
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x50, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
    // Payload (HTTP "TEST")
    'T', 'E', 'S', 'T'
};

int main() {
    printf("=== RUNNING UNIT TEST: PACKET PARSER ===\n");
    // On appelle notre fonction avec le faux paquet
    process_packet(mock_packet, sizeof(mock_packet));
    printf("=== TEST FINISHED ===\n");
    return 0;
}