#ifndef __LISTFILE_H__
#define __LISTFILE_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
typedef struct node {
    char word[50];
    char synonym[50];
    char antonym[50];
    int numChars[3];
    int numVowels[3];
    struct node* next;
} node;
 typedef node *TList ;

 typedef struct nodebd{
    char word[50];
    char synonym[50];
    char antonym[50];
    int numChars[3];
    int numVowels[3];
    struct nodebd* next; 
    struct nodebd* prev; 

}nodebd;
typedef nodebd* TListBD;
typedef struct queue{
    TList front;
    TList rear;
}queue;
typedef queue *TQueue ;

int countChars(const char *word);
int countVowels(const char *word);
 TList createNode(char *word,char *synonym,char*antonym);
 TList getSynWords(FILE *f); 
 TList getAntoWords(FILE  *f);
 void getInfWord(TList syn, TList ant, char *word);
 void getInfWord2(TList syn, TList ant, char *inf);
 bool issortedbynumCHRAS(TList head  );
 TList merge2bychar(TList head1,TList head2);
 int count(TList head);
 void split2(TList head,TList *head1);
 void sortWord2(TList *syn);
 bool issortedbynumvowls(TList head  );
 TList merge2byvowls(TList head1,TList head2);
 void sortWord3(TList *syn);
 TList sortWord(TList syn);
 TList searchword(char *word,TList list);
 void addtolist(TList *head,char *word,char *synonym,char*antonym);
 void deleteWord(FILE *file,char *file_name,TList *syn,TList *ant ,char *word);
 void updateWord(FILE *f , TList *syn, TList *ant, char *word, char *syne, char *anton);
 TList countWord(TList syn, char *prt);
 void reverseString(char* str);
 TList palindromWord(TList syn);
 void addWord(FILE *f,TList *syn, TList *ant, char *word, char *syne, char *anton);
 float matchRate(char *word1, char *word2);
 TList copyNode(TList src);
 TListBD copyNodetobd(TList src);

 TList copybdtoNode(TListBD src);
 TList similarWord(TList syn, char* word,  float rate);
 TListBD copyToBDList(TList head);
 TListBD merge(TList syn, TList ant);
 TList merge2(TList syn, TList ant);
 void enqueuenode(TQueue  q,TList syn);
 int isVowel(char c);
 int countSyllables(const char *word);
 TQueue syllable(TList syn);
 int containsDiphthong(const char *word);
 int isLongVowel(const char *word);
 TQueue *prounounciation(TList syn);
 TQueue toQueue(TListBD merged);
 





#endif