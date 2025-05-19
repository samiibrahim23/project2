#ifndef __TREES_H__
#define __TRESS_H__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include"linkedlist.h"



typedef struct TREE{
    int id;
    char timestamp[40];  //[ DD_MM_YYYY HH:MM:SS ]do not forget espace at the begening and at the end
    int severity;
   char message[256];
   struct TREE* leftchild;
   struct TREE* rightchild;

}TREE;
typedef TREE* tree;


void timestampcmphelp(char* origin,char* result);
tree InsertLogintoBST(tree root,Plogentry node);
tree Findnextinorder(tree root);
tree DeleteLogFromBST(tree root, char* timestampDeleted);
tree SearchLogInBST(tree root,char* timestampSearched);
void inorder(tree root);
void preorder(tree root);
void postorder(tree root);
tree ConvertListToBST(Plogentry head);







#endif