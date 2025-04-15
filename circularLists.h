#ifndef __CIRCULARLISTS_H__
#define __CIRCULARLISTS_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


typedef struct Clogentry
{
int id;
char timestamp[40];  //[ DD_MM_YYYY HH:MM:SS ]do not forget espace at the begening and at the end
int severity;
char message[256];
struct Clogentry *next;


}Clogentry;

typedef Clogentry* PClogentry;


typedef struct Logbuffer
{
    PClogentry oldest;
    PClogentry recent;
    int maxsize;
    int size;
}Logbuffer;
typedef Logbuffer *PLogbuffer ;


void putNULL(PClogentry*head);

void InsertLogEntry(PClogentry*head,int ID,int SEVERITY ,char MESSAGE[256],int where ); //0 mean at the start / -1 mean at the end /else dependes 

void deleteClogentrybyid(PClogentry*head,int ID);

void deleteClogentrybytimestamp(PClogentry *head,char time[40]);

void deleteClogentry(PClogentry *head,int where); //0 at the start /-1 mean at the end

void reverseClist(PClogentry *head);

int CountTotalCLogs(PClogentry head);

PClogentry SearchCLogEntrybyid(PClogentry head,int ID);

PClogentry SearchCLogEntrybykeyword(PClogentry head,char keyword[256]);

PClogentry SearchCLogEntrybytimestamp(PClogentry head,char time[40]);

void printClogentry(PClogentry head);

void split2(PClogentry head,PClogentry *head1);

bool issortedbyseveritylevel(PClogentry head);

PClogentry merge2byseveritylevel(PClogentry head1,PClogentry head2);

void SortCLogsbyseveritylevel(PClogentry *head);  //merge sort

bool issortedbydate(PClogentry head);

PClogentry merge2bydate(PClogentry head1,PClogentry head2);

void SortCLogsbydate(PClogentry *head); //merge sort


void createlogbuffer(PLogbuffer *buffer,int max);

void insertlogbuffer(PLogbuffer buffer,int ID,int SEVERITY ,char MESSAGE[256]);

void deletelogbuffer(PLogbuffer buffer);

bool DetectCyclesintheList(PClogentry head);//using Floyd’s Algorithm


#endif
