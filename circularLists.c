#include"circularLists.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include<string.h>

void putNULL(PClogentry*head){
    *head=NULL;

}

void InsertCLogEntry(PClogentry*head,int ID,int SEVERITY ,char MESSAGE[256],int where ) //0 mean at the start / -1 mean at the end /else dependes 
{
    time_t t=time(NULL);
    struct tm date=*localtime(&t);
if(NULL==*head){
    *head=malloc(sizeof(Clogentry));
    (*head)->id=ID;
    (*head)->severity=SEVERITY;
    strcpy((*head)->message,MESSAGE);
    snprintf((*head)->timestamp,sizeof((*head)->timestamp)," %02d_%02d_%d %02d:%02d:%02d ",date.tm_mday,date.tm_mon+1,date.tm_year+1900,date.tm_hour,date.tm_min,date.tm_sec);
(*head)->next=(*head);
 return;
}
if(0==where||where<-1 ){
    PClogentry temp=*head,tail=(*head);
    *head=malloc(sizeof(Clogentry));
    (*head)->id=ID;
    (*head)->severity=SEVERITY;
    strcpy((*head)->message,MESSAGE);
snprintf((*head)->timestamp,sizeof((*head)->timestamp)," %02d_%02d_%d %02d:%02d:%02d ",date.tm_mday,date.tm_mon+1,date.tm_year+1900,date.tm_hour,date.tm_min,date.tm_sec);
(*head)->next=temp;
while(tail->next!=temp)
tail=tail->next;
tail->next=(*head);
 return;

}
if(-1==where){
    PClogentry temp=*head,temp2,save=*head;
    while(save!=temp->next){
        temp=temp->next;
    }
        temp2=malloc(sizeof(Clogentry));
    temp2->id=ID;
    temp2->severity=SEVERITY;
    strcpy(temp2->message,MESSAGE);
snprintf(temp2->timestamp,sizeof(temp2->timestamp)," %02d_%02d_%d %02d:%02d:%02d ",date.tm_mday,date.tm_mon+1,date.tm_year+1900,date.tm_hour,date.tm_min,date.tm_sec);
temp->next=temp2;
temp2->next=*head;
 return;
}
if(-1!=where && 0!=where){
    PClogentry temp=*head,temp2,temp3=temp,save=*head; // temp curent temp2 new temp3 prvious 
    int count=0;
     while(count!=where){
        
        temp3=temp;
        temp=temp->next;
        count++;
       
    }
    
    
    
        temp2=malloc(sizeof(Clogentry));
    temp2->id=ID;
    temp2->severity=SEVERITY;
    strcpy(temp2->message,MESSAGE);
snprintf(temp2->timestamp,sizeof(temp2->timestamp)," %02d_%02d_%d %02d:%02d:%02d ",date.tm_mday,date.tm_mon+1,date.tm_year+1900,date.tm_hour,date.tm_min,date.tm_sec);


temp3->next=temp2;
temp2->next=temp;

return;
}

}


void deleteClogentrybyid(PClogentry*head,int ID){
        if(*head==NULL)
    return;
    if((*head)->id==ID){
        PClogentry deleted=*head,save=*head,temp=*head;
        *head=(*head)->next;
        if(*head==save){
        free(deleted);
        return;            
        }
        while(temp->next!=save){
            temp=temp->next;
        }
        temp->next=*head;
        free(deleted);
        return;
    }
    else{
        PClogentry save=*head,deleted=(*head)->next,stop=*head;
        while(deleted!=stop){
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



void deleteClogentrybytimestamp(PClogentry *head,char time[40]){
        if(*head==NULL)
    return;
    if(strcmp((*head)->timestamp,time)==0){
         PClogentry deleted=*head,save=*head,temp=*head;
        *head=(*head)->next;
        if(*head==save){
        free(deleted);
        return;            
        }
        while(temp->next!=save){
            temp=temp->next;
        }
        temp->next=*head;        
        free(deleted);
        return;
    }
    else{
        PClogentry save=*head,deleted=(*head)->next,stop=*head;
         while(deleted!=stop){
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


void deleteClogentry(PClogentry *head,int where) //0 at the start /-1 mean at the end
{
if(*head==NULL||(0!=where&&-1!=where))
return;
if((*head)->next==*head){
free(*head);
return;
}
if(0==where){
    PClogentry deleted=*head,stop=*head,temp=*head;
    (*head)=(*head)->next;
    while(temp->next!=stop)
    temp=temp->next;
    temp->next=*head;
    free(deleted);
    return ;
}
if(-1==where){
    PClogentry deleted=(*head)->next,save=*head;
    while(deleted->next!=*head){
        save=(save)->next;
        deleted=deleted->next;
    }
    free(deleted);
    (save)->next=*head;
return;
}



}


void reverseClist(PClogentry *head){
    PClogentry tail=*head,temp,save=*head;
    temp=(*head)->next;
    do{
        tail=(*head);
        *head=temp;
        temp=(*head)->next;
        (*head)->next=tail;
        
    }while((*head)!=save);
    *head=tail;
}


int CountTotalCLogs(PClogentry head){
    PClogentry save=head;
    int count=0;
    if(head!=NULL){
        count++;
        head=head->next;
    }
    while(head!=save){ 
        count++;
        head=head->next;
    }
    return count;


}


PClogentry SearchCLogEntrybyid(PClogentry head,int ID){
    PClogentry save=head;
    do{
        if(head->id==ID)
        return head;
        head=head->next;
    }while(head!=save);
    return NULL;
}


PClogentry SearchCLogEntrybykeyword(PClogentry head,char keyword[256]){
     PClogentry save=head;
     do{
        if(strstr(head->message,keyword)!=NULL)
        return head;
        head=head->next;
     }while(head!=save);
     return NULL;
}


PClogentry SearchCLogEntrybytimestamp(PClogentry head,char time[40]){
     PClogentry save=head;
     do{
        if(strcmp(head->timestamp,time)==0)
        return head;
        head=head->next;
     }while(head!=save);
     return NULL;
}


void printClogentry(PClogentry head){
    PClogentry save=head;
    if(head==NULL){
        printf("THE LOG LIST IS EMPTY ");
        return;
    }
    

    
    do{
        printf("[ID: %02d] [%s] [severity : %02d] %s\n",
        head->id,
        head->timestamp,head->severity,
        head->message );
        
        head=head->next;
    }while(save!=head);
}


void split2(PClogentry head,PClogentry *head1){
    *head1=NULL;PClogentry save=head;
    int index=CountTotalCLogs( head);
    if(0==index){
        return;
    }
    PClogentry temp=head;
    for(int i=1;i<index/2;i++)
    temp=temp->next;
    *head1=temp->next;
    temp->next=head;
    temp=*head1;
    while(temp->next!=save)
    temp=temp->next;
    temp->next=*head1;

}


bool issortedbyseveritylevel(PClogentry head){
    PClogentry save=head;
    do{
        if(head->severity>head->next->severity)
        return false;
        head=head->next;
    }while(save!=head->next);
    return true;

}


PClogentry merge2byseveritylevel(PClogentry head1,PClogentry head2){
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
    PClogentry head3,temp,save1=head1,save2=head2;
    bool take1=false,take2=false;
    if(head1->severity<head2->severity){
        head3=head1;
        head1=head1->next;
        take1=true;
    }else{
        head3=head2;
        head2=head2->next;
        take2=true;
    }
    temp=head3;
    PClogentry save=NULL;
    while((save1!=head1 || take1!=true ) && (save2!=head2 || take2!=true)) /*take1 and take2 because in the first time one of them should be save1 or save 2 
    and the condition becomes false */
    {
        
        if(head1->severity<head2->severity){
            save=head1;
            head1=head1->next;
            temp->next=save;
            take1=true;
        }else{
            save=head2;
            head2=head2->next;
            temp->next=save;
            take2=true;
        }
        temp=temp->next;

    }
    if(save1==head1&&take1==true){
        temp->next=head2;
        temp=temp->next;
        while(temp->next!=save2)
        temp=temp->next;
        temp->next=head3;        
        return head3;
    }
    if(save2==head2&&take2==true){
        temp->next=head1;
        temp=temp->next;
        while(temp->next!=save1)
        temp=temp->next;
        temp->next=head3;
        return head3;
    }
    return head3;
}


void SortCLogsbyseveritylevel(PClogentry *head)  //merge sort
{ 
        if(issortedbyseveritylevel(*head))
    return;
    PClogentry half=NULL;
    
    split2(*head,&half);
    
    
        
        SortCLogsbyseveritylevel(head);
        SortCLogsbyseveritylevel(&half);
        
    
    *head=merge2byseveritylevel(*head,half);
}

bool issortedbydate(PClogentry head){



        char current[40],next[40];
    if(NULL==head)
    return true;
    PClogentry save=head;
    while(save!=head->next){
        snprintf(current, sizeof(current), "'%c''%c''%c''%c'_'%c''%c'_'%c''%c'", 
         head->timestamp[7], head->timestamp[8], head->timestamp[9], 
         head->timestamp[10], head->timestamp[4], head->timestamp[5], 
         head->timestamp[1], head->timestamp[2]);
        head=head->next;
                snprintf(next, sizeof(next), "'%c''%c''%c''%c'_'%c''%c'_'%c''%c'", 
         head->timestamp[7], head->timestamp[8], head->timestamp[9], 
         head->timestamp[10], head->timestamp[4], head->timestamp[5], 
         head->timestamp[1], head->timestamp[2]);
        if(strcmp(current,next)>0)
        return false;
        
    }
    return true;
}
PClogentry merge2bydate(PClogentry head1,PClogentry head2){
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
    PClogentry head3,temp,save1=head1,save2=head2;
    bool take1=false,take2=false;
    if(strcmp(first,second)<0){
        head3=head1;
        head1=head1->next;
        take1=true;
    }else{
        head3=head2;
        head2=head2->next;
        take2=true;
    }
    temp=head3;
    PClogentry save=NULL;
    while((save1!=head1 || take1!=true ) && (save2!=head2 || take2!=true)){
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
            take1=true;
        }else{
            save=head2;
            head2=head2->next;
            temp->next=save;
            take2=true;
        }
        temp=temp->next;

    }
    if(save1==head1&&take1==true){
        temp->next=head2;
        temp=temp->next;
        while(temp->next!=save2)
        temp=temp->next;
        temp->next=head3;        
        return head3;
    }
    if(save2==head2&&take2==true){
        temp->next=head1;
        temp=temp->next;
        while(temp->next!=save1)
        temp=temp->next;
        temp->next=head3;
        return head3;
    }
    return head3;
}
void SortCLogsbydate(PClogentry *head) //merge sort
{
        if(issortedbydate(*head))
    return;
    PClogentry half=NULL;
    
    split2(*head,&half);
    
    
        
        SortCLogsbydate(head);
        SortCLogsbydate(&half);
        
    
    *head=merge2bydate(*head,half);
}

/////// logbuffer///////

void createlogbuffer(PLogbuffer *buffer,int max)
{
    *buffer=malloc(sizeof(Logbuffer));
    (*buffer)->oldest=NULL;
    (*buffer)->recent=NULL;
    (*buffer)->maxsize=max;
    (*buffer)->size=0;

}

void insertlogbuffer(PLogbuffer buffer,int ID,int SEVERITY ,char MESSAGE[256]){
   
    if(buffer->maxsize==0){
        return;
    }
    if(buffer->oldest==NULL){
      InsertCLogEntry(&(buffer->oldest),ID,SEVERITY,MESSAGE,0);
      
      buffer->recent=buffer->oldest;
      buffer->size++;
      return;

    }
    if(buffer->size<buffer->maxsize){
        InsertCLogEntry(&(buffer->oldest),ID,SEVERITY,MESSAGE,-1);

        buffer->recent=buffer->recent->next;
        buffer->size++;
        return ;

    }
    else{
     PClogentry temp=buffer->oldest;
     buffer->oldest=buffer->oldest->next;
     free(temp);
     buffer->recent->next=buffer->oldest;
     InsertCLogEntry(&(buffer->oldest),ID,SEVERITY,MESSAGE,-1);
     buffer->recent=buffer->recent->next;
     return;


    }



}
void deletelogbuffer(PLogbuffer buffer){
    if((buffer)->size>0){
    deleteClogentry(&((buffer)->oldest),0);
    
    (buffer)->size--;
    }
}


bool DetectCyclesintheList(PClogentry head)//using Floyd’s Algorithm
{
if(head==NULL||head->next==head)
return true;
PClogentry fast=head->next;

while(fast!=NULL && fast->next!=NULL)
{ // head act like slow
fast=fast->next->next;
head=head->next;
if(fast==head){
    return true;
}

}
return true;

}



int main(){

    PLogbuffer logsami=NULL;
    createlogbuffer(&logsami,5);
    char wow[256]="nice";
    for(int i=0;i<5;i++){
    insertlogbuffer(logsami,i,i,wow);
    

    }
    

    printClogentry(logsami->oldest);
    for(int i=7;i<10;i++){
    insertlogbuffer(logsami,i,i,wow);
    

    }
    
    printf(" after:\n");
    printClogentry(logsami->oldest);
printf("noice:\n");
    PClogentry sami=NULL;
        printf("noice:\n");

    deletelogbuffer(logsami);
    printClogentry(logsami->oldest);

    
       
}












