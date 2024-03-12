# Introduction
Ce projet est une application client-serveur de base qui permet la communication bidirectionnelle entre un client et un serveur via des sockets TCP en utilisant la bibliothèque Winsock sur Windows. Voici une description détaillée :

# Fonctionnalités :
Communication client-serveur : Le projet permet à un client de communiquer avec un serveur via des sockets TCP/IP.
Envoi et réception de messages : Le client peut envoyer des messages au serveur, et le serveur peut répondre en envoyant des messages au client.
Gestion des connexions : Le serveur peut accepter les connexions entrantes de plusieurs clients et gérer simultanément les communications avec chacun d'eux.
Interaction console : Les messages sont affichés dans la console du client et du serveur, permettant une interaction utilisateur simple.
Structure du projet :
Serveur : Le serveur est implémenté dans le fichier serveur.c. Il crée un socket d'écoute, accepte les connexions entrantes, gère les communications avec les clients, et envoie des réponses aux messages reçus.
Client : Le client est implémenté dans le fichier client.c. Il se connecte au serveur, envoie des messages au serveur, et affiche les réponses du serveur dans la console.
Utilisation typique :
Lancement du serveur : Le serveur est lancé en premier en exécutant le fichier exécutable serveur.exe. Il commence à écouter sur le port spécifié.
Connexion des clients : Les clients se connectent au serveur en exécutant le fichier exécutable client.exe. Ils fournissent l'adresse IP et le port du serveur auquel ils veulent se connecter.
Communication client-serveur : Une fois connectés, les clients peuvent envoyer des messages au serveur, qui les affiche dans sa console. Le serveur peut également envoyer des réponses aux clients, qui les affichent dans leur console.
# Objectif :
Ce projet peut servir de base pour développer des applications plus avancées telles qu'un système de messagerie instantanée, un jeu multijoueur en ligne, ou toute autre application nécessitant une communication en temps réel entre plusieurs clients et un serveur. Il offre une infrastructure simple mais robuste pour mettre en place des fonctionnalités de communication réseau dans des applications Windows.