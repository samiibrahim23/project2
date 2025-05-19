#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include<string.h>



typedef struct logentry{
	int id,severity;
	char message[50],date[20];
	struct logentry *next;
	}logentry;

typedef struct node{
	int value;
struct	node *next;
}node;

node* reverse_lls(node *head){
	node *temp;
	if(head->next==NULL){
		return(head);
	}
	else{
		temp=reverse_lls((head)->next);
		(head)->next->next=head;
		(head)->next=NULL;
		return(temp);
	}
}
int fact(int val){
	if(val==1)
	return 1;
	else{
		return(val*fact(val-1));
	}
}
int max_id(node *head){
	int max;
	if(head->next==NULL)
	return(head->value);
	max=max_id(head->next);
	if (head->value > max)
    return head->value;
else
    return max;

}
int binary_serch(int arr[],int left, int right,int val){
	int mid;
	mid=(right+left)/2;
	if(left==right){
		if(arr[left]==val)
		return(left);
	     else
		return(-1);
	}
	if(arr[mid]==val)
	return(mid);
	if(arr[mid]>val)
	return(binary_serch(arr,left,mid-1,val));
	else
	return(binary_serch(arr,mid+1,right,val));
	
}
void infix_postfix(char string[]){
	
	while(string[i]!="\0"){
		switch(string[i])
		case("+"):return
	}	
}
