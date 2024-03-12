#include <winsock2.h> // Bibliothèque pour les sockets Windows
#include <windows.h> // Bibliothèque Windows
#include <stdio.h> // Bibliothèque d'entrée/sortie standard
#include <stdlib.h> // Bibliothèque standard
#include <ws2tcpip.h> // Déclarations pour la manipulation des sockets TCP/IP

#define PORT 5000 // Port utilisé pour la communication
#define LG_MESSAGE 256 // Longueur maximale du message

#pragma comment(lib, "ws2_32.lib") // Lien statique vers la bibliothèque ws2_32.lib

int handleClient(SOCKET socketDialogue) {
    char messageRecu[LG_MESSAGE]; /* le message reçu de la couche Application */
    char messageEnvoi[LG_MESSAGE];
    int ecrits, lus; /* nb d’octets lus */

    // Lire les données envoyées par le client
    lus = recv(socketDialogue, messageRecu, LG_MESSAGE, 0);
    if (lus > 0) {
        messageRecu[lus] = '\0'; // Ajouter un caractère de fin de chaîne
        printf("Client : %s\n", messageRecu);

        // Envoyer une réponse au client
        printf("Moi : ");
        fgets(messageEnvoi, LG_MESSAGE, stdin);
        ecrits = send(socketDialogue, messageEnvoi, (int)strlen(messageEnvoi), 0);
        if (ecrits == SOCKET_ERROR) {
            printf("Erreur lors de l'envoi du message : %d\n", WSAGetLastError());
            return 1;
        }
    }
    else if (lus == 0) {
        printf("Client déconnecté.\n");
        return 1;
    }
    else {
        printf("Erreur de lecture : %d\n", WSAGetLastError());
        return 1;
    }

    return 0;
}

int main() {
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData); // Initialisation de la bibliothèque Winsock

    SOCKET socketEcoute;
    SOCKET socketDialogue;
    struct sockaddr_in pointDeRencontreLocal;
    struct sockaddr_in pointDeRencontreDistant;
    int iResult;

    socketEcoute = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP); // Création du socket pour écouter
    if (socketEcoute == INVALID_SOCKET) {
        printf("Erreur lors de la création du socket : %d\n", WSAGetLastError());
        WSACleanup(); // Nettoyage des ressources
        return 1;
    }

    // Configuration du point de rencontre local
    pointDeRencontreLocal.sin_family = AF_INET;
    pointDeRencontreDistant.sin_addr.s_addr = inet_addr("127.0.0.1");
    pointDeRencontreLocal.sin_port = htons(PORT);

    // Lier le socket à l'adresse et au port spécifiés
    iResult = bind(socketEcoute, (SOCKADDR *)&pointDeRencontreLocal, sizeof(pointDeRencontreLocal));
    if (iResult == SOCKET_ERROR) {
        printf("Erreur lors du bind : %d\n", WSAGetLastError());
        closesocket(socketEcoute); // Fermeture du socket
        WSACleanup(); // Nettoyage des ressources
        return 1;
    }

    printf("Socket attaché avec succès.\n");

    // Mettre en écoute pour les connexions entrantes
    if (listen(socketEcoute, SOMAXCONN) == SOCKET_ERROR) {
        printf("Erreur lors de la mise en écoute : %d\n", WSAGetLastError());
        closesocket(socketEcoute);
        WSACleanup();
        return 1;
    }

    printf("En attente de connexions...\n");

    while (1) {
        int longueurAdresse = sizeof(pointDeRencontreDistant);
        socketDialogue = accept(socketEcoute, (SOCKADDR*)&pointDeRencontreDistant, &longueurAdresse); // Accepter une connexion entrante
        if (socketDialogue == INVALID_SOCKET) {
            printf("Erreur lors de l'accept : %d\n", WSAGetLastError());
            closesocket(socketEcoute);
            WSACleanup();
            return 1;
        }

        // Gérer la communication avec le client
        while (1) {
            if (handleClient(socketDialogue)) {
                closesocket(socketDialogue);
                break;
            }
        }
    }

    closesocket(socketEcoute); // Fermeture du socket d'écoute
    WSACleanup(); // Nettoyage des ressources

    return 0;
}
