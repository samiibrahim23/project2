#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct logentry
{
int id;
char timestamp[40];  //[ DD_MM_YYYY HH:MM:SS ]do not forget espace at the begening and at the end
int severity;
char message[256];
struct logentry *next;


}logentry;
typedef logentry *Plogentry;
void putNULL(Plogentry*head);

void InsertLogEntry(Plogentry*head,int ID,int SEVERITY ,char MESSAGE[256],int where ) ;
int CountTotalLogs(Plogentry head);
void reverse (Plogentry* head);
Plogentry SearchLogEntrybyid(Plogentry head,int ID);
Plogentry SearchLogEntrybykeyword(Plogentry head,char WORD[256]);
Plogentry SearchLogEntrybytimestamp(Plogentry head,char time[40]);

void  DeleteLogEntry(Plogentry *head,int where ); //0 at the start -1 at the end else delete nothing
void DeleteLogEntrybytimestamp(Plogentry *head ,char time[40]);
void DeleteLogEntrybyid(Plogentry *head,int ID);
bool issortedbyseveritylevel(Plogentry head );
Plogentry merge2byseveritylevel(Plogentry head1,Plogentry head2);
void split2(Plogentry head,Plogentry *head1);
void SortLogsbyseveritylevel(Plogentry *head); //merge sort 
bool issortedbydate(Plogentry head );
Plogentry merge2bydate(Plogentry head1,Plogentry head2);
void SortLogsbydate(Plogentry *head); //merge sort

void printlogentry(Plogentry head);
















#endif