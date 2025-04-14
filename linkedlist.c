#include"linkedlist.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include<string.h>

void putNULL(Plogentry*head){
    *head=NULL;

}


void InsertLogEntry(Plogentry*head,int ID,int SEVERITY ,char MESSAGE[256],int where ) //0 mean at the start / -1 mean at the end /else dependes 
{
    time_t t=time(NULL);
    struct tm date=*localtime(&t);
if(NULL==*head){
    *head=malloc(sizeof(logentry));
    (*head)->id=ID;
    (*head)->severity=SEVERITY;
    strcpy((*head)->message,MESSAGE);
    snprintf((*head)->timestamp,sizeof((*head)->timestamp)," %02d_%02d_%d %02d:%02d:%02d ",date.tm_mday,date.tm_mon+1,date.tm_year+1900,date.tm_hour,date.tm_min,date.tm_sec);
(*head)->next=NULL;
 return;
}
if(0==where ||where<-1 ){
    Plogentry temp=*head;
    *head=malloc(sizeof(logentry));
    (*head)->id=ID;
    (*head)->severity=SEVERITY;
    strcpy((*head)->message,MESSAGE);
snprintf((*head)->timestamp,sizeof((*head)->timestamp)," %02d_%02d_%d %02d:%02d:%02d ",date.tm_mday,date.tm_mon+1,date.tm_year+1900,date.tm_hour,date.tm_min,date.tm_sec);
(*head)->next=temp;
 return;

}
if(-1==where){
    Plogentry temp=*head,temp2;
    while(NULL!=temp->next){
        temp=temp->next;
    }
        temp2=malloc(sizeof(logentry));
    temp2->id=ID;
    temp2->severity=SEVERITY;
    strcpy(temp2->message,MESSAGE);
snprintf(temp2->timestamp,sizeof(temp2->timestamp)," %02d_%02d_%d %02d:%02d:%02d ",date.tm_mday,date.tm_mon+1,date.tm_year+1900,date.tm_hour,date.tm_min,date.tm_sec);
temp->next=temp2;
temp2->next=NULL;
 return;
}
if(-1!=where && 0!=where){
    Plogentry temp=*head,temp2,temp3=temp,save=*head; // temp curent temp2 new temp3 prvious 
    int count=0;
    while(save!=temp->next&&count!=where){
        temp3=temp;
        temp=temp->next;
        count++;
    }
    
    
    
        temp2=malloc(sizeof(logentry));
    temp2->id=ID;
    temp2->severity=SEVERITY;
    strcpy(temp2->message,MESSAGE);
snprintf(temp2->timestamp,sizeof(temp2->timestamp)," %02d_%02d_%d %02d:%02d:%02d ",date.tm_mday,date.tm_mon+1,date.tm_year+1900,date.tm_hour,date.tm_min,date.tm_sec);
if(temp->next==NULL&&count!=where){
    temp->next=temp2;
    temp2->next=NULL;
}
else{
temp3->next=temp2;
temp2->next=temp;
}
return;
}

}

int CountTotalLogs(Plogentry head){ 
    int count=0;
 while(NULL!=head){
    count++;
    head=head->next;
 }
 return count;
} 
void reverse (Plogentry* head){
    Plogentry temp1 ,temp2,temp;
    temp=(*head)->next;
    temp2=*head;
    while(temp!=NULL){
       temp1=temp;
       temp=temp->next;
       temp1->next=(*head);
       (*head)=temp1;
    }
    temp2->next=NULL;
    
}

Plogentry SearchLogEntrybyid(Plogentry head,int ID){
    while(head!=NULL){
        if(head->id==ID)
        return head;
        head=head->next;
    }
    return head;
}


Plogentry SearchLogEntrybykeyword(Plogentry head,char WORD[256]){
    while(head!=NULL){
        if(strstr(head->message,WORD)!=NULL)
        return head;
        head=head->next;
    }
    return head;
}

Plogentry SearchLogEntrybytimestamp(Plogentry head,char time[40]){
     while(head!=NULL){
        if(strcmp(head->timestamp,time)==0)
        return head;
        head=head->next;
    }
    return head;
}

void  DeleteLogEntry(Plogentry *head,int where ) //0 at the start -1 at the end else delete nothing
{

if(*head==NULL||(0!=where&&-1!=where))
return;
if((*head)->next==NULL){
free(*head);
return;
}
if(0==where){
    Plogentry deleted=*head;
    (*head)=(*head)->next;
    free(deleted);
    return ;
}
if(-1==where){
    Plogentry deleted=(*head)->next,save=*head;
    while(deleted->next!=NULL){
        save=(save)->next;
        deleted=deleted->next;
    }
    free(deleted);
    (save)->next=NULL;
return;
}
}


void DeleteLogEntrybyid(Plogentry *head,int ID){
    if(*head==NULL)
    return;
    if((*head)->id==ID){
        Plogentry deleted=*head;
        *head=(*head)->next;
        free(deleted);
        return;
    }
    else{
        Plogentry save=*head,deleted=(*head)->next;
        while(deleted!=NULL){
            if(deleted->id==ID){
                save->next=deleted->next;
                free(deleted);
                return;
            }
            save=deleted;
            deleted=deleted->next;
        }
        return;
    }
}


void DeleteLogEntrybytimestamp(Plogentry *head ,char time[40]){
        if(*head==NULL)
    return;
    if(strcmp((*head)->timestamp,time)==0){
                Plogentry deleted=*head;
        *head=(*head)->next;
        free(deleted);
        return;
    }
    else{
        Plogentry save=*head,deleted=(*head)->next;
         while(deleted!=NULL){
            if(strcmp(deleted->timestamp,time)==0){
                 save->next=deleted->next;
                free(deleted);
                return; 
            }
            save=deleted;
            deleted=deleted->next;
         }
         return;
    }
}


bool issortedbyseveritylevel(Plogentry head ){
    int temp;
    if(NULL==head)
    return true;
    temp=head->severity;
    while(NULL!=head->next){
        head=head->next;
        if(temp>head->severity)
        return false;
        temp=head->severity;
    }
    return true;
}


Plogentry merge2byseveritylevel(Plogentry head1,Plogentry head2){
    if(!issortedbyseveritylevel(head1) || !issortedbyseveritylevel(head2)){
        printf("there is mistake");
        exit(EXIT_FAILURE);
    }
    if(head1==NULL){
        return head2;
    }
    if(head2==NULL){
        return head1;
    }
    Plogentry head3,temp;
    if(head1->severity<head2->severity){
        head3=head1;
        head1=head1->next;
    }else{
        head3=head2;
        head2=head2->next;
    }
    temp=head3;
    Plogentry save=NULL;
    while(NULL!=head1 && NULL!=head2){
        if(head1->severity<head2->severity){
            save=head1;
            head1=head1->next;
            temp->next=save;
        }else{
            save=head2;
            head2=head2->next;
            temp->next=save;
        }
        temp=temp->next;

    }
    if(NULL==head1){
        temp->next=head2;
        return head3;
    }
    if(NULL==head2){
        temp->next=head1;
        return head3;
    }
    return head3;
}


void split2(Plogentry head,Plogentry *head1){
    *head1=NULL;
    int index=CountTotalLogs( head);
    if(0==index){
        return;
    }
    Plogentry temp=head;
    for(int i=1;i<index/2;i++)
    temp=temp->next;
    *head1=temp->next;
    temp->next=NULL;


}


void SortLogsbyseveritylevel(Plogentry *head) {  //merge sort
        if(issortedbyseveritylevel(*head))
    return;
    Plogentry half=NULL;
    
    split2(*head,&half);
    
    while(!issortedbyseveritylevel(*head) || !issortedbyseveritylevel(half)){
        
        SortLogsbyseveritylevel(head);
        SortLogsbyseveritylevel(&half);
        
    }
    *head=merge2byseveritylevel(*head,half);
}


bool issortedbydate(Plogentry head ){
    char current[40],next[40];
    if(NULL==head)
    return true;
    while(NULL!=head->next){
        snprintf(current, sizeof(current), "'%c''%c''%c''%c'_'%c''%c'_'%c''%c'", 
         head->timestamp[7], head->timestamp[8], head->timestamp[9], 
         head->timestamp[10], head->timestamp[4], head->timestamp[5], 
         head->timestamp[1], head->timestamp[2]);
        head=head->next;
                snprintf(next, sizeof(next), "'%c''%c''%c''%c'_'%c''%c'_'%c''%c'", 
         head->timestamp[7], head->timestamp[8], head->timestamp[9], 
         head->timestamp[10], head->timestamp[4], head->timestamp[5], 
         head->timestamp[1], head->timestamp[2]);
        if(strcmp(current,next)!=0)
        return false;
        
    }
    return true;
}


Plogentry merge2bydate(Plogentry head1,Plogentry head2){
    if(!issortedbydate(head1) || !issortedbydate(head2)){
        printf("there is mistake");
        exit(EXIT_FAILURE);
    }
    char first[40],second[40];
    snprintf(first, sizeof(first), "'%c''%c''%c''%c'_'%c''%c'_'%c''%c'", 
         head1->timestamp[7], head1->timestamp[8], head1->timestamp[9], 
         head1->timestamp[10], head1->timestamp[4], head1->timestamp[5], 
         head1->timestamp[1], head1->timestamp[2]);

         snprintf(second, sizeof(second), "'%c''%c''%c''%c'_'%c''%c'_'%c''%c'", 
         head2->timestamp[7], head2->timestamp[8], head2->timestamp[9], 
         head2->timestamp[10], head2->timestamp[4], head2->timestamp[5], 
         head2->timestamp[1], head2->timestamp[2]);
    if(head1==NULL){
        return head2;
    }
    if(head2==NULL){
        return head1;
    }
    Plogentry head3,temp;
    if(strcmp(first,second)<0){
        head3=head1;
        head1=head1->next;
    }else{
        head3=head2;
        head2=head2->next;
    }
    temp=head3;
    Plogentry save=NULL;
    while(NULL!=head1 && NULL!=head2){
         snprintf(first, sizeof(first), "'%c''%c''%c''%c'_'%c''%c'_'%c''%c'", 
         head1->timestamp[7], head1->timestamp[8], head1->timestamp[9], 
         head1->timestamp[10], head1->timestamp[4], head1->timestamp[5], 
         head1->timestamp[1], head1->timestamp[2]);

         snprintf(second, sizeof(second), "'%c''%c''%c''%c'_'%c''%c'_'%c''%c'", 
         head2->timestamp[7], head2->timestamp[8], head2->timestamp[9], 
         head2->timestamp[10], head2->timestamp[4], head2->timestamp[5], 
         head2->timestamp[1], head2->timestamp[2]);

        if(strcmp(first,second)<0){
            save=head1;
            head1=head1->next;
            temp->next=save;
        }else{
            save=head2;
            head2=head2->next;
            temp->next=save;
        }
        temp=temp->next;

    }
    if(NULL==head1){
        temp->next=head2;
       
        return head3;
    }
    if(NULL==head2){
        temp->next=head1;
        
        return head3;
    }
    
    return head3;
}


void SortLogsbydate(Plogentry *head) //merge sort
{
        if(issortedbydate(*head))
    return;
    Plogentry half=NULL;
    
    split2(*head,&half);
    
    while(!issortedbydate(*head) || !issortedbydate(half)){
        
        SortLogsbydate(head);
        SortLogsbydate(&half);
        
    }
    *head=merge2bydate(*head,half);
}
void printlogentry(Plogentry head){
    
    if(head==NULL){
        printf("THE LOG LIST IS EMPTY ");
        return;
    }
    

    
    while(NULL!=head){
        printf("[ID: %02d] [%s] [severity : %02d] %s\n",
        head->id,
        head->timestamp,head->severity,
        head->message );
        
        head=head->next;
    }
}



int main(){
Plogentry logsami;
putNULL(&logsami);
char nice[256]="sami nice";
int i=0,j=0;
for(i;i<5;i++){
    InsertLogEntry(&logsami,i,i+1,nice,1);
}
printf("%d\n",CountTotalLogs(logsami));
Plogentry sami=logsami;
char time[40]=" 26_03_2020 05:52:57 ";
char time2[40]=" 28_03_2024 05:52:57 ";
strcpy(logsami->next->timestamp,time);
for(j;j<5;j++){
    printf("user %d log in at %s have %d and put %s\n",logsami->id,logsami->timestamp,logsami->severity,logsami->message);
    logsami=logsami->next;
}
logsami=sami;
strcpy(logsami->timestamp,time2);


SortLogsbydate(&logsami);

printf("aftrer :\n");
while(logsami!=NULL){
        printf("user %d log in at %s have %d and put %s\n",logsami->id,logsami->timestamp,logsami->severity,logsami->message);
    logsami=logsami->next;
}
logsami=sami;
printf("nice\n");
logsami->timestamp[7];
printf(" %c%c%c%c_%c%c_%c%c ",logsami->timestamp[7],logsami->timestamp[8],logsami->timestamp[9],logsami->timestamp[10],logsami->timestamp[4],logsami->timestamp[5],logsami->timestamp[1],logsami->timestamp[2]);

}
