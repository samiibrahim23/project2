#ifndef __STACKS_H__
#define __STACKS_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include"linkedlist.h"


typedef struct STACK{
    Plogentry top;
    
}STACK;
typedef STACK* stack;
void creatstack(stack *s);
bool isemptystack(stack s);
void PushNewLogEntry(stack s,int ID,int SEVERITY,char MESSAGE[256]);
void Pushlogentry(stack s,Plogentry log);
logentry peeklogentry(stack s);
void InsertlogentryAtBottom(stack s, Plogentry log);
void ReverseaStack(stack s);


#endif