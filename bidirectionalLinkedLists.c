#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include<string.h>



typedef struct logentry{
	struct logentry *prv;
	int id,severity;
	char message[50],date[20];
	struct logentry *next;
	}logentry;
	
	
void InsertLogEntry(logentry **head,logentry **tail ,int ID,int SEVERITY ,char MESSAGE[256],int where ){
logentry 	*temp,*temp1=*head,*temp2=*head;
int count=0;
time_t t=time(NULL);
    struct tm datetime=*localtime(&t);
    temp=malloc(sizeof(logentry));
	temp->id=ID;
	temp->severity=SEVERITY;
	strcpy(temp->message,MESSAGE);
	strftime(temp->date,sizeof(temp->date),"%Y-%m-%d %H:%M",&datetime);
	if(*head==NULL){
		*head=temp;
		temp->next=NULL;
		temp->prv=NULL;
		*tail=temp;
		return;
	}
	if(where==0){
	temp->prv=NULL;
	temp->next=*head;
	*head=temp;}
	if(where==-1){
	(*tail)->next=temp;
	temp->prv=*tail;
	temp->next=NULL;
	*tail=temp;}
	if(where!=-1 && where!=0){
	 while(temp1->next!=NULL && count!=where){
	 	temp2=temp1;
	 	temp1=temp1->next;
		 count++;}
		 if(count==where){
		 	temp2->next=temp;
		 	temp->next=temp1;
		 	temp->prv=temp2;
		 	temp1->prv=temp;
		 }
		 else{
	    (*tail)->next=temp;
	    temp->prv=*tail;
      	temp->next=NULL;
	    *tail=temp;}}}
void Delete_Log_Entry_ID(logentry **head,logentry **tail,int ID){//  if the id dont exist delete the last one  
	logentry *temp=*head,*temp1=*tail,*temp0;
	while(temp->id!=ID && temp1->id!=ID && temp->prv!=temp1){
		temp=temp->next;
		temp1=temp1->prv;}
		if(temp->id==ID){
			if(temp==*head){
				temp0=temp->next;
				temp0->prv=NULL;
				*head=temp0;
				free(temp);}
			else{
			temp0=temp->prv;
			temp1=temp->next;
			temp0->next=temp1;
			temp1->prv=temp0;
			free(temp);
			return;}}
			if(temp1->id==ID){
				if(temp1==*tail){
					temp0=temp1->prv;
				    temp0->next=NULL;
				    *tail=temp0;
				free(temp1);}
			else{
			temp0=temp1->prv;
			temp=temp1->next;
			temp0->next=temp;
			temp->prv=temp0;
			free(temp1);}}
			if(temp1==temp->prv){
				temp0=(*tail)->prv;
				temp0->next=NULL;
				free(*tail);
				*tail=temp0;}}
void sort_log_by_date(logentry **head,logentry **tail){
	logentry *temp=*head,*mid=NULL,*temp2=NULL,*temp3=NULL;
	int check=0;
	char date[20];
	while(check!=1500){
		strcpy(date,temp->date);
		while(temp->next!=NULL){
			mid=temp->next;
		if(strcmp(date,mid->date)<=0){
		temp=temp->next;
		mid=temp->next;
		strcpy(date,temp->date);
		}
		else{
			if(temp->prv==NULL){
				temp2=mid->next;
				*head=mid;
				mid->prv=NULL;
				mid->next=temp;
				temp->prv=mid;
				temp->next=temp2;
				temp2->prv=temp;
			}
			else{
				if(mid->next==NULL){
					temp2=temp->prv;
					temp2->next=mid;
					mid->prv=temp2;
					mid->next=temp;
					temp->prv=mid;
					temp->next=NULL;
					*tail=temp;
					
				}
				else{
		
			temp3=temp->prv;
			temp2=mid->next;
			temp->next=temp2;
			temp->prv=mid;
			mid->next=temp;
			temp2->prv=temp;
			temp3->next=mid;
			}}}}
			temp=*head;
			check++;}}































logentry* createLogEntry(int id, int severity, const char *message, const char *date) {
    logentry *newLog = (logentry*)malloc(sizeof(logentry));
    if (newLog == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newLog->id = id;
    newLog->severity = severity;
    strncpy(newLog->message, message, sizeof(newLog->message) - 1);
    newLog->message[sizeof(newLog->message) - 1] = '\0';  // Ensure null termination
    strncpy(newLog->date, date, sizeof(newLog->date) - 1);
    newLog->date[sizeof(newLog->date) - 1] = '\0';  // Ensure null termination
    newLog->prv = NULL;
    newLog->next = NULL;
    return newLog;
}













void PrintLogEntries(logentry *head) {
    logentry *temp =head;
    while (temp != NULL) {
        printf("ID: %d, Severity: %d, Message: %s, Date: %s\n", temp->id, temp->severity, temp->message, temp->date);
        temp=temp->next;}}

int main() {
	logentry *head = NULL, *tail = NULL;

    // Create 5 log entries with different timestamps
    logentry *log1 = createLogEntry(1, 3, "System started", "2099-09-30 09:00:15");
    logentry *log2 = createLogEntry(2, 2, "Warning: High CPU usage", "2025-10-29 09:05:42");
    logentry *log3 = createLogEntry(3, 1, "Error: Disk space low", "2054-01-30 08:30:30");
    logentry *log4 = createLogEntry(4, 4, "Security Alert: Unauthorized login", "2029-01-18 08:31:10");
    logentry *log5 = createLogEntry(5, 2, "System shutdown initiated", "2101-01-29 09:50:05");

    // Link nodes in a doubly linked list
    head = log1;
    log1->prv=NULL;
    log1->next = log2;
    log2->prv = log1;
    
    log2->next = log3;
    log3->prv = log2;
    
    log3->next = log4;
    log4->prv = log3;
    
    log4->next = log5;
    log5->prv = log4;
    log5->next=NULL;
    tail = log5;  

   
    printf("Log Entries:\n");
    sort_log_by_date(&head,&tail);
    PrintLogEntries(head);

    
    

    return 0;
}
