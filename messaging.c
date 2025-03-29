// messaging.c
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "messaging.h"

// Initialiser le système de messagerie
void initMessageSystem(MessageSystem *msgSystem) {
    msgSystem->count = 0;
}

// Fonction pour obtenir l'heure actuelle
void getCurrentTime(char *buffer, int size) {
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Fonction pour envoyer un message
void sendMessage(MessageSystem *msgSystem, const char *sender, const char *receiver, const char *content) {
    if (msgSystem->count >= MAX_MESSAGES) {
        printf("Boîte de messagerie pleine !\n");
        return;
    }

    Message *msg = &msgSystem->messages[msgSystem->count++];
    msg->id = msgSystem->count;
    strncpy(msg->sender, sender, sizeof(msg->sender) - 1);
    strncpy(msg->receiver, receiver, sizeof(msg->receiver) - 1);
    strncpy(msg->content, content, sizeof(msg->content) - 1);
    getCurrentTime(msg->timestamp, sizeof(msg->timestamp));

    printf("Message envoye de %s à %s.\n", sender, receiver);
}

// Afficher les messages reçus par un utilisateur
void displayMessages(const MessageSystem *msgSystem, const char *user) {
    printf("Messages recus par %s :\n", user);
    for (int i = 0; i < msgSystem->count; i++) {
        if (strcmp(msgSystem->messages[i].receiver, user) == 0) {
            printf("[%s] %s -> %s: %s\n", msgSystem->messages[i].timestamp, 
                   msgSystem->messages[i].sender, msgSystem->messages[i].receiver,
                   msgSystem->messages[i].content);
        }
    }
}

// Afficher tous les messages (pour l'administrateur)
void displayAllMessages(const MessageSystem *msgSystem) {
    printf("Tous les messages :\n");
    for (int i = 0; i < msgSystem->count; i++) {
        printf("[%s] %s -> %s: %s\n", msgSystem->messages[i].timestamp, 
               msgSystem->messages[i].sender, msgSystem->messages[i].receiver,
               msgSystem->messages[i].content);
            }
}
