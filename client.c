#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ws2tcpip.h>

#define PORT 5000
#define LG_MESSAGE 256

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData); // Initialisation de la bibliothèque Winsock

    SOCKET descripteurSocket;
    struct sockaddr_in pointDeRencontreDistant;
    int iResult;

    descripteurSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // Création du socket
    if (descripteurSocket == INVALID_SOCKET) {
        printf("Erreur lors de la création du socket : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("Socket créé avec succès.\n");

    // Configuration du point de rencontre distant
    pointDeRencontreDistant.sin_family = AF_INET;
    pointDeRencontreDistant.sin_addr.s_addr = inet_addr("127.0.0.1");
    pointDeRencontreDistant.sin_port = htons(PORT);

    // Établir une connexion avec le serveur
    iResult = connect(descripteurSocket, (SOCKADDR *)&pointDeRencontreDistant, sizeof(pointDeRencontreDistant));
    if (iResult == SOCKET_ERROR) {
        printf("Erreur lors de la connexion : %d\n", WSAGetLastError());
        closesocket(descripteurSocket);
        WSACleanup();
        return 1;
    }

    printf("Connexion au serveur réussie.\n");

    char messageEnvoi[LG_MESSAGE];
    char messageRecu[LG_MESSAGE];
    int ecrits, lus;
    while(1){
        printf("Moi : ");
        fgets(messageEnvoi, LG_MESSAGE, stdin);

        // Envoyer le message au serveur
        ecrits = send(descripteurSocket, messageEnvoi, (int)strlen(messageEnvoi), 0);
        if (ecrits == SOCKET_ERROR) {
            printf("Erreur lors de l'envoi du message : %d\n", WSAGetLastError());
            closesocket(descripteurSocket);
            WSACleanup();
            return 1;
        }

        lus =  recv(descripteurSocket, messageRecu, LG_MESSAGE, 0); // Recevoir la réponse du serveur
        if (lus > 0) {
            messageRecu[lus] = '\0'; // Ajouter un caractère de fin de chaîne
            printf("Serveur : %s\n", messageRecu);
        }
        else if (lus == 0) {
            printf("Serveur déconnecté.\n");
        }
        else {
            printf("Erreur de lecture : %d\n", WSAGetLastError());
        }

    }    

    closesocket(descripteurSocket); // Fermeture du socket
    WSACleanup(); // Nettoyage des ressources

    return 0;
}
