#include"stacks.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include<string.h>


void creatstack(stack *s){
    *s=malloc(sizeof(STACK));
    (*s)->top=NULL;

}

bool isemptystack(stack s){
    if(s==NULL ||s->top==NULL)
    return true;
    return false;
}
void PushNewLogEntry(stack s,int ID,int SEVERITY,char MESSAGE[256]){
if(s==NULL){
    return;

}
Plogentry newone;
newone=malloc(sizeof(logentry));
InsertLogEntry(&newone,ID,SEVERITY,MESSAGE,0);
newone->next=s->top;
s->top=newone;


}
void Pushlogentry(stack s,Plogentry log){
    if(s==NULL){
    return;

}
log->next=NULL;
log->next=s->top;
s->top=log;
}

Plogentry poplogentry(stack s){
Plogentry temp;
if(isemptystack(s)){
    temp=malloc(sizeof(logentry));  ///default return
    temp->id=-1;
    temp->message[0]='\0';
    temp->timestamp[0]='\0';
    temp->severity=-1;
    temp->next=NULL;
    return temp;

}
temp=s->top;
s->top=s->top->next;
temp->next=NULL;
return temp; 
}
logentry peeklogentry(stack s){
    Plogentry temp;
if(isemptystack(s)){
    temp=malloc(sizeof(logentry));
    temp->id=-1;
    temp->message[0]='\0';
    temp->timestamp[0]='\0';
    temp->severity=-1;
    temp->next=NULL;
    return *temp;

}
logentry temp1;
temp1=*(s->top);
temp1.next=NULL;
return temp1;

}


void InsertlogentryAtBottom(stack s, Plogentry log) {
    if(s==NULL)
    return;
   if(isemptystack(s)){
    Pushlogentry(s,log);
    return;
   }
   Plogentry temp=poplogentry(s);

   InsertlogentryAtBottom(s,log);
   Pushlogentry(s,temp);

}


void ReverseaStack(stack s){
    if(isemptystack(s))
    return;  
    Plogentry temp=poplogentry(s);
   
    ReverseaStack(s);
    InsertlogentryAtBottom(s,temp);

    

}


int main(){
    stack R=NULL;char nice[256]="nice";
    creatstack(&R);
int sami;
    for(int i=0;i<5;i++)
    PushNewLogEntry(R,i,i,nice);

    
    printlogentry(R->top);
    printf("wow\n");

    ReverseaStack(R);
    printf("wow\n");
    printlogentry(R->top);
    

}