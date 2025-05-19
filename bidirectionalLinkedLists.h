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
logentry* serch_by_id(logentry *head,logentry *tail,int id){
	 
	 
	 while(tail->id!=id && head->id!=id) {
	 	if(tail==head | tail->next==head)
	 	return(NULL);
	 	tail=tail->prv;
	 	head=head->next;
	 }
	 if(tail->id==id)
	 return(tail);
	 else
	 return(head);
}
logentry* serch_by_date(logentry *head,logentry *tail,char date[25]){// write the date like this %Y-%m-%d %H:%M
      while(strcmp(date,head->date)!=0){
      	if(head==NULL)
      	return(NULL);
      	head=head->next;}
		  return(head);}
logentry* serch_by_keyword(logentry *head,logentry *tail,char keyword[25]){
	while(strstr(head->message,keyword)!=NULL){
		if(head==NULL)
		return(NULL);
		head=head->next;}
		return(head);
}
void sort_log_by_severity(logentry **head,logentry **tail){
	logentry *temp=*head,*mid=NULL,*temp2=NULL,*temp3=NULL;
	int check=1;
	char date[20];
	while(check!=0){
		check=0;
		temp=*head;
		while(temp->next!=NULL){
			mid=temp->next;
		if(temp->severity<=mid->severity){
		temp=temp->next;
		mid=temp->next;}
		else{
			check=1;
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
			temp=*head;}}
void sort_log_by_date(logentry **head,logentry **tail){
	logentry *temp=*head,*mid=NULL,*temp2=NULL,*temp3=NULL;
	int check=2;
	char date[20];
	while(check!=0){
		check=0;
		strcpy(date,temp->date);
		while(temp->next!=NULL){
			mid=temp->next;
		if(strcmp(date,mid->date)<=0){
		temp=temp->next;
		mid=temp->next;
		strcpy(date,temp->date);
		}
		else{
			check=1;
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
			temp=*head;}}
int CountTotalLogs(logentry *left,logentry *right){ 
    int count=1;
 while(left!=right){
    count++;
    left=left->next;
 }
 return count;
}

void reverse(logentry **head,logentry **tail){
  logentry *left,*temp=*head,*right,*temp2,*left1;
  while(temp2!=NULL){
  	if((*head)->prv==NULL){
  		(*head)->prv=(*head)->next;
	    (*head)->next=NULL;
		  right=(*head)->prv;
		  right=right->next;
		  temp=right;
        left=(*head)->prv;
        left1=*head;
		temp2=temp->next;}
	    else{

	  right->next=left;
	  left->prv=temp;
	  left->next=left1;
	  left1=left;
	  left=right;
	  right=temp2;
	  temp2=temp2->next;}}
	  left->prv=*tail;
	  left->next=left1;
	  (*tail)->next=left;
	  (*tail)->prv=NULL;
	  temp=*head;
	  *head=*tail;
	  *tail=temp;
}
void DeleteLogAtIndex(logentry **head, logentry **tail, int index) {
    if (*head == NULL) return;
    logentry *temp = *head;
    int count = 0;
    while (temp != NULL && count < index) {
        temp = temp->next;
      count++;
    }
    if (temp == NULL) return; 
    if (temp == *head) {
        *head = temp->next;
        if (*head != NULL) (*head)->prv = NULL;
        else *tail = NULL;
    }
    else if (temp == *tail) {
        *tail = temp->prv;
        (*tail)->next = NULL;
    }

    else {
        temp->prv->next = temp->next;
        temp->next->prv = temp->prv;
}
    free(temp);}
void MergeLogLists(logentry **head1, logentry **tail1, logentry *head2) {
    if (*head1 == NULL) {
        *head1 = head2;
        *tail1 = head2;
        while (*tail1 && (*tail1)->next != NULL)
            *tail1 = (*tail1)->next;
        return;
    }
    if (head2 == NULL) return; 
    (*tail1)->next = head2;
    head2->prv = *tail1;
    while (head2->next != NULL)
        head2 = head2->next;
    *tail1 = head2;
}































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
	logentry *head = NULL, *tail = NULL,*temp;
	int arr[5]={1,2,3,4,5};

    // Create 5 log entries with different timestamps
    logentry *log1 = createLogEntry(7, 3, "System started", "2099-09-30 09:00:15");
    logentry *log2 = createLogEntry(2, 20, "Warning: High CPU usage", "2025-10-29 09:05:42");
    logentry *log3 = createLogEntry(3, 1, "Error: Disk space low", "2020-01-30 08:30:30");
    logentry *log4 = createLogEntry(4, 4, "Security Alert: Unauthorized login", "2029-01-18 08:31:10");
    logentry *log5 = createLogEntry(5, -1, "System shutdown initiated", "2101-01-29 09:50:05");

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
  
      printf("%d",binary_serch(arr,0,4,5));
        PrintLogEntries(temp);
      
    

    
    

    return 0;
}
