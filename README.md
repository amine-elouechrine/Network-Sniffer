# 🛡️ Low-Level Raw Network Sniffer (No libpcap)

![Language](https://img.shields.io/badge/language-C-blue.svg)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)
![Architecture](https://img.shields.io/badge/architecture-Modular-orange.svg)
![Build](https://img.shields.io/badge/build-Makefile-green.svg)

> **Projet Portfolio :** Implémentation manuelle d'un analyseur de paquets réseau (Sniffer) en C pur, interagissant directement avec le Kernel Linux sans aucune librairie externe type `libpcap`.

## 📋 Présentation

Ce projet est une démonstration technique de programmation système bas niveau. L'objectif est de capturer et d'analyser le trafic réseau en utilisant les **Raw Sockets (`AF_PACKET`)**.

Contrairement aux outils classiques, ce sniffer analyse manuellement les en-têtes Ethernet, IP et TCP en respectant scrupuleusement les RFCs. Cette approche "Bare Metal" est critique dans le développement de **systèmes embarqués de défense**, de **pare-feux souverains** ou de **sondes de détection temps réel**.

## 🛠️ Compétences Techniques Démontrées

### 1. Interaction Kernel & Raw Sockets
- Utilisation de `socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))` pour contourner la stack réseau de l'OS.
- Capture en mode "Promiscuous" pour intercepter tout le trafic passant par la carte réseau.

### 2. "Zero-Copy" Parsing & Arithmétique de Pointeurs
- **Memory Overlay** : Pas de `memcpy` coûteux. Le parsing est effectué par "Type Casting" de structures directement sur le buffer de réception.
- **Arithmétique Dynamique** : Calcul manuel des offsets pour gérer les tailles d'en-têtes variables (Options IP et TCP).
  - *Formule :* `Payload = Buffer + sizeof(Ethernet) + (IP_Header_Len * 4) + (TCP_Data_Offset * 4)`

### 3. Architecture Modulaire & Tests
- Code structuré (`src/`, `include/`) séparant la logique socket, le parsing et le main.
- **Unit Testing** : Banc de test intégré (`tests/`) injectant des faux paquets (Mocking) pour valider la logique de parsing sans accès réseau.
- **Documentation** : Génération automatique via Doxygen.

## 🚀 Architecture du Projet

```bash
raw-packet-sniffer/
├── src/
│   ├── main.c           # Point d'entrée et boucle principale
│   ├── raw_socket.c     # Gestion bas niveau du socket (Syscalls)
│   └── packet_parser.c  # Logique de décodage (Ethernet/IP/TCP)
├── include/
│   ├── raw_socket.h     # Interfaces Socket
│   └── packet_parser.h  # Interfaces Parser
├── tests/
│   └── test_parser.c    # Tests unitaires (Injection de paquets hexadécimaux)
├── Doxyfile             # Configuration de la documentation
├── Makefile             # Système de build automatisé
└── README.md            # Documentation du projet
