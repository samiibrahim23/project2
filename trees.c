#include"trees.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include<string.h>

void timestampcmphelp(char* origin,char* result) {
    snprintf(result, sizeof(result), "'%c''%c''%c''%c'_'%c''%c'_'%c''%c' '%c''%c':'%c''%c':'%c''%c'", 
         origin[7], origin[8], origin[9], 
         origin[10], origin[4], origin[5], 
         origin[1], origin[2],origin[12],origin[13],origin[15],
         origin[16],origin[18],origin[19]);
}




 tree InsertLogintoBST(tree root,Plogentry node){
    if(root==NULL){
        root= (tree) malloc(sizeof(TREE));
        root->id=node->id;
        root->severity=node->severity;
        root->leftchild=NULL;
        root->rightchild=NULL;
        strcpy(root->timestamp,node->timestamp);
        strcpy(root->message,node->message);
        return root;
    }
    char newnode[40],current[40];
    timestampcmphelp(root->timestamp,current);
        timestampcmphelp(node->timestamp,newnode);
               int cmp=strcmp(current,newnode);
               if(cmp==0)
               return;
        if(cmp < 0)
       root->rightchild = InsertLogintoBST( root->rightchild, node);
        else{
         root->leftchild = InsertLogintoBST( root->leftchild, node);
        }
        return root;

 }
 tree Findnextinorder(tree root) {  //by findinf the min of thr right
    while (root&&root->leftchild!=NULL)
        root=root->leftchild;
    return root;
}
tree DeleteLogFromBST(tree root, char* timestampDeleted) 
{
    if (root == NULL)
        return NULL;

    char roott[40],target[40];
    timestampcmphelp(root->timestamp,roott);
    timestampcmphelp(timestampDeleted,target);
    int cmp = strcmp(target,roott);
    if(cmp<0) {
        root->leftchild=DeleteLogFromBST(root->leftchild,timestampDeleted);
    } else if(cmp>0) {
        root->rightchild=DeleteLogFromBST(root->rightchild,timestampDeleted);
    } else {
        if (root->leftchild==NULL&&root->rightchild==NULL){
            free(root);
            return NULL;
        } else if(root->leftchild==NULL){
            tree temp=root->rightchild;
            free(root);
            return temp;
        } else if (root->rightchild==NULL) {
            tree temp = root->leftchild;
            free(root);
            return temp;
        } else {
            tree minNode = Findnextinorder(root->rightchild);
            root->id=minNode->id;
            strcpy(root->timestamp, minNode->timestamp);
            root->severity = minNode->severity;
            strcpy(root->message,minNode->message);
            root->rightchild=DeleteLogFromBST(root->rightchild,minNode->timestamp);
        }
    }
    return root;
}
tree SearchLogInBST(tree root,char* timestampSearched){
    if (root==NULL)
        return NULL;

    char rootTime[40], searchTime[40];
    timestampcmphelp(root->timestamp,rootTime);
    timestampcmphelp(timestampSearched,searchTime);

    int cmp = strcmp(searchTime,rootTime);

    if (cmp==0)
        return root;
     if (cmp<0)
        return SearchLogInBST(root->leftchild,timestampSearched);
    else
        return SearchLogInBST(root->rightchild,timestampSearched);
}

void inorder(tree root){
    if(root!=NULL){
        inorder(root->leftchild);
        printf("[ID: %02d] [%s] [severity : %02d] %s\n",
        root->id,
        root->timestamp,root->severity,
        root->message );

        inorder(root->rightchild);
    }
}

void preorder(tree root){
    if(root!=NULL){
        printf("[ID: %02d] [%s] [severity : %02d] %s\n",
        root->id,
        root->timestamp,root->severity,
        root->message );
        preorder(root->leftchild);
        preorder(root->rightchild);
    }
}
void postorder(tree root){
    if(root!=NULL){
        postorder(root->leftchild);
        postorder(root->rightchild);
        printf("[ID: %02d] [%s] [severity : %02d] %s\n",
        root->id,
        root->timestamp,root->severity,
        root->message );
    }
}
tree ConvertListToBST(Plogentry head) {
    tree root=NULL;
    while (head!=NULL) {
        root=InsertLogintoBST(root, head);
        head=head->next;
    }
    return root;
}

