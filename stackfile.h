#ifndef __STACKfile_H__
#define __STACKfile_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include"listfile.h"
typedef struct stack{
    TList top;
}stack;
typedef stack* TStack;

typedef struct charNode{
    char data;
    struct charNode *next;
} charNode;

typedef struct{
    charNode *top;
} CharStack;


 TStack createstack();
 bool isempty(TStack stk);
 void push(TStack stk,TList node);
 TList pop(TStack stk);
 TList peek(TStack stk);
 TStack toStack(TListBD merged);
 void getInfWordStack(TStack stk, char *word);
 TStack sortWordStack(TStack syn);
 TQueue stackToQueue(TStack stk);
 TListBD StacktoList(TStack stk);
 TStack addWordStack(TStack stk, char *word, char *syne, char *anton);
 char *getSmallest(TStack stk);
 TStack syllableStack(TStack stk);
 TStack *pronunciationStack(TStack stk);
 void initStack(CharStack *stack);
 void pushc(CharStack *stack, char c);
 char popc(CharStack *stack);
 bool isEmpty(CharStack *stack);
 bool isPalindromeStack(char *word);
 void insertAtBottom(TStack stk,TList node);
 TStack StackRev(TStack stk);
 bool deleteWordStack(TStack stk,char *word);
 bool updateWordStack(TStack stk,char *word,char *syne,char *anton);
 





#endif