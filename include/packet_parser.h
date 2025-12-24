#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <net/ethernet.h>

/**
 * @file packet_parser.h
 * @brief Fonctions d'analyse et d'affichage des paquets réseaux.
 * @author Amine
 * @version 1.0
 */

/**
 * @brief Affiche le contenu ASCII d'une payload TCP.
 * * Remplace les caractères non-imprimables par des points.
 * * @param data Pointeur vers le début des données.
 * @param size Taille des données en octets.
 */
void print_payload(unsigned char* data, int size);

/**
 * @brief Analyse un paquet brut capturé sur le réseau.
 * * Découpe les couches Ethernet -> IP -> TCP et affiche les informations
 * si le protocole est supporté.
 * * @param buffer Le buffer contenant le paquet brut.
 * @param size La taille totale du paquet reçu.
 */
void process_packet(unsigned char* buffer, int size);

#endif