#ifndef BIDIRECTIONALLINKEDLISTS_H
#define BIDIRECTIONALLINKEDLISTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// Structure de log
typedef struct logentry {
    struct logentry *prv;
    int id, severity;
    char message[50], date[20];
    struct logentry *next;
} logentry;

// Prototypes des fonctions
void InsertLogEntry(logentry **head, logentry **tail, int ID, int SEVERITY, char MESSAGE[256], int where);
void Delete_Log_Entry_ID(logentry **head, logentry **tail, int ID);
void sort_log_by_date(logentry **head, logentry **tail);
logentry* createLogEntry(int id, int severity, const char *message, const char *date);
void PrintLogEntries(logentry *head);

#endif // BIDIRECTIONALLINKEDLISTS_H

